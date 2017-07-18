#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class Player;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void handleButton();
    void reset();
    void sobre();

private:
    Ui::MainWindow *ui;
    bool showMessage;
    Player* player1;
    Player* player2;
};

#endif // MAINWINDOW_H
