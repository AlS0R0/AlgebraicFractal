#include "fractalwidget.h"
#include "./ui_fractalwidget.h"
// #include "complexnumber.h"

FractalWidget::FractalWidget(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::FractalWidget)
{
    ui->setupUi(this);
}

FractalWidget::~FractalWidget()
{
    delete ui;
}
