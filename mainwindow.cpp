#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QApplication>
#include <QtCore>
#include <QFileDialog>
#include <QLabel>
#include <opencv2/opencv.hpp>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    _evol(new EvolveThread())
{
    ui->setupUi(this);

    // models' initialization
    _modelGenerations = new QStandardItemModel(this);
    ui->tableView_Generations->setModel(_modelGenerations);

    _modelIndividuals = new QStandardItemModel(this);
    QStringList strList;
    strList.append("fitness");
    strList.append("genotype");
    _modelIndividuals->setHorizontalHeaderLabels(strList);
    ui->tableView_Individuals->setModel(_modelIndividuals);


    // connect Table View click signal and slot
    connect(ui->tableView_Individuals, SIGNAL(clicked(QModelIndex)),
            this, SLOT(tableview_individuals_clicked(QModelIndex)));
    connect(ui->tableView_Generations, SIGNAL(clicked(QModelIndex)),
            this, SLOT(tableview_generations_clicked(QModelIndex)));

    connect(this, SIGNAL(openOriginFile(QString)), _evol, SLOT(setOriginFilename(QString)));
    connect(this, SIGNAL(openTargetFile(QString)), _evol, SLOT(setTargetFilename(QString)));


    on_setGPLogDir("");
}

MainWindow::~MainWindow()
{
    if(_evol)
    {
        _evol->terminate();
        delete _evol;
        _evol = NULL;
    }
    delete ui;
}

void MainWindow::on_actionStart_Evolving_triggered(bool checked)
{
    if(checked)
    {
        _evol->start();
    }
    else
    {
        _evol->terminate();

    }
}


void MainWindow::on_actionOpen_Origin_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this, "Open Origin File");
    if (filename == "")
        return;
    else
    {
        ui->label_origin->setPixmap(QPixmap(filename).scaled(ui->label_origin->width(),ui->label_origin->height(),Qt::KeepAspectRatio));
        emit openOriginFile(filename);
    }

}

void MainWindow::on_actionOpen_Target_triggered()
{
    QString filename = QFileDialog::getOpenFileName(this, "Open Evolving Targe File");
    if (filename == "")
        return;
    else
    {
        ui->label_target->setPixmap(QPixmap(filename).scaled(ui->label_target->width(),ui->label_target->height(),Qt::KeepAspectRatio));
        emit openTargetFile(filename);
    }
}

void MainWindow::tableview_individuals_clicked(QModelIndex index)
{
    QStandardItem *item = _modelIndividuals->itemFromIndex(index);
    qDebug() << "clicked signal";
    qDebug() << item->text();
    ui->textEdit_Genotype->clear();
    ui->textEdit_Genotype->setText(item->text().trimmed());
}

void MainWindow::tableview_generations_clicked(QModelIndex index)
{
    QStandardItem *item = _modelGenerations->itemFromIndex(index);
    item->column();
    qDebug() << "clicked signal";
    qDebug() << item->text();

    QDomDocument doc;
    QString filename = _strLogDir + "/" + item->text();
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly))
    {   qDebug() << "Fail to open file...";
        return;
    }
    if (!doc.setContent(&file)) {
        qDebug() << "Fail to populize domdocument...";
        file.close();
        return;
    }
    file.close();

    // clear old model
    _modelIndividuals->clear();

    // initialize view header
    QStringList strList;
    strList.append("Fitness");
    strList.append("Size");
    strList.append("Depth");
    strList.append("Genotype");
    _modelIndividuals->setHorizontalHeaderLabels(strList);

    // get individuals
    QDomNodeList individuals = doc.elementsByTagName("Individual");

    // for each individual get fitness value and genotype
    for(int i = 0; i < individuals.size(); i++)
    {
        QDomElement elem = individuals.at(i).firstChildElement();

        // add individual index
        QList<QStandardItem *> items;

        while (!elem.isNull())
        {

            if ( elem.tagName() == "Fitness" ) {
                items.append(new QStandardItem(elem.text()));
            }

            if ( elem.tagName() == "Genotype" ) {
                items.append(new QStandardItem( elem.attribute("size") ));
                items.append(new QStandardItem( elem.attribute("depth") ));
                QString str;
                QTextStream stream(&str);
                stream << elem.firstChildElement();
                stream.flush();
                items.append(new QStandardItem( str.trimmed() ));
            }
            elem = elem.nextSiblingElement();
        }
        _modelIndividuals->appendRow(items);
    }
    ui->tableView_Individuals->resizeColumnsToContents();
    ui->tableView_Individuals->sortByColumn(0);
}

void MainWindow::on_setGPLogDir(QString dirname)
{
    if ( dirname.isEmpty() )
    {
        qDebug() << "No dir is selected \n Using Current Directory";
        _strLogDir = QDir::currentPath();
    }
    else
    {
        _strLogDir = dirname;
    }

    qDebug() << "Directory " << _strLogDir << " selected";

    // clear old model
    _modelGenerations->clear();

    // initialize view header
    QStringList generationList;
    generationList.append("generation milestone");
    _modelGenerations->setHorizontalHeaderLabels(generationList);

    QDir qDir(_strLogDir);
    QStringList filters;

    // set generations' files
    // get the largest generation
    filters << "beagle_g?.obm";
    QStringList entries = qDir.entryList(filters);
    for( int i = 0; i < entries.size(); i++ ) {
        QStandardItem * item = new QStandardItem;
        item->setText(entries.at(i));
        _modelGenerations->appendRow(item);
    }

    filters.clear();
    filters << "beagle_g??.obm";
    entries = qDir.entryList(filters);
    for( int i = 0; i < entries.size(); i++ ) {
        QStandardItem * item = new QStandardItem;
        item->setText(entries.at(i));
        _modelGenerations->appendRow(item);
    }

    filters.clear();
    filters << "beagle_g???.obm";
    entries = qDir.entryList(filters);
    for( int i = 0; i < entries.size(); i++ ) {
        QStandardItem * item = new QStandardItem;
        item->setText(entries.at(i));
        _modelGenerations->appendRow(item);
    }

    // set log file
    //setLogFile(_strLogDir + "/beagle.log");
}
