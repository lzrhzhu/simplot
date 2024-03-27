#include <QPainter>
#include <QPen>
#include <QtAlgorithms>
#include "digit.hpp"
#include "drawwidget.h"
#include "parameter.h"

DrawWidget::DrawWidget(QWidget *parent) : QWidget(parent)
{
}
DrawWidget::~DrawWidget()
{
}

void DrawWidget::resizeEvent(QResizeEvent * event)
{

}

void DrawWidget::recievePicture(QPicture *pic)
{
    picture = * pic;
}

void DrawWidget:: paintEvent(QPaintEvent * event)
{   
    QPainter * painter = new QPainter(this);
    QTransform transform;
    double scale =  double( this->width())/double( core_width);
    transform.scale(scale, scale);
    painter->setTransform(transform);
    painter->drawPicture(0, 0, picture);
    delete painter;
}

