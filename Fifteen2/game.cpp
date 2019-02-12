#include "Game.h"
#include "MainWindow.h"
#include <QtGlobal>
#include <QGridLayout>
#include <QPoint>
#include <QPushButton>
#include <QTime>
#include "QMessageBox"
#include <cstdlib>
#include <QDebug>

Game::Game(QWidget*) : mode("Classic")
{
    build();
}

void Game::build()
{
    grid = new QGridLayout(this);
    grid->setContentsMargins(0, 0, 0, 0);
    grid->setSpacing(0);

    QTime midnight(0, 0, 0);
    srand(midnight.secsTo(QTime::currentTime()));

    // картинки
    QString directory;
    if(mode == "Classic")
        directory = ":/gelik/classic";
    else if(mode == "Gelik")
        directory = ":/gelik/";
    else if(mode == "Android")
        directory = ":/gelik/android";
    for(int i=0;i<15;i++)
        px[i]=new QPixmap(directory + QString::number(i+1) +".jpg");
    //
    int n;

    do
    {
        numbers.clear();

        for(int i = 0; i < 15; i++)
        { // случайные числа
            do n = rand() % 15 + 1;
            while(numbers.contains(n));
            numbers << n;
        }

        n = 0;

        for(int i = 2; i <= 15; i++)
        for(int j = 0; j < numbers.indexOf(i); j++)
            if(numbers[j] < i)
                ++n;
    } while(n%2 == 1);

    do path.setY(rand() % 4);
    while(n%2 != path.y()%2);

    path.setX(rand() % 4);

    n = 0;

    for(int y = 0; y < 4; ++y) // строка
    for(int x = 0; x < 4; ++x) // столбец
    {
        if(path.x() == x && path.y() == y)
            continue;

        createButton(NULL, numbers[n++], x, y);
    }
    setLayout(grid);
}

void Game::destroy()
{
    while (QLayoutItem* item = grid->takeAt(0)) {
        delete item->widget();
        delete item;
    }
    delete grid;
    buttons.clear();
}

void Game::move()
{
    int x, y, rs, cs;
    QPushButton* clickedBtn = static_cast<QPushButton*>(sender());
    grid->getItemPosition(grid->indexOf(clickedBtn), &y, &x, &rs, &cs);

    if((path.x() == x && (path.y() == y+1 || path.y() == y-1))
    || (path.y() == y && (path.x() == x+1 || path.x() == x-1))) // Можно ли двигать кнопку?
    {
        // удаляем кнопку со старого места
        grid->removeWidget(clickedBtn);
        // и добавляем на свободную ячейку
        createButton(clickedBtn, 0, path.x(), path.y());
        // и обновляем координаиы свободной ячейки
        path = QPoint(x, y);
        checkGameOver(); // проверка на конец игры
        emit incRecord();
    }
}

void Game::changeMode(QString mode)
{
    this->mode = mode;
}

void Game::checkGameOver()
{
    Q_ASSERT(grid->count() == numbers.size());

    int i=1, n=0;

    for(int y = 0; y < grid->rowCount(); ++y) // строка
    for(int x = 0; x < grid->columnCount(); ++x) // столбец
    {
        if(grid->itemAtPosition(y, x) == NULL)
            continue;
        n = numbers.indexOf(i++);
        if(buttons[n] != (QPushButton*)grid->itemAtPosition(y, x)->widget())
            return;
    }

    // проверка, свободна ли последняя ячейка
    if(path.y() == grid->rowCount()-1 && path.x() == grid->columnCount()-1)
    { // игра окончена
        // блокировка всех кнопок
        for(QList<QPushButton*>::const_iterator it = buttons.begin(); it != buttons.end(); ++it)
            (*it)->setDisabled(true);
        QMessageBox::information(this, "message", "ПОБЕДА!!!");
        emit signalGameOver();
    }
}

void Game::createButton(QPushButton* b, int no, int x, int y) // Создание кнопки
{
    QPushButton* btn = b;
    if(!btn)
    {
        btn = new QPushButton();
        buttons << btn;
        connect(btn, SIGNAL(clicked()), this, SLOT(move()));
        btn->setFixedSize(270,270);

        QIcon ButtonIcon(*px[no-1]);
        btn->setIcon(ButtonIcon);
        btn->setIconSize(QSize(270,270));

    }
    grid->addWidget(btn, y, x);
}
