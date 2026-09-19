#ifndef FRACTALWIDGET_H
#define FRACTALWIDGET_H

#include <QMainWindow>
#include <QPaintEvent>
#include <QPainter>
#include "complexnumber.h"

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

    friend QRgb getColor(ComplexNumber arg, const double& border);

protected:
    ComplexNumber pixelToComplNum(const double& px, const double& py);
    void renderImage();

    void paintEvent(QPaintEvent* event) override;

private:
    Ui::FractalWidget *ui;
    QImage image_;
    double border_ = 4.0;

    double xmin_ = -2.0, xmax_ = 0.5;
    double ymin_ = -1.25, ymax_ = 1.25;
};

#endif // FRACTALWIDGET_H