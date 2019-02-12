#ifndef RECORDSFORM_H
#define RECORDSFORM_H

#include <QtWidgets>
#include "QtSql/QSqlDatabase"
#include "QSqlQuery"
#include "QSqlError"

namespace Ui {
class RecordsForm;
}

class RecordsForm : public QWidget
{
    Q_OBJECT

public:
    explicit RecordsForm(QWidget *parent = nullptr);
    ~RecordsForm();

private:
    Ui::RecordsForm *ui;
    QPushButton* exitgame;
    QVBoxLayout* layout;
    QSqlDatabase db;
    QLabel* labelRecords;
    QPushButton* clearButton;

public slots:
     void exitGame();
     void recieveRecord(int rec);
     void showRecords();
     void clearRecords();

signals:
     void signalExit();
};

#endif // RECORDSFORM_H
