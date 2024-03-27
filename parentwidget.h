#ifndef WIDGET_H
#define WIDGET_H

#include "core.h"
#include "drawwidget.h"
#include "xstringwidget.h"
#include "ystringwidget.h"

class ParentWidget : public QWidget
{
    Q_OBJECT
private:
    double drawCap           = 0.15;
    double xStringDrawCap    = 0.01;
    double xStringWidgetCap  = 0.05;

    double yStringDrawCap   = 0.01;
    double yStringWidgetCap = 0.05;

    void setDraw();
    void setXString();
    void setYString();

protected:
     void resizeEvent(QResizeEvent * event);


public :

    DrawWidget  * draw;
    XStringWidget * xString;
    YStringWidget * yString;

public :
    ParentWidget(QWidget *parent);
    ~ParentWidget();
    void setWidgetRegion(int left,  int up,
                         int width, int height);
    void setDrawWidgetCap(int cap);
    void setXStringDrawCap(int cap);
    void setYStringDrawCap(int cap);
    void showAll();
    DrawWidget * getDraw();
};
#endif // WIDGET_H
