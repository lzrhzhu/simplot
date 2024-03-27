#ifndef DIGIT_HPP
#define DIGIT_HPP

#include <QString>
#include <QDebug>
#include <QTextStream>
#include <cmath>
using namespace std;

class BitMath
{
public:
    static double ceilBits(double inData, int inBit)
    {
        if(abs(inData) > pow(10, inBit)){
            int i = 0;
            for(; abs(inData) > pow(10, inBit); i++) inData = inData/10.0;
            inData = ceil(inData);
            for(; i >0 ; i-- ) inData = inData * 10.0;
        }
        else if(abs(inData) < pow(10, inBit-1))
        {
            int i = 0;
            for(; abs(inData) < pow(10, inBit-1); i++) inData = inData * 10.0;
            inData = ceil(inData);
            for(; i > 0 ; i-- ) inData = inData /10.0;
        }
        else {
            inData = ceil(inData);
        }
        return inData;
    }

    static int ceilData(double compare, double & in)
    {
        int bits;
        for(bits = 0; ceilBits(in, bits) >  compare; bits++);
        in = ceilBits(in, bits++);
        return bits;
    }



   //  floor
    static double floorBits(double inData, int inBit)
    {
        if(abs(inData) > pow(10, inBit)){
            int i = 0;
            for(; abs(inData) > pow(10, inBit); i++)   inData = inData / 10.0;
            inData = floor(inData);
            for(;i > 0; i-- ) inData = inData * 10.0;
        }
        else if(abs(inData) < pow(10, inBit-1)){
            int i = 0;
            for(; abs(inData) < pow(10, inBit-1); i++) inData = inData * 10.0;
            inData = floor(inData);
            for(int j = 0; j < i ; j++) inData = inData /10.0;
        }
        else {
            inData = floor(inData);
        }
        return inData;
    }

    static int floorData(double compare, double & in)
    {
        int bits;
        for(bits=0; floorBits(in, bits) < compare; bits++);
        in = floorBits(in, bits);
        return bits;
    }

    static QString doubleToQString(double in, int bit)
    {
        QString mid, out;
        qDebug() << "bit   ====" << bit << endl;
        QTextStream oneString(&mid);
        oneString.setRealNumberNotation(QTextStream::RealNumberNotation(0));
        oneString.setRealNumberPrecision(bit);
        oneString<< in;
        oneString>> out;
        return out;
    }

    static double inline interpolation(double x1, double y1, double x2, double y2, double x)
    {
        double y  = (y2-y1)/(x2-x1)*(x-x1) + y1;
        return y;
    }
};

#endif // DIGIT_HPP
