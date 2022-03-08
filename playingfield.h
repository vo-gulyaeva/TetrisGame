//////////////////////////////////////////////////////////////////////////
//
//! \file playingfield.h
//! \brief Виджет игрового поля
//
//  Gulyaeva V.
//
//////////////////////////////////////////////////////////////////////////
#ifndef PLAYINGFIELD_H
#define PLAYINGFIELD_H

#include <QWidget>

namespace Ui {
class PlayingField;
}

class PlayingField : public QWidget
{
    Q_OBJECT

public:
    explicit PlayingField(QWidget *parent = nullptr);
    ~PlayingField();
signals:
    void goToMenu();
private slots:
    void slotToMenu();
private:
    Ui::PlayingField *ui;
};

#endif // PLAYINGFIELD_H
