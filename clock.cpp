#include "clock.h"
#include "map.h"
#include <QMessageBox>
#include <QTimer>


Clock::Clock(QWidget* parent) : QLCDNumber(parent), current_qtime(0,0,0)
{
    pcmap.load("PATH/wicon.png");
    msg.setWindowTitle("Game Finished");
    msg.setDefaultButton(QMessageBox::Ok);
    msg.setIconPixmap(pcmap);
    setFixedSize(WIDTH, HEIGHT);
    setSegmentStyle(Flat);
    timer = new QTimer(this);
    timer -> setInterval(1000);
    connect(timer, &QTimer::timeout, this, &Clock::updateTime);
    display(current_qtime.toString("hh:mm:ss"));
    timer->start(1000);
}
void Clock::stopTime()
{
    timer->stop();
    Map* t = reinterpret_cast<Map*> (sender());
    if (t->get_wins())
    {

           QString text = ("You win, my congratulations, sir!\nYour result is ");
           text.append(current_qtime.toString("hh:mm:ss"));
           text.append("\nGood job! :)");
           msg.setText(text);
    }
    else
    {
          msg.setText("\nYou LOSE!\n:(");
    }
    msg.exec();
}
void Clock::updateTime()
{
    current_qtime = current_qtime.addSecs(1);
    display(current_qtime.toString("hh:mm:ss"));
}
