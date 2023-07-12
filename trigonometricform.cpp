#include "trigonometricform.h"
#include "ui_trigonometricform.h"
#include <QPainter>
#include <QMouseEvent>
#include <QFontMetrics>
#include <QFont>


#include "triangleform.h"

Context exContext;

TrigonometricForm::TrigonometricForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TrigonometricForm)
{
    ui->setupUi(this);
    setMouseTracking(true);

    app_sample();
}

void TrigonometricForm::drawString(QPainter& painter,int x,int y,const QFont& font,const QString& string)
{
    QFontMetrics fm(font);
    int flags=Qt::TextWordWrap;
    auto size=fm.size(flags,string);
    QRect rect(x,y,size.width()+100,size.height()+100);
    painter.drawText(rect,flags,string);
}

void TrigonometricForm::init()
{
    if(exContext.mCoordinateSystem.init==false)
    {
        int x=width()/2;
        int y=height()/2;
        exContext.mCoordinateSystem.nZeroX=x;
        exContext.mCoordinateSystem.nZeroY=y;
        exContext.mCoordinateSystem.dScale=1.0;
        exContext.mCoordinateSystem.init=true;
    }
}

void TrigonometricForm:: paintEvent(QPaintEvent *event)
{


    QPainter painter;
    painter.begin(this);
    painter.fillRect(QRect(0,0,width(),height()),QBrush(QColor::fromRgb(255,255,255,255)));

    QPen penAxis(QBrush(QColor::fromRgb(64,64,64,64)),1);
    painter.setPen(penAxis);
    {
        //x轴
        QPoint ptBegin(0,exContext.mCoordinateSystem.nZeroY);
        QPoint ptEnd(width(),exContext.mCoordinateSystem.nZeroY);
        painter.drawLine(ptBegin,ptEnd);
        //刻度
        for(double i=(exContext.mCoordinateSystem.nZeroX%exContext.mCoordinateSystem.nMarkPixel);
            i<width();
            i+=exContext.mCoordinateSystem.nMarkPixel)
        {
            QPoint ptUnitBegin(i,exContext.mCoordinateSystem.nZeroY);
            QPoint ptUnitEnd(i,exContext.mCoordinateSystem.nZeroY-exContext.mCoordinateSystem.nMarkWidth);
            painter.drawLine(ptUnitBegin,ptUnitEnd);
        }

    }
    {
        //y轴
        QPoint ptBegin(exContext.mCoordinateSystem.nZeroX,0);
        QPoint ptEnd(exContext.mCoordinateSystem.nZeroX,height());
        painter.drawLine(ptBegin,ptEnd);
        //刻度
        for(double i=(exContext.mCoordinateSystem.nZeroY%exContext.mCoordinateSystem.nMarkPixel);
            i<height();
            i+=exContext.mCoordinateSystem.nMarkPixel)
        {
            QPoint ptUnitBegin(exContext.mCoordinateSystem.nZeroX,i);
            QPoint ptUnitEnd(exContext.mCoordinateSystem.nZeroX+exContext.mCoordinateSystem.nMarkWidth,i);
            painter.drawLine(ptUnitBegin,ptUnitEnd);
        }
    }

    QFont font(QStringLiteral("雅黑"),9);
    QPen penFont(QColor(QColor::fromRgb(0,0,255)),1);
    QPen penTriangle(QColor(QColor::fromRgb(96,96,96,96)),1);
    painter.setPen(penFont);
    painter.setFont(font);

    {//鼠标读数
        point2 p=exContext.dev2logic(exContext.mMouse.x,exContext.mMouse.y);
        QString strMouse=QString("x:%1 , y:%2").arg(p[0]).arg(p[1]);
        drawString(painter,exContext.mMouse.x+30,exContext.mMouse.y,font,strMouse);
    }

    {//绘制三角形内的数据
        for(int i=0;i<exContext.mTriangles.size();i++)
        {
            auto triangle=exContext.mTriangles[i];
            point2 A=triangle->points[0];
            point2 B=triangle->points[1];
            point2 C=triangle->points[2];

            auto dA=exContext.logic2dev(A);
            auto dB=exContext.logic2dev(B);
            auto dC=exContext.logic2dev(C);



            //绘制三条边
            auto oldPen=painter.pen();
            painter.setPen(penTriangle);
            painter.drawLine(dA[0],dA[1],dB[0],dB[1]);
            painter.drawLine(dB[0],dB[1],dC[0],dC[1]);
            painter.drawLine(dC[0],dC[1],dA[0],dA[1]);
            painter.setPen(oldPen);

            //边长
            auto ptSideC=(dA+dB)/2;
            auto ptSideB=(dA+dC)/2;
            auto ptSideA=(dC+dB)/2;

            double c_side_length=(dA-dB).length();
            double b_side_length=(dA-dC).length();
            double a_side_length=(dC-dB).length();

            QString strSideA=QString(QStringLiteral("a %1")).arg(a_side_length);
            QString strSideB=QString(QStringLiteral("b %1")).arg(b_side_length);
            QString strSideC=QString(QStringLiteral("c %1")).arg(c_side_length);

            drawString(painter,ptSideA[0],ptSideA[1],font,strSideA);
            drawString(painter,ptSideB[0],ptSideB[1],font,strSideB);
            drawString(painter,ptSideC[0],ptSideC[1],font,strSideC);

            //绘制坐标,角度
            double aC=cosine_calc_angle(c_side_length,a_side_length,b_side_length);
            double aB=cosine_calc_angle(b_side_length,a_side_length,c_side_length);
            double aA=cosine_calc_angle(a_side_length,b_side_length,c_side_length);

            QString strA=QString(QStringLiteral("A %1\n角度:%2°")).arg(A.toString().c_str()).arg(aA);
            QString strB=QString(QStringLiteral("B %1\n角度:%2°")).arg(B.toString().c_str()).arg(aB);
            QString strC=QString(QStringLiteral("C %1\n角度:%2°")).arg(C.toString().c_str()).arg(aC);

            drawString(painter,dA[0],dA[1],font,strA);
            drawString(painter,dB[0],dB[1],font,strB);
            drawString(painter,dC[0],dC[1],font,strC);

        }
    }

    painter.end();

}




