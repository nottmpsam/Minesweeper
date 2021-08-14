#include "gamestart.h"
#include "map.h"
#include "clock.h"
#include <QGridLayout>
GameStart::GameStart() : mapStart(nullptr), timeStart(nullptr)
{
    grid = new QGridLayout;
    grid->setAlignment(Qt::AlignCenter);
    setLayout(grid);
    gameRestart();
}
void GameStart::gameRestart()
{
    if (mapStart)
    {
      delete mapStart;
      delete timeStart;
    }
    timeStart = new Clock(this);
    grid->addWidget(timeStart, 0, 0, 1, 1, Qt::AlignCenter);
    mapStart = new Map(this);
    grid->addWidget(mapStart, 1, 0, 1, 1, Qt::AlignCenter);
    connect(mapStart, &Map::gameFinished, timeStart, &Clock::stopTime);

}
