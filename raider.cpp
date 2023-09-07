#include "raider.h"

//Fuck it hard code time
Raider::Raider()
{
    raiderCharacter = -1;
    populateRaiders();
}
void Raider::populateRaiders()
{
    //raiderList.append("Cell");
    //raiderList.append("Frieza");
    //raiderList.append("Buu");
    //raiderList.append("Vegeta");
    //raiderList.append("Ginyu");

    //Iterate through enum in datanamespace to populate QStringList raiderList

        //for an enum Raiders named 'raider' set to the 1st value
    for(DataNamespace::Raiders raider = static_cast<DataNamespace::Raiders>(0);
        //as long as 'raider' does not equal the the max length of enum
        raider!=DataNamespace::Raiders::Length_Raiders;
        //make 'raider' equal to it's int value static casted as an int, + 1, and static casted as a Raiders
        raider = static_cast<DataNamespace::Raiders>(static_cast<int>(raider)+1))

    {
        //Create a QMetaEnum of the QMeta Object System called Raiders within DataNamespace
        QMetaEnum me = QMetaEnum::fromType<DataNamespace::Raiders>();

        //save the string of character values at the static casted index 'raider'
        const char * str = me.valueToKey(static_cast<int>(raider));

        //convert to QString
        QString r = static_cast<QString>(str);

        //Use the QString info, Append the raider list
        raiderList.append(r);
    }
}
void Raider::record_Raider(QString r)
{
    //function called to record raider from dblog
    for(int x=0; x<raiderList.size(); x++)
    {
        if(r == raiderList[x])
        {
            raiderCharacterName = r;    //save raider by name
            raiderCharacter = x;        //save raider by position in raider list
            qDebug() << raiderCharacterName << " Recorded";
        }
    }
}


