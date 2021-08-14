#ifndef WINDOW_H
#define WINDOW_H
#include <QWidget>
#include <QGridLayout>

class Map;
class Clock;

class GameStart : public QWidget
{
    Q_OBJECT

public:
    GameStart();
    Map* mapStart;
    Clock* timeStart;
    QGridLayout* grid;
public slots:
    void gameRestart();
};
#endif
