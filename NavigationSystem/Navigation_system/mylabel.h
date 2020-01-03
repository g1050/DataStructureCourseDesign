#ifndef MYLABEL_H
#define MYLABEL_H

#include <QWidget>
#include <QLabel>
#include "common.h"

class MyLabel : public QLabel
{
    Q_OBJECT
private:
       std::vector<Coordinate> *p;
public:
    explicit MyLabel(QWidget *parent = 0);
    MyLabel(std::vector<Coordinate> *p);

    void paintEvent(QPaintEvent *)
    {
        //QPainter p(this);
        QPainter p;

        QPixmap mypix("/home/gxk/图片/xiyoulinux.png");

        QPen pen;
        pen.setWidth(5);
        pen.setColor(Qt::red);
        pen.setStyle(Qt::SolidLine);

        p.begin(this);
        p.setPen(pen);

        int size = this->p->size();
        qDebug() << "size = " <<size;
        if(size != 0){
            for(std::vector<Coordinate>::iterator it = this->p->begin(); it != this->p->end();it++){
                int x1 = it->x,y1 = it->y;
                it++;
                int x2 = it->x,y2 = it->y;
                qDebug() << x1 << " " << y1 << " " << x2 << " " << y2;
                p.drawLine(x1,y1,x2,y2);
            }
        }
    }

signals:

public slots:
};

#endif // MYLABEL_H
