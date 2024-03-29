#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Добавляем узлы
    graph.addNode(1, "Node 1", "This is the first node");
    graph.addNode(2, "Node 2", "This is the second node");
    graph.addNode(3, "Node 3", "This is the third node");

    // Добавляем связи
    graph.addEdge(1, 2);
    graph.addEdge(2, 3);

    // Удаляем узел и одну из связей
    //graph.removeNode(3); // Удалит и связь 2-3
    //graph.removeEdge(1, 2); // Удаление оставшейся связи

    // Снова добавляем узлы и связи для демонстрации
    graph.addNode(3, "Node 3", "This is the third node, re-added");
    //graph.addEdge(1, 3);

    graph.printGraph();
        // Сохраняем граф в JSON и выводим результат
    std::string graph_str = graph.saveToJson();
    writeStringToFile("../pisia", graph_str, ".json");
    //graph.saveToJson();
}
void MainWindow::writeStringToFile(const std::string& filename, const std::string& str, const std::string&postfix) {
//    std::cout << str << std::endl;
    std::string  cur_file = filename + postfix;
    std::ofstream fileStream(cur_file);
    if (!fileStream) {
        std::cout << "Ошибка при открытии файла: " << cur_file << std::endl;
        return;
    }

    fileStream << str;
    fileStream.close();
}

MainWindow::~MainWindow()
{
    delete ui;
}
