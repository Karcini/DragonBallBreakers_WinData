#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include "parsetext.h"
#include "stats.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void refreshInformation();
    void getTextFromFile();
    void submitSelection();
    void clearSelection();

    void addCellStats();
    void addFriezaStats();
    void addBuuStats();
    void addVegetaStats();
    void addGinyuStats();

private:
    Ui::MainWindow *ui;
    QTextEdit * display_main;
    ParseText textReader;
    QStringList selectedRaiders;
    QList<int> statList;
    QList<ReadLineDBLog> * data;

    void parseData();
    void lockSelectionsBeforeData();
    void releaseSelectionsAfterData();
};
#endif // MAINWINDOW_H
