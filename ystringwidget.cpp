#include "ystringwidget.h"
#include "parameter.h"
#include <QDebug>

YStringWidget::YStringWidget(QWidget *parent) : QWidget(parent)
{
}
YStringWidget::~YStringWidget()
{
}
void YStringWidget::paintEvent(QPaintEvent *event)
{
    double scale = double( this->height() )/
                   double( core_height );
    QTransform transform;
    transform.scale(scale, scale);
    QPainter painter(this);
    painter.setTransform(transform);
    painter.drawPicture(0, 0, picture);
}

void YStringWidget:: resizeEvent(QResizeEvent * event)
{
}

void YStringWidget::recievePicture(QPicture * pic)
{
    picture = *pic;
}
