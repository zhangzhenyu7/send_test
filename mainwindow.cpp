#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("测试发送");
    QString pattern="^((25[0-5]|2[0-4]\\d|[01]?\\d\\d?)\\.){3}(25[0-5]|2[0-4]\\d|[01]?\\d\\d?)$";
    QRegularExpression regularExpression(pattern);

    QRegularExpressionMatch match;
    QList<QHostAddress>::iterator i;
    QList<QHostAddress> list=QNetworkInterface::allAddresses();
    for (i = list.begin(); i != list.end(); ++i){
        match=regularExpression.match(i->toString());
        if(match.hasMatch())
            ui->comboBox->addItem(i->toString());
    }
    for(int ii=0;ii<ui->comboBox->count();++ii){
        if(ui->comboBox->itemText(ii).compare("127.0.0.1")==0){
            ui->comboBox->setCurrentIndex(ii);
            break;
        }
    }
    m_sock.bind(QHostAddress(ui->comboBox->currentText()),0);
    m_sock.setSocketOption(QAbstractSocket::MulticastLoopbackOption,1);

    m_timer.setInterval(1000);
    connect(&m_timer, SIGNAL(timeout()), this, SLOT(keepSend()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    sendMsg(ui->lineEdit_3->text());
}

void MainWindow::keepSend()
{
    sendMsg(ui->lineEdit_3->text());
}

void MainWindow::sendMsg(QString str){
    m_sock.writeDatagram(str.toLatin1(),QHostAddress(ui->lineEdit->text()),ui->lineEdit_2->text().toInt());
}

void MainWindow::on_comboBox_currentIndexChanged(const QString &arg1)
{
    m_sock.destroyed();
    m_sock.bind(QHostAddress(ui->comboBox->currentText()),0);
    m_sock.setSocketOption(QAbstractSocket::MulticastLoopbackOption,1);
}

void MainWindow::on_checkBox_clicked()
{
    if(ui->checkBox->checkState()){
        m_timer.start();
    }
    else{
        m_timer.stop();
    }
}
