#include "main-window.hpp"
#include "ui_main-window.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    animation = new QPropertyAnimation(ui->mainMenu, "geometry");

    connect(ui->newGame, &QPushButton::clicked, this, MainWindow::OnStartClicked);
    connect(ui->toMainMenu, &QPushButton::clicked, this, MainWindow::OnMainMenuClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::OnStartClicked()
{
    animation->setDuration(1000);
    animation->setEasingCurve(QEasingCurve::Linear);
    QRect startValue = ui->mainMenu->rect();
    QRect endValue(startValue.left(), -50 , startValue.width(), startValue.height());
    animation->setEndValue(endValue);
    animation->start();

    ui->gameField->setEnabled(true);
}

void MainWindow::OnMainMenuClicked()
{
    animation->setDuration(1000);
    animation->setEasingCurve(QEasingCurve::Linear);
    QRect startValue = ui->mainMenu->rect();
    QRect endValue(startValue.left(), startValue.top()+50 , startValue.width(), startValue.height());
    animation->setEndValue(startValue);
    animation->start();

    ui->gameField->setEnabled(false);
}

