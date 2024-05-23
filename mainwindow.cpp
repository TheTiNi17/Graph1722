#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(int argc, char *argv[], QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(this);   // Инициализируем графическую сцену
    scene->setItemIndexMethod(QGraphicsScene::NoIndex); // настраиваем индексацию элементов
    ui->graphicsView->resize(600,600);  // Устанавливаем размер graphicsView
    ui->graphicsView->setScene(scene);  // Устанавливаем графическую сцену в graphicsView
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);    // Настраиваем рендер
    ui->graphicsView->setCacheMode(QGraphicsView::CacheBackground); // Кэш фона
    ui->graphicsView->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    connect(scene,SIGNAL(changed(QList<QRectF>)),SLOT(update()));

    QRegExpValidator *validator1 = new QRegExpValidator(QRegExp("[0-9]+(,[0-9]+)*"));
    ui->WeightAddEdgeLine->setValidator(validator1);

    QRegExpValidator *validator2 = new QRegExpValidator(QRegExp("^[^\\s\\W]*\\.?[a-zA-Z]*$"));
    ui->FileNameLine->setValidator(validator2);

    if (argc > 1)
    {
        ui->FileNameLine->setText(argv[1]);
        on_LoadGraphButton_clicked();
    }
}

MainWindow::~MainWindow()
{
    for (QMap <QString ,MoveItem*>::iterator i = ObjectsContainer.begin(); i != ObjectsContainer.end(); i++)
    {
        delete i.value();
    }
    delete ui;
}

QVector<QString> MainWindow::StrToVector(QString a)
{
    QVector<QString> Arr;
    QString tmp = "";
    for (int i = 0; i < a.size(); i++)
    {
        if(a[i] != ',')
        {
            tmp += a[i];
        }
        else
        {
            Arr.push_back(tmp);
            tmp = "";
        }
    }
    if (tmp.size() != 0)
    {
        Arr.push_back(tmp);
    }
    return Arr;
}

int MainWindow::GetRandomNumberBetween(int a, int b)
{
    return (randomgenerator.bounded(b - a) + a);
}

void MainWindow::on_AddNodeButton_clicked()
{
    amount++;
    QString name =  ui->NameAddLine->text();
    QString fname = ui->DescriptionAddLine->text();

    auto it = ObjectsContainer.find(name);
    //если итератр не прошел весь массив
    if(it != ObjectsContainer.end())
    {
        QMessageBox::critical(this, "Ошибка", "Имя узела " + name + " занято");
        return;
    }
    //создание графического элемента
    MoveItem *item = new MoveItem(0, amount, name, fname);
    item->setPos(GetRandomNumberBetween(0, 500), GetRandomNumberBetween(0,500));
    //добавление элемента на сцену
    scene->addItem(item);
    ObjectsContainer[name] = item;
    item->PairContainer = &PairContainer;
}

//удаляем один узел
void MainWindow::on_DelNodeButton_clicked()
{
    QString del_st = ui->NameDelLine->text();
    QVector<QString> delp = StrToVector(del_st);
    //ищем все ребра связанные с ним и удаляем их
    for(int k = 0; k < delp.size(); k++)
    {
        auto it = ObjectsContainer.find(delp[k]);
        if (it != ObjectsContainer.end()){
            for(auto i = PairContainer.begin(); i != PairContainer.end(); i++)
            {
                for(auto j = i->begin(); j != i->end(); j++)
                {
                    if(j->first == ObjectsContainer[delp[k]]){
                        i->erase(j);
                    }
                }
            }
            PairContainer[ObjectsContainer[delp[k]]].clear();
            auto ite = PairContainer.find(ObjectsContainer[delp[k]]);
            PairContainer.erase(ite);
            delete ObjectsContainer[delp[k]]; // удаляем сам узел
            ObjectsContainer.erase(it);
        }
    }
}

