#pragma once

#include <QWidget>
#include <QMouseEvent>
#include <QWheelEvent>

class Canvas : public QWidget {
public:
    explicit Canvas(QWidget *parent = nullptr);
    ~Canvas() override = default;

public slots:
    void onSceneChanged();

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private:
    Qt::MouseButton mousePressed;
    QPoint mousePrevPos;
    QImage buffer;
};