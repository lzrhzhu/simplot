#include "core.h"
#include "digit.hpp"
#include "parameter.h"

#include <QPolygon>

Core::Core()
{
}
Core::~Core()
{
}
void Core:: recieveDataXY(QVector<QPointF> xy)
{
    xysReal.push_back(xy);
    this->AutoXYRegion();
    this->dataWidget();
}

void Core:: recieveXAxis(double start, double increase, int numerics)
{
    xTicksReal.clear();
    xTicksWidget.clear();
    xTicksString.clear();
    while (start < leftReal) start+= increase;
    for(double mid = start; mid < rightReal; mid += increase)
    {
        xTicksReal.push_back(mid);
        xTicksWidget.push_back( int
                                (BitMath::interpolation(leftReal,  0,
                                         rightReal, core_width, mid)));
        xTicksString.push_back( BitMath::doubleToQString(mid,numerics));
    }
    xTicksNumber = xTicksReal.size();
}

void Core:: recieveYAxis(double start, double increase, int numerics)
{
    yTicksReal.clear();
    yTicksWidget.clear();
    yTicksString.clear();
    if(start< bottomReal) start += increase ;
    for(double mid = start; mid < upReal; mid += increase)
    {
        yTicksReal.push_back(mid);
        yTicksWidget.push_back( int (BitMath::interpolation(
                                         bottomReal,  core_height,
                                         upReal,      0,
                                         mid)));
        yTicksString.push_back(BitMath::doubleToQString(mid, numerics));
    }
    yTicksNumber = yTicksReal.size();
}

void Core:: recieveDrawType(DrawTypes type)
{
    drawType = type;
}

void Core :: dataWidget()
{
    xysWidget.resize(xysReal.size());
    for(int j = 0; j< xysWidget.size(); j++)
    {
        xysWidget[j].resize(this->xysReal[j].size());
    }

    for(int j = 0; j< xysReal.size(); j++)
    {
        for(int i = 0 ; i< xysReal[j].size(); i++)
        {
            xysWidget[j][i]=
                    QPoint(
                     int((xysReal[j][i].x() -leftReal) /(rightReal - leftReal)  * core_width),
                     int((xysReal[j][i].y() - upReal) /(bottomReal   - upReal)  * core_height));
        }
    }
}

bool Core ::AutoXYRegion()
{
    if(xysReal.size()<= 0 ) return false;
    for(int i = 0;  i < xysReal.size(); i++ ) if(xysReal[i].isEmpty() ) return false;

    double xMax = xysReal[0][0].x();
    double xMin = xysReal[0][0].x();
    double yMax = xysReal[0][0].y();
    double yMin = xysReal[0][0].y();

    for(int j = 0; j< xysReal.size(); j++) for(int i = 0; i< xysReal[j].size(); i++)
    {
        if(xMax < xysReal[j][i].x()) xMax = xysReal[j][i].x();
        if(xMin > xysReal[j][i].x()) xMin = xysReal[j][i].x();
        if(yMax < xysReal[j][i].y()) yMax = xysReal[j][i].y();
        if(yMin > xysReal[j][i].y()) yMin = xysReal[j][i].y();
    }
    if( xMax == xMin) return false;
    if( yMax == yMin) return false;


    leftReal   = xMin - (xMax - xMin) * 0.1;
    rightReal  = xMax + (xMax - xMin) * 0.1;
    bottomReal = yMin - (yMax - yMin) * 0.1;
    upReal     = yMax + (yMax - yMin) * 0.1;

    double ticksLeftReal        = leftReal;
    double ticksRightReal       = rightReal;
    double ticksUpReal          = upReal;
    double ticksBottomReal      = bottomReal;

    double accuracy = (ticksRightReal - ticksLeftReal)*0.05;
    int xBits = max( BitMath::ceilData( xMin + accuracy, ticksLeftReal),
                 BitMath::floorData(    xMax - accuracy, ticksRightReal )) + 2;

    accuracy = (ticksUpReal - ticksBottomReal)* 0.05;
    int yBits = max( BitMath::ceilData( yMin +  accuracy, ticksBottomReal ),
                     BitMath::floorData(yMax -  accuracy,  ticksUpReal   )) + 2;

    double xIncrease = (ticksRightReal - ticksLeftReal)/xTicksNumber;
           xIncrease = BitMath::ceilBits(xIncrease, xBits-2);

    xTicksReal.clear();
    xTicksWidget.clear();
    xTicksString.clear();

    /*
    for(int i = 0; i< xTicksNumber + 1; i++)
    {
        double oneReal =  i * (ticksRightReal - ticksLeftReal) / xTicksNumber  + ticksLeftReal;
        int oneWidget  =  int (BitMath::interpolation(axisLeftReal,  0,
                                             axisRightReal, core_width,
                                             oneReal));
        xTicksReal.push_back(oneReal);
        xTicksWidget.push_back(oneWidget);
        xTicksString.push_back(BitMath::doubleToQString(oneReal, xBits));
    }    */

    for(double oneReal = ticksLeftReal; oneReal < rightReal; oneReal += xIncrease )
    {
        int oneWidget  =  int (BitMath::interpolation(leftReal,  0,  rightReal, core_width, oneReal));
        xTicksReal.push_back(oneReal);
        xTicksWidget.push_back(oneWidget);
        xTicksString.push_back(BitMath::doubleToQString(oneReal, xBits));
    }
    double yIncrease = (ticksUpReal    - ticksBottomReal)/yTicksNumber;
    yIncrease = BitMath::ceilBits(yIncrease, yBits-1);
    yTicksReal.clear();
    yTicksWidget.clear();
    yTicksString.clear();

    for(double oneReal = ticksBottomReal; oneReal <upReal; oneReal +=yIncrease)
    {
        int oneWidget  = int(BitMath::interpolation(bottomReal, core_height,  upReal, 0,  oneReal));
        yTicksReal.push_back(oneReal);
        yTicksWidget.push_back(oneWidget);
        yTicksString.push_back(BitMath::doubleToQString(oneReal, yBits));
    }

   /*
        int i = 0; i< yTicksNumber + 1; i++)
    {
        double oneReal = i *  (ticksUpReal    - ticksBottomReal)/ yTicksNumber  + ticksBottomReal;
        int oneWidget  = int(BitMath::interpolation(axisBottomReal, core_height,
                                           axisUpReal,     0,
                                           oneReal));
        yTicksReal.push_back(oneReal);
        yTicksWidget.push_back(oneWidget);
        yTicksString.push_back(BitMath::doubleToQString(oneReal, yBits));
    }
    */
    return true;
}

