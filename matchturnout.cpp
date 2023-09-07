#include "matchturnout.h"

MatchTurnout::MatchTurnout()
{
    infoValid = true;
    populateLogList();
}
void MatchTurnout::populateLogList()
{
    //QMetaEnum me = QMetaEnum::fromType<DataNamespace::DBLog>();

    for(DataNamespace::DBLog log = static_cast<DataNamespace::DBLog>(0);
        //as long as 'log' does not equal the the max length of enum DBLog
        log!=DataNamespace::DBLog::Length_DBLog;
        //make 'log' equal to it's int value staticly casted as an int, + 1, and static casted as a DBLog
        log = static_cast<DataNamespace::DBLog>(static_cast<int>(log)+1))
    {
        //Create a QMetaEnum of the QMeta Object System called Raiders within DataNamespace
        QMetaEnum me = QMetaEnum::fromType<DataNamespace::DBLog>();

        //save the string of character values at the staticly casted index 'log'
        const char * str = me.valueToKey(static_cast<int>(log));

        //convert to QString
        QString l = static_cast<QString>(str);

        //Use the QString info, Append the raider list
        dbLogList.append(l);
    }
}
DataNamespace::DBLog MatchTurnout::getNamespaceValue(QString dataPoint)
{
    for(int x=0; x<dbLogList.size(); x++)
    {
        if(dataPoint == dbLogList[x])
        {
            //qDebug() << dataPoint << "  was found =   " << dbLogList[x] << " " << x;
            DataNamespace::DBLog dbVal = DataNamespace::DBLog(x);
            return dbVal;
        }
    }
    return DataNamespace::DBLog::Length_DBLog; //this should not be reached
}

bool MatchTurnout::validator(DataNamespace::DBLog vtrue, DataNamespace::DBLog vfalse, QString dataPoint, bool * boolVal)
{
    DataNamespace::DBLog dp = getNamespaceValue(dataPoint);
    if(vtrue == dp)
        return true;        //info yields a TRUE response, but data is correct
    else if(vfalse == dp)
        return false;       //info yields a FALSE response, but data is correct
    else
        *boolVal = false;  //info yields NEITHER repsonse, data is incorrect

    return false;   //default return value
}
int MatchTurnout::validator(int min, int max, QString dataPoint, bool * boolVal)
{
    //Regular Expression, check for any amount of any digits
        //  '\' to identify the next symbol, digits symbol '\d', '*' .. for any amount of instances
    QRegExp re("\\d*");

    //If dataPoint is a digit
    if(re.exactMatch(dataPoint))
    {
        int num = dataPoint.toInt();
        if(num>=min && num <=max)
            return num; //tested datapoint yields an int between correct values
    }
    //otherwise...
    *boolVal = false;
    return -1;  //default return value
}

void MatchTurnout::recordAllStats(QStringList data)
{
    m_raiderAccLvl = validator(1, 100, data[1], &infoValid);         //data[1]   int 1~100
    m_raiderWon = validator(DataNamespace::DBLog::lived, DataNamespace::DBLog::died, data[2], &infoValid);
    m_lossReason = validator(DataNamespace::DBLog::STM, DataNamespace::DBLog::HP, data[3], &infoValid);

    m_STMstatus = validator(DataNamespace::DBLog::yes, DataNamespace::DBLog::no, data[4], &infoValid);
    if(!m_STMstatus)
    {
        //check if true stm was summoned, but broken
        m_STMstatus = validator(DataNamespace::DBLog::broken, DataNamespace::DBLog::no, data[4], &infoValid);
        //validator returned that STM wasn't just summoned, but also broken
        if(m_STMstatus)
            m_STMbroken = true;
    }

    m_raiderLvlAtSTM = validator(1, 4, data[5], &infoValid);       //data[5]   int 1~4
    m_raiderLvlAtEnd = validator(1, 4, data[6], &infoValid);       //data[6]   int 1~4
    m_survRemainingAtSTM = validator(1, 7, data[7], &infoValid);   //data[7]   int 1~7
    m_survRemainingAtEnd = validator(0, 7, data[8], &infoValid);   //data[8]   int 0~7
    m_wishCalled = validator(DataNamespace::DBLog::surv, DataNamespace::DBLog::raider, data[9], &infoValid);
    m_wishStatus = validator(DataNamespace::DBLog::on, DataNamespace::DBLog::off, data[10], &infoValid);

    m_STMcharged = validator(0, 100, data[11], &infoValid);           //data[11]  int 0~100 by rounded %
    m_raiderHP = validator(0, 100, data[12], &infoValid);             //data[12]  int 0~100 by rounded %


    if(infoValid)
    {
        qDebug() << "ALL INFO VALID FOR THIS SET";
        /*
        tabulateMatch(raiderAccLvl, raiderVictory, lossReason,STMstatus, raiderLvAtSTM,
                       raiderLvAtEnd, survRemainingAtSTM, survRemainingAtEnd,
                       wishCalled, wishStatus, STMcharged, raiderHP);
        */
    }
}



//RECORD STATS
void MatchTurnout::record_RaiderVictory(int num)                                   //died, lived
{
    if(num == static_cast<int>(DataNamespace::DBLog::died) )
        m_raiderWon = false;
    else if(num == static_cast<int>(DataNamespace::DBLog::lived) )
        m_raiderWon = true;
}
void MatchTurnout::record_RaiderAccLvl(int num)      {m_raiderAccLvl = num;}       //values 1~100
void MatchTurnout::record_LossReason(int num)        {m_lossReason = num;}         //HP, STM
void MatchTurnout::record_STMstatus(int num)         {m_STMstatus = num;}          //yes, no, broken
void MatchTurnout::record_RiaderLvAtSTM(int num)     {m_raiderLvlAtSTM = num;}     //values 1~4
void MatchTurnout::record_RaiderLvAtEnd(int num)     {m_raiderLvlAtEnd = num;}     //values 1~4
void MatchTurnout::record_SurvRemainAtSTM(int num)   {m_survRemainingAtSTM = num;} //values 1~7
void MatchTurnout::record_SurvRemainAtEnd(int num)   {m_survRemainingAtEnd = num;} //values 0~7
void MatchTurnout::record_WishCalledBy(int num)      {m_wishCalled = num;}         //surv, raider
void MatchTurnout::record_WishStatus(int num)        {m_wishStatus = num;}         //on, off
void MatchTurnout::record_STMcharge(int num)         {m_STMcharged = num;}         //values 0~100 in factors of 25
void MatchTurnout::record_RaiderHP(int num)          {m_raiderHP = num;}           //values 0~100 in factors of 10

void MatchTurnout::tabulateMatch(int v1,int v2,int v3,int v4,int v5,int v6,int v7,int v8,int v9,int v10,int v11,int v12)
{
    record_RaiderAccLvl(v1);
    record_RaiderVictory(v2);
    record_LossReason(v3);
    record_STMstatus(v4);
    record_RiaderLvAtSTM(v5);
    record_RaiderLvAtEnd(v6);
    record_SurvRemainAtSTM(v7);
    record_SurvRemainAtEnd(v8);
    record_WishCalledBy(v9);
    record_WishStatus(v10);
    record_STMcharge(v11);
    record_RaiderHP(v12);
}
