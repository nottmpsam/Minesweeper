#include "map.h"
#include "onecell.h"
#include <QGridLayout>
#include <QMessageBox>
#include <QVBoxLayout>


bool Map::isCellInMap(int i, int j)
{
    return (i >= 0) && (j >= 0) && (i < MAP_SIZE) && (j < MAP_SIZE);
}
void Map::openAll()
{
    for (int i = 0; i < MAP_SIZE; ++i)
        for (int j = 0; j < MAP_SIZE; ++j)
            map_pointer[i][j]->openCell();
}
void Map::openCell(int i, int j)
{
    OneCell* cell = map_pointer[i][j];
    if (isCellInMap(i,j) && !cell->isOpen())
    {

        cell->openCell();
        ++openedCells;
        if (cell->isFlag())
            --countFLAGS;
        if (cell->getValue())
             return;
        for (int i_x = -1; i_x < 2;  ++i_x)
        {
          for (int j_y = -1; j_y < 2; ++j_y)
          {
            openCell(i + i_x, j + j_y);
          }
        }

    }
    return;
}
void Map::slot_rcm()
{

    //sender() - для того, чтобы узнать какой объект испустил сигнал
    OneCell* c = reinterpret_cast<OneCell*> (sender());
    if (c->isOpen() || (!c->isFlag() && countFLAGS >= MINE_COUNT)) 
    	return;
    if (!c->isFlag()) ++countFLAGS;
    else --countFLAGS;
    c->swapFlag();
}
void Map::slot_lcm()
{
    OneCell* t = reinterpret_cast<OneCell*> (sender());
    if (!t->isOpen() && !t->isFlag())
    {
        if (t->isMine())
        {
            openAll();
            emit gameFinished();
            return;
        }
        openCell(t->get_i(), t->get_j());
        if (openedCells == MAP_SIZE * MAP_SIZE - MINE_COUNT)
        {
            isWin = true;
            openAll();
            emit gameFinished();
        }
    }
}

Map::Map(QWidget* parent) : QWidget(parent)
{
    QGridLayout* grid = new QGridLayout (this);
    grid->setSpacing(1);
    for (int i = 0; i < MAP_SIZE; ++i)
    {
        for (int j = 0; j < MAP_SIZE; ++j)
        {
            map_pointer[i][j] = new OneCell(i, j, this);
            grid->addWidget(map_pointer[i][j],i,j);
            connect(map_pointer[i][j], &OneCell::rcm, this, &Map::slot_rcm);
            connect(map_pointer[i][j], &OneCell::lcm, this,  &Map::slot_lcm);
        }
    }
    srand(time(NULL));
    int x, y;
    for (int i = 0; i < MINE_COUNT; ++i)
    {
        OneCell* p;
        x = rand() % MAP_SIZE;
        y = rand () % MAP_SIZE;
        p = map_pointer[x][y];
        if (p->isMine()) 
        {
            --i;
            continue;
        }
        else
        {
            bool check_it = false;
            for (int i_x = -1; i_x < 2; i_x= i_x + 2)
            {
                if (isCellInMap(i_x + x, y))
                {
                        if (map_pointer[i_x+x][y]->isMine())
                        {
                            check_it = true;
                            break;
                        }
                }
                if (isCellInMap(x, y + i_x))
                {
                    if (map_pointer[x][y + i_x]->isMine())
                    {
                        check_it = true;
                        break;
                    }
                }
            }
            if (check_it)
            {
                --i;
                continue;
            }
            p->setMine();
        }
        for (int i_x = -1; i_x < 2; ++i_x)
        {
            for (int j_y = -1 ; j_y < 2; ++j_y)
            {
                if (isCellInMap(i_x + x, j_y + y))
                {
                    map_pointer[i_x + x][j_y + y]->getValue()++;
                }
            }
        }
    }
}

bool& Map::get_wins()
{
    return isWin;
}
