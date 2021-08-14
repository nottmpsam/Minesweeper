#ifndef MAP_H
#define MAP_H
#include <QWidget>

class OneCell;
class Map: public QWidget
{
    Q_OBJECT
private:
    int openedCells = 0;
    int countFLAGS = 0;
    bool isWin = false;
    QPixmap IMG_icon;
public:
    enum {MAP_SIZE = 10, MINE_COUNT = 10};
    OneCell* map_pointer[MAP_SIZE][MAP_SIZE];
    Map(QWidget* parent = nullptr);
    bool isCellInMap(int i, int j);
    void openCell(int i, int j);
    void openAll();
    bool& get_wins();
public slots:
    void slot_lcm();
    void slot_rcm();
signals:
    void gameFinished();

};
#endif
