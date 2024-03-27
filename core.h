#ifndef CORE_H
#define CORE_H

#include <QPointF>
#include <QPoint>
#include <QVector>
#include <QString>
#include <QPicture>
#include <QPainter>
#include <QPen>
#include <QFont>

#include "def.h"

class Core : public QObject
{
    Q_OBJECT
private:
    double leftReal;
    double rightReal;
    double upReal;
    double bottomReal;
    int tickLength        = 20;
    int xTickRegionHeight = 200;
    int yTickRegionWidth  = 200;
    int xTicksNumber      = 5 ;
    int yTicksNumber      = 5 ;
    DrawTypes drawType    = line;
    QVector<QVector<QPointF>> xysReal;
    QVector<QVector<QPoint>> xysWidget;
    QVector<double>          xTicksReal, yTicksReal;
    QVector<int>             xTicksWidget, yTicksWidget;
    QVector<QString>         xTicksString, yTicksString;

private:
    void renderAxisData();
    void renderXTicksString();
    void renderYTicksString();

public:
    Core();
    ~Core();
    bool AutoXYRegion();
    void dataWidget();
    void render();

public:
    void recieveDataXY(QVector<QPointF> xy);
    void recieveXAxis(double start, double increase, int bit);
    void recieveYAxis(double start, double increase, int bit);
    void recieveDrawType(DrawTypes type);

signals:
    void sendRenderSize(int width, int height);
    void sendAxisDataPicture    (QPicture * pic);
    void sendXTicksStringPicture(QPicture * pic);
    void sendYTicksStringPicture(QPicture * pic);
};

#endif // CORE_H
