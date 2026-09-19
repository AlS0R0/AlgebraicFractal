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

QRgb getColor(const ComplexNumber& c, const double& border, int maxIter)
{
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

void FractalWidget::renderImage()
{
    image_ = QImage(size(), QImage::Format_RGB32);

    for (int py = 0; py < height(); ++py) {

        QRgb *line = reinterpret_cast<QRgb *>(image_.scanLine(py));

        for (int px = 0; px < width(); ++px) {
            ComplexNumber c = pixelToComplNum(px, py);

            line[px] = getColor(c, border_, maxIter_);
        }
    }
}

void FractalWidget::paintEvent(QPaintEvent* event)
{
    if (!viewInitialized_) {
        setView(-0.5, 0.0, 3.5 / std::max(1, width()));

        viewInitialized_ = true;
        reset_ = true;
    }

    if (reset_ || image_.size() != size()) {
        renderImage();
        reset_ = false;
    }

    QPainter painter(this);

    painter.drawImage(0, 0, image_);

    if (selected_) {
        QRectF sel_rect = QRectF(start_, end_).normalized();
        painter.setPen(QPen(Qt::red, 1));
        painter.drawRect(sel_rect);
    }

    return;
}

void FractalWidget::resizeEvent(QResizeEvent* event)
{
    if (!viewInitialized_) return;

    double upp = (xmax_ - xmin_) / std::max(1, event->oldSize().width());
    double cx = (xmin_ + xmax_) * 0.5;
    double cy = (ymin_ + ymax_) * 0.5;

    setView(cx, cy, upp);
    reset_ = true;
}

void FractalWidget::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton) {

        selected_ = true;
        start_ = end_ = event->pos();
    } else if (event->button() == Qt::RightButton) {

        setView(-0.5, 0.0, 3.5 / std::max(1, width()));

        maxIter_ = 100;
        reset_ = true;
    }

    update();
}

void FractalWidget::mouseMoveEvent(QMouseEvent* event)
{
    if (selected_) {
        end_ = event->pos();
        update();
    }
}

void FractalWidget::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() != Qt::LeftButton || !selected_) return;
    selected_ = false;

    QRectF sel = QRectF(start_, end_).normalized();

    if (sel.width() < 5 || sel.height() < 5) {
        update();
        return;
    }

    ComplexNumber topLeft = pixelToComplNum(sel.left(),  sel.top());
    ComplexNumber bottomRight = pixelToComplNum(sel.right(), sel.bottom());

    double selWc = bottomRight.real() - topLeft.real();
    double selHc = topLeft.imag() - bottomRight.imag();

    double uppX = selWc / width();
    double uppY = selHc / height();

    double upp = std::max(uppX, uppY);

    double cx = (topLeft.real() + bottomRight.real()) * 0.5;
    double cy = (topLeft.imag() + bottomRight.imag()) * 0.5;

    setView(cx, cy, upp);
    double baseUpp = 3.5 / 800.0;
    maxIter_ = std::min(1000, int(300 * std::sqrt(baseUpp / upp)));

    reset_ = true;
    update();
}

void FractalWidget::setView(double cx, double cy, double unitsPerPixel)
{
    double halfW = width()  * 0.5 * unitsPerPixel;
    double halfH = height() * 0.5 * unitsPerPixel;

    xmin_ = cx - halfW;
    xmax_ = cx + halfW;
    ymin_ = cy - halfH;
    ymax_ = cy + halfH;
}
