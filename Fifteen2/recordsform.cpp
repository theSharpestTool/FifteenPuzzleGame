#include "recordsform.h"
#include "ui_recordsform.h"

#include "mainwindow.h"
#include "ui_mainwindow.h"


RecordsForm::RecordsForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RecordsForm)
{
    ui->setupUi(this);

    exitgame = new QPushButton("Exit");
    exitgame->setFixedSize(1080,200);
    exitgame->setStyleSheet(QString("font-size: %1px").arg(80));
    connect(exitgame, SIGNAL(clicked()), this, SLOT(exitGame()));

    QString appData = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QString fileName = appData + "/fifteenRecords.db";

    if(QFile::exists(fileName))
        qDebug() << "file exists";
    else
    {
        qDebug() << "file not exists";
        QFile file(":/gelik/fifteenRecords.db");
        if( file.copy(fileName) )
             QFile::setPermissions( fileName, QFile::WriteOwner | QFile::ReadOwner );
    }

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(fileName);

    if(!db.open()){
    qDebug()<< "DB_NOT_OPEN";
    }

    labelRecords = new QLabel;
    labelRecords->setStyleSheet(QString("font-size: %1px").arg(80));
    showRecords();

    clearButton = new QPushButton("Clear");
    clearButton->setFixedSize(1080,200);
    clearButton->setStyleSheet(QString("font-size: %1px").arg(80));
    connect(clearButton, SIGNAL(clicked()), this, SLOT(clearRecords()));

    layout = new QVBoxLayout;
    layout->addWidget(clearButton);
    layout->addWidget(labelRecords);
    layout->addStretch(1);
    layout->addWidget(exitgame);
    layout->setContentsMargins(0,0,0,0);

    setLayout(layout);
}

RecordsForm::~RecordsForm()
{
    delete ui;
}

void RecordsForm::exitGame()
{
    this->hide();
    emit signalExit();
}

void RecordsForm::recieveRecord(int rec)
{
    QSqlQuery query;
    query.prepare("INSERT INTO Records (record) VALUES (:reco)");
    query.bindValue(":reco", rec);
    if(!query.exec())
        qDebug() << query.lastError().text();

    showRecords();
}

void RecordsForm::showRecords()
{
    QSqlQuery query;
    query.exec("SELECT record FROM Records ORDER BY record ASC");

    QString allRecords;
    int counter = 1;
    while(query.next())
    {
        QString record = query.value(0).toString();
        allRecords += QString::number(counter) + ".  " + record + "\n";
        counter++;
    }
    qDebug() << "all" << allRecords;

    labelRecords->setText(allRecords);
}

void RecordsForm::clearRecords()
{
    QSqlQuery query;
    if(!query.exec("DELETE FROM Records"))
        query.lastError().text();
    showRecords();
}
