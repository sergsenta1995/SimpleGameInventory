#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QPropertyAnimation>

namespace Ui {
class MainWindow;
}

/*!
 * \brief Главное окно приложения
 * \details В данном окне происходит "игровой" процессю
 */
class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    //! Настраивает окно выбора конфигурации: клиент или сервер.
    void configurationSetup(QWidget *parent);

private:
    Ui::MainWindow     *ui;
    QPropertyAnimation *animation;              ///< управляет анимацией показа главного меню
    QDialog            *clientOrServerChoise;   ///< управляет выбором конфигурации: клиент или сервер

private slots:
    //! Обрабатывает нажатие на кнопку "Новая игра".
    void onStartClicked();
    //! Обрабатывает нажатие на кнопку "Главное меню".
    void onMainMenuClicked();
    //! Обрабатывает нажатие на кнопку "Выход".
    void onExitClicked();
};

#endif // MAINWINDOW_HPP
