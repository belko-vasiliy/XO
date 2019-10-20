#ifndef WIN_H
#define WIN_H

#include <QObject>
#include <QProcess>
#include "mainwindow.h"
#include <iostream>

class Win
{
public:
    QProcess* proc;
    Win();
    void winner(int enum_xo);
};

#endif // WIN_H
