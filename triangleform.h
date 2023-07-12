#ifndef TRIANGLEFORM_H
#define TRIANGLEFORM_H

#include <QWidget>

#include "vec2.h"

namespace Ui {
class TriangleForm;
}

//
class Triangle
{
public:
    point2 points[3];
    int iPointIndex;
    Triangle()
    {
        iPointIndex=0;
    }
};


class TriangleForm : public QWidget
{
    Q_OBJECT

public:
    explicit TriangleForm(QWidget *parent = nullptr,Triangle* triangle=nullptr);
    ~TriangleForm();

private:
    Ui::TriangleForm *ui;
    Triangle* mTriangle;
};

#endif // TRIANGLEFORM_H
