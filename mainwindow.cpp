#include "mainwindow.h"
#include "ui_mainwindow.h"


// разделят строку на подстроки через , [asd,fgh,jkl]->[asd][fgh][hjk]
QVector<QString> MainWindow::StrToVector(QString a)
{
    QVector<QString>ans;
    QString b = "";
    for (int i = 0; i < a.size(); i++)
    {
        if(a[i] != ',')
        {
            b += a[i];
        }
        else
        {
            ans.push_back(b);
            b = "";
        }
    }
    if (b.size() != 0)
    {
        ans.push_back(b);
    }
    return ans;
}

static int RandomBetween(int low, int high)
{
    return (qrand() % ((high + 1) - low) + low);
}

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
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

    QRegExpValidator *validator = new QRegExpValidator(QRegExp("[0-9]+(,[0-9]+)*"));
    ui->WeightAddEdgeLine->setValidator(validator);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// создание нового узла
void MainWindow::on_AddNodeButton_clicked()
{
    amount++;
    QString name =  ui->NameAddLine->text();//имя
    QString fname = ui->DescriptionAddLine->text();//описание
    auto it = del.find(name); // проверка на повторение имя
    if(it != del.end())
    {
        QMessageBox::warning(this, "Ошибка", "Узел с именем " + name + " уже существует");
        return;
    }
    MoveItem *item = new MoveItem(0, amount, name, fname);        // Создаём графический элемента
    item->setPos(RandomBetween(0, 500), RandomBetween(0,500));
    scene->addItem(item); // Добавляем элемент на графическую сцену
    del[name] = item;
    item->del = &par;
}

