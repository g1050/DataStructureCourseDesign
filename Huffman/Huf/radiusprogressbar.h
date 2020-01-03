#ifndef RADIUSPROGRESSBAR_H
#define RADIUSPROGRESSBAR_H

#include <QProgressBar>
#include <QDebug>

class RadiusProgressBar : public QProgressBar
{
    Q_OBJECT
public:
    explicit RadiusProgressBar(QWidget *parent = 0);

signals:

public slots:

protected:
    void paintEvent(QPaintEvent *) ;//Q_OVERRIDE;
};

#endif // RADIUSPROGRESSBAR_H
