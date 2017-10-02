#include "main-window.hpp"
#include "ui_main-window.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->object_graphicsView->setFixedSize(100,100);

    ui->inventory_tableWidget->setColumnCount(3);
    ui->inventory_tableWidget->setRowCount(3);
    ui->inventory_tableWidget->horizontalHeader()->hide();
    ui->inventory_tableWidget->verticalHeader()->hide();
    ui->inventory_tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->inventory_tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->inventory_tableWidget->setFixedSize(300,300);
}

MainWindow::~MainWindow()
{
    delete ui;
}
