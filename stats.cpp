#include "stats.h"

Stats::Stats()
{

}

QString Stats::winLossRate(QList<int> raiderList, QList<ReadLineDBLog> * allData)
{
    QString formData = "";
    //Choose specific data within data
    QList<ReadLineDBLog> * data = new QList<ReadLineDBLog>;
    for(int x=0; x<allData->size(); x++)
    {
        for(int raider=0; raider<raiderList.size(); raider++)
        {
            if(allData->at(x).raider->raiderCharacter == raiderList[raider])
            {
                //qDebug() << "Detected  " << QString::number(allData->at(x).raider->raiderCharacter) << " = " << QString::number(raiderList[raider])
                //         << "    in position " << QString::number(x) << " -> " << allData->at(x).raider->raiderCharacterName;
                data->append(allData->at(x));
                formData += allData->at(x).getStringLine() + "\n";
            }
        }
    }

    //Get Strings from specified data
    QStringList output;
    output.append(getLine_WinRate(data));
    output.append(getLine_LossRate(data));
    output.append(getLine_wishSummonRate(data));
    output.append(getLine_stmSummonRate(data));
    output.append(getLine_endGameStats(data));


    //Format Output
    QString out;
    for(QString s : output)
        out += s;
    //Format Single line data
    out += "\n\n--------------------------------------------------------------------------------------------\n";
    out += formData;


    data->clear();
    delete data;


    return out;
}
QString Stats::getLine_WinRate(QList<ReadLineDBLog> * data)
{
    //Calculate Stats
    int total = data->size();
    int wins = 0, stmBroken=0;
    for(int x=0; x<data->size(); x++)
    {
        if(data->at(x).matchTurnout->m_raiderWon)
        {
            wins++;
            if(!data->at(x).matchTurnout->m_lossReason) //didn't lose by STM
            {
                if(data->at(x).matchTurnout->m_STMbroken) //but managed to break machine
                    stmBroken++;
            }
        }
    }
    double winrate = ( static_cast<double>(wins)/static_cast<double>(total) ) * 100;
    double stmBreakRate = ( static_cast<double>(stmBroken)/static_cast<double>(wins) ) * 100;

    //Assign strings
    QString raiderWinRate = QString::number(wins) + " games won out of "
            + QString::number(total) + "\t\t: " + QString::number(winrate) + "%";
    QString raiderSTMbreak = "Rate raiders breaks the STM on victory\t: " + QString::number(stmBreakRate) + "%";

    //Format Output
    QString output = "Win Rates\n\t" + raiderWinRate + "\n\t" + raiderSTMbreak + "\n\n";
    return output;
}
QString Stats::getLine_LossRate(QList<ReadLineDBLog> * data)
{
    //Calculate Stats
    int total = data->size();
    int loss = 0, lossByHP=0, lossBySTM=0, stmBroken=0;
    for(int x=0; x<data->size(); x++)
    {
        if(!data->at(x).matchTurnout->m_raiderWon)
        {
            loss++;
            if(data->at(x).matchTurnout->m_lossReason) //STM if true
            {
                lossBySTM++;
                if(data->at(x).matchTurnout->m_STMbroken)
                    stmBroken++;
            }
            else    //only other loss condition is HP
                lossByHP++;
        }
    }
    double lossrate = ( static_cast<double>(loss)/static_cast<double>(total) ) * 100;
    double lossByHpRate = ( static_cast<double>(lossByHP)/static_cast<double>(loss) ) * 100;
    double lossByStmRate = ( static_cast<double>(lossBySTM)/static_cast<double>(loss) ) * 100;
    double stmBreakRate = ( static_cast<double>(stmBroken)/static_cast<double>(loss) ) * 100;

    //Assign strings
    QString raiderLossRate = QString::number(loss) + " games lost out of "
            + QString::number(total) + "\t\t: " + QString::number(lossrate) + "%";
    QString raiderLossHP = "Rate of losses by HP loss\t\t: " + QString::number(lossByHpRate) + "%";
    QString raiderLossSTM = "Rate of losses by STM erasure\t\t: " + QString::number(lossByStmRate) + "%";
    QString raiderSTMbreak = "Rate raiders break the STM on loss\t: " + QString::number(stmBreakRate) + "%";

    //Format Output
    QString output = "Loss Rates\n\t" + raiderLossRate + "\n\t" + raiderLossHP + "\n\t"
            + raiderLossSTM + "\n\t" + raiderSTMbreak + "\n\n";
    return output;
}
QString Stats::getLine_stmSummonRate(QList<ReadLineDBLog> * data)
{
    //Calculate Stats
    int total = data->size();
    int stmSummoned=0, stmBroken=0;
    int sumOf_raiderLvls=0, sumOf_remainingSurv=0, validPoints=0;
    int raidlv1=0, raidlv2=0, raidlv3=0, raidlv4=0;
    for(int x=0; x<data->size(); x++)
    {
        int lv_atX = data->at(x).matchTurnout->m_raiderLvlAtSTM;

        if(data->at(x).matchTurnout->m_STMbroken) //if STM was summoned and broken
        {
            stmSummoned++;
            stmBroken++;
            if(lv_atX != -1)
            {
                sumOf_raiderLvls += lv_atX;
                sumOf_remainingSurv += data->at(x).matchTurnout->m_survRemainingAtSTM;
                validPoints ++;
                if(lv_atX == 1)
                    raidlv1++;
                else if(lv_atX == 2)
                    raidlv2++;
                else if(lv_atX == 3)
                    raidlv2++, raidlv3++;
                else if(lv_atX == 4)
                    raidlv2++, raidlv3++, raidlv4++;
            }
        }
        else if (data->at(x).matchTurnout->m_STMstatus) //if STM was summoned
        {
            stmSummoned++;
            if(lv_atX != -1)
            {
                sumOf_raiderLvls += lv_atX;
                sumOf_remainingSurv += data->at(x).matchTurnout->m_survRemainingAtSTM;
                validPoints ++;
                if(lv_atX == 1)
                    raidlv1++;
                else if(lv_atX == 2)
                    raidlv2++;
                else if(lv_atX == 3)
                    raidlv2++, raidlv3++;
                else if(lv_atX == 4)
                    raidlv2++, raidlv3++, raidlv4++;
            }
        }
    }
    double stmSummmonR = ( static_cast<double>(stmSummoned)/static_cast<double>(total) ) * 100;
    double stmBreakR = ( static_cast<double>(stmBroken)/static_cast<double>(stmSummoned) ) * 100;
    int avgSurvRemain = qRound( static_cast<double>(sumOf_remainingSurv)/static_cast<double>(validPoints) );
    int avgRaiderLvl = qRound( static_cast<double>(sumOf_raiderLvls)/static_cast<double>(validPoints) );
    double raidAtlv1 = (static_cast<double>(raidlv1)/static_cast<double>(validPoints)) * 100;
    double raidAtlv2 = (static_cast<double>(raidlv2)/static_cast<double>(validPoints)) * 100;
    double raidAtlv3 = (static_cast<double>(raidlv3)/static_cast<double>(validPoints)) * 100;
    double raidAtlv4 = (static_cast<double>(raidlv4)/static_cast<double>(validPoints)) * 100;

    //Assign strings
    QString stmPosText = "Rates when STM is Called";
    QString stmSummonRate = "Rate the STM is summoned\t\t: " + QString::number(stmSummmonR) + "%";
    QString stmBreakRate = "Rate the STM is broken\t\t: " + QString::number(stmBreakR) + "%";
    QString amountSurvAtSTM = "Avg. Remaining survivors at STM arrival\t: #_" + QString::number(avgSurvRemain);
    QString lvlRaiderAtSTM = "Avg. raider lvl at STM arrival\t\t: Lvl_" + QString::number(avgRaiderLvl);
    QString rateRaidAtLv1 = "Rate raider stays Lvl_1 by STM arrival\t: " + QString::number(raidAtlv1) + "%";
    QString rateRaidAtLv2 = "Rate raider reaches Lvl_2 by STM arrival\t: " + QString::number(raidAtlv2) + "%";
    QString rateRaidAtLv3 = "Rate raider reaches Lvl_3 by STM arrival\t: " + QString::number(raidAtlv3) + "%";
    QString rateRaidAtLv4 = "Rate raider reaches Lvl_4 by STM arrival\t: " + QString::number(raidAtlv4) + "%";


    //Format Output
    QString output = stmPosText + "\n\t" + stmSummonRate + "\n\t" + stmBreakRate + "\n\n\t"
            + amountSurvAtSTM + "\n\t" + lvlRaiderAtSTM + "\n\t"
            + rateRaidAtLv1 + "\n\t" + rateRaidAtLv2 + "\n\t" + rateRaidAtLv3 + "\n\t" + rateRaidAtLv4 + "\n\n" ;
    return output;
}
QString Stats::getLine_wishSummonRate(QList<ReadLineDBLog> * data)
{
    //Calculate Stats
    int total = data->size();
    int wishesMade=0, survivorWished = 0, raiderWished=0, lv4SurvLives=0;
    for(int x=0; x<data->size(); x++)
    {
        if(data->at(x).matchTurnout->m_wishCalled) //true if survivors wished
        {
            wishesMade++;
            survivorWished++;
            if(data->at(x).matchTurnout->m_wishStatus) //true if lv4 survivor lived
            {
                lv4SurvLives++;
            }
        }
        else if(data->at(x).matchTurnout->m_wishStatus) //a wish was called by non survivors
        {
            wishesMade++;
            raiderWished++;
        }
    }
    double wishSummonRate = ( static_cast<double>(wishesMade)/static_cast<double>(total) ) * 100;
    double survivorWishRate = ( static_cast<double>(survivorWished)/static_cast<double>(wishesMade) ) * 100;
    double lv4SurvivalRate = ( static_cast<double>(lv4SurvLives)/static_cast<double>(survivorWished) ) * 100;
    double raiderWishRate = ( static_cast<double>(raiderWished)/static_cast<double>(wishesMade) ) * 100;

    //Assign strings
    QString wishSummons = "Rate Shenron is summoned\t\t: " + QString::number(wishSummonRate) + "%";
    QString survivorWishSummons = "Rate the survivors wished\t\t: " + QString::number(survivorWishRate) + "%";
    QString survivorlv4LiveRate = "Rate the lv4 survivor Lived\t\t: " + QString::number(lv4SurvivalRate) + "%";
    QString raiderWishSummons = "Rate the raider wished\t\t: " + QString::number(raiderWishRate) + "%";

    //Format Output
    QString output = "Overall Wish Rates\n\t" + wishSummons + "\n\t" + raiderWishSummons + "\n\t"
            + survivorWishSummons + "\n\t" + survivorlv4LiveRate + "\n\n";
    return output;
}
QString Stats::getLine_endGameStats(QList<ReadLineDBLog> * data)
{
    //Calculate Stats
    //int total = data->size();
    int sumOf_raiderLvls=0, sumOf_remainingSurv=0, sumOf_stmCharge=0, sumOf_raiderHP=0;
    int validEndgameStat=0, validPercentageStat=0;
    int raidlv1=0, raidlv2=0, raidlv3=0, raidlv4=0;
    for(int x=0; x<data->size(); x++)
    {
        int lv_atX = data->at(x).matchTurnout->m_raiderLvlAtEnd;
        int stm_atX = data->at(x).matchTurnout->m_STMcharged;

        if(lv_atX != -1)
        {
            validEndgameStat++;
            sumOf_raiderLvls += data->at(x).matchTurnout->m_raiderLvlAtEnd;
            sumOf_remainingSurv += data->at(x).matchTurnout->m_survRemainingAtEnd;
            if(lv_atX == 1)
                raidlv1++;
            else if(lv_atX == 2)
                raidlv2++;
            else if(lv_atX == 3)
                raidlv2++, raidlv3++;
            else if(lv_atX == 4)
                raidlv2++, raidlv3++, raidlv4++;
        }
        if(stm_atX != -1)
        {
            validPercentageStat++;
            sumOf_raiderHP += data->at(x).matchTurnout->m_raiderHP;
            sumOf_stmCharge += data->at(x).matchTurnout->m_STMcharged;
        }
    }
    int avgRaiderLvl = qRound( static_cast<double>(sumOf_raiderLvls)/static_cast<double>(validEndgameStat) );
    int avgSurvRemain = qRound( static_cast<double>(sumOf_remainingSurv)/static_cast<double>(validEndgameStat) );
    int avgSTMcharge = qRound( static_cast<double>(sumOf_stmCharge)/static_cast<double>(validPercentageStat) );
    int avgRaiderHP = qRound( static_cast<double>(sumOf_raiderHP)/static_cast<double>(validPercentageStat) );
    double raidAtlv1 = (static_cast<double>(raidlv1)/static_cast<double>(validEndgameStat)) * 100;
    double raidAtlv2 = (static_cast<double>(raidlv2)/static_cast<double>(validEndgameStat)) * 100;
    double raidAtlv3 = (static_cast<double>(raidlv3)/static_cast<double>(validEndgameStat)) * 100;
    double raidAtlv4 = (static_cast<double>(raidlv4)/static_cast<double>(validEndgameStat)) * 100;

    //Assign strings
    QString endGamePosText = "Rates when Game Ends";
    QString stmCheckpoint = "Avg. STM charge checkpoint reached\t: STM_" + QString::number(avgSTMcharge) + "%";
    QString raiderRemainingHP = "Avg. raider HP at Endgame\t\t: HP_" + QString::number(avgRaiderHP) + "%";
    QString amountSurvAtEnd = "Avg. Remaining survivors at Endgame\t: #_" + QString::number(avgSurvRemain);
    QString lvlRaiderAtEnd = "Avg. raider lvl at Endgame\t\t: Lvl_" + QString::number(avgRaiderLvl);
    QString rateRaidAtLv1 = "Rate raider stays Lvl_1 by End of Game\t: " + QString::number(raidAtlv1) + "%";
    QString rateRaidAtLv2 = "Rate raider reaches Lvl_2 by End of Game\t: " + QString::number(raidAtlv2) + "%";
    QString rateRaidAtLv3 = "Rate raider reaches Lvl_3 by End of Game\t: " + QString::number(raidAtlv3) + "%";
    QString rateRaidAtLv4 = "Rate raider reaches Lvl_4 by End of Game\t: " + QString::number(raidAtlv4) + "%";

    //Format Output
    QString output = endGamePosText + "\n\t" + stmCheckpoint + "\n\t" + raiderRemainingHP + "\n\n\t"
            + amountSurvAtEnd + "\n\t" + lvlRaiderAtEnd + "\n\t"
            + rateRaidAtLv1 + "\n\t" + rateRaidAtLv2 + "\n\t" + rateRaidAtLv3 + "\n\t" + rateRaidAtLv4 + "\n\n" ;
    return output;
}
