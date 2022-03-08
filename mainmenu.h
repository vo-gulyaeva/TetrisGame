//////////////////////////////////////////////////////////////////////////
//
//! \file mainmenu.h
//! \brief Главное меню
//
//  Gulyaeva V.
//
//////////////////////////////////////////////////////////////////////////
#ifndef MAINMENU_H
#define MAINMENU_H

#include <QMainWindow>
#include "playingfield.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainMenu; }
QT_END_NAMESPACE

class MainMenu : public QMainWindow
{
    Q_OBJECT

public:
    MainMenu(QWidget *parent = nullptr);
    ~MainMenu();
private slots:
    void toGame();
private:
    Ui::MainMenu *ui;
    PlayingField *playingField_;
};
#endif // MAINMENU_H
