//////////////////////////////////////////////////////////////////////////
//
//! \file gamescene.h
//! \brief Игровая сцена, унаследована от QGraphicsScene
//
//  Gulyaeva V.
//
//////////////////////////////////////////////////////////////////////////
#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QGraphicsScene>
#include <qobject.h>
#include <QKeyEvent>
#include <QGraphicsSceneMouseEvent>

class GameScene : public QGraphicsScene
{
    Q_OBJECT
public:
    GameScene();
protected:
    void keyPressEvent(QKeyEvent *);
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
signals:
    void signalPressControlKeys(QKeyEvent *);
    void signalPressMouse();
};

#endif // GAMESCENE_H
