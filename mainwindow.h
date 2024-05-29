#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QGraphicsScene>
#include <QWidget>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QTextCodec>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <QRegExpValidator>
#include <QRandomGenerator>

#include "edge.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    //MainWindow(QWidget *parent = nullptr);
    MainWindow(int argc, char *argv[], QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_AddNodeButton_clicked();

    void on_DelNodeButton_clicked();

    void on_ChangeNodeButton_clicked();

    void on_AddEdgeButton_clicked();

    void on_DelEdgeButton_clicked();

    void on_DelGraphButton_clicked();

    void on_SaveGraphButton_clicked();

    void on_LoadGraphButton_clicked();

private:
    QMap<QString, Node*> NodeContainer;
    QSet<Edge*> EdgeContainer;

    int GetRandomNumberFromTo(int a, int b);
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QMessageBox ErrorMsgBox;
    QMessageBox msgBox;
    QRandomGenerator randomgenerator;
    int amount = 0;
    void AddNode(QString Name, QString Description, int PositionA, int PositionB);
    void RemoveNode(QString Name);
    void ChangeNode(QString OldName, QString NewName, QString Description);
    void AddEdge(QString Name1, QString Name2, QString Weight);
    void RemoveEdge(QString Name1, QString Name2);
    void RemoveAllNodes();
    void SaveGraph(std::string Name);
    void LoadGraph(std::string Name);
};
#endif // MAINWINDOW_H
