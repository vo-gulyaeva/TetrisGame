//////////////////////////////////////////////////////////////////////////
//
//! \file activshape.h
//! \brief Игровой элемент, унаследован от QGraphicsObject
//
//  Gulyaeva V.
//
//////////////////////////////////////////////////////////////////////////
#ifndef ACTIVSHAPE_H
#define ACTIVSHAPE_H

#include <QGraphicsObject>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QRectF>
#include <QTimer>
#include <QKeyEvent>
#include "game/fixedshape.h"

using Shape = QVector<QVector<bool>>;

class ActivShape : public QGraphicsObject
{
     Q_OBJECT
public:
    ActivShape(int widthScene, int heightScene, int width,  const FixField &field);
    void setTypeShape(const Shape&);
    void setSpeed(int);
signals:
    //посылаем новое фикс поле и минимальную изменившуюся строчку
    void signalFell(FixField,int);
public slots:
    void rotateShape();
    void slotMoveShape(QKeyEvent *);
    void setPause();
    void setPlay();
    void clearField();
    bool isActive();
private:
    enum Side
    {
        left,
        right
    };
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void slotTimerMove();
    bool isTouchedField();
    void changeFixField();
    //функция проверки свободности поля в заданной стороне
    bool isFieldFree(const Side&);
    bool isRotatePossible(int,int);
private:
    Shape shape_;
    int widthScene_;         //ширина сцены
    int heightScene_;        //высота сцены
    int width_;
    FixField field_;
    QTimer *timerMove_;
};

#endif // ACTIVSHAPE_H
