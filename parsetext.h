#ifndef PARSETEXT_H
#define PARSETEXT_H

#include <QList> //QString
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include "readlinedblog.h"

class ParseText
{
public:
    ParseText();
    ~ParseText();

    void parseTextFromFile();
    void resetData();
    QString getText();
    QList<ReadLineDBLog> * getData();

    QList<ReadLineDBLog> * data;
    QString text;
};

#endif // PARSETEXT_H
