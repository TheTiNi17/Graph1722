#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(int argc, char *argv[], QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(this);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    ui->graphicsView->resize(600, 600);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setCacheMode(QGraphicsView::CacheBackground);
    ui->graphicsView->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);

    QRegExpValidator *validator1 = new QRegExpValidator(QRegExp("[0-9]+(,[0-9]+)*"));
    ui->WeightAddEdgeLine->setValidator(validator1);

    QRegExpValidator *validator2 = new QRegExpValidator(QRegExp("^[^\\s\\W]*\\.?[a-zA-Z]*$"));
    ui->FileNameLine->setValidator(validator2);

    QRegExpValidator *validator3 = new QRegExpValidator(QRegExp("[^;]*"));
    ui->NameAddLine->setValidator(validator3);
    ui->DescriptionAddLine->setValidator(validator3);
    ui->OldNameChangeLine->setValidator(validator3);
    ui->NewNameChangeLine->setValidator(validator3);
    ui->NewDescriptionChangeLine->setValidator(validator3);
    ui->Name1AddEdgeLine->setValidator(validator3);
    ui->Name2AddEdgeLine->setValidator(validator3);
    ui->Name1DelEdgeLine->setValidator(validator3);
    ui->Name2DelEdgeLine->setValidator(validator3);

    msgBox.setWindowTitle("Внимание");
    msgBox.setIcon(QMessageBox::Warning);
    msgBox.setText("Данное имя файла уже используется, хотите переписать файл?");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);

    if (argc > 1)
    {
        ui->FileNameLine->setText(argv[1]);
        std::string name = ui->FileNameLine->text().toStdString();
        LoadGraph(name);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

int MainWindow::GetRandomNumberFromTo(int a, int b)
{
    return (randomgenerator.bounded(b - a) + a);
}

void MainWindow::AddNode(QString Name, QString Description, int PositionA, int PositionB)
{
    if (Name == "")
    {
        ErrorMsgBox.setIcon(QMessageBox::Critical);
        ErrorMsgBox.setWindowTitle("Ошибка");
        ErrorMsgBox.setText("Имя узла не может быть пустым!");
        ErrorMsgBox.exec();
        return;
    }

    if (NodeContainer.contains(Name))
    {
        ErrorMsgBox.setIcon(QMessageBox::Critical);
        ErrorMsgBox.setWindowTitle("Ошибка");
        ErrorMsgBox.setText("Данное имя узла занято!");
        ErrorMsgBox.exec();
        return;
    }

    Node *node = new Node(0, Name, Description);
    node->setPos(PositionA, PositionB);
    NodeContainer[Name] = node;
    scene->addItem(node);
}

void MainWindow::RemoveNode(QString Name)
{
    if ( ! NodeContainer.contains(Name))
    {
        ErrorMsgBox.setIcon(QMessageBox::Critical);
        ErrorMsgBox.setWindowTitle("Ошибка");
        ErrorMsgBox.setText("Нет узла с данным именем!");
        ErrorMsgBox.exec();
        return;
    }

    Node* node = NodeContainer[Name];

    //удаление всех ребер для данного Node
    foreach (Edge *edge, EdgeContainer)
    {
        if (edge->Contains1(node))
        {
            EdgeContainer.remove(edge);
            scene->removeItem(edge);
            delete edge;
        }
    }

    scene->removeItem(node);
    NodeContainer.remove(Name);
    delete node;
}

void MainWindow::ChangeNode(QString OldName, QString NewName, QString Description)
{
    if ( ! NodeContainer.contains(OldName))
    {
        ErrorMsgBox.setIcon(QMessageBox::Critical);
        ErrorMsgBox.setWindowTitle("Ошибка");
        ErrorMsgBox.setText("Нет узла с данным именем!");
        ErrorMsgBox.exec();
        return;
    }

    if ((NewName == "") && (Description != ""))
    {
        NodeContainer[OldName]->ChangeDescription(Description);
        return;
    }

    if (NodeContainer.contains(NewName))
    {
        ErrorMsgBox.setIcon(QMessageBox::Critical);
        ErrorMsgBox.setWindowTitle("Ошибка");
        ErrorMsgBox.setText("Данное имя узла занято!");
        ErrorMsgBox.exec();
        return;
    }

    Node* tmp = NodeContainer.take(OldName);
    tmp->ChangeName(NewName);
    NodeContainer[NewName] = tmp;

    if (Description != QString::fromStdString(NodeContainer[NewName]->GetDescription()))
    {
        NodeContainer[NewName]->ChangeDescription(Description);
    }
}

void MainWindow::AddEdge(QString Name1, QString Name2, QString Weight)
{
    if ( ! NodeContainer.contains(Name1))
    {
        ErrorMsgBox.setIcon(QMessageBox::Critical);
        ErrorMsgBox.setWindowTitle("Ошибка");
        ErrorMsgBox.setText("Нет узла с первым именем!");
        ErrorMsgBox.exec();
        return;
    }

    if ( ! NodeContainer.contains(Name2))
    {
        ErrorMsgBox.setIcon(QMessageBox::Critical);
        ErrorMsgBox.setWindowTitle("Ошибка");
        ErrorMsgBox.setText("Нет узла со вторым именем!");
        ErrorMsgBox.exec();
        return;
    }

    if (Weight == "")
    {
        Weight = "10";
    }

    if (Name1 == Name2)
    {
        ErrorMsgBox.setIcon(QMessageBox::Critical);
        ErrorMsgBox.setWindowTitle("Ошибка");
        ErrorMsgBox.setText("Данный граф не может содержать петель!");
        ErrorMsgBox.exec();
        return;
    }

    Node* node1 = NodeContainer[Name1];
    Node* node2 = NodeContainer[Name2];

    foreach (Edge *edge, EdgeContainer)
    {
        if (edge->Contains2(node1, node2))
        {
            edge->ChangeWeight(Weight);
            //ErrorMsgBox.setIcon(QMessageBox::Warning);
            //ErrorMsgBox.setWindowTitle("Изменение");
            //ErrorMsgBox.setText("Существующее ребро изменено!");
            //ErrorMsgBox.exec();
            return;
        }
    }

    // нет такого ребра, создание ребра
    Edge *edge = new Edge(0, node1, node2, Weight);
    edge->setZValue(-1);
    scene->addItem(edge);
    EdgeContainer.insert(edge);
}

void MainWindow::RemoveEdge(QString Name1, QString Name2)
{
    if ( ! NodeContainer.contains(Name1))
    {
        ErrorMsgBox.setIcon(QMessageBox::Critical);
        ErrorMsgBox.setWindowTitle("Ошибка");
        ErrorMsgBox.setText("Нет узла с первым именем!");
        ErrorMsgBox.exec();
        return;
    }

    if ( ! NodeContainer.contains(Name2))
    {
        ErrorMsgBox.setIcon(QMessageBox::Critical);
        ErrorMsgBox.setWindowTitle("Ошибка");
        ErrorMsgBox.setText("Нет узла со вторым именем!");
        ErrorMsgBox.exec();
        return;
    }

    if (Name1 == Name2)
    {
        ErrorMsgBox.setIcon(QMessageBox::Critical);
        ErrorMsgBox.setWindowTitle("Ошибка");
        ErrorMsgBox.setText("Данного ребра не существует!");
        ErrorMsgBox.exec();
        return;
    }

    Node* node1 = NodeContainer[Name1];
    Node* node2 = NodeContainer[Name2];

    foreach (Edge *edge, EdgeContainer)
    {
        if (edge->Contains2(node1, node2))
        {
            EdgeContainer.remove(edge);
            scene->removeItem(edge);
            delete edge;
            return;
        }
    }

    ErrorMsgBox.setIcon(QMessageBox::Critical);
    ErrorMsgBox.setWindowTitle("Ошибка");
    ErrorMsgBox.setText("Данного ребра не существует!");
    ErrorMsgBox.exec();
}

void MainWindow::RemoveAllNodes()
{
    //удаление всех ребер
    foreach (Edge *edge, EdgeContainer)
    {
        scene->removeItem(edge);
        delete edge;
    }
    EdgeContainer.clear();

    for (auto i = NodeContainer.begin(); i != NodeContainer.end(); i++)
    {
        scene->removeItem(i.value());
        delete i.value();
    }
    NodeContainer.clear();
}

std::vector<std::string> SplitStr(std::string str, char split)
{
    // Разделить строку на отдельные учасстки, в данном случае числа разделенные запятыми
    std::stringstream ss(str);
    std::string token;
    std::vector<std::string> arr;

    while (std::getline(ss, token, split))
    {
        arr.push_back((token));
    }
    return arr;
}

bool CheckFileName(std::string filename)
{
    std::string name = filename;
    if (name.length() < 5)
        return false;

    std::vector<std::string> parts = SplitStr(name, '.');
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

void MainWindow::SaveGraph(std::string Name)
{
    if (!CheckFileName(Name))
    {
        ErrorMsgBox.setIcon(QMessageBox::Critical);
        ErrorMsgBox.setWindowTitle("Ошибка");
        ErrorMsgBox.setText("Неправильное имя файла!\nФайл должн оканчиватся на '.txt' '.json' '.xml'!");
        ErrorMsgBox.exec();
        return;
    }

    std::ifstream check;
    check.open(Name);
    if (check.is_open())
    {
        check.close();
        int result = msgBox.exec();
        if (result != QMessageBox::Yes)
        {
            return;
        }
        //иначе result == QMessageBox::Yes
        //продолжаем
    }

    std::ofstream file;
    file.open(Name, std::ios::trunc);
    if ( ! file.is_open())
    {
        ErrorMsgBox.setIcon(QMessageBox::Critical);
        ErrorMsgBox.setWindowTitle("Ошибка");
        ErrorMsgBox.setText("Не удается открыть файл!");
        ErrorMsgBox.exec();
        return;
    }
    for (auto i = NodeContainer.begin(); i != NodeContainer.end(); i++)
    {
        file << i.value()->GetName() << ';' << i.value()->GetDescription() << ';' << i.value()->pos().x() << ';' << i.value()->pos().y();
        file << '\n';
    }
    file << "|\n";

    foreach (Edge *edge, EdgeContainer)
    {
        file << edge->GetNode1()->GetName() << ';' << edge->GetNode2()->GetName() << ';' << edge->GetWeight();
        file << '\n';
    }

    file.close();
    ErrorMsgBox.setIcon(QMessageBox::Warning);
    ErrorMsgBox.setWindowTitle("Сохранение");
    ErrorMsgBox.setText("Граф записан в файл " + QString::fromStdString(Name));
    ErrorMsgBox.exec();
}

void MainWindow::LoadGraph(std::string Name)
{
    if (!CheckFileName(Name))
    {
        ErrorMsgBox.setIcon(QMessageBox::Critical);
        ErrorMsgBox.setWindowTitle("Ошибка");
        ErrorMsgBox.setText("Неправильное имя файла!\nФайл должн оканчиватся на '.txt' '.json' '.xml'!");
        ErrorMsgBox.exec();
        return;
    }

    std::ifstream file;
    file.open(Name);
    if ( ! file.is_open())
    {
        ErrorMsgBox.setIcon(QMessageBox::Critical);
        ErrorMsgBox.setWindowTitle("Ошибка");
        ErrorMsgBox.setText("Не удается открыть файл!");
        ErrorMsgBox.exec();
        return;
    }

    RemoveAllNodes();

    bool edges = false;
    std::vector<std::vector<std::string>> Array;
    std::string line;
    while (std::getline(file, line))
    {
        Array.push_back(SplitStr(line, ';'));
    }

    int counter = 0;
    for (auto i = Array.begin(); i != Array.end(); i++)
    {
        counter++;
        if ((i->at(0) == ""))
        {
            continue;
        }

        if (i->at(0) == "|")
        {
            counter = 0;
            edges = true;
            continue;
        }

        if ( ! edges)
        {
            if (i->size() != 4)
            {
                ErrorMsgBox.setIcon(QMessageBox::Critical);
                ErrorMsgBox.setWindowTitle("Ошибка");
                ErrorMsgBox.setText("Узел графа № " + QString::number(counter) + " в файле задан неправильно");
                ErrorMsgBox.exec();
                continue;
            }

            try
            {
                std::stoi(i->at(2));
                std::stoi(i->at(3));
            }
            catch (std::invalid_argument)
            {
                ErrorMsgBox.setIcon(QMessageBox::Critical);
                ErrorMsgBox.setWindowTitle("Ошибка");
                ErrorMsgBox.setText("Позиция узела графа № " + QString::number(counter) + " в файле задана неправильно");
                ErrorMsgBox.exec();
                continue;
            }

            AddNode(QString::fromStdString(i->at(0)), QString::fromStdString(i->at(1)), std::stoi(i->at(2)), std::stoi(i->at(3)));

        }
        else
        {
            if (i->size() != 3)
            {
                ErrorMsgBox.setIcon(QMessageBox::Critical);
                ErrorMsgBox.setWindowTitle("Ошибка");
                ErrorMsgBox.setText("Ребро графа № " + QString::number(counter) + " в файле задано неправильно");
                ErrorMsgBox.exec();
                continue;
            }

            try
            {
                std::stoi(i->at(2));
            }
            catch (std::invalid_argument)
            {
                ErrorMsgBox.setIcon(QMessageBox::Critical);
                ErrorMsgBox.setWindowTitle("Ошибка");
                ErrorMsgBox.setText("Вес ребра № " + QString::number(counter) + " в файле задан неправильно");
                ErrorMsgBox.exec();
                continue;
            }

            AddEdge(QString::fromStdString(i->at(0)), QString::fromStdString(i->at(1)), QString::fromStdString(i->at(2)));
        }
    }
    file.close();
}

void MainWindow::on_AddNodeButton_clicked()
{
    QString Name = ui->NameAddLine->text();
    QString Description = ui->DescriptionAddLine->text();

    int PositionA = GetRandomNumberFromTo(-500, 500);
    int PositionB = GetRandomNumberFromTo(-500, 500);

    AddNode(Name, Description, PositionA, PositionB);
}

void MainWindow::on_DelNodeButton_clicked()
{
    QString Name = ui->NameDelLine->text();
    RemoveNode(Name);
}

void MainWindow::on_ChangeNodeButton_clicked()
{
    QString OldName = ui->OldNameChangeLine->text();
    QString NewName = ui->NewNameChangeLine->text();
    QString NewDescription = ui->NewDescriptionChangeLine->text();

    ChangeNode(OldName, NewName, NewDescription);
}

void MainWindow::on_AddEdgeButton_clicked()
{
    QString Name1 = ui->Name1AddEdgeLine->text();
    QString Name2 = ui->Name2AddEdgeLine->text();
    QString Weight = ui->WeightAddEdgeLine->text();

    AddEdge(Name1, Name2, Weight);
}

void MainWindow::on_DelEdgeButton_clicked()
{
    QString Name1 = ui->Name1DelEdgeLine->text();
    QString Name2 = ui->Name2DelEdgeLine->text();

    RemoveEdge(Name1, Name2);
}

void MainWindow::on_DelGraphButton_clicked()
{
    RemoveAllNodes();
}

void MainWindow::on_SaveGraphButton_clicked()
{
    QString Name = ui->FileNameLine->text();
    SaveGraph(Name.toStdString());
}

void MainWindow::on_LoadGraphButton_clicked()
{
    QString Name = ui->FileNameLine->text();
    LoadGraph(Name.toStdString());
}
