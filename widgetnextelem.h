//////////////////////////////////////////////////////////////////////////
//
//! \file widgetnextelem.h
//! \brief Класс для отображения следующего активного элемента, унаследован от QWidget
//
//  Gulyaeva V.
//
//////////////////////////////////////////////////////////////////////////
#ifndef WIDGETNEXTELEM_H
#define WIDGETNEXTELEM_H

#include <QWidget>
#include <QPaintEvent>

namespace Ui {
class WidgetNextElem;
}

using Shape = QVector<QVector<bool>>;

class WidgetNextElem : public QWidget
{
    Q_OBJECT
public:
    explicit WidgetNextElem(QWidget *parent = nullptr);
    ~WidgetNextElem();
    void setShape(const Shape&);
protected:
    void paintEvent(QPaintEvent *event);
private:
    Ui::WidgetNextElem *ui;
    Shape shape_;
};

#endif // WIDGETNEXTELEM_H
