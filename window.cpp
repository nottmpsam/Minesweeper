#include "window.h"
#include "gamestart.h"
#include <QAction>
#include <QApplication>
#include <QMenuBar>
Window::Window(QWidget* parent) : QMainWindow(parent)
{
    QMenuBar *menuBar;
    setWindowTitle("Minesweeper");
    setWindowIcon(QIcon("PATH/icon.png"));
    setIconSize(QSize(32,32));
    temp = new GameStart;
    setCentralWidget(temp);
    menuBar = this->menuBar();
    QAction *newAct = new QAction("New game", this);
    QAction *quit = new QAction("Quit", this);
    connect(newAct, &QAction::triggered, temp, &GameStart::gameRestart);
    menuBar->addAction(newAct);
    connect(quit, &QAction::triggered, qApp, QApplication::quit);
    menuBar->addAction(quit);
}
