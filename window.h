#ifndef MENUBAR_H
#define MENUBAR_H
#include <QMainWindow>
class GameStart;
class Window : public QMainWindow
{
public:
    GameStart* temp;
    Window(QWidget* parent = nullptr);
};

#endif
