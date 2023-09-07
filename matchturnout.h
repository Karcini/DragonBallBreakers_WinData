#ifndef MATCHTURNOUT_H
#define MATCHTURNOUT_H

#include <QStringList>
#include <QString>
#include <QMetaEnum>
#include <QDebug>
#include "datanamespace.h"

//To add a new stat on txt file
    //include a primitive value, add an enum in datanamespace if its a turnout of 2 things
    //include a validator func. in recordAllStats
class MatchTurnout
{
public:
    MatchTurnout();
    void recordAllStats(QStringList);

    //DataNamespace status;
    bool infoValid;
    QStringList dbLogList;

    //match variables
    int m_raiderAccLvl;         //data[1]   int 1~100
    bool m_raiderWon;           //data[2]   won TRUE, lost FALSE
    bool m_lossReason;          //data[3]   by stm TRUE, by hp loss FALSE
    bool m_STMstatus;           //data[4]   called TRUE, broken TRUE, not called FALSE
    bool m_STMbroken;           //data[4]   called TRUE if broken
    int m_raiderLvlAtSTM;       //data[5]   int 1~4
    int m_raiderLvlAtEnd;       //data[6]   int 1~4
    int m_survRemainingAtSTM;   //data[7]   int 1~7
    int m_survRemainingAtEnd;   //data[8]   int 0~7
    bool m_wishCalled;          //data[9]   surv TRUE, raider FALSE
    bool m_wishStatus;          //data[10]  lv4 active TRUE, lv4 inactive FALSE
    int m_STMcharged;           //data[11]  int 0~100 by rounded %
    int m_raiderHP;             //data[12]  int 0~100 by rounded %

private:
    void populateLogList();
    bool validator(DataNamespace::DBLog, DataNamespace::DBLog, QString, bool *);
    int validator(int min, int max, QString dataPoint, bool *);
    DataNamespace::DBLog getNamespaceValue(QString dataPoint);

    void record_RaiderAccLvl(int);
    void record_RaiderVictory(int);
    void record_LossReason(int);
    void record_STMstatus(int);
    void record_RiaderLvAtSTM(int);
    void record_RaiderLvAtEnd(int);
    void record_SurvRemainAtSTM(int);
    void record_SurvRemainAtEnd(int);
    void record_WishCalledBy(int);
    void record_WishStatus(int);
    void record_STMcharge(int);
    void record_RaiderHP(int);

    void tabulateMatch(int, int, int, int, int, int, int, int, int, int, int, int);
};

#endif // MATCHTURNOUT_H
