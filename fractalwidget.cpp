#include "fractalwidget.h"
#include "./ui_fractalwidget.h"

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

QRgb getColor(const ComplexNumber& c, const double& border)
{
    const int maxIter = 300;
    ComplexNumber res_num;
    int iter = 0;

    while (iter < maxIter && res_num.radius() < border) {
        res_num = res_num.square() + c;
        ++iter;
    }

    if (iter == maxIter) return qRgb(0, 0, 0);

    double t = sqrt(double(iter) / maxIter);

    int r = 0;
    int g = static_cast<int>(255 * t);
    int b = 0;

    return qRgb(r, g, b);
}

ComplexNumber FractalWidget::pixelToComplNum(const double& px, const double& py)
{
    double re = xmin_ + (px / width()) * (xmax_ - xmin_);
    double im = ymax_ - (py / height()) * (ymax_ - ymin_);

    ComplexNumber res(re, im);
    return res;
}

// void FractalWidget::renderImage()
// {
//     image_ = QImage(size(), QImage::Format_RGB32);

//     for (int py = 0; py < height(); ++py) {

//         QRgb *line = reinterpret_cast<QRgb *>(image_.scanLine(py));

//         for (int px = 0; px < width(); ++px) {
//             ComplexNumber c = pixelToComplNum(px, py);

//             line[px] = getColor(c, border_);
//         }
//     }
// }

void FractalWidget::renderImage()
{
    image_ = QImage(size(), QImage::Format_RGB32);

    const int SS = 2;
    const double inv = 1.0 / (SS * SS);

    for (int py = 0; py < height(); ++py) {
        QRgb *line = reinterpret_cast<QRgb *>(image_.scanLine(py));

        for (int px = 0; px < width(); ++px) {
            int r = 0, g = 0, b = 0;

            for (int sy = 0; sy < SS; ++sy) {
                for (int sx = 0; sx < SS; ++sx) {
                    double fx = px + (sx + 0.5) / SS;
                    double fy = py + (sy + 0.5) / SS;

                    ComplexNumber c = pixelToComplNum(fx, fy);
                    QRgb col = getColor(c, border_);

                    r += qRed(col);
                    g += qGreen(col);
                    b += qBlue(col);
                }
            }

            line[px] = qRgb(int(r * inv), int(g * inv), int(b * inv));
        }
    }
}

void FractalWidget::paintEvent(QPaintEvent* event)
{
    renderImage();
    QPainter painter(this);

    painter.drawImage(0, 0, image_);
    return;
}
