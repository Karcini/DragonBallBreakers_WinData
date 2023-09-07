#ifndef DATANAMESPACE_H
#define DATANAMESPACE_H

#include <QObject>

class DataNamespace : public QObject
{
    Q_OBJECT
public:
    //Values of data being kept in DBLog.txt
    enum DBLog{
        died,
        lived,

        HP,
        STM,

        yes,
        no,
        broken,

        surv,
        raider,

        on,
        off,

        Length_DBLog
    };
    Q_ENUM(DBLog) //register DBLog with Meta-Object System

    //Values of raiders eligible to contain stats
    enum class Raiders{
        Cell,
        Frieza,
        Buu,
        Vegeta,
        Ginyu,
        Length_Raiders
    };
    Q_ENUM(Raiders) //register Raiders with Meta-Object System

    //Raiders operator++ (Raiders& r);

    DataNamespace();
    virtual ~DataNamespace();

};

#endif // DATANAMESPACE_H
