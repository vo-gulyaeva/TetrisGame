// Тетрис, 2022
#include "game/activshape.h"

ActivShape::ActivShape(int widthScene, int heightScene, int width,  const FixField &field) :
    QGraphicsObject(), widthScene_(widthScene), heightScene_(heightScene), width_(width), field_(field)
{
    timerMove_ = new QTimer(this);
    connect(timerMove_,&QTimer::timeout, this, &ActivShape::slotTimerMove);
    timerMove_->setInterval(600);
    timerMove_->start();
}

void ActivShape::setTypeShape(const Shape &shape)
{
    shape_ = shape;
}

void ActivShape::setSpeed(int speed)
{
    timerMove_->setInterval(speed);
}

void ActivShape::slotTimerMove()
{
    if(!this->scene())
        return;
    this->setPos(this->pos().x(), this->pos().y()+width_);
    if(isTouchedField())
    {
       changeFixField();
       emit signalFell(field_,(int)this->pos().y()/width_);
    }
}

bool ActivShape::isTouchedField()
{
    int str = (int)this->pos().y()/width_;
    int stb = (int)this->pos().x()/width_;
    int height = (int)shape_.size();
    //достигли нижней границы
    if(str+height==ceil(heightScene_/width_))
        return true;
    //проверка на касание фиксированных элементов
    for(int i = 0; i<(int)shape_.size();++i)
        for(int j = 0;j<(int)shape_.at(i).size();++j)
            if(shape_[i][j] && field_[str+height-i][stb+j])
                return true;
    return false;
}

void ActivShape::changeFixField()
{
    int str = (int)this->pos().y()/width_;
    int stb = (int)this->pos().x()/width_;
    int height = (int)shape_.size()-1;
    for(int i = 0; i<=height;++i)
        for(int j = 0;j<(int)shape_.at(i).size();++j)
            if(shape_[i][j])
                field_[str+height-i][stb+j] = true;
}

QRectF ActivShape::boundingRect() const
{
    //зависит от размеров задающей матрицы
    int width = ((int)shape_.at(0).size())*width_;
    int height = ((int)shape_.size())*width_;
    return QRectF(0.,0.,width,height);
}

void ActivShape::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    if(width_ == 0 || shape_.isEmpty())
        return;

    int n = (int)shape_.size();         //кол-во строк
    for(int i = 0;i<n;++i)
        for(int j = 0; j<(int)shape_[i].size();++j)
            if(shape_[i][j])
            {
                //рисуем по квадратикам
                int x = width_*j;
                int y = width_*(n-i-1);
                QRectF rectangle(x,y,width_,width_);
                painter->setBrush(QColor(178,34,34));
                painter->setPen(QPen(Qt::black, 3, Qt::SolidLine));
                painter->drawRect(rectangle);
            }
}

void ActivShape::rotateShape()
{
    if(width_ == 0 || shape_.isEmpty())
        return;

    int m = (int)shape_.at(0).size();   //кол-во столбцов сейчас
    int n = (int)shape_.size();         //кол-во строк сейчас
    Shape shape(m);
    for(int j = m-1;j>=0;j--)
        for(int i = 0; i<n;++i)
            shape[m-j-1].push_back(shape_[i][j]);
    shape_ = shape;
}

void ActivShape::slotMoveShape(QKeyEvent *event)
{
    if(width_ == 0 || shape_.isEmpty())
        return;

    QPointF pos = this->pos();
    switch (event->key()) {
    case Qt::Key_Left: case Qt::Key_A:
    {
        //если выйдем за границы поля
        if(pos.x()-width_<0)
            break;
        if(isFieldFree(Side::left))
            this->setPos(pos.x()-width_, pos.y());
        break;
    }
    case Qt::Key_Right: case Qt::Key_D:
    {
        int wElem = ((int)shape_.at(0).size())*width_;
        //если выйдем за границы поля
        if(pos.x()+width_+wElem>widthScene_)
            break;
        if(isFieldFree(Side::right))
            this->setPos(pos.x()+width_, pos.y());
        break;
    }
    case Qt::Key_Up: case Qt::Key_W:
    {
        int height = ((int)shape_.size())*width_;
        int width = ((int)shape_.at(0).size())*width_;
        if(isRotatePossible(width,height))
        {
            this->setVisible(false);
            this->rotateShape();
            this->update(QRectF(0,0,width,height));
            this->setVisible(true);
        }
        break;
    }
    case Qt::Key_Down: case Qt::Key_S:
        while(!isTouchedField())
            this->setPos(this->pos().x(), this->pos().y()+width_);
        break;
    }
    //проверяем не коснулись ли мы фиксированных элементов
    if(isTouchedField())
    {
       changeFixField();
       emit signalFell(field_,(int)this->pos().y()/width_);
    }
}

bool ActivShape::isRotatePossible(int width, int height)
{
    //если при повоте мы выйдем за правую границу поля
    if(this->pos().x()+height>widthScene_)
        return false;
    //если при повороте выйдем за нижнюю границу поля
    if(this->pos().y()+width>heightScene_)
        return false;
    //иначе рассматриваем возможность поворота относительно фиксированных элементов
    int str = (int)this->pos().y()/width_;
    int stb = (int)this->pos().x()/width_;
    for(int i=(int)width/width_-1;i>=0;i--)
        for(int j=0;j<(int)height/width_;++j)
            if(field_[str+i][stb+j] && shape_[j][i])
                return false;
    return true;
}

bool ActivShape::isFieldFree(const Side &side)
{
    int str = (int)this->pos().y()/width_;
    int stb = (int)this->pos().x()/width_;
    int height = (int)shape_.size()-1;
    int shift = side == Side::left? -1: (int)shape_.at(0).size();
    int j = side == Side::left? 0: (int)shape_.at(0).size()-1;
    for(int i = 0; i<=height;++i)
        if(field_[str+height-i][stb+shift] && shape_[i][j])
            return false;
    return true;
}

void ActivShape::setPause()
{
    timerMove_->stop();
}

void ActivShape::setPlay()
{
    timerMove_->start();
}

bool ActivShape::isActive() const
{
    return timerMove_->isActive();
}

void ActivShape::clearField()
{
    for(int i = 0;i<(int)field_.size();++i)
        field_[i].fill(false);
}
