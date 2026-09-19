#ifndef FRACTALWIDGET_H
#define FRACTALWIDGET_H

#include <QMainWindow>
// #include "complexnumber.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class FractalWidget;
}
QT_END_NAMESPACE

class FractalWidget : public QMainWindow
{
    Q_OBJECT

public:
    explicit FractalWidget(QWidget *parent = nullptr);
    ~FractalWidget() override;

private:
    Ui::FractalWidget *ui;
};

#endif // FRACTALWIDGET_H
