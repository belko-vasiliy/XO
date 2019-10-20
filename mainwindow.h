#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>
#include <QPushButton>
#include "win.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

static quint16 port = 1212;

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QTcpServer* server = nullptr;
    QTcpSocket* socket = nullptr;
    QPixmap* pix_x;
    QPixmap* pix_o;
    QIcon* icon_x;
    QIcon* icon_o;
    QPushButton* btnref = nullptr;
    int enum_xo;
    int cango;
    quint32 nextBlockSize;
    QMap<int,int> blockedbtns;
    //Win* winner = nullptr;
    //Win winner;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void on_AnyButton_clicked(int num,QPushButton* btn);

    void checkwinner ();

private slots:
    void on_ServerListenButton_clicked();

    void on_ClientConnectButton_clicked();

    void CreateConnectionSlot();

    void ClientConnectedSlot();

    void GetFromSocketSlot();

    //void on_AnyButton_clicked(int num,QPushButton btn);

    void on_pushButton1_clicked();

    void on_pushButton2_clicked();

    void on_pushButton3_clicked();

    void on_pushButton4_clicked();

    void on_pushButton5_clicked();

    void on_pushButton6_clicked();

    void on_pushButton7_clicked();

    void on_pushButton8_clicked();

    void on_pushButton9_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
