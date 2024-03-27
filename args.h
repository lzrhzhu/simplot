#ifndef ARGS_H
#define ARGS_H


#include<QObject>
#include<QVector>
#include<QString>
#include<QPointF>

#include "def.h"

struct Axis
{
    bool startFlag;
    bool increaseFlag;
    bool numericsFlag;
    double start;
    double increase;
    int numerics;
};



class Args : public QObject
{
    Q_OBJECT
private:  // member
    Axis xAxis, yAxis;
    QVector<QString> args;
    QVector<QString>fileNames;
    bool drawTypeFlag = false;
    DrawTypes drawType = line;

private:
    bool isDirExist(QString fullPath);
    void myReadFile(QString fileName, QVector<double> & x, QVector<double> & y);
    bool fileArgs(QString arg);

    bool xNumericsArgs(QString arg);
    bool xStartArgs(QString arg);
    bool xIncreaseArgs(QString arg);

    bool yNumericsArgs(QString arg);
    bool yStartArgs(QString arg);
    bool yIncreaseArgs(QString arg);

    bool drawTypeArgs(QString arg);


public:
    Args(int argc, char *argv[]);
public:
    void analyzeArgs();
    void runArgs();

signals:
    void  sendDataXY(QVector<QPointF> xy);
    void  sendXAxis(double start, double increase, int numerics);
    void  sendYAxis(double start, double increase, int numerics);
    void  sendDrawType(DrawTypes type);
};

#endif // ARGS_H
