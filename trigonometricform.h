#ifndef TRIGONOMETRICFORM_H
#define TRIGONOMETRICFORM_H

#include <QWidget>
#include <QDateTime>


#include "vec2.h"
#include "triangleform.h"


namespace Ui {
class TrigonometricForm;
}

class CoordinateSystem
{
public:
    int nZeroX;//0点x位置
    int nZeroY;//0点y位置
    int nMarkPixel;//1格刻度(多少个单元像素)
    int nMarkWidth;//1格刻度绘制宽度
    double dScale;//缩放比例
    bool init;//是否初始化
    CoordinateSystem()
    {
        init=false;
        nMarkPixel=100;
        nMarkWidth=10;
    }
};

class Mouse
{
public:
    int x;
    int y;
    QDateTime lastMoveTime;
};





class Context
{
public:
    CoordinateSystem mCoordinateSystem;
    Mouse mMouse;
    point2 dev2logic(int x,int y)
    {
        int x0=x-mCoordinateSystem.nZeroX;
        int y0=mCoordinateSystem.nZeroY-y;
        point2 p;
        p[0]=x0;
        p[1]=y0;
        return p;
    }

    point2 logic2dev(const point2& p)
    {
        int x0=p[0]+mCoordinateSystem.nZeroX;
        int y0=mCoordinateSystem.nZeroY-p[1];
        point2 dp(x0,y0);
        return dp;
    }


    QVector<Triangle*> mTriangles;
    Triangle* mTriangle;
    Context()
    {
        mTriangle=nullptr;
    }
};

extern Context exContext;











//


class TrigonometricForm : public QWidget
{
    Q_OBJECT
public:
    explicit TrigonometricForm(QWidget *parent = nullptr);
    ~TrigonometricForm();

    void init();
    Triangle* hitTest();
    void drawString(QPainter& painter,int x,int y,const QFont& font,const QString& string);
    void paintEvent(QPaintEvent *event) override;

    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void drawString();

private:
    Ui::TrigonometricForm *ui;
};

#endif // TRIGONOMETRICFORM_H
