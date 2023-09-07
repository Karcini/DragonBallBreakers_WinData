#ifndef READLINEDBLOG_H
#define READLINEDBLOG_H

#include <QStringList>
#include <QMetaEnum> //we use meta object to get char* data from enumerator types
#include <QDebug>
#include "raider.h"
#include "matchturnout.h"

//This class contains the string list of a single line of tabulated data on dblog.txt
//if text file changes, this string list will increase with new qstring data
    //Note that text file should have NO SPACES, and use tabs in between each segment of data to read...
    //Cell\t15\tdied\tHP\tyes\t  ..... and so on

class ReadLineDBLog
{
public:
    ReadLineDBLog();
    void parseLine(QString);    //WIP, reads line and stores all QString data
    QString getStringLine() const;

    QStringList data;           //split QString of DBLog data
    Raider * raider;            //check if correct type of raider, then record raider
    MatchTurnout * matchTurnout;//the rest of the DBLog data


    //type of data in dblog
    //QString raider;
    //QString accountLevel;
    //QString status;
    //QString death;
    //QString lvAtETM;
    //QString lvAtEnd;
    //QString survAtETM;
    //QString survAtEnd;
    //QString wish;
    //QString lv4Surv;
    //QString stmProg;
    //QString raiderHP;
};

#endif // READLINEDBLOG_H
