// Тетрис, 2022
#include "game/fixedshape.h"

FixedShape::FixedShape(int str, int stb, int width, int yShift):
    str_(str), stb_(stb), width_(width), yShift_(yShift), minFixStr_(str-1)
{
    field_.resize(str_);
    for(int i=0;i<str_;++i)
    {
         field_[i].resize(stb_);
         field_[i].fill(false);
    }
}

QRectF FixedShape::boundingRect() const
{
    int width = stb_*width_;
    int height = str_*width_ + yShift_;
    return QRectF(0.,0.,width,height);
}

void FixedShape::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    for(int i = str_-1;i>=0;i--)
        for(int j = 0; j<stb_;++j)
            if(field_[i][j])
            {
                //рисуем по квадратикам
                int x = width_*j;
                int y = width_*i + yShift_;
                QRectF rectangle(x,y,width_,width_);
                painter->setBrush(QColor(128,24,24));
                painter->setPen(QPen(Qt::black, 3, Qt::SolidLine));
                painter->drawRect(rectangle);
            }
}

FixField FixedShape::getField()
{
    return field_;
}

void FixedShape::setField(const FixField &field)
{
    field_ = field;
    while(isBottomLineFill())
    {
        field_.pop_back();
        field_.push_front(QBitArray(stb_));
    }
    this->update(QRectF(0.,0.,width_*stb_,width_*str_+yShift_));
}

bool FixedShape::isBottomLineFill()
{
    for(int j=0;j<stb_;++j)
        if(!field_[str_-1][j])
            return false;
    return true;
}

bool FixedShape::setMinFixStr(int str)
{
    if(str<minFixStr_)
        minFixStr_ = str;
    if(minFixStr_ <= 0)
        return true;
    return false;
}

void FixedShape::clearField()
{
    for(int i=0;i<str_;++i)
         field_[i].fill(false);
    minFixStr_ =str_-1;
    this->update(QRectF(0.,0.,width_*stb_,width_*str_+yShift_));
}
