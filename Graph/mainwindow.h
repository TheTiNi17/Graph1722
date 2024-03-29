#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <string>
#include <fstream>
#include "graph.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void writeStringToFile(const std::string& filename, const std::string& str, const std::string&postfix);
private:
    Ui::MainWindow *ui;
    ////
    Graph graph;
};
#endif // MAINWINDOW_H