//удаляем один узел
void MainWindow::on_DelNodeButton_clicked()
{
    QString del_st = ui->NameDelLine->text();
    QVector<QString> delp = StrToVector(del_st);
    //ищем все ребра связанные с ним и удаляем их
    for(int k = 0; k < delp.size(); k++)
    {
        auto it = del.find(delp[k]);
        if (it != del.end()){
            for(auto i = par.begin(); i != par.end(); i++)
            {
                for(auto j = i->begin(); j != i->end(); j++)
                {
                    if(j->first == del[delp[k]]){
                        i->erase(j);
                    }
                }
            }
            par[del[delp[k]]].clear();
            auto ite = par.find(del[delp[k]]);
            par.erase(ite);
            delete del[delp[k]]; // удаляем сам узел
            del.erase(it);
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
        auto it = del.find(old);
        if(it == del.end()){//есть ли старое имя
            QMessageBox::warning(this, "Ошибка", "Узла с названием " + old + " нет");
            return;
        }
        del[old]->Description = Description;
        QMessageBox::warning(this, " ", "Описание изменино");
        return;
    }
    auto it = del.find(old);
    if(it == del.end()){//есть ли старое имя
        QMessageBox::warning(this, "Ошибка", "Узла с названием " + old + " нет");
        return;
    }
    if (old == new_){
        return;
    }
    it = del.find(new_);
    if(it != del.end()){//есть ли новое
        QMessageBox::warning(this, "Ошибка", "Узел с названием " + new_ + " уже существует");
        return;
    }
    //смена имени
    del[old]->Name = new_;
    del[new_] = del[old];
    it = del.find(old);
    del.erase(it);
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
    for (int i = 0; i < len.size(); i++){ //проверка что в весе число
        if( len[i] < '0' || len[i] > '9'){
            QMessageBox::warning(this, "Ошибка", "ВВедено не число в вес");
            return;
        }
    }
    int len_int = len.toInt(); // "123"->123 string to int
    auto it = del.find(first);
    auto it1 = del.find(second);
    if (it ==  del.end() || it1 ==  del.end()){ // Есть ли такие узлы
        QMessageBox::warning(this, "Ошибка", "Не найдены узлы");
        return;
    }
    //Проверка на сущ. ребра. Если есть то изменяем вес, если нет то добавляем
    for (auto iter = par[del[first]].begin(); iter != par[del[first]].end(); iter++){
        if (iter->first == del[second]){
            iter->second = len_int;
            break;
        }
    }
    for (auto iter = par[del[second]].begin(); iter != par[del[second]].end(); iter++){
        if (iter->first == del[first]){
            iter->second = len_int;
            return;
        }
    }
    par[del[first]].append({del[second], len_int});
    par[del[second]].append({del[first], len_int});

}

//удаление ребра
void MainWindow::on_DelEdgeButton_clicked()
{
    QString first = ui->Name1DelEdgeLine->text();
    QString second = ui->Name2DelEdgeLine->text();
    auto it = del.find(first);
    auto it1 = del.find(second);
    if (it ==  del.end() || it1 ==  del.end()){//проверка на сущ. узлов
        return;
    }
    bool f = false;
    // Удаление ребра, если нет его, то будет сообщение
    for (auto iter = par[del[first]].begin(); iter != par[del[first]].end(); iter++){
        if (iter->first == del[second]){
            par[del[first]].erase(iter);
            f = true;
            break;
        }
    }
    for (auto iter = par[del[second]].begin(); iter != par[del[second]].end(); iter++){
        if (iter->first == del[first]){
            par[del[second]].erase(iter);
            f = true;
            break;
        }
    }
    if(!f){
        QMessageBox::warning(this, "Ошибка", "Нет ребра:(");
    }
}

// удаляем все элементы
void MainWindow::on_DelGraphButton_clicked()
{
    for(auto iter = del.begin(); del.end()!= iter; iter++){
        delete *iter;
    }
    del.clear();
    par.clear();
    amount = 0;
}

//сохранение
void MainWindow::on_SaveGraphButton_clicked()
{
    QString name = ui->FileNameLine->text();//имя файла
    // проверка на правильность
    if(name.size() < 5){
        QMessageBox::warning(this, "Ошибка", "Файл должн оканчиватся на .txt .json .xml");
        return;
    }
    if (!((name.size()> 4 && name[name.size()-1] =='t' && name[name.size()-3] =='t'&& name[name.size()-2] =='x' && name[name.size()-4] == '.') ||(name.size()> 4 && name[name.size()-1] =='l' && name[name.size()-3] =='x' && name[name.size()-2] =='m' && name[name.size()-4] == '.')
            || (name.size()> 5 && name[name.size()-1] =='n' && name[name.size()-3] =='s'&& name[name.size()-2] =='o' && name[name.size()-5] == '.' && name[name.size()-4] =='j'))){
        QMessageBox::warning(this, "Ошибка", "Файл должн оканчиватся на .txt .json .xml");
        return;
    }
    std::string name_s = name.toLocal8Bit().constData();
    std::ofstream fout;
    fout.open(name_s);
    if (fout.is_open() == false){
        QMessageBox::warning(this, "Ошибка", "Не удается открыть файл");
        return;
    }
    fout << del.size() << std::endl;//число узлов
    for (auto iter = del.begin(); iter != del.end(); iter++){
        std::string name_uz = (*iter)->Name.toLocal8Bit().constData();
        std::string Description = (*iter)->Description.toLocal8Bit().constData();
        int x = (*iter)->pos().toPoint().x();
        int y = (*iter)->pos().toPoint().y();
        fout << "<" << name_uz << "><"<< Description <<"> pos(" << x << ";" << y << ")" << std::endl;
    }
    int kol_par = 0;
    for(auto iter = del.begin(); iter!= del.end(); iter++){
        kol_par+= par[(*iter)].size();
    }
    fout << kol_par << std::endl;//число ребер
    for(auto iter = del.begin(); iter != del.end(); iter++){
        for(auto j = par[(*iter)].begin(); j != par[(*iter)].end(); j++){
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
    //проверка на кор.
    if(name.size() < 5){
        QMessageBox::warning(this, "Ошибка", "Файл должн оканчиватся на .txt .json .xml");
        return;
    }
    if (!((name.size()> 4 && name[name.size()-1] =='t' && name[name.size()-3] =='t'&& name[name.size()-2] =='x' && name[name.size()-4] == '.') ||(name.size()> 4 && name[name.size()-1] =='l' && name[name.size()-3] =='x' && name[name.size()-2] =='m' && name[name.size()-4] == '.')
            || (name.size()> 5 && name[name.size()-1] =='n' && name[name.size()-3] =='s'&& name[name.size()-2] =='o' && name[name.size()-5] == '.' && name[name.size()-4] =='j'))){
        QMessageBox::warning(this, "Ошибка", "Файл должн оканчиватся на .txt .json .xml");
        return;
    }
    std::string name_s = name.toLocal8Bit().constData();
    std::ifstream fin;
    fin.open(name_s);
    if (fin.is_open() == false){
        QMessageBox::warning(this, "Ошибка", "Не удается открыть файл");
        return;
    }
    QMap<std::string, QList<std::pair<std::string, int>>> par_new;
    QMap<std::string ,std::pair<int, int>> del_new;
    QMap<std::string , std::string>fname_op;
    if (fin.eof()){
        QMessageBox::warning(this, "Ошибка", "Файл пуст");
        return;
    }
    std::string e;
    std::getline(fin, e);
    for (unsigned long long i = 0; i < e.size(); i++)
    {
            if( e[i] < '0' || e[i] > '9')
        {
                QMessageBox::warning(this, "Ошибка", "Нет колличества узлов в файле");
                return;
            }
    }
    qDebug() << QString::fromStdString(e);
    QString Qe = QString::fromStdString(e);
    int size = Qe.toInt();
    unsigned long long j = 0;
    for (int i = 0; i < size && !fin.eof(); i++){
        std::getline(fin, e);
        qDebug() << QString::fromStdString(e);
        if (e.size() == 0 || e[0] != '<'){
            QMessageBox::warning(this, "Ошибка", "Файл не корректен нет начальной <");
            del_new.clear();
            par_new.clear();
            return;
        }
        std::string name_uz = "";
        for (j = 1; j < e.size() && e[j] != '>'; j++){
            name_uz += e[j];
        }
        if (j == e.size()){
            QMessageBox::warning(this, "Ошибка", "Файл не корректен нет конечной >");
            del_new.clear();
            par_new.clear();
            return;
        }
        j++;
        if(e[j] != '<'){
            QMessageBox::warning(this, "Ошибка", "Файл не корректен нет описания узла");
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
        if (e.size() < j + 8 || (e[j+1] != 'p' || e[j+2] != 'o' || e[j+3] != 's' || e[j+4] != '(')){
            QMessageBox::warning(this, "Ошибка", "Файл не корректен нет pos");
            del_new.clear();
            par_new.clear();
            return;
        }
        j += 5;
        bool min = false;
        if(e[j] == '-'){
            min = true;
            j++;
        }
        for (;j < e.size() && e[j]!=';'; j++){
            if(e[j] < '0' || e[j] > '9'){
                QMessageBox::warning(this, "Ошибка", "Файл не корректен нет позиции");
                del_new.clear();
                par_new.clear();
                return;
            }
            x = x*10 + e[j] - '0';
            if(min){
                x = -x;
            }
        }
        if (e.size() == j || e[j-1] == '('){
            QMessageBox::warning(this, "Ошибка", "Файл не корректен нет позиции");
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
        for (;j < e.size() && e[j]!=')'; j++){
            if(e[j] < '0' || e[j] > '9'){
                QMessageBox::warning(this, "Ошибка", "Файл не корректен нет позиции y");
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
        if(j != e.size()-1){
            QMessageBox::warning(this, "Ошибка", "Файл не корректен");
            del_new.clear();
            par_new.clear();
            return;
        }
        auto it = del_new.find(name_uz);
        if(it != del_new.end()){
            QMessageBox::warning(this, "Ошибка", "Узел с именем " + name + " повторяется");
            del_new.clear();
            par_new.clear();
            return;
        }
        del_new[name_uz]= {x, y};
        fname_op[name_uz] = fname;
    }
    if (fin.eof()){
        QMessageBox::warning(this, "Ошибка", "Нет колличества ребер в файле");
        return;
    }
    std::getline(fin, e);
    qDebug() <<QString::fromStdString(e);
    for (unsigned long long i = 0; i < e.size(); i++){
            if( e[i] < '0' || e[i] > '9'){
                QMessageBox::warning(this, "Ошибка", "Нет колличества ребер в файле");
                return;
            }
    }
    Qe = QString::fromStdString(e);
    size = Qe.toInt();
    int i;
    for(i = 0; !fin.eof() && i < size; i++){
        std::getline(fin, e);
        qDebug() << QString::fromStdString(e);
        if (e.size() == 0 || e[0] != '<'){
            QMessageBox::warning(this, "Ошибка", "Файл не корректен");
            del_new.clear();
            par_new.clear();
            return;
        }
        std::string fir = "";
        std::string sec = "";
        std::string ch = "";
        for(j = 1; e[j] != '>' && j < e.size(); j++){
            fir += e[j];
        }
        if(j >= e.size()-1){
            QMessageBox::warning(this, "Ошибка", "Файл не корректен");
            del_new.clear();
            par_new.clear();
            return;
        }
        j++;
        if(e[j] != '<'){
            QMessageBox::warning(this, "Ошибка", "Файл не корректен");
            del_new.clear();
            par_new.clear();
            return;
        }
        j++;
        for(; e[j] != '>' && j < e.size(); j++){
            sec += e[j];
        }
        if(j >= e.size()){
            QMessageBox::warning(this, "Ошибка", "Файл не корректен");
            del_new.clear();
            par_new.clear();
            return;
        }
        j++;
        if(e[j] == ' '){
            j++;
        }
        for(; j < e.size(); j++){
            ch += e[j];
        }
        for (unsigned long long k = 0; k < ch.size(); k++)
        {
                if( ch[k] < '0' || ch[k] > '9')
            {
                    QMessageBox::warning(this, "Ошибка", "Вес ребра не число");
                    del_new.clear();
                    par_new.clear();
                    return;
                }
        }
        if(ch.size() == 0){
            ch = "1";
        }
        int ch_int = QString::fromStdString(ch).toInt();
        auto it1 = del_new.find(fir);
        auto it2 = del_new.find(sec);
        if (it1 == del_new.end() || it2 == del_new.end()){
            QMessageBox::warning(this, "Ошибка", "Ребра содержат не сущ. узлы");
            del_new.clear();
            par_new.clear();
            return;
        }
        bool f = false;
        for (auto it = par_new[fir].begin(); it !=par_new[fir].end(); it++){
            if((*it).first == sec && (*it).second != ch_int){
                QMessageBox::warning(this, "Ошибка", "В файле содержатся два одинаковых ребра");
                del_new.clear();
                par_new.clear();
                return;
            }
            if((*it).first == sec && (*it).second == ch_int){
                f = true;
            }
        }
        if(!f){
            par_new[fir].append({sec, ch_int});
            par_new[sec].append({fir, ch_int});
        }
    }
    if(!fin.eof() && i != size){
        QMessageBox::warning(this, "Ошибка", "Файл не корректен");
        del_new.clear();
        par_new.clear();
        return;
    }
    for(auto iter = del.begin(); del.end()!= iter; iter++){
        delete *iter;
    }
    del.clear();
    par.clear();
    amount = 0;
    for(auto iter = del_new.begin(); del_new.end()!= iter; iter++){
        amount++;
        QString name =  QString::fromStdString(iter.key());
        QString fname = QString::fromStdString(fname_op[iter.key()]);
        auto it = del.find(name);
        if(it != del.end()){
            QMessageBox::warning(this, "Ошибка", "Узел с именем " + name + " уже существует");
            return;
        }
        MoveItem *item = new MoveItem(0, amount, name, fname);        // Создаём графический элемента
        item->setPos(iter->first,    // Устанавливаем случайную позицию элемента
                     iter->second);
        scene->addItem(item); // Добавляем элемент на графическую сцену
        del[name] = item;
        item->del = &par;
    }
    for(auto iter = par_new.begin(); iter != par_new.end(); iter++){
        for(auto ite = iter->begin(); ite != iter->end(); ite++){
            bool ff = false;
            QString first = QString::fromStdString(iter.key());
            QString second = QString::fromStdString(ite->first);
            for (auto iterat = par[del[first]].begin(); iterat != par[del[first]].end(); iterat++){
                if (iterat->first == del[second]){
                    iterat->second = ite->second;
                    ff = true;
                    break;
                }
            }
            for (auto iterat = par[del[second]].begin(); iterat != par[del[second]].end(); iterat++){
                if (iterat->first == del[first]){
                    iterat->second = ite->second;
                    ff = true;
                    break;
                }
            }
            if (!ff){
                par[del[first]].append({del[second], ite->second});
                par[del[second]].append({del[first], ite->second});
            }
        }
    }
    fin.close();
}
