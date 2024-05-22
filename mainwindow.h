#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QGraphicsScene>
#include <QWidget>
#include <moveitem.h>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QTextCodec>
#include <fstream>
#include <iostream>
#include <QRegExpValidator>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QMap<MoveItem*, QList<std::pair<MoveItem*, int>>> par;
    QMap <QString ,MoveItem*> del;

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
    QVector<QString> StrToVector(QString a);
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    int amount = 0;
};
#endif // MAINWINDOW_H
