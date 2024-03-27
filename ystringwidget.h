#ifndef YSTRINGWIDGET_H
#define YSTRINGWIDGET_H

#include <QWidget>
#include <QPicture>
#include <QPainter>

class YStringWidget : public QWidget
{
    Q_OBJECT
private:
    QPicture picture;
public:
    explicit YStringWidget(QWidget *parent = nullptr);
    ~YStringWidget();
public:
    void recievePicture(QPicture * pic);
protected:
    void paintEvent(QPaintEvent * event);
    void resizeEvent(QResizeEvent * event);
};

#endif // YSTRINGWIDGET_H
