#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QPropertyAnimation>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;    
    QPropertyAnimation *animation;

private slots:
    void OnStartClicked();
    void OnMainMenuClicked();
};

#endif // MAINWINDOW_HPP
