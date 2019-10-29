#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>
#include <QPushButton>
#include "win.h"
#include "qpushbuttonid.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

static quint16 port = 1212;

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QTcpServer* server = nullptr;
    QTcpSocket* socket = nullptr;
    QIcon* icon_x;
    QIcon* icon_o;
    int enum_xo;
    int cango;
    quint32 nextBlockSize;
    QMap<int,int> blockedbtns;
    QList<QPushButtonID*>  buttonlist;
    const int total_in_row = 3;
    int counter = 0;



public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void on_AnyButton_clicked();

    void checkwinner ();

private slots:
    void on_ServerListenButton_clicked();

    void on_ClientConnectButton_clicked();

    void CreateConnectionSlot();

    void ClientConnectedSlot();

    void GetFromSocketSlot();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
