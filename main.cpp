//  #include "widget.h"

#include "args.h"
#include "core.h"
#include "parentwidget.h"
#include "drawwidget.h"

#include <QApplication>
#include <QObject>
#include <QVector>


using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Args *arg = new Args(argc, argv);
    Core *core= new Core;
    ParentWidget * parentWidget = new ParentWidget( nullptr);
    QObject::connect(   arg,                     &Args::sendDataXY,
                        core,                    &Core::recieveDataXY);
    QObject::connect(   arg,                     &Args::sendXAxis,
                        core,                    &Core::recieveXAxis);
    QObject::connect(   arg,                     &Args::sendYAxis,
                        core,                    &Core::recieveYAxis);
    QObject::connect(   arg,                     &Args::sendDrawType,
                        core,                    &Core::recieveDrawType);
    QObject::connect(   core,                    &Core::sendAxisDataPicture,
                        parentWidget->draw,      &DrawWidget::recievePicture);
    QObject::connect(   core,                    &Core::sendXTicksStringPicture,
                        parentWidget->xString,   &XStringWidget::recievePicture);
    QObject::connect(   core,                    &Core::sendYTicksStringPicture,
                        parentWidget->yString,   &YStringWidget::recievePicture);
    arg->analyzeArgs();
    arg->runArgs();
    core->render();
    parentWidget->showAll();
    return a.exec();
}
