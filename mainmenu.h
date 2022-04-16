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
#include "game/playingfield.h"
#include "help/help.h"
#include "settings/settings.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainMenu; }
QT_END_NAMESPACE

class MainMenu : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainMenu(QWidget *parent = nullptr);
    ~MainMenu();
private slots:
    void toGame();
    void toHelp();
    void toSettings();
    void changeLevel(int);
private:
    Ui::MainMenu *ui;
    PlayingField *playingField_;
    Help *help_;
    Settings *settings_;
    int level_;
};
#endif // MAINMENU_H