void Core:: render()
{
    renderAxisData();
    renderXTicksString();
    renderYTicksString();
}

void Core:: renderAxisData()
{
    QPainter * painter =new QPainter;
    QPicture  axisDataPicture ;
    QPen pen;
    pen.setWidth(2);
    pen.setStyle(Qt::SolidLine);
    pen.setColor(Qt::black);    

    painter->begin(&axisDataPicture);
    painter->setPen(pen);
    painter->setRenderHint(QPainter::Antialiasing);
    painter->drawRect(0,             0,
                      core_width -1, core_height-1 );

    if(drawType ==line )
    {
        for(int j = 0; j< xysWidget.size(); j++)
        {
            painter->drawPolyline(QPolygon(xysWidget[j]));
        }
    }
    else if(drawType ==dot)
    {
        for(int j = 0; j< xysWidget.size();j++)
        {
            for(int i = 0; i< xysWidget[j].size(); i++)
            painter->drawPoint(xysWidget[j][i]);
        }
    }

    for(int i = 0; i< xTicksWidget.size(); i++)
    {
        painter->drawLine(xTicksWidget[i], core_height-1,
                          xTicksWidget[i], core_height-1 - tickLength);
    }
    for(int i = 0; i< yTicksWidget.size(); i++)
    {
        painter->drawLine(0,          yTicksWidget[i],
                         tickLength,  yTicksWidget[i]);
    }
    pen.setStyle(Qt::DashLine);
    painter->setPen(pen);
    for(int i = 0; i< xTicksWidget.size(); i++)
    {
        painter->setPen(pen);
        painter->drawLine(xTicksWidget[i], core_width-1,
                          xTicksWidget[i], 0      );
    }
    for(int i = 0; i< yTicksWidget.size(); i++)
    {
        painter->setPen(pen);
        painter->drawLine(0,       yTicksWidget[i],
                          core_width-1, yTicksWidget[i]);
    }
    painter->end();
    emit sendAxisDataPicture(&axisDataPicture);
    delete painter;
}

void Core:: renderXTicksString()
{
    QPainter  * painter = new QPainter;
    QPicture xTicksStringPicture;
    QFont font;
    font.setFamily("Times New Roman");
    font.setBold(false);
    font.setPointSize(30);
    painter->begin(&xTicksStringPicture);
    painter->setFont(font);
    painter->setPen(Qt::black);
    painter->setRenderHint(QPainter::TextAntialiasing);
    for(int i = 0; i< xTicksString.size(); i++)
    {
        painter->drawText( xTicksWidget[i],  xTickRegionHeight/2, xTicksString[i]);
    }
    painter->end();
    emit sendXTicksStringPicture(&xTicksStringPicture);
    delete painter;
}

void Core:: renderYTicksString()
{
    QPicture yTicksStringPicture;
    QFont font;
    font.setFamily("Times New Roman");
    font.setBold(false);
    font.setPointSize(30);
    QPainter * painter = new QPainter;
    painter->begin(&yTicksStringPicture);
    painter->setFont(font);
    painter->setPen(Qt::black);
    painter->setRenderHint(QPainter::TextAntialiasing);
    for(int i = 0; i< yTicksString.size(); i++)
    {
        painter->drawText(yTickRegionWidth*0.1, yTicksWidget[i],  yTicksString[i]);
    }
    painter->end();
    emit sendYTicksStringPicture(&yTicksStringPicture);
    delete painter;
}
