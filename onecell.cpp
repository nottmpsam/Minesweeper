#include "onecell.h"
#include <QPainter>
#include <QMouseEvent>
#include <QLabel>

int OneCell::get_i()
{
    return i;
}

int OneCell::get_j()
{
    return j;
}

int& OneCell::getValue()
{
  return valueInCell;
}

bool OneCell::isFlag()
{
    return flag;
}

bool OneCell::isOpen()
{
    return cell;
}

bool OneCell::isMine()
{
    return mine;
}
void OneCell::setMine()
{
    mine = true;
}
void OneCell::swapFlag()
{
    flag = !flag;
    if (flag)
    {
         icn.addPixmap(IMG_flag);
         setIcon(icn);
    } else
        setIcon(QIcon());

}
void OneCell::openCell()
{
    cell = true;
    update();
}

void OneCell::painting(QPainter* p)
{
    QRect rect(-1,-1, width() + 1, height() + 1);
    if (isOpen() && isMine() == false && valueInCell == 0)
    {
        p->fillRect(rect, QBrush(Qt::white));
        if (flag)
        {
           setIcon(QIcon());
           QPixmap xd("PATH/mine_error.png");
        }
        return;
    }
    if (isOpen())
    {
        if (isMine())
        {
          icn.addPixmap(IMG_mine);
          setIcon(icn);
          return;
        }
        switch (valueInCell)
        {
            case 1 :
                p->setPen(QColor(Qt::darkBlue));
                break;
            case 2:
                p->setPen(QColor(Qt::darkGreen));
                break;
            case 3:
                p->setPen(QColor(Qt::darkRed));
                break;
            default:
                p->setPen(QColor(Qt::darkMagenta));
        }
        QRectF R;
        R.setRect(width() / 4, width() % 4, width(), width());
        QFont font = p->font();
        font.setPixelSize(CELL_SIZE - 5);
        p->setFont(font);
        p->fillRect(rect, QBrush(Qt::white));
        p->drawText(R, QString::number(valueInCell));
      }
}
void OneCell::paintEvent(QPaintEvent* event)
{
    QPushButton::paintEvent(event);
    QPainter p(this);
    painting(&p);
}
void OneCell::mouseReleaseEvent(QMouseEvent* click)
{
    if (click->button() == Qt::LeftButton)
        emit lcm();
    if (click->button() == Qt::RightButton)
        emit rcm();
}
OneCell::OneCell(int i_, int j_, QWidget* parent) :
   QPushButton (parent), i(i_), j(j_)
{
  setStyleSheet("background-color: grey");
  setFixedSize(CELL_SIZE, CELL_SIZE);
  IMG_mine.load("PATH/mine.png");
  IMG_flag.load("PATH/flag.png");
  setIconSize(QSize(width(), height()));
}
