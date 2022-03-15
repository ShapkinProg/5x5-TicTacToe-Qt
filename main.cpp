#include "mainwindow.h"
#include <QtGui>
#include <QApplication>
#include <QLayout>
#include <QPushButton>



int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    MainWindow w;
    w.show();
    return a.exec();
}
