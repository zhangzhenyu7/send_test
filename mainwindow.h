#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QUdpSocket>
#include <QNetworkInterface>
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QTimer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void keepSend();

    void on_comboBox_currentIndexChanged(const QString &arg1);

    void on_checkBox_clicked();

private:
    Ui::MainWindow *ui;
    QNetworkInterface m_netInt;
    QTimer m_timer;
    QUdpSocket m_sock;

    void sendMsg(QString str);
};

#endif // MAINWINDOW_H
