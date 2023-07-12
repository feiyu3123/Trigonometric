#ifndef TRIANGLEPOINTFORM_H
#define TRIANGLEPOINTFORM_H

#include <QWidget>

#include "triangleform.h"

namespace Ui {
class TrianglePointForm;
}

class TrianglePointForm : public QWidget
{
    Q_OBJECT
public:
    explicit TrianglePointForm(QWidget *parent = nullptr);
    ~TrianglePointForm();

    void setPointIndex(int index);
    void setTriangle(Triangle* triangle);
public Q_SLOTS:
    void onButtonModifyXY();

signals:
    void modifyFinish();

private:
    Ui::TrianglePointForm *ui;
    int mPointIndex;
    Triangle* mTriangle;
};

#endif // TRIANGLEPOINTFORM_H