void TrigonometricForm::mouseMoveEvent(QMouseEvent *event)
{
    auto pos=event->pos();
    exContext.mMouse.x=pos.x();
    exContext.mMouse.y=pos.y();
    exContext.mMouse.lastMoveTime=QDateTime::currentDateTime();
    update();
}

Triangle* TrigonometricForm::hitTest()
{
    Triangle* hitObj=nullptr;
    for(auto it=exContext.mTriangles.begin();it!=exContext.mTriangles.end();it++)
    {
        Triangle* triangle= (*it);
        if(triangle)
        {
            QPolygon polygon;

            auto dA=exContext.logic2dev(triangle->points[0]);
            auto dB=exContext.logic2dev(triangle->points[1]);
            auto dC=exContext.logic2dev(triangle->points[2]);

            polygon.append(QPoint(dA[0],dA[1]));
            polygon.append(QPoint(dB[0],dB[1]));
            polygon.append(QPoint(dC[0],dC[1]));

            if(polygon.containsPoint(QPoint(exContext.mMouse.x,exContext.mMouse.y),Qt::OddEvenFill))
            {
                hitObj=triangle;
            }

        }
    }
    return hitObj;
}

void TrigonometricForm::mousePressEvent(QMouseEvent *event)
{
    if(event->button()&Qt::MouseButton::LeftButton)
    {
        if(exContext.mTriangle==nullptr)
        {
            exContext.mTriangle=new Triangle();
            exContext.mTriangles.push_back(exContext.mTriangle);
        }

        Triangle* hitTriangle=hitTest();
        if(hitTriangle!=nullptr)//选中的三角形
        {
            TriangleForm* triangleForm=new TriangleForm(this,hitTriangle);
            triangleForm->setWindowModality(Qt::WindowModal);
            triangleForm->setAttribute(Qt::WA_ShowModal, true);    //属性设置 true:模态 false:非模态
            triangleForm->setWindowFlags(Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint | Qt::Dialog);
            triangleForm->show();

        }
        else if(exContext.mTriangle!=nullptr)//临时三角形
        {
            point2& point=exContext.mTriangle->points[exContext.mTriangle->iPointIndex++];
            point=exContext.dev2logic(exContext.mMouse.x,exContext.mMouse.y);
            if(exContext.mTriangle->iPointIndex>=3)
            {
                exContext.mTriangle->iPointIndex=0;
            }
        }
    }
}

TrigonometricForm::~TrigonometricForm()
{
    delete ui;
}
