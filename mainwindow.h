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
//#include <experimental/filesystem>

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
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_Button_del_clicked();

    void on_But_add_clicked();

    void on_but_del_reb_clicked();

    void on_but_save_clicked();

    void on_but_change_clicked();

    void on_but_down_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    int kol = 0;
};
#endif // MAINWINDOW_H
