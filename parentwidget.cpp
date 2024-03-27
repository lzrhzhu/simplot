
#include <QDebug>
#include "parentwidget.h"
using namespace std;

ParentWidget::ParentWidget(QWidget *parent): QWidget(parent)
{
    draw    = new DrawWidget(this);
    xString = new XStringWidget(this);
    yString = new YStringWidget(this);
    setDraw();
    setXString();
    setYString();
}
ParentWidget::~ParentWidget()
{
    delete draw;
    delete xString;
    delete yString;
}


void ParentWidget:: resizeEvent(QResizeEvent *event)
{
    setDraw();
    setXString();
    setYString();
}
void ParentWidget:: setDraw()
{
    int squareLength = min(this->width(), this->height());

    draw->move(int(squareLength  *drawCap),
               int(squareLength  *drawCap));
    draw->resize(int( squareLength * ( 1- 2*drawCap)),
                 int( squareLength * ( 1 -2*drawCap)));
}

void ParentWidget:: setXString()
{
    int squareLength = min(this->width(), this->height());
    xString->move(  int( squareLength * drawCap ),
                    int( squareLength * (1- drawCap + xStringDrawCap)));
    xString->resize(int( squareLength * (1 - 2 * drawCap)) ,
                    int( squareLength * (drawCap- xStringDrawCap - xStringWidgetCap)));
}

void ParentWidget:: setYString()
{
    int squareLength = min(this->width(), this->height());
    yString->move( int( squareLength * yStringWidgetCap) ,
                   int( squareLength * drawCap));
    yString->resize( int(  squareLength * ( drawCap - yStringDrawCap - yStringWidgetCap)),
                     int(  squareLength * ( 1 - 2*drawCap)));
}

void ParentWidget::showAll()
{
    this->show();
    draw->show();
    xString->show();
    xString->show();
}

DrawWidget * ParentWidget::getDraw()
{
    return draw;
}

void ParentWidget:: setWidgetRegion(int left, int up,  int width, int height)
{
    this->move(left, up);
    this->resize(width, height);
}
void ParentWidget:: setDrawWidgetCap(int Cap)
{
    this->drawCap = Cap;
    setDraw();
}

void ParentWidget:: setXStringDrawCap(int cap)
{
    xStringDrawCap = cap;
    setXString();

}

void ParentWidget:: setYStringDrawCap(int cap)
{
    yStringDrawCap = cap;
    setYString();

}


