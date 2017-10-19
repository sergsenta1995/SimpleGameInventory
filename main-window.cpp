#include "main-window.hpp"
#include "ui_main-window.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{    
    ui->setupUi(this);

    animation = new QPropertyAnimation(ui->mainMenu, "maximumHeight");

    connect(ui->newGame, &QPushButton::clicked, this, MainWindow::onStartClicked);
    connect(ui->exit, &QPushButton::clicked, this, MainWindow::onExitClicked);
    connect(ui->toMainMenu, &QPushButton::clicked, this, MainWindow::onMainMenuClicked);


    configurationSetup(parent);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::configurationSetup(QWidget *parent)
{
    QMessageBox *configurationSelection = new QMessageBox(parent);
    configurationSelection->setWindowTitle("Окно выбора конфигурации");
    configurationSelection->setText("Выберите конфигурацию используемого приложения:");
    configurationSelection->setInformativeText("  клиент изменяет инвентарь и отправляет изменения на сервер \n"
                                               "  сервер не изменяет инвентарь и принимат изменения от клиента");
    QPushButton *clientButton = configurationSelection->addButton("Клиент", QMessageBox::NoRole);
    QPushButton *serverButton = configurationSelection->addButton("Сервер", QMessageBox::YesRole);

    ui->stackedWidget->setEnabled(false);
    const int CLIENT_WIDGET = 0;
    const int SERVER_WIDGET = 1;
    ui->stackedWidget->setCurrentIndex(CLIENT_WIDGET);
    configurationSelection->exec();
    if (configurationSelection->clickedButton() == serverButton)
    {
        ui->stackedWidget->setCurrentIndex(SERVER_WIDGET);        
        presenter = new ServerPresenter(ui->serverInventory);
    }
    else
    {
        ui->stackedWidget->setCurrentIndex(CLIENT_WIDGET);        
        presenter = new ClientPresenter(ui->clientInventory);
    }
}


void MainWindow::onStartClicked()
{
    animation->setDuration(1000);
    animation->setEasingCurve(QEasingCurve::Linear);
    QSize startValue = ui->mainMenu->size();
    animation->setStartValue(startValue.height());
    animation->setEndValue(0);
    animation->start();

    ui->stackedWidget->setEnabled(true);
}

void MainWindow::onMainMenuClicked()
{
    animation->setDuration(1000);
    animation->setEasingCurve(QEasingCurve::Linear);    
    animation->setStartValue(0);
    animation->setEndValue(50);
    animation->start();

    ui->stackedWidget->setEnabled(false);
}

void MainWindow::onExitClicked()
{
    this->close();
}

