#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include "Game.h"
class QHBoxLayout;
class QLabel;
class QLCDNumber;
class QSpinBox;
class QVBoxLayout;

namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = 0);
    ~Form();
public slots:
    void newGame();
    void exitGame();
    void changeMode();
    void setRecord();
    void gameOver();
private slots:
private:
    Ui::Form *ui;
    Game* game;
    QHBoxLayout* settingsLayout;
    QVBoxLayout* layout;
    QSpinBox* cubesize;
    QTimer* timer;
    QPushButton* mode;
    QLabel* record;
    int recordValue;
signals:
     void signalExit();
     void sendRecord(int rec);
};

#endif // FORM_H
