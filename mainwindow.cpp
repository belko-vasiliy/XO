#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    pix_x = new QPixmap("D:\\T_x.jpg");
    pix_o = new QPixmap("D:\\T_o.jpg");

    icon_x = new QIcon(*pix_x);
    icon_o = new QIcon(*pix_o);
    //winner = new Win();

    cango = 1;
    enum_xo = 1;
    nextBlockSize = 0;
    blockedbtns.clear();
    blockedbtns[1] = 2;
    blockedbtns[2] = 2;
    blockedbtns[3] = 2;
    blockedbtns[4] = 2;
    blockedbtns[5] = 2;
    blockedbtns[6] = 2;
    blockedbtns[7] = 2;
    blockedbtns[8] = 2;
    blockedbtns[9] = 2;
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_ServerListenButton_clicked()
{
    server = new QTcpServer(this);
    server->listen(QHostAddress::Any, port);
    connect(server,SIGNAL(newConnection()),this,SLOT(CreateConnectionSlot()));
    ui->textlog->append("listen");
}

void MainWindow::CreateConnectionSlot()
{
    socket = server->nextPendingConnection();
    connect(socket,SIGNAL(disconnected()),socket,SLOT(deleteLater()));
    connect(socket,SIGNAL(readyRead()),this,SLOT(GetFromSocketSlot()));
}

void MainWindow::on_ClientConnectButton_clicked()
{
    socket = new QTcpSocket(this);
    socket->connectToHost(ui->lineIP->text(),port);
    connect(socket,SIGNAL(connected()),this,SLOT(ClientConnectedSlot()));
    connect(socket,SIGNAL(readyRead()),this,SLOT(GetFromSocketSlot()));
}

void MainWindow::ClientConnectedSlot()
{
    ui->textlog->append("Connected");
}

void MainWindow::GetFromSocketSlot()
{

    int num;
    int cando;
    int exo;
    QDataStream stream(socket);
    stream.setVersion(QDataStream::Qt_5_13);

    while(true)
    {
        if (nextBlockSize==0)    // !nextBlockSize
        {
            if (socket->bytesAvailable() < sizeof(quint32))
            {
                break;
            }
            stream >> nextBlockSize;
        }

        if (socket->bytesAvailable() < nextBlockSize)
        {
            break;
        }

        stream >> num >> exo >> cando;
        QString str = "number=" +QString::number(num) + " enum=" + QString::number(exo) +" cando=" + QString::number(cando);
        ui->textlog->append(str);
        nextBlockSize = 0;
    }
    cango = cando;
    enum_xo = exo;
    //btnref = new QPushButton;

    switch (num)
    {
    case 1:
        btnref = ui->pushButton1;
        break;
    case 2:
        btnref = ui->pushButton2;
        break;
    case 3:
        btnref = ui->pushButton3;
        break;
    case 4:
        btnref = ui->pushButton4;
        break;
    case 5:
        btnref = ui->pushButton5;
        break;
    case 6:
        btnref = ui->pushButton6;
        break;
    case 7:
        btnref = ui->pushButton7;
        break;
    case 8:
        btnref = ui->pushButton8;
        break;
    case 9:
        btnref = ui->pushButton9;
        break;
    default:
        break;
    }

    if (enum_xo == 1)
    {
        btnref->setIcon(*icon_x);
        enum_xo=1;
    }
    else
    {
        btnref->setIcon(*icon_o);
        enum_xo=0;
    }
    blockedbtns[num] = enum_xo;
    checkwinner();
}

void MainWindow::on_AnyButton_clicked(int num,QPushButton* btn)
{     
    int total = blockedbtns.size();
    bool isconsist = false;
    /*
    if (blockedbtns[num]!=2)
    {
        isconsist = true;
    }
    for (int i = 1; i < total; i++)
    {
        //if (blockedbtns[i]!=2)
        if ()
        {
            isconsist = true;
        }
    }*/
    if (cango && blockedbtns[num]==2)
    {
        QPushButton* btn_ref = btn;

        if (enum_xo == 1)
        {
            btn_ref->setIcon(*icon_o);
            enum_xo=0;
        }
        else
        {
            btn_ref->setIcon(*icon_x);
            enum_xo=1;
        }

        QByteArray block;
        QDataStream stream(&block,QIODevice::WriteOnly);
        stream.setVersion(QDataStream::Qt_5_13);
        stream << quint32(0) << num  <<  enum_xo << cango;
        stream.device()->seek(0);
        stream << quint32(block.size() - sizeof(quint32));
        socket->write(block);
        cango = 0;
        blockedbtns[num] = enum_xo;
        checkwinner();
    }
}

void MainWindow::checkwinner()
{
    int win_selector = 2; // 0 is zero   1 is cross  2 is no winner
    for (int i = 1; i < 8;)  // check strings
    {
        if ( blockedbtns[i]==blockedbtns[i+1] && blockedbtns[i+1] == blockedbtns[i+2] && blockedbtns[i]!=2)
        {
            win_selector = blockedbtns.value(i);
        }
        i=i+3;
    }
    if (win_selector!=2)
    {
        for (int i = 1; i < 4; i++) //check columns
        {
            if ( blockedbtns[i]==blockedbtns[i+3] && blockedbtns[i+3] == blockedbtns[i+6] && blockedbtns[i]!=2)
            {
                win_selector = blockedbtns.value(i);
            }
        }
    }
    if (win_selector!=2)
    {
        if ( blockedbtns[1]==blockedbtns[5] && blockedbtns[5] == blockedbtns[9] && blockedbtns[1]!=2)
        {
            win_selector = blockedbtns.value(1);
        }
        if ( blockedbtns[3]==blockedbtns[5] && blockedbtns[5] == blockedbtns[7] && blockedbtns[3]!=2)
        {
            win_selector = blockedbtns.value(1);
        }
    }
    if (win_selector == 0)
    {
        Win winner;
        winner.winner(0);
        cango = 0;
    }
    if (win_selector == 1)
    {
        Win winner;
        winner.winner(1);
        cango = 0;
    }
}

/*
QList<QObject*> buttonlist;
buttonlist = ui->gridLayout->children();
int size = buttonlist.length();
for (int i = 0; i < size; ++i)
{
    QPushButton * pb = new QPushButton;
    connect(button)
}
*/

void MainWindow::on_pushButton1_clicked()
{
    on_AnyButton_clicked(1,ui->pushButton1);
}

void MainWindow::on_pushButton2_clicked()
{
    on_AnyButton_clicked(2,ui->pushButton2);
}

void MainWindow::on_pushButton3_clicked()
{
    on_AnyButton_clicked(3,ui->pushButton3);
}

void MainWindow::on_pushButton4_clicked()
{
    on_AnyButton_clicked(4,ui->pushButton4);
}

void MainWindow::on_pushButton5_clicked()
{
    on_AnyButton_clicked(5,ui->pushButton5);
}

void MainWindow::on_pushButton6_clicked()
{
    on_AnyButton_clicked(6,ui->pushButton6);
}

void MainWindow::on_pushButton7_clicked()
{
    on_AnyButton_clicked(7,ui->pushButton7);
}

void MainWindow::on_pushButton8_clicked()
{
    on_AnyButton_clicked(8,ui->pushButton8);
}

void MainWindow::on_pushButton9_clicked()
{
    on_AnyButton_clicked(9,ui->pushButton9);
}
