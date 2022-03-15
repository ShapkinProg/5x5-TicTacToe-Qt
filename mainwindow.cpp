#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "programstarter.h"
#include <QScrollArea>
#include <QGridLayout>
#include <QMessageBox>

QPushButton** buttons;
QScrollArea* scroller;
ProgramStarter *program;

short size1 = 50;
short lenx = 20;
short leny = lenx;
short sx = size1/2-lenx/2;
short sy = size1/2-leny/2;
bool addfielad = 0;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    this->setFixedSize(600, 600);
    ui->setupUi(this);
    ui->toolBar->hide();
    buttons = new QPushButton*[size1];
    for ( int i = 0; i < size1; i++)
           buttons[i] = new QPushButton[size1];
    program = new ProgramStarter;
    program->setButtons(buttons, &sx, &sy, &lenx, &leny, size1);
    short count = 0;
    short x1 = geometry().width()/20;
    short y1 = (geometry().height()-20)/20;
    for (int i = 0; i < size1; i++)
    {
            for (int j = 0; j < size1; j++)
            {
                buttons[i][j].setFixedHeight(y1);
                buttons[i][j].setFixedWidth(x1);
                connect(&buttons[i][j], SIGNAL(clicked()), program, SLOT(startProgram()));
                buttons[i][j].setObjectName(QString::number(count));
                count++;
            }
    }
    setWindowTitle("Game");
}

MainWindow::~MainWindow()
{
    for(int i = 0; i < size1; ++i)
        delete[] buttons[i];
    delete[] buttons;
    delete ui;
}

void MainWindow::preDelUi()
{
    ui->verticalLayoutWidget->deleteLater();
    ui->toolBar->show();
    QGridLayout* layout = new QGridLayout();
    layout->setHorizontalSpacing(0);
    layout->setVerticalSpacing(0);
    for (int i = 0; i < size1; i++)
    {
            for (int j = 0; j < size1; j++)
            {
                buttons[i][j].setParent(ui->centralwidget);
                layout->addWidget(&buttons[i][j], i, j);
                if(i == sx || i == sx+1 || j == sy || j== sy+1|| i == sx+leny-1 || j == sy+lenx-1 || i == sx+leny-2 || j == sy+lenx-2)
                {
                    buttons[i][j].setStyleSheet("background-color: gray");
                    if(addfielad)
                        buttons[i][j].show();
                }
                if(i > sx+1 && i < sx+lenx-2 && j > sy+1 && j< sy+leny-2)
                    buttons[i][j].show();
                else
                    buttons[i][j].hide();

            }
    }
    ui->centralwidget->setLayout(layout);
    scroller = new QScrollArea(this);
    scroller->setWidget(ui->centralwidget);
    scroller->setWidgetResizable(true);
    scroller->setGeometry(0, 23, layout->geometry().width(), layout->geometry().height());
    scroller->show();
}

void MainWindow::on_Together_clicked()
{
    preDelUi();
    program->setP(0);
}


void MainWindow::on_actionExit_triggered()
{
    QApplication::exit();
}


void MainWindow::on_actionInfo_triggered()
{
    QMessageBox::about(this, "Information", "In this game, to win, you will need to be the first to fill five in a row with the desired symbol (X or 0), and you also need to take care that the opponent does not do this earlier.");
}


void MainWindow::on_actionEnlarge_the_field_triggered()
{
    if(!program->pobeda)
    if(!addfielad)
    {
        for (int i = sx; i < sx+leny; i++)
                for (int j = sy; j < sy+lenx; j++)
                    if(i == sx || i == sx+1 || j == sy || j== sy+1|| i == sx+leny-1 || j == sy+lenx-1 || i == sx+leny-2 || j == sy+lenx-2)
                            buttons[i][j].show();
        addfielad = 1;
    }
    else
    {
        for (int i = sx; i < sx+leny; i++)
                for (int j = sy; j < sy+lenx; j++)
                    if(i == sx || i == sx+1 || j == sy || j== sy+1|| i == sx+leny-1 || j == sy+lenx-1 || i == sx+leny-2 || j == sy+lenx-2)
                            buttons[i][j].hide();
        addfielad = 0;
    }
}


void MainWindow::on_actionRestart_triggered()
{
    for(int i = sx; i < sx+leny; i++)
    {
        for(int j = sy; j < sy+lenx; j++)
        {
            buttons[i][j].setStyleSheet("background-color: none");
            buttons[i][j].setText("");
            if(!buttons[i][j].isHidden())
                buttons[i][j].hide();
        }
    }
    lenx = 20;
    leny = lenx;
    sx = size1/2-lenx/2;
    sy = size1/2-leny/2;
    addfielad = 0;
    for (int i = sx; i <  sx+lenx; i++)
    {
            for (int j = sy; j <  sy+leny; j++)
            {
                if(i == sx || i == sx+1 || j == sy || j== sy+1|| i == sx+leny-1 || j == sy+lenx-1 || i == sx+leny-2 || j == sy+lenx-2)
                {
                    buttons[i][j].setStyleSheet("background-color: gray");
                    if(addfielad)
                        buttons[i][j].show();
                }
                if(i > sx+1 && i < sx+lenx-2 && j > sy+1 && j< sy+leny-2)
                    buttons[i][j].show();
                else if(!buttons[i][j].isHidden())
                    buttons[i][j].hide();

            }
    }
    program->setButtons(buttons, &sx, &sy, &lenx, &leny, size1);
    program->setDef();
    program->setTempP();
}



void MainWindow::on_actionGame_difficulty_triggered()
{
    QWidget *widget = new QWidget();
    widget->setWindowTitle("Settings");
    widget->setFixedSize(250, 100);
    widget->show();
    QGridLayout* lay = new QGridLayout();
    QPushButton* but1 = new QPushButton();
    QPushButton* but2 = new QPushButton();
    QPushButton* but3 = new QPushButton();
    but1->setFixedSize(60, 60);
    but2->setFixedSize(60, 60);
    but3->setFixedSize(60, 60);
    but1->setText("Together");
    but2->setText("Easy");
    but3->setText("Hard");
    connect(but1, SIGNAL(clicked()), program, SLOT(change1()));
    connect(but2, SIGNAL(clicked()), program, SLOT(change2()));
    connect(but3, SIGNAL(clicked()), program, SLOT(change3()));
    lay->addWidget(but1, 0, 0);
    lay->addWidget(but2, 0, 1);
    lay->addWidget(but3, 0, 2);
    widget->setLayout(lay);

}


void MainWindow::on_Easy_clicked()
{
    preDelUi();
    program->setP(1);
}


void MainWindow::on_Hard_clicked()
{
    preDelUi();
    program->setP(2);
}

