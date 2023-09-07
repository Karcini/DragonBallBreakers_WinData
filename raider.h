#ifndef RAIDER_H
#define RAIDER_H

#include <QStringList>
#include <QMetaEnum>
#include <QDebug>
#include "datanamespace.h"

//Contains Stringlist of raiders, assigns this objects int as the selected raider
class Raider
{
public:
    Raider();
    void record_Raider(QString);

    //DataNamespace
    QStringList raiderList;

    //raider vairables
    int raiderCharacter;
    QString raiderCharacterName;

private:
    void populateRaiders();
};

#endif // RAIDER_H

