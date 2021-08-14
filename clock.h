#ifndef CLOCK_H
#define CLOCK_H
#include <QIcon>
#include <QLCDNumber>
#include <QTime>
#include <QMessageBox>


class Clock :public QLCDNumber {
    Q_OBJECT
public:
  enum {WIDTH = 450, HEIGHT = 40};
  Clock(QWidget *parent = nullptr);
public slots:
 void updateTime();
 void stopTime();
public:
  QIcon icon;
  QPixmap pcmap;
  QMessageBox msg;
  QTime current_qtime;
  QTimer* timer;
};

#endif
