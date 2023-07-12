#include "trianglepointform.h"
#include "ui_trianglepointform.h"

#include <QGroupBox>

TrianglePointForm::TrianglePointForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TrianglePointForm),
    mTriangle(nullptr)
{
    ui->setupUi(this);

    connect(ui->mButtonModifyXY,SIGNAL(clicked(bool)),this,SLOT(onButtonModifyXY()));
}

TrianglePointForm::~TrianglePointForm()
{
    delete ui;
}

void TrianglePointForm::onButtonModifyXY()
{
    double x=ui->mX->text().toDouble();
    double y=ui->mY->text().toDouble();
    mTriangle->points[mPointIndex][0]=x;
    mTriangle->points[mPointIndex][1]=y;

    emit modifyFinish();
}


void TrianglePointForm::setTriangle(Triangle* triangle)
{
    mTriangle=triangle;
}

void TrianglePointForm::setPointIndex(int index)
{
    mPointIndex= index;

    char labels[3]={'A','B','C'};

    char mainLabel=labels[mPointIndex];
    QString strMainLabel=QString(QStringLiteral("%1 点")).arg(mainLabel);
    ui->mGroupBox->setTitle(strMainLabel);


    //点的坐标
    double x=mTriangle->points[mPointIndex][0];
    double y=mTriangle->points[mPointIndex][1];

    QString strX=QString("%1").arg(x);
    QString strY=QString("%1").arg(y);

    ui->mX->setText(strX);
    ui->mY->setText(strY);

    //


}
