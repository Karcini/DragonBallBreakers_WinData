#include "readlinedblog.h"

ReadLineDBLog::ReadLineDBLog()
{
    data.clear();
    raider = new Raider();
    matchTurnout = new MatchTurnout();
    //qDebug() << "values initialized"; //This occurs every DBline
}

//This function is very hard coded for the specifics in amount of data, and type of data
void ReadLineDBLog::parseLine(QString line)
{
    //Split line to QStringList
    data = line.split("\t");
    qDebug() << line;

    //check if data is a proper line of data by iterating through all raiders (the 1st data kept on line of txt)
    for(int x = 0; x < raider->raiderList.size(); x++)
    {
        if(raider->raiderList[x] == data[0])
        {
            //Line is a proper line of data
                //I didn't do this here

            //Use this line to set raider in raider.h
            raider->record_Raider(data[0]);

            //Use this line to set values to each data point in matchturnout.h
            matchTurnout->recordAllStats(data);
        }
    }
}

//This function reads a single line of code and returns a QString of the line
QString ReadLineDBLog::getStringLine() const
{
    //Alternatively just print out QString data

    //1st line, raider stats
    QString str = raider->raiderCharacterName + "\tAcc. Level: "
            + QString::number(matchTurnout->m_raiderAccLvl) + "\t";
    if(matchTurnout->m_raiderWon)
        str += "Win\t";
    else
        str += "Lost\t";
    if(matchTurnout->m_raiderHP != -1)
        str += "HP_" + QString::number(matchTurnout->m_raiderHP);
    str += "\n";


    //2nd line, stm turnouts
    str += "\tSTM INFO\t\t";
    if(matchTurnout->m_STMbroken) //stm was called, but broken
        str += "Called - Broken\t";
    else if(matchTurnout->m_STMstatus) //stm was called
        str += "Called\t";
    else
        str += "Not Called\t";
    if(matchTurnout->m_STMcharged != -1)
        str += "Charged: " + QString::number(matchTurnout->m_STMcharged) + "%";
    str += "\n";


    //3rd line, wish turnouts
    str += "\tWISH INFO\t\t";
    if(matchTurnout->m_wishCalled) //survivors made a wish
        str += "Wish: Survivors\t";
    else if(matchTurnout->m_wishStatus) //non survivor made a wish
        str += "Wish: Raider\t";
    else                                //No wish
        str += "Wish: None\t";
    str+= "\n";


    //4th 5th line
    if(matchTurnout->m_raiderLvlAtSTM != -1)
        str += "\tAt STM START\t\tRaider Lvl: " + QString::number(matchTurnout->m_raiderLvlAtSTM) +
                "\tSurvivors Remaining: " + QString::number(matchTurnout->m_survRemainingAtSTM) + "\n";

    str += "\tAt END GAME\t\tRaider Lvl: " + QString::number(matchTurnout->m_raiderLvlAtEnd) +
            "\tSurvivors Remaining: " + QString::number(matchTurnout->m_survRemainingAtEnd) + "\n";


    //return string
    return str;
}
