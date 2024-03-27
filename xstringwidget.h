#ifndef XSTRINGWIDGET_H
#define XSTRINGWIDGET_H

#include <QWidget>
#include <QPicture>
#include <QPainter>

class XStringWidget : public QWidget
{
    Q_OBJECT
private:
    QPicture picture;
public:
    explicit XStringWidget(QWidget *parent = nullptr);
    ~XStringWidget();

protected:
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent * event);

public:
    void recievePicture(QPicture * image);
};

#endif // XSTRINGWIDGET_H
