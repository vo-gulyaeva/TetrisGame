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
#include "game/gamescene.h"
#include <QVector>
#include <QBitArray>
#include "game/activshape.h"
#include <QTime>
#include <QTimer>
#include "game/fixedshape.h"
#include <QGraphicsSimpleTextItem>

namespace Ui {
class PlayingField;
}

using Shape = QVector<QVector<bool>>;

class PlayingField : public QWidget
{
    Q_OBJECT
public:
    explicit PlayingField(QWidget *parent = nullptr);
    ~PlayingField();
    void openGame();
    void changeSpeed(int level);
private:
    int speedActivElem(int level) const;
    int generalNumElem();
    void startGame();
    void updatePosActiveElem();
    void addGameElemToScene();
    void gameOver();
    void pauseGame();
    void playGame();
signals:
    void goToMenu();
private slots:
    void slotToMenu();
    void slotUpdateTime();
    void slotUpdateFieldAndPosElem(const FixField&, int);
    void slotPauseOrPlayGame();
    void slotGameReset();
private:
    Ui::PlayingField *ui;
    GameScene *gameScene_;
    ActivShape *activElem_;
    QVector<Shape> typeForm;
    FixedShape *field_;
    QVector<int> prevElem_;
    int width_;         //ширина сцены
    int height_;        //высота сцены
    QTime timeGame_;
    QTimer *timerGame_;
    int score_;
    int nextElem_;
    QGraphicsSimpleTextItem *textGameOver_;
    int level_;
    bool statusGame_;   //true - идет игра, false - стоим на паузе
};

#endif // PLAYINGFIELD_H
