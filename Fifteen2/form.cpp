#include "form.h"
#include "ui_form.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QLCDNumber>
#include <QPushButton>
#include <QSpinBox>
#include <QTimer>
#include <QVBoxLayout>

Form::Form(QWidget *parent) : game(NULL),
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);

    layout = new QVBoxLayout(this);
    settingsLayout = new QHBoxLayout;

    QPushButton* newgame = new QPushButton("New Game");
    QPushButton* exitgame = new QPushButton("Exit");

    newgame->setFixedSize(530,200);
    newgame->setStyleSheet(QString("font-size: %1px").arg(80));
    exitgame->setFixedSize(530,200);
    exitgame->setStyleSheet(QString("font-size: %1px").arg(80));

    connect(newgame, SIGNAL(clicked()), this, SLOT(newGame()));
    connect(exitgame, SIGNAL(clicked()), this, SLOT(exitGame()));

    settingsLayout->setSpacing(20);
    settingsLayout->addWidget(newgame);
    settingsLayout->addWidget(exitgame);
    settingsLayout->setContentsMargins(0, 0, 0, 0);

    mode = new QPushButton("Classic");
    mode->setFixedSize(1080,200);
    mode->setStyleSheet(QString("font-size: %1px").arg(80));
    connect(mode, SIGNAL(clicked()), this, SLOT(changeMode()));

    layout->setContentsMargins(0, 0, 0, 0);
    layout->addLayout(settingsLayout);
    layout->addWidget(mode);

    record = new QLabel("0");
    record->setFixedSize(1080,200);
    record->setStyleSheet(QString("font-size: %1px").arg(100));
    record->setAlignment(Qt::AlignCenter);
    layout->addWidget(record);

    recordValue = 0;

    game = new Game(this); //рисуем новое поле
    connect(game, SIGNAL(incRecord()), this, SLOT(setRecord()));
    connect(game, SIGNAL(signalGameOver()), this, SLOT(gameOver()));

    layout->addWidget(game);

    QPushButton* buttonGameOver = new QPushButton("Game over");
    buttonGameOver->setFixedSize(1080,200);
    buttonGameOver->setStyleSheet(QString("font-size: %1px").arg(80));
    connect(buttonGameOver, SIGNAL(clicked()), this, SLOT(gameOver()));

    layout->addWidget(buttonGameOver);
    layout->addStretch(1);

    setLayout(layout);
}

Form::~Form()
{
    delete ui;
}

void Form::newGame()
{
    game->destroy();
    recordValue = 0;
    record->setText(QString::number(recordValue));
    game->build();
    //resize(sizeHint());
}

void Form::exitGame()
{
    this->hide();
    emit signalExit();
}

void Form::changeMode()
{
    if(mode->text() == "Classic")
        mode->setText("Gelik");
    else if(mode->text() == "Gelik")
        mode->setText("Android");
    else
        mode->setText("Classic");

    game->changeMode(mode->text());

    newGame();
}

void Form::setRecord()
{
    recordValue++;
    record->setText(QString::number(recordValue));
}

void Form::gameOver()
{
    emit sendRecord(recordValue);
}
