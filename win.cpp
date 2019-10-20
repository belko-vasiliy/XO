#include "win.h"

Win::Win()
{

}
void Win::winner(int enum_xo)
{

    QProcess *proc=new QProcess();

    QStringList argument;
    if (enum_xo==0)
    {
        argument
                 <<"                 _.---._    /\\    "
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
    proc->start("cmd.exe /C start cmd.exe");


    //proc->start("cmd.exe /C start cmd.exe",argument);

    //QProcess::startDetached("\"C:\\Windows\\System32\\cmd.exe\"");
    //proc->startDetached("\"C:\\Windows\\System32\\cmd.exe\"");

    //QProcess::startDetached("C:\\Windows\System32\cmd.exe", arguments);
    //proc->startDetached("\"C:\\Windows\\System32\\cmd.exe\"",arguments);

}
