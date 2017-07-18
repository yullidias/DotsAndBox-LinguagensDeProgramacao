#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "player.h"

#include <QDebug>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    showMessage(true),
    player1(new Player(1,Qt::red,true)),
    player2(new Player(2,Qt::blue,false)) {
    ui->setupUi(this);
    for(int i=0;i<7;i++){
       for(int j=0;j<4;j++){
           LineButton* button = this->findChild<LineButton*>(QString("line%1%2").arg(i).arg(j));
           if(button){
               QObject::connect( button, SIGNAL(clicked(bool)),this, SLOT(handleButton()));
               QObject::connect(ui->actionNovo, SIGNAL(triggered(bool)), button, SLOT(reset()));
           }
       }
    }
    QObject::connect(ui->actionSair, SIGNAL(triggered(bool)), qApp, SLOT(quit()) );
    QObject::connect(ui->actionNovo, SIGNAL(triggered(bool)), this, SLOT(reset()) );
    QObject::connect(ui->actionSobre, SIGNAL(triggered(bool)), this,  SLOT(sobre()));   
    Player* currentPlayer = (player1->getTurn())? player1 : player2 ;
    ui->statusBar->showMessage(QString("P1:  %1 vs P2:  %2                É a vez do jogador P%3").arg(player1->getTotalBoxes()).arg(player2->getTotalBoxes()).arg(currentPlayer->getNumber()));
}

void MainWindow::sobre(){
    QMessageBox::information(this,"Desenvolvedoras: ", "Sarah Rodrigues (sarahrodriguesmoreira@gmail.com)\nYulli Dias (yulli.dias@hotmail.com)");
}

void MainWindow::reset(){
    showMessage=true;
    player1->reset();
    player2->reset();
    player1->setTurn(true);
    player2->setTurn(false);
    for(int x=0;x<3;x++){
       for(int y=0;y<3;y++){
           QLabel* box = this->findChild<QLabel*>(QString("box%1%2").arg(x).arg(y));
           if(box){
              box->setText(QString(""));
           }
       }
    }  
    ui->statusBar->showMessage(QString("P1:  %1 vs P2:  %2                É a vez do jogador P1").arg(player1->getTotalBoxes()).arg(player2->getTotalBoxes()));
}

void MainWindow::handleButton(){   
    Player* currentPlayer = (player1->getTurn())? player1 : player2 ;
    QString Message = QString("P%1").arg(currentPlayer->getNumber());
    bool closedBox = false;
    LineButton* button = qobject_cast<LineButton*>(QObject::sender());
    button->setColor(currentPlayer->getColor());
    QString name = button->objectName();
    int index = name.mid(4,5).toInt();
    int line = index / 10;
    int column = index % 10;
    if(line%2==0){ //se eh par, eh uma linha horizontal//
        //a caixa de cima//
        LineButton* button1 = this->findChild<LineButton*>(QString("line%1%2").arg(line-2).arg(column));
        LineButton* button2 = this->findChild<LineButton*>(QString("line%1%2").arg(line-1).arg(column));
        LineButton* button3 = this->findChild<LineButton*>(QString("line%1%2").arg(line-1).arg(column+1));
        if( button1 && button2 && button3){
            if( button1->isEnabled()==false && button2->isEnabled()==false && button3->isEnabled()==false){
                QLabel* box = this->findChild<QLabel*>(QString("box%1%2").arg((line/2)-1).arg(column));                
                box->setText(Message);
                QString rgba = currentPlayer->getColor().name(QColor::HexArgb);
                box->setStyleSheet(QString("color: %1").arg(rgba));
                currentPlayer->incrementTotalBoxes();
                closedBox = true;
            }
        }
        //a caixa de baixo//
        button1 = this->findChild<LineButton*>(QString("line%1%2").arg(line+2).arg(column));
        button2 = this->findChild<LineButton*>(QString("line%1%2").arg(line+1).arg(column));
        button3 = this->findChild<LineButton*>(QString("line%1%2").arg(line+1).arg(column+1));
        if( button1 && button2 && button3){
            if( button1->isEnabled()==false && button2->isEnabled()==false && button3->isEnabled()==false){
                QLabel* box = this->findChild<QLabel*>(QString("box%1%2").arg((line/2)).arg(column));
                box->setText(Message);
                QString rgba = currentPlayer->getColor().name(QColor::HexArgb);
                box->setStyleSheet(QString("color: %1").arg(rgba));
                currentPlayer->incrementTotalBoxes();
                closedBox = true;
            }
        }
    }
    else{ //eh vertical//
        //a caixa do lado esquerdo//
        LineButton* button1 = this->findChild<LineButton*>(QString("line%1%2").arg(line-1).arg(column-1));
        LineButton* button2 = this->findChild<LineButton*>(QString("line%1%2").arg(line+1).arg(column-1));
        LineButton* button3 = this->findChild<LineButton*>(QString("line%1%2").arg(line).arg(column-1));
        if( button1 && button2 && button3){
            if( button1->isEnabled()==false && button2->isEnabled()==false && button3->isEnabled()==false){
                QLabel* box = this->findChild<QLabel*>(QString("box%1%2").arg((line/2)).arg(column-1));
                box->setText(Message);
                QString rgba = currentPlayer->getColor().name(QColor::HexArgb);
                box->setStyleSheet(QString("color: %1").arg(rgba));
                currentPlayer->incrementTotalBoxes();
                closedBox = true;
            }
        }
        //a caixa do lado direito//
        button1 = this->findChild<LineButton*>(QString("line%1%2").arg(line-1).arg(column));
        button2 = this->findChild<LineButton*>(QString("line%1%2").arg(line+1).arg(column));
        button3 = this->findChild<LineButton*>(QString("line%1%2").arg(line).arg(column+1));
        if( button1 && button2 && button3){
            if( button1->isEnabled()==false && button2->isEnabled()==false && button3->isEnabled()==false){
                QLabel* box = this->findChild<QLabel*>(QString("box%1%2").arg((line/2)).arg(column));
                box->setText(Message);
                QString rgba = currentPlayer->getColor().name(QColor::HexArgb);
                box->setStyleSheet(QString("color: %1").arg(rgba));
                currentPlayer->incrementTotalBoxes();
                closedBox = true;
            }
        }
    }
    if(closedBox==false){
        currentPlayer->setTurn(false);
        if(currentPlayer->getNumber()==1){
            player2->setTurn(true);
        }
        else
            player1->setTurn(true);
    }
    currentPlayer = (player1->getTurn())? player1 : player2 ;
    ui->statusBar->showMessage(QString("P1:  %1 vs P2:  %2                É a vez do jogador P%3").arg(player1->getTotalBoxes()).arg(player2->getTotalBoxes()).arg(currentPlayer->getNumber()));

    if(currentPlayer->getTotalBoxes()>=5&&showMessage){
        showMessage=false;
        QMessageBox::information(this,"Fim de Jogo",QString("Parabéns, o jogador P%1 venceu!").arg(currentPlayer->getNumber()));
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
