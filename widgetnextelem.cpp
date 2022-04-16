// Тетрис, 2022
#include "game/widgetnextelem.h"
#include "ui_widgetnextelem.h"
#include <QPainter>

WidgetNextElem::WidgetNextElem(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetNextElem)
{
    ui->setupUi(this);
}

WidgetNextElem::~WidgetNextElem()
{
    delete ui;
}

void WidgetNextElem::setShape(const Shape &shape)
{
    shape_ = shape;
    repaint();
}

void WidgetNextElem::paintEvent(QPaintEvent *event)
{
    if(shape_.isEmpty())
        return;
    Q_UNUSED(event);
    QPainter painter(this); // Создаём объект отрисовщика
    int n = (int)shape_.size();         //кол-во строк
    int widthRect = 30;
    int widthElem = ((int)shape_.at(0).size())*widthRect;
    int xStart = (int)(this->size().width()-widthElem)/2;
    for(int i = 0;i<n;++i)
        for(int j = 0; j<(int)shape_[i].size();++j)
            if(shape_[i][j])
            {
                //рисуем по квадратикам
                int x = xStart + widthRect*j;
                int y = widthRect*(n-i);
                QRectF rectangle(x,y,widthRect,widthRect);
                painter.setBrush(QColor(178,34,34));
                painter.setPen(QPen(Qt::black, 3, Qt::SolidLine));
                painter.drawRect(rectangle);
            }
}
