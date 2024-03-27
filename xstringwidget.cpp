#include "xstringwidget.h"
#include "parameter.h"
#include <QDebug>

XStringWidget::XStringWidget(QWidget *parent) : QWidget(parent)
{
}
XStringWidget::~XStringWidget()
{
}
void XStringWidget:: paintEvent(QPaintEvent *event)
{
    double scale = double( this->width() )/double(core_width);
    QTransform transform;
    transform.scale(scale, scale);
    QPainter painter(this);
    painter.resetTransform();
    painter.setTransform(transform);
    painter.drawPicture(0,0, picture);
}
void XStringWidget::resizeEvent(QResizeEvent *event)
{

}

void XStringWidget:: recievePicture(QPicture * pic)
{    
    picture = * pic;
}



