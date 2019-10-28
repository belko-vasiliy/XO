#ifndef QPUSHBUTTONID_H
#define QPUSHBUTTONID_H

#include <QObject>
#include <QPushButton>

class QPushButtonID : public QPushButton
{
    Q_OBJECT
public:
    QPushButtonID(QWidget *parent);
    void setID(int id);
    int ID;
};

#endif // QPUSHBUTTONID_H
