#include "main-window.hpp"
#include "ui_main-window.h"

#include <QDebug>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    animation = new QPropertyAnimation(ui->mainMenu, "geometry");

    connect(ui->newGame, &QPushButton::clicked, this, MainWindow::OnStartClicked);
    connect(ui->toMainMenu, &QPushButton::clicked, this, MainWindow::OnMainMenuClicked);

    QMessageBox *c = new QMessageBox(parent);
    c->setWindowTitle("Окно выбора конфигурации");
    c->setText("Выберите конфигурацию используемого приложения:");
    c->setInformativeText("     клиент изменяет инвентарь и отправляет изменения на сервер \n"
                          "     сервер не изменяет инвентарь и принимат изменения от клиента");
    QPushButton *clientButton = c->addButton("Клиент", QMessageBox::NoRole);
    QPushButton *serverButton = c->addButton("Сервер", QMessageBox::YesRole);

    const int CLIENT_WIDGET = 0;
    const int SERVER_WIDGET = 1;
    ui->stackedWidget->setCurrentIndex(CLIENT_WIDGET);
    c->exec();
    if (c->clickedButton() == serverButton)
    {
        ui->stackedWidget->setCurrentIndex(SERVER_WIDGET);
        ui->serverInventory->startServer();
    }
    else
    {
        ui->stackedWidget->setCurrentIndex(CLIENT_WIDGET);
        ui->clientInventory->startClient();
    }

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
    QRect endValue(startValue.left(), startValue.top() , startValue.width(), 0);
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

