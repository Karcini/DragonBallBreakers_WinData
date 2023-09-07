#include "parsetext.h"

ParseText::ParseText()
{
    data = new QList<ReadLineDBLog>; //make list pointer to data
    text = "";
}
ParseText::~ParseText()
{
    delete data; //delete pointer
}

//Every time the file is Refreshed, it is Re-Read
void ParseText::parseTextFromFile()
{
    resetData();

    QString text_display = "";
    QFile file("../DragonBallBreakers_WinData/dblog.txt");    //Original Line
    //QFile file("dblog.txt");                                    //Absolute Path
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug() << "Could not open file";
    }
    else
    {
        //Read File
        QTextStream in(&file);

        while(!in.atEnd())
        {
            //Read line from txt file
            QString lineStr = in.readLine();
            //add to display
            text_display += lineStr + "\n";

            //Parse Line
            ReadLineDBLog line;
            line.parseLine(lineStr);
            data->append(line);
        }
    }
    file.close();

    text = text_display;
}
void ParseText::resetData()
{
    data->clear();
    text = "";
}

QString ParseText::getText()                 {return text;}
QList<ReadLineDBLog> * ParseText::getData()  {return data;}


