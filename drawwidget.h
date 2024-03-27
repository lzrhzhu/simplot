#ifndef AXISWIDGET_H
#define AXISWIDGET_H

#include <QWidget>
#include <QPicture>


class DrawWidget : public QWidget
{
    Q_OBJECT
private:
    QPicture picture;
protected:
    void paintEvent(QPaintEvent * Event);
    void resizeEvent(QResizeEvent * event);
public:

    DrawWidget(QWidget *parent = nullptr);
    ~DrawWidget();
    void recievePicture(QPicture * pic);
    void recieveDrawType(int type);
};

#endif // AXISWIDGET_H
