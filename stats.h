#ifndef STATS_H
#define STATS_H

#include <QList>
#include "readlinedblog.h"

class Stats
{
public:
    Stats();

    QString winLossRate(QList<int>, QList<ReadLineDBLog> * data);

private:
    QString getLine_WinRate         (QList<ReadLineDBLog> *);
    QString getLine_LossRate        (QList<ReadLineDBLog> *);
    QString getLine_stmSummonRate   (QList<ReadLineDBLog> *);
    QString getLine_wishSummonRate  (QList<ReadLineDBLog> *);
    QString getLine_endGameStats    (QList<ReadLineDBLog> *);
};

#endif // STATS_H