// новое имя узла или изменить описание
void MainWindow::on_ChangeNodeButton_clicked()
{
    QString old = ui->OldNameChangeLine->text();//старое
    QString new_ = ui->NewNameChangeLine->text();//новое
    QString Description = ui->NewDescriptionChangeLine->text();
    if(new_.size() == 0){
        auto it = ObjectsContainer.find(old);
        if(it == ObjectsContainer.end()){//есть ли старое имя
            QMessageBox::critical(this, "Ошибка", "Узла с названием " + old + " нет");
            return;
        }
        ObjectsContainer[old]->Description = Description;
        QMessageBox::warning(this, " ", "Описание узла изменено");
        return;
    }
    auto it = ObjectsContainer.find(old);
    if(it == ObjectsContainer.end())
    {
        QMessageBox::critical(this, "Ошибка", "Узла с названием " + old + " нет");
        return;
    }
    if (old == new_){
        return;
    }
    it = ObjectsContainer.find(new_);
    if(it != ObjectsContainer.end()){//есть ли новое
        QMessageBox::critical(this, "Ошибка", "Узел с названием " + new_ + " уже существует");
        return;
    }
    //смена имени
    ObjectsContainer[old]->Name = new_;
    ObjectsContainer[new_] = ObjectsContainer[old];
    it = ObjectsContainer.find(old);
    ObjectsContainer.erase(it);
}

//(добавляем/изменяем вес)
void MainWindow::on_AddEdgeButton_clicked()
{
    QString first = ui->Name1AddEdgeLine->text();//первый узел
    QString second = ui->Name2AddEdgeLine->text();//второй узел
    QString len = ui->WeightAddEdgeLine->text();//вес
    if (len.size() == 0){//если вес не задается, он по умолчанию один
        len = "1";
    }
    for (int i = 0; i < len.size(); i++)
    {
        if( len[i] < '0' || len[i] > '9')
        {
            QMessageBox::critical(this, "Ошибка", "ВВедено не число в вес");
            return;
        }
    }
    int len_int = len.toInt(); // "123"->123 string to int
    auto it = ObjectsContainer.find(first);
    auto it1 = ObjectsContainer.find(second);
    if (it ==  ObjectsContainer.end() || it1 ==  ObjectsContainer.end()){ // Есть ли такие узлы
        QMessageBox::critical(this, "Ошибка", "Не найдены узлы");
        return;
    }
    //Проверка на сущ. ребра. Если есть то изменяем вес, если нет то добавляем
    for (auto iter = PairContainer[ObjectsContainer[first]].begin(); iter != PairContainer[ObjectsContainer[first]].end(); iter++){
        if (iter->first == ObjectsContainer[second]){
            iter->second = len_int;
            break;
        }
    }
    for (auto iter = PairContainer[ObjectsContainer[second]].begin(); iter != PairContainer[ObjectsContainer[second]].end(); iter++){
        if (iter->first == ObjectsContainer[first]){
            iter->second = len_int;
            return;
        }
    }
    PairContainer[ObjectsContainer[first]].append({ObjectsContainer[second], len_int});
    PairContainer[ObjectsContainer[second]].append({ObjectsContainer[first], len_int});

}

//удаление ребра
void MainWindow::on_DelEdgeButton_clicked()
{
    QString first = ui->Name1DelEdgeLine->text();
    QString second = ui->Name2DelEdgeLine->text();
    auto it = ObjectsContainer.find(first);
    auto it1 = ObjectsContainer.find(second);
    if (it ==  ObjectsContainer.end() || it1 ==  ObjectsContainer.end()){//проверка на сущ. узлов
        return;
    }
    bool f = false;
    // Удаление ребра, если нет его, то будет сообщение
    for (auto iter = PairContainer[ObjectsContainer[first]].begin(); iter != PairContainer[ObjectsContainer[first]].end(); iter++){
        if (iter->first == ObjectsContainer[second]){
            PairContainer[ObjectsContainer[first]].erase(iter);
            f = true;
            break;
        }
    }
    for (auto iter = PairContainer[ObjectsContainer[second]].begin(); iter != PairContainer[ObjectsContainer[second]].end(); iter++){
        if (iter->first == ObjectsContainer[first]){
            PairContainer[ObjectsContainer[second]].erase(iter);
            f = true;
            break;
        }
    }
    if(!f)
    {
        QMessageBox::critical(this, "Ошибка", "Данного ребра не существует");
    }
}

// удаляем все элементы
void MainWindow::on_DelGraphButton_clicked()
{
    for(auto iter = ObjectsContainer.begin(); ObjectsContainer.end()!= iter; iter++){
        delete *iter;
    }
    ObjectsContainer.clear();
    PairContainer.clear();
    amount = 0;
}

