#include "Canvas.hpp"

#include <QPainter>
#include "backend.hpp"
#include <ctime>

Canvas::Canvas(QWidget *parent) : QWidget(parent), mousePressed(Qt::NoButton) {
    setMinimumSize(600, 600);
    setBackgroundRole(QPalette::Base);
    buffer = QImage(this->rect().size(), QImage::Format_RGB888);
}

void Canvas::paintEvent(QPaintEvent *event) {
    auto width = this->rect().width();
    auto height = this->rect().height();

    if (width == 0 || height == 0) {
        return;
    }

    ColorBuffer colorBuffer(width, height);
    Backend backend;
    auto t1 = clock();
    backend.Render(colorBuffer);
    auto t2 = clock();
    double tms = (double)(t2 - t1) * 1e3 / CLOCKS_PER_SEC;
    auto fps = std::lround(1000. / tms);

    buffer = QImage((unsigned char *)colorBuffer.Data().get(), width, height, width * 3, QImage::Format_RGB888);

    auto text = QString::number(fps) + " FPS " + QString::number(width) + "x" + QString::number(height);
    QPainter p;
    p.begin(&buffer);
    p.setPen(QPen(Qt::red));
    p.setFont(QFont("Times", 16));
    p.drawText(buffer.rect(), Qt::AlignBottom | Qt::AlignRight, text);
    p.end();

    QPainter painter(this);
    painter.drawImage(this->rect(), buffer);
}

void Canvas::resizeEvent(QResizeEvent *event) {
    buffer = QImage(event->size(), QImage::Format_RGBA64);
    update();
}

void Canvas::mousePressEvent(QMouseEvent *event) {
    mousePressed = event->button();
    mousePrevPos = event->pos();
}

float fromUnitsToRadians(float units) {
    return (float) (units * M_PI) / 180;
}

void Canvas::mouseMoveEvent(QMouseEvent *event) {
    auto mouseCurrPos = event->pos();
    auto x = mouseCurrPos.x();
    auto y = mouseCurrPos.y();

    auto w = this->width();
    auto h = this->height();

    auto dx = (float) (x - mousePrevPos.x());
    auto dy = (float) (y - mousePrevPos.y());
    float xAcceleration = 1 / (float) w;
    float yAcceleration = 1 / (float) h;

    Backend backend;
    switch (mousePressed) {
        case Qt::MouseButton::LeftButton: {
            float pitch = 360 * fromUnitsToRadians(yAcceleration * dy);
            float yaw = 360 * fromUnitsToRadians(xAcceleration * dx);
            backend.CameraPitch(pitch);
            backend.CameraYaw(yaw);
            update();
        }
            break;

        case Qt::MouseButton::RightButton:
            dx *= -xAcceleration;
            dy *= yAcceleration;

            backend.CameraMoveRightAxis(3 * dx);
            backend.CameraMoveForwardAxis(3 * dy);
            update();
            break;

        default:
            return;
    }

    mousePrevPos = mouseCurrPos;
}


void Canvas::mouseReleaseEvent(QMouseEvent *event) {
    mousePressed = Qt::MouseButton::NoButton;
}

void Canvas::onSceneChanged() {
    update();
}

void Canvas::wheelEvent(QWheelEvent *event) {
    auto angle = event->angleDelta().y();
    float ratio = 0.9;
    if (angle < 0) {
        ratio = 1 / ratio;
    }

    Backend backend;
    backend.CameraScale(ratio);
    update();

}
