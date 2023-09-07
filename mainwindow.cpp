#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    //Initializers
    ui->setupUi(this);
    display_main = ui->textEdit_display;
    lockSelectionsBeforeData();
    statList.clear();
    selectedRaiders.clear();

    //connections
    connect(ui->button_refresh, SIGNAL(clicked(bool)), this, SLOT(refreshInformation()));
    connect(ui->button_refreshDisplay, SIGNAL(clicked(bool)), this, SLOT(getTextFromFile()));
    connect(ui->button_submit, SIGNAL(clicked(bool)), this, SLOT(submitSelection()));
    connect(ui->button_clear, SIGNAL(clicked(bool)), this, SLOT(clearSelection()));

    connect(ui->button_cell, SIGNAL(clicked(bool)), this, SLOT(addCellStats()));
    connect(ui->button_frieza, SIGNAL(clicked(bool)), this, SLOT(addFriezaStats()));
    connect(ui->button_buu, SIGNAL(clicked(bool)), this, SLOT(addBuuStats()));
    connect(ui->button_vegeta, SIGNAL(clicked(bool)), this, SLOT(addVegetaStats()));
    connect(ui->button_ginyu, SIGNAL(clicked(bool)), this, SLOT(addGinyuStats()));
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::refreshInformation()
{
    //parse data
    textReader.parseTextFromFile();
    parseData();

    //release options on data having been read
    releaseSelectionsAfterData();

    qDebug() << "Information Refreshed!";
}
void MainWindow::getTextFromFile()
{
    if(textReader.getText() == "")
        display_main->setText("Please calculate information");
    else
        display_main->setText(textReader.getText());
}
void MainWindow::parseData()
{
    //separated by func in case we need other steps in parsing data (like adding a database)
    data = textReader.getData();
}

//HANDLE UI
void MainWindow::lockSelectionsBeforeData()
{
    ui->button_cell->setEnabled(false);
    ui->button_frieza->setEnabled(false);
    ui->button_buu->setEnabled(false);
    ui->button_vegeta->setEnabled(false);
    ui->button_ginyu->setEnabled(false);

    ui->button_submit->setEnabled(false);
    ui->button_clear->setEnabled(false);
}
void MainWindow::releaseSelectionsAfterData()
{
    ui->button_cell->setEnabled(true);
    ui->button_frieza->setEnabled(true);
    ui->button_buu->setEnabled(true);
    ui->button_vegeta->setEnabled(true);
    ui->button_ginyu->setEnabled(true);

    ui->button_submit->setEnabled(true);
    ui->button_clear->setEnabled(true);
}
//HANDLE LIST
void MainWindow::submitSelection()
{
    if(!statList.empty())
    {
        //Add selected raiders to string
        QString str = "Compiled Data for... ";
        for(int x=0; x<selectedRaiders.size(); x++)
        {
            str += selectedRaiders[x];
            if(x+1<selectedRaiders.size())
                str+= ", ";
        }
        str += "\n\n";

        //Add stats to string
        Stats v;
        str += v.winLossRate(statList, data);


        //display string
        display_main->setText(str);
    }
    else
        display_main->setText("Please select some raiders to calculate information");
}
void MainWindow::clearSelection()
{
    //reset values
    statList.clear();
    selectedRaiders.clear();

    //make all clicked buttons clickable again
    releaseSelectionsAfterData();

    //display feedback
    display_main->setText("Raider slection released");
}
//ADD RAIDERS TO STAT LIST
void MainWindow::addCellStats()
{
    display_main->setText("Cell added to selection");
    selectedRaiders.append("Cell");
    statList.append((int)DataNamespace::Raiders::Cell);
    ui->button_cell->setEnabled(false);
}
void MainWindow::addFriezaStats()
{
    display_main->setText("Frieza added to selection");
    selectedRaiders.append("Frieza");
    statList.append((int)DataNamespace::Raiders::Frieza);
    ui->button_frieza->setEnabled(false);
}
void MainWindow::addBuuStats()
{
    display_main->setText("Buu added to selection");
    selectedRaiders.append("Buu");
    statList.append((int)DataNamespace::Raiders::Buu);
    ui->button_buu->setEnabled(false);
}
void MainWindow::addVegetaStats()
{
    display_main->setText("Vegeta added to selection");
    selectedRaiders.append("Vegeta");
    statList.append((int)DataNamespace::Raiders::Vegeta);
    ui->button_vegeta->setEnabled(false);
}
void MainWindow::addGinyuStats()
{
    display_main->setText("Ginyu added to selection");
    selectedRaiders.append("Ginyu");
    statList.append((int)DataNamespace::Raiders::Ginyu);
    ui->button_ginyu->setEnabled(false);
}
