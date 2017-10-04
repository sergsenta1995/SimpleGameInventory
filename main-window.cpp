#include "main-window.hpp"
#include "ui_main-window.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    setAcceptDrops(true);

    ui->setupUi(this);

    ui->gameObject->setFixedSize(100,100);

    ui->inventory->setColumnCount(3);
    ui->inventory->setRowCount(3);
    ui->inventory->horizontalHeader()->hide();
    ui->inventory->verticalHeader()->hide();
    ui->inventory->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->inventory->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->inventory->setFixedSize(300,300);

    ui->gameObject->setPixmap(QPixmap(":/images/red-apple.jpg").scaled(100, 100));

}

MainWindow::~MainWindow()
{
    delete ui;
}