std::vector<std::string> SplitStr(std::string str)
{
    // Разделить строку на отдельные учасстки, в данном случае числа разделенные запятыми
    std::stringstream ss(str);
    std::string token;
    std::vector<std::string> arr;

    while (std::getline(ss, token, '.'))
    {
        arr.push_back((token));
    }
    return arr;
}

bool CheckFileName(QString filename)
{
    std::string name = filename.toStdString();
    if (name.length() < 5)
        return false;

    std::vector<std::string> parts = SplitStr(name);
    if (parts.size() > 2)
        return false;

    if ( (parts.at(1) == "txt") || (parts.at(1) == "json") || (parts.at(1) == "xml") )
    {
        return true;
    }
    else
    {
        return false;
    }
}

//сохранение
void MainWindow::on_SaveGraphButton_clicked()
{
    QString name = ui->FileNameLine->text();//имя файла
    if (!CheckFileName(name))
    {
        QMessageBox::critical(this, "Ошибка", "Неправильное имя файла!\nФайл должн оканчиватся на .txt .json .xml");
        return;
    }

    std::string name_s = name.toLocal8Bit().constData();
    std::ofstream fout;
    fout.open(name_s);
    if (fout.is_open() == false)
    {
        QMessageBox::critical(this, "Ошибка", "Не удается открыть файл");
        return;
    }
    fout << ObjectsContainer.size() << std::endl;//число узлов
    for (auto iter = ObjectsContainer.begin(); iter != ObjectsContainer.end(); iter++){
        std::string name_uz = (*iter)->Name.toLocal8Bit().constData();
        std::string Description = (*iter)->Description.toLocal8Bit().constData();
        int x = (*iter)->pos().toPoint().x();
        int y = (*iter)->pos().toPoint().y();
        fout << "<" << name_uz << "><"<< Description <<"> pos(" << x << ";" << y << ")" << std::endl;
    }
    int kol_par = 0;
    for(auto iter = ObjectsContainer.begin(); iter!= ObjectsContainer.end(); iter++){
        kol_par+= PairContainer[(*iter)].size();
    }
    fout << kol_par << std::endl;//число ребер
    for(auto iter = ObjectsContainer.begin(); iter != ObjectsContainer.end(); iter++){
        for(auto j = PairContainer[(*iter)].begin(); j != PairContainer[(*iter)].end(); j++){
            std::string fir = (*iter)->Name.toLocal8Bit().constData();
            std::string sec = (*j).first->Name.toLocal8Bit().constData();
            fout << "<" << fir << "><" << sec << "> " << (*j).second << std::endl;
        }
    }
    QMessageBox::warning(this, " ", "Файл сохранен");
    fout.close();
}

