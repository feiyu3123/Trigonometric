#include "triangleform.h"
#include "ui_triangleform.h"

TriangleForm::TriangleForm(QWidget *parent,Triangle* triangle) :
    QWidget(parent),
    ui(new Ui::TriangleForm),
    mTriangle(triangle)
{
    ui->setupUi(this);

    ui->mPointForm1->setTriangle(triangle);
    ui->mPointForm2->setTriangle(triangle);
    ui->mPointForm3->setTriangle(triangle);

    ui->mPointForm1->setPointIndex(0);
    ui->mPointForm2->setPointIndex(1);
    ui->mPointForm3->setPointIndex(2);


    connect(ui->mPointForm1,SIGNAL(modifyFinish()),parent,SLOT(update()));
    connect(ui->mPointForm2,SIGNAL(modifyFinish()),parent,SLOT(update()));
    connect(ui->mPointForm3,SIGNAL(modifyFinish()),parent,SLOT(update()));


}

TriangleForm::~TriangleForm()
{
    delete ui;
}


