#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    f = new Form();
    recForm = new RecordsForm();

    connect(f, SIGNAL(signalExit()), this, SLOT(show()));
    connect(recForm, SIGNAL(signalExit()), this, SLOT(show()));
    connect(f, SIGNAL(sendRecord(int)), recForm, SLOT(recieveRecord(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_2_clicked()
{
    this->hide();
    recForm->show();
}

void MainWindow::on_pushButton_clicked()
{
    this->hide();
    f->show();
}

void MainWindow::on_pushButton_3_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this,"Exit", "Do you really want to leave the game?", QMessageBox::No | QMessageBox::Yes);
    if(reply == QMessageBox::Yes)
        close();
}
