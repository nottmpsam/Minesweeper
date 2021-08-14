#ifndef ONECELL_H
#define ONECELL_H

#include <QPushButton>

class OneCell : public QPushButton
{
    Q_OBJECT
private:
    int i, j;
    bool cell = false;
    bool mine = false;
    bool flag = false;
    int  valueInCell = 0;
    QPixmap IMG_mine;
    QPixmap IMG_flag;
    QIcon icn;
public:
    enum {CELL_SIZE = 45};
    OneCell(int i, int j, QWidget *parent = nullptr);
    bool isMine();
    bool isFlag();
    bool isOpen();
    void openCell();
    void setMine();
    int& getValue();
    int get_i();
    int get_j();
    void swapFlag();
    void paintEvent(QPaintEvent*) override;
    void painting(QPainter* brush);
    void mouseReleaseEvent(QMouseEvent*) override;
signals:
    void lcm();
    void rcm();
};
#endif
