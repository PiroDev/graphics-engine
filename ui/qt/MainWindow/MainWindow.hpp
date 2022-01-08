#pragma once

#include <QMainWindow>
#include <QMenu>
#include <QAction>

#include "qt/Canvas/Canvas.hpp"
#include "qt/ObjectsWidget/ObjectsWidget.hpp"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow();

signals:
    void sceneLoaded();

private slots:
    void loadScene();
    void saveScene();

private:
    void createMenu();
    void createObjectsBar();

    Canvas *canvas;
    ObjectsWidget *objectsWidget;
};
