#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //pix_x = new QPixmap("D:\\T_x.jpg");
    //pix_o = new QPixmap("D:\\T_o.jpg");

    //pix_x = new QPixmap(":/T_x.jpg");
    //pix_o = new QPixmap(":/T_o.jpg");

    //icon_x = new QIcon(*pix_x);
    //icon_o = new QIcon(*pix_o);

    icon_x = new QIcon();
    icon_o = new QIcon();

    icon_x->addFile(QStringLiteral(":/T_x.jpg"),QSize(), QIcon::Normal, QIcon::On);
    icon_o->addFile(QStringLiteral(":/T_o.jpg"),QSize(), QIcon::Normal, QIcon::On);

    cango = 1;
    enum_xo = 1;
    nextBlockSize = 0;
    blockedbtns.clear();
    buttonlist.clear();

    for (int i = 0; i < total_in_row; ++i)
    {
        for (int j = 0; j < total_in_row; ++j)
        {
            QPushButtonID *btn_id = new QPushButtonID(this);
            btn_id->setID(counter);
            ui->gridLayout->addWidget(btn_id,i,j);
            buttonlist << btn_id;
            blockedbtns[counter] = 2;
            connect (btn_id, &QPushButtonID::clicked,this, on_AnyButton_clicked);
            counter++;
        }
    }
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

    if (enum_xo == 0)
    {
        buttonlist[num]->setIcon(*icon_o);
        enum_xo=1;
    }
    else
    {
        buttonlist[num]->setIcon(*icon_x);
        enum_xo=0;
    }
    blockedbtns[num] = enum_xo;
    checkwinner();
}


void MainWindow::on_AnyButton_clicked()
{
    QObject* btn_ref = sender();
    int num = reinterpret_cast<QPushButtonID*>(btn_ref)->ID;

    if (cango && blockedbtns[num]==2)
    {
        QByteArray block;
        QDataStream stream(&block,QIODevice::WriteOnly);
        stream.setVersion(QDataStream::Qt_5_13);
        stream << quint32(0) << num  <<  enum_xo << cango;
        stream.device()->seek(0);
        stream << quint32(block.size() - sizeof(quint32));
        socket->write(block);
        cango = 0;
        blockedbtns[num] = enum_xo;
        if (enum_xo == 1)
        {
            reinterpret_cast<QPushButtonID*>(btn_ref)->setIcon(*icon_x);
            enum_xo=0;
        }
        else
        {
            reinterpret_cast<QPushButtonID*>(btn_ref)->setIcon(*icon_o);
            enum_xo=1;
        }
        checkwinner();
    }
}

void MainWindow::checkwinner()
{
    int win_selector = 2; // 0 is zero   1 is cross  2 is no winner
    for (int i = 0; i < 7;)  // check strings
    {
        if ( blockedbtns[i]==blockedbtns[i+1] && blockedbtns[i+1] == blockedbtns[i+2] && blockedbtns[i]!=2)
        {
            win_selector = blockedbtns.value(i);
        }
        i=i+3;
    }
    if (win_selector!=2)
    {
        for (int i = 0; i < 3; i++) //check columns
        {
            if ( blockedbtns[i]==blockedbtns[i+3] && blockedbtns[i+3] == blockedbtns[i+6] && blockedbtns[i]!=2)
            {
                win_selector = blockedbtns.value(i);
            }
        }
    }
    if (win_selector!=2)
    {
        if ( blockedbtns[0]==blockedbtns[4] && blockedbtns[4] == blockedbtns[2] && blockedbtns[0]!=2)
        {
            win_selector = blockedbtns.value(1);
        }
        if ( blockedbtns[2]==blockedbtns[4] && blockedbtns[4] == blockedbtns[6] && blockedbtns[2]!=2)
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
