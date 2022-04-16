//////////////////////////////////////////////////////////////////////////
//
//! \file help.h
//! \brief Окно с настройкой уровня сложности игры
//
//  Gulyaeva V.
//
//////////////////////////////////////////////////////////////////////////
#ifndef SETTINGS_H
#define SETTINGS_H

#include <QWidget>

namespace Ui {
class Settings;
}

class Settings : public QWidget
{
    Q_OBJECT
signals:
    void goToMenu(int);
public:
    explicit Settings(int level, QWidget *parent = nullptr);
    ~Settings();
    void setLevel(int level);
private slots:
    void slotToMenu();
    void slotChangeLevel(bool);
private:
    Ui::Settings *ui;
    int level_;
};

#endif // SETTINGS_H