//загрузка
void MainWindow::on_LoadGraphButton_clicked()
{
    QString name = ui->FileNameLine->text();//имя файла
    if (!CheckFileName(name))
    {
        QMessageBox::critical(this, "Ошибка", "Неправильное имя файла!\nФайл должн оканчиватся на .txt .json .xml");
        return;
    }

    std::string name_s = name.toLocal8Bit().constData();
    std::ifstream fin;
    fin.open(name_s);
    if (fin.is_open() == false)
    {
        QMessageBox::critical(this, "Ошибка", "Не удается открыть файл");
        return;
    }
    QMap<std::string, QList<std::pair<std::string, int>>> par_new;
    QMap<std::string ,std::pair<int, int>> del_new;
    QMap<std::string , std::string>fname_op;
    if (fin.eof()){
        QMessageBox::critical(this, "Ошибка", "Файл пуст");
        return;
    }
    std::string e;
    std::getline(fin, e);
    for (unsigned long long i = 0; i < e.size(); i++)
    {
            if( e[i] < '0' || e[i] > '9')
        {
                QMessageBox::critical(this, "Ошибка", "Нет колличества узлов в файле");
                return;
            }
    }
    qDebug() << QString::fromStdString(e);
    QString Qe = QString::fromStdString(e);
    int size = Qe.toInt();
    unsigned long long j = 0;
    for (int i = 0; i < size && !fin.eof(); i++)
    {
        std::getline(fin, e);
        qDebug() << QString::fromStdString(e);
        if (e.size() == 0 || e[0] != '<')
        {
            QMessageBox::critical(this, "Ошибка", "Файл не корректен нет начальной <");
            del_new.clear();
            par_new.clear();
            return;
        }
        std::string name_uz = "";
        for (j = 1; j < e.size() && e[j] != '>'; j++)
        {
            name_uz += e[j];
        }
        if (j == e.size())
        {
            QMessageBox::critical(this, "Ошибка", "Файл не корректен нет конечной >");
            del_new.clear();
            par_new.clear();
            return;
        }
        j++;
        if(e[j] != '<')
        {
            QMessageBox::critical(this, "Ошибка", "Файл не корректен нет описания узла");
            del_new.clear();
            par_new.clear();
            return;
        }
        j++;
        std::string fname = "";
        for (;j < e.size() && e[j] != '>'; j++)
        {
            fname += e[j];
        }
        j++;
        int x = 0, y = 0;
        if (e.size() < j + 8 || (e[j+1] != 'p' || e[j+2] != 'o' || e[j+3] != 's' || e[j+4] != '('))
        {
            QMessageBox::critical(this, "Ошибка", "Файл не корректен нет pos");
            del_new.clear();
            par_new.clear();
            return;
        }
        j += 5;
        bool min = false;
        if(e[j] == '-')
        {
            min = true;
            j++;
        }
        for (;j < e.size() && e[j]!=';'; j++)
        {
            if(e[j] < '0' || e[j] > '9')
            {
                QMessageBox::critical(this, "Ошибка", "Файл не корректен нет позиции");
                del_new.clear();
                par_new.clear();
                return;
            }
            x = x*10 + e[j] - '0';
            if(min){
                x = -x;
            }
        }
        if (e.size() == j || e[j-1] == '(')
        {
            QMessageBox::critical(this, "Ошибка", "Файл не корректен нет позиции");
            del_new.clear();
            par_new.clear();
            return;
        }
        j++;
        min = false;
        if(e[j] == '-'){
            min = true;
            j++;
        }
        for (;j < e.size() && e[j]!=')'; j++)
        {
            if(e[j] < '0' || e[j] > '9')
            {
                QMessageBox::critical(this, "Ошибка", "Файл не корректен нет позиции y");
                qDebug() << e[j];
                del_new.clear();
                par_new.clear();
                return;
            }
            y = y*10 + e[j] - '0';
            if(min){
                y =-y;
            }
        }
        if(j != e.size()-1)
        {
            QMessageBox::critical(this, "Ошибка", "Файл не корректен");
            del_new.clear();
            par_new.clear();
            return;
        }
        auto it = del_new.find(name_uz);
        if(it != del_new.end())
        {
            QMessageBox::critical(this, "Ошибка", "Узел с именем " + name + " повторяется");
            del_new.clear();
            par_new.clear();
            return;
        }
        del_new[name_uz]= {x, y};
        fname_op[name_uz] = fname;
    }
    if (fin.eof())
    {
        QMessageBox::critical(this, "Ошибка", "Нет колличества ребер в файле");
        return;
    }
    std::getline(fin, e);
    qDebug() <<QString::fromStdString(e);
    for (unsigned long long i = 0; i < e.size(); i++)
    {
            if( e[i] < '0' || e[i] > '9')
        {
                QMessageBox::critical(this, "Ошибка", "Нет колличества ребер в файле");
                return;
            }
    }
    Qe = QString::fromStdString(e);
    size = Qe.toInt();
    int i;
    for(i = 0; !fin.eof() && i < size; i++)
    {
        std::getline(fin, e);
        qDebug() << QString::fromStdString(e);
        if (e.size() == 0 || e[0] != '<')
        {
            QMessageBox::critical(this, "Ошибка", "Файл не корректен");
            del_new.clear();
            par_new.clear();
            return;
        }
        std::string fir = "";
        std::string sec = "";
        std::string ch = "";
        for(j = 1; e[j] != '>' && j < e.size(); j++)
        {
            fir += e[j];
        }
        if(j >= e.size()-1)
        {
            QMessageBox::critical(this, "Ошибка", "Файл не корректен");
            del_new.clear();
            par_new.clear();
            return;
        }
        j++;
        if(e[j] != '<')
        {
            QMessageBox::critical(this, "Ошибка", "Файл не корректен");
            del_new.clear();
            par_new.clear();
            return;
        }
        j++;
        for(; e[j] != '>' && j < e.size(); j++)
        {
            sec += e[j];
        }
        if(j >= e.size())
        {
            QMessageBox::critical(this, "Ошибка", "Файл не корректен");
            del_new.clear();
            par_new.clear();
            return;
        }
        j++;
        if(e[j] == ' ')
        {
            j++;
        }
        for(; j < e.size(); j++)
        {
            ch += e[j];
        }
        for (unsigned long long k = 0; k < ch.size(); k++)
        {
                if( ch[k] < '0' || ch[k] > '9')
            {
                    QMessageBox::critical(this, "Ошибка", "Вес ребра не число");
                    del_new.clear();
                    par_new.clear();
                    return;
                }
        }
        if(ch.size() == 0)
        {
            ch = "1";
        }
        int ch_int = QString::fromStdString(ch).toInt();
        auto it1 = del_new.find(fir);
        auto it2 = del_new.find(sec);
        if (it1 == del_new.end() || it2 == del_new.end())
        {
            QMessageBox::critical(this, "Ошибка", "Ребра содержат не сущ. узлы");
            del_new.clear();
            par_new.clear();
            return;
        }
        bool f = false;
        for (auto it = par_new[fir].begin(); it !=par_new[fir].end(); it++)
        {
            if((*it).first == sec && (*it).second != ch_int)
            {
                QMessageBox::critical(this, "Ошибка", "В файле содержатся два одинаковых ребра");
                del_new.clear();
                par_new.clear();
                return;
            }
            if((*it).first == sec && (*it).second == ch_int)
            {
                f = true;
            }
        }
        if(!f){
            par_new[fir].append({sec, ch_int});
            par_new[sec].append({fir, ch_int});
        }
    }
    if(!fin.eof() && i != size)
    {
        QMessageBox::critical(this, "Ошибка", "Файл не корректен");
        del_new.clear();
        par_new.clear();
        return;
    }
    for(auto iter = ObjectsContainer.begin(); ObjectsContainer.end()!= iter; iter++)
    {
        delete *iter;
    }
    ObjectsContainer.clear();
    PairContainer.clear();
    amount = 0;
    for(auto iter = del_new.begin(); del_new.end()!= iter; iter++)
    {
        amount++;
        QString name =  QString::fromStdString(iter.key());
        QString fname = QString::fromStdString(fname_op[iter.key()]);
        auto it = ObjectsContainer.find(name);
        if(it != ObjectsContainer.end())
        {
            QMessageBox::critical(this, "Ошибка", "Узел с именем " + name + " уже существует");
            return;
        }
        MoveItem *item = new MoveItem(0, amount, name, fname);        // Создаём графический элемента
        item->setPos(iter->first, iter->second);
        scene->addItem(item); // Добавляем элемент на графическую сцену
        ObjectsContainer[name] = item;
        item->PairContainer = &PairContainer;
    }
    for(auto iter = par_new.begin(); iter != par_new.end(); iter++)
    {
        for(auto ite = iter->begin(); ite != iter->end(); ite++)
        {
            bool ff = false;
            QString first = QString::fromStdString(iter.key());
            QString second = QString::fromStdString(ite->first);
            for (auto iterat = PairContainer[ObjectsContainer[first]].begin(); iterat != PairContainer[ObjectsContainer[first]].end(); iterat++)
            {
                if (iterat->first == ObjectsContainer[second])
                {
                    iterat->second = ite->second;
                    ff = true;
                    break;
                }
            }
            for (auto iterat = PairContainer[ObjectsContainer[second]].begin(); iterat != PairContainer[ObjectsContainer[second]].end(); iterat++)
            {
                if (iterat->first == ObjectsContainer[first])
                {
                    iterat->second = ite->second;
                    ff = true;
                    break;
                }
            }
            if (!ff)
            {
                PairContainer[ObjectsContainer[first]].append({ObjectsContainer[second], ite->second});
                PairContainer[ObjectsContainer[second]].append({ObjectsContainer[first], ite->second});
            }
        }
    }
    fin.close();
}
