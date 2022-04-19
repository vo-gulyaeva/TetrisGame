// Тетрис, 2022
#include "game/gamescene.h"

GameScene::GameScene(QObject *parent):
    QGraphicsScene(parent)
{
}

void GameScene::keyPressEvent(QKeyEvent * event)
{
    if( event->key() == Qt::Key_Left || event->key() == Qt::Key_Right
            || event->key() == Qt::Key_Up || event->key() == Qt::Key_Down ||
            event->key() == Qt::Key_W || event->key() == Qt::Key_A ||
            event->key() == Qt::Key_S || event->key() == Qt::Key_D)
    {
        emit signalPressControlKeys(event);
    }
}

void GameScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    Q_UNUSED(mouseEvent);
    emit signalPressMouse();
}
