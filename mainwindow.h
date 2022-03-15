#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_Together_clicked();
    void preDelUi();
    void on_actionExit_triggered();
    void on_actionInfo_triggered();
    void on_actionEnlarge_the_field_triggered();
    void on_actionRestart_triggered();
    void on_actionGame_difficulty_triggered();

    void on_Easy_clicked();

    void on_Hard_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
