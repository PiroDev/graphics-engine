#include "MainWindow.hpp"

#include <QtWidgets>
#include <QGridLayout>

#include "backend.hpp"

MainWindow::MainWindow() {
    setFont(QFont("Times New Roman", 16));
    setWindowTitle(tr("3D Constructor"));

    canvas = new Canvas;
    setCentralWidget(canvas);

    createMenu();
    createObjectsBar();

    connect(objectsWidget, &ObjectsWidget::sceneChanged, canvas, &Canvas::onSceneChanged);
    connect(this, &MainWindow::sceneLoaded, objectsWidget, &ObjectsWidget::onSceneLoaded);


    for (auto widget : findChildren<QWidget*>())
        widget->setFocusPolicy(Qt::NoFocus);

    canvas->setFocusPolicy(Qt::StrongFocus);
}

void MainWindow::createMenu() {
    auto fileMenu = menuBar()->addMenu(tr("&Project"));

    auto openAct = new QAction("&Open", this);
    openAct->setShortcuts(QKeySequence::Open);
    openAct->setStatusTip(tr("Open existing project"));

    auto saveAct = new QAction("&Save", this);
    saveAct->setShortcuts(QKeySequence::Save);
    saveAct->setStatusTip(tr("Save current project"));

    connect(openAct, &QAction::triggered, this, &MainWindow::loadScene);
    connect(saveAct, &QAction::triggered, this, &MainWindow::saveScene);

    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAct);
}

void MainWindow::createObjectsBar() {
    auto rightBar = new QDockWidget(tr("Objects"), this);
    rightBar->setAllowedAreas(Qt::RightDockWidgetArea);
    addDockWidget(Qt::RightDockWidgetArea, rightBar);

    objectsWidget = new ObjectsWidget(rightBar);

    rightBar->setWidget(objectsWidget);
    rightBar->setFeatures(QDockWidget::DockWidgetFeature::NoDockWidgetFeatures);
}


void MainWindow::loadScene() {
    auto fileNameString = QFileDialog::getOpenFileName(
            this,
            tr("Load Scene File"), "",
            tr("Scene Configuration (*.scene)")
    ).toStdString();

    const char *fileName = fileNameString.c_str();

    Backend backend;
    if (backend.LoadScene(fileName)) {
        emit sceneLoaded();
    }
}

void MainWindow::saveScene() {
    auto fileNameString = QFileDialog::getSaveFileName(
            this,
            tr("Save Current Scene"), "Untitled.scene",
            tr("Scene Configuration (*.scene)")
    ).toStdString();

    if (fileNameString.find(".scene") == std::string::npos) {
        fileNameString += ".scene";
    }

    const char *fileName = fileNameString.c_str();

    Backend backend;
    backend.SaveScene(fileName);
}
