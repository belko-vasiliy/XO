#include "win.h"

Win::Win()
{

}
void Win::winner(int enum_xo)
{
    QStringList argument;
    if (enum_xo==0)
    {
        argument <<"                 _.---._    /\\    "
                 <<"              ./'        --`\//    "
                 <<"           ./              o \     "
                 <<"          /./\  )______   \__ \    "
                 <<"         ./  / /\ \   | \ \  \ \   "
                 <<"            / /  \ \  | |\ \  \7   "
                 <<"                                   \n";
    }
    if (enum_xo==1)
    {
        argument <<"            .----.-.    "
                 <<"           /    ( o \   "
                 <<"          '|  __ ` ||   "
                 <<"           |||  ||| -'  \n";
    }
    int total = argument.size();
    for (int i = 0; i < total; i++)
    {
        QString tmpstr = argument[i];
        char str[50];
        strncpy(str,qPrintable(tmpstr),49);
        std::cout<<str<<std::endl;

    }
    //         I'll do it later
    ///////////////////////////////////////
    QProcess* proc=new QProcess();
    QString str = " more C:\\win_o.txt";
    QByteArray user_cmd = str.toUtf8();
    proc->start("cmd.exe /C start cmd.exe \n\r");
    proc->write("cd C:\\ \n\r");
    proc->write(user_cmd+"\n\r");
}
