#include "mylabel.h"

MyLabel::MyLabel(QWidget *parent) : QLabel(parent)
{

    this->setText("23333");
}

MyLabel::MyLabel(std::vector<Coordinate> *p)
{
    this->p = p;

    //this->setText("23333");
}
