
#include <QApplication>
#include <QString>
#include <QVector>
#include <QDebug>
#include <QFile>
#include <QIODevice>
#include <QDir>
#include <fstream>
#include <sstream>
#include <iostream>

#include "args.h"

Args::Args(int argc, char *argv[])
{
    for(int i = 1; i< argc; i++)
    {
        args.push_back(QString(argv[i]));
    }
}


void Args:: analyzeArgs()
{
    xAxis.startFlag    = false;
    xAxis.increaseFlag = false;
    xAxis.numericsFlag = false;
    yAxis.startFlag    = false;
    yAxis.increaseFlag = false;
    yAxis.numericsFlag = false;
    for(int i = 0; i< args.size(); i++)
    {
        if(fileArgs(args[i]))
        {
            fileNames.push_back(args[i].right(args[i].size() - 5));
        }
        else if(xStartArgs(args[i]))
        {
            xAxis.startFlag= true;
            xAxis.start    = args[i].right(args[i].size()-5).toDouble();
        }
        else if(xIncreaseArgs(args[i]))
        {
            xAxis.increaseFlag = true;
            xAxis.increase = args[i].right(args[i].size()-5).toDouble();
        }
        else if(xNumericsArgs(args[i]))
        {
            xAxis.numericsFlag = true;
            xAxis.numerics     = args[i].right(args[i].size()-5).toInt();
        }
        else if(yStartArgs(args[i]))
        {
            yAxis.startFlag = true;
            yAxis.start     = args[i].right(args[i].size()-5).toDouble();
        }
        else if(yIncreaseArgs(args[i]))
        {
            yAxis.increaseFlag = true;
            yAxis.increase     = args[i].right(args[i].size()-5).toDouble();
        }
        else if(yNumericsArgs((args[i])))
        {
            yAxis.numericsFlag =true;
            yAxis.numerics     =args[i].right(args[i].size()-5).toInt();
        }
        else if(drawTypeArgs((args[i])))
        {
            drawTypeFlag = true;
            if(args[i].right(args[i].size()-9)==QString("line"))  drawType = line;
            if(args[i].right(args[i].size()-9)==QString("dot"))   drawType = dot;
            if(args[i].right(args[i].size()-9)==QString("dot"))   drawType = contour;
            if(args[i].right(args[i].size()-9)==QString("vector"))drawType = vector;
        }
    }
}

void Args:: runArgs()
{
    for(int i= 0; i< fileNames.size(); i++)
    {
        QVector<double> x, y;
        QVector<QPointF> xy;
        myReadFile(fileNames[i], x, y);
        for(int i = 0; i< x.size() ;  i++ ) xy.push_back(QPointF(x[i], y[i]));
        emit  this->sendDataXY(xy);
    }

    if( xAxis.startFlag    == true &&
        xAxis.increaseFlag == true &&
        xAxis.numericsFlag == true    )
    {
        emit sendXAxis( xAxis.start, xAxis.increase, xAxis.numerics);
    }

    if( yAxis.startFlag    == true &&
        yAxis.increaseFlag == true &&
        yAxis.numerics     == true   )
    {
        emit sendYAxis( yAxis.start, yAxis.increase, yAxis.numerics);
    }
    if(drawTypeFlag==true)
    {
        emit sendDrawType(drawType);
    }
}

bool Args:: isDirExist(QString fullPath)
 {
     QDir dir(fullPath);
     if(dir.exists())
     {
       return true;
     }
     return false;
 }

void Args::myReadFile(QString fileName, QVector<double> & x, QVector<double> & y)
{
    QFile file(fileName);
    file.open(QIODevice::ReadOnly);
    QTextStream out(&file);
    double data = 0;
    bool   xFlag = true;
    for ( out>> data;  !out.atEnd(); out >> data)
    {
        if(xFlag == true)
        {
            x.push_back(data);
            xFlag = false;
        }
        else if(xFlag == false)
        {
            y.push_back(data);
            xFlag = true;
        }
    }
}
bool Args:: fileArgs(QString arg)
{
    if(arg.left(5) == QString("file="))   return true;
    return false;
}

bool Args:: xNumericsArgs(QString arg)
{
    if(arg.left(5) == QString("xnum=")) return true;
    return false;
}

bool Args:: xStartArgs(QString arg)
{
    if(arg.left(5) == QString("xsta=")) return true;
    return false;
}

bool Args:: xIncreaseArgs(QString arg)
{
    if(arg.left(5) == QString("xinc=")) return true;
    return false;
}

bool Args:: yNumericsArgs(QString arg)
{
    if(arg.left(5) == QString("ynum=")) return true;
    return false;
}

bool Args:: yStartArgs(QString arg)
{
    if(arg.left(5) == QString("ysta=")) return true;
    return false;
}

bool Args:: yIncreaseArgs(QString arg)
{
    if(arg.left(5)  ==QString("yinc=")) return true;
    return false;
}

bool Args:: drawTypeArgs(QString arg)
{
    if(arg.left(9)  ==QString("drawtype=")) return true;
    return false;
}




