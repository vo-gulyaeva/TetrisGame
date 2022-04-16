//////////////////////////////////////////////////////////////////////////
//
//! \file fixedshape.h
//! \brief Фиксированный элемент - стена, унаследован от QGraphicsObject
//
//  Gulyaeva V.
//
//////////////////////////////////////////////////////////////////////////
#ifndef FIXEDSHAPE_H
#define FIXEDSHAPE_H

#include <QGraphicsObject>
#include <QRectF>
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QVector>
#include <QBitArray>

using FixField = QVector<QBitArray>;

class FixedShape : public QGraphicsObject
{
     Q_OBJECT
public:
    FixedShape(int str, int stb, int width, int yShift);
    FixField getField();
    void setField(const FixField&);
    //возвращаем true - конец игры, false - продолжаем игру
    bool setMinFixStr(int);
    void clearField();
private:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    bool isBottomLineFill();
private:
    FixField field_;
    int str_, stb_;
    int width_;
    int yShift_;
    int minFixStr_;
};

#endif // FIXEDSHAPE_H
