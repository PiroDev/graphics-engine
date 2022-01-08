#include "ObjectsWidget.hpp"

#include <QVBoxLayout>
#include <QGroupBox>
#include <QPushButton>
#include <QLabel>
#include <QListView>
#include <QStringListModel>

#include "backend.hpp"

ObjectsWidget::ObjectsWidget(QWidget *parent) : QWidget(parent) {
    auto mainLayout = new QVBoxLayout;
    auto addObjGb = new QGroupBox(this);
    auto addObjGbLayout = new QHBoxLayout(addObjGb);

    selectSizeCbx = new QComboBox(addObjGb);
    auto lblBrick = new QLabel("Brick", addObjGb);
    selectSizeCbx->addItem("1x1", QSize(1, 1));
    selectSizeCbx->addItem("1x2", QSize(1, 2));
    selectSizeCbx->addItem("2x2", QSize(2, 2));
    selectSizeCbx->addItem("2x3", QSize(2, 3));
    selectSizeCbx->addItem("3x3", QSize(3, 3));

    auto btnAdd = new QPushButton(tr("Add"), addObjGb);
    connect(btnAdd, &QPushButton::released, this, &ObjectsWidget::onBtnAddClick);

    addObjGbLayout->addWidget(lblBrick);
    addObjGbLayout->addWidget(selectSizeCbx);
    addObjGbLayout->addWidget(btnAdd);

    mainLayout->addWidget(addObjGb);

    auto objListGb = new QGroupBox(this);
    auto objListLayout = new QVBoxLayout(objListGb);
    objList = new QListView(objListGb);
    auto model = new QStringListModel(this);
    objList->setModel(model);

    objList->setStyleSheet("QListView::item:!active { color: black; }");
    objList->setEditTriggers(QAbstractItemView::NoEditTriggers);
    connect(objList->selectionModel(), &QItemSelectionModel::selectionChanged,
            this,
            &ObjectsWidget::onSelectionChanged);


    auto btnDel = new QPushButton(tr("Remove selected"), objListGb);
    connect(btnDel, &QPushButton::released, this, &ObjectsWidget::onBtnRemoveClick);

    objListLayout->addWidget(objList);
    objListLayout->addWidget(btnDel);

    mainLayout->addWidget(objListGb);

    auto posGb = new QGroupBox(tr("Transform selected"), this);
    auto posLayout = new QGridLayout(posGb);
    auto btnRotClock = new QPushButton("⟳", posGb);
    auto btnMoveForward = new QPushButton("↑", posGb);
    auto btnRotCounterClock = new QPushButton("⟲", posGb);
    auto btnMoveLeft = new QPushButton("←", posGb);
    auto btnMoveRight = new QPushButton("→", posGb);
    auto btnMoveDown = new QPushButton("Down", posGb);
    auto btnMoveBackward = new QPushButton("↓", posGb);
    auto btnMoveUp = new QPushButton("Up", posGb);

    connect(btnRotClock, &QPushButton::released, this, &ObjectsWidget::onBtnRotClockClick);
    connect(btnMoveForward, &QPushButton::released, this, &ObjectsWidget::onBtnMoveForwardClick);
    connect(btnRotCounterClock, &QPushButton::released, this, &ObjectsWidget::onBtnRotCounterClockClick);
    connect(btnMoveLeft, &QPushButton::released, this, &ObjectsWidget::onBtnMoveLeftClick);
    connect(btnMoveRight, &QPushButton::released, this, &ObjectsWidget::onBtnMoveRightClick);
    connect(btnMoveDown, &QPushButton::released, this, &ObjectsWidget::onBtnMoveDownClick);
    connect(btnMoveBackward, &QPushButton::released, this, &ObjectsWidget::onBtnMoveBackwardClick);
    connect(btnMoveUp, &QPushButton::released, this, &ObjectsWidget::onBtnMoveUpClick);


    posLayout->addWidget(btnRotCounterClock, 0, 1, 1, 1);
    posLayout->addWidget(btnMoveForward, 0, 2, 1, 1);
    posLayout->addWidget(btnRotClock, 0, 3, 1, 1);
    posLayout->addWidget(btnMoveLeft, 1, 1, 1, 1);
    posLayout->addWidget(btnMoveBackward, 1, 2, 1, 1);
    posLayout->addWidget(btnMoveRight, 1, 3, 1, 1);
    posLayout->addWidget(btnMoveUp, 0, 0, 1, 1);
    posLayout->addWidget(btnMoveDown, 1, 0, 1, 1);

    mainLayout->addWidget(posGb);

    mainLayout->setSizeConstraint(QLayout::SetFixedSize);

    setLayout(mainLayout);
}

void ObjectsWidget::onBtnAddClick() {
    Backend backend;
    auto qVar = selectSizeCbx->currentData();
    auto size = qVar.value<QSize>();
    unsigned w = size.width();
    unsigned l = size.height();
    BrickGenerationParams params{w, l, 1, 0.5, 16};
    backend.AddModel(params);
    auto name = selectSizeCbx->currentText();
    auto model = objList->model();
    if (model->insertRow(model->rowCount())) {
        QModelIndex index = model->index(model->rowCount() - 1, 0);
        model->setData(index, "Brick " + name);
        objList->selectionModel()->select(index, QItemSelectionModel::ClearAndSelect);
    }

    emit sceneChanged();
}

void ObjectsWidget::onBtnRemoveClick() {
    auto indexes = objList->selectionModel()->selection().indexes();
    if (!indexes.empty()) {
        Backend backend;
        for (auto index = indexes.end() - 1; index >= indexes.begin(); index--) {
            auto row = index->row();
            backend.RemoveModel(row);
            objList->model()->removeRow(row);
        }
        objList->selectionModel()->clearSelection();
        emit sceneChanged();
    }
}

void ObjectsWidget::onSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected) {
    Backend backend;

    for (auto index : deselected.indexes()) {
        auto row = index.row();
        backend.RemoveWireFramed(row);
    }

    if (!selected.indexes().empty()) {
        for (auto index : selected.indexes()) {
            auto row = index.row();
            backend.AddWireFramed(row);
        }
    } else {
        for (auto i = 0; i < objList->model()->rowCount(); i++) {
            backend.RemoveWireFramed(i);
        }
    }
    emit sceneChanged();
}

void ObjectsWidget::onBtnRotClockClick() {
    auto indexes = objList->selectionModel()->selection().indexes();
    if (!indexes.empty()) {
        Backend backend;
        for (auto index = indexes.end() - 1; index >= indexes.begin(); index--) {
            auto row = index->row();
            backend.ModelRotateAroundUpAxis(row, M_PI / 2);
        }
        emit sceneChanged();
    }
}

void ObjectsWidget::onBtnMoveForwardClick() {
    auto indexes = objList->selectionModel()->selection().indexes();
    if (!indexes.empty()) {
        Backend backend;
        for (auto index = indexes.end() - 1; index >= indexes.begin(); index--) {
            auto row = index->row();
            backend.ModelMoveForwardAxis(row, 0.5);
        }
        emit sceneChanged();
    }
}

void ObjectsWidget::onBtnRotCounterClockClick() {
    auto indexes = objList->selectionModel()->selection().indexes();
    if (!indexes.empty()) {
        Backend backend;
        for (auto index = indexes.end() - 1; index >= indexes.begin(); index--) {
            auto row = index->row();
            backend.ModelRotateAroundUpAxis(row, -M_PI / 2);
        }
        emit sceneChanged();
    }
}

void ObjectsWidget::onBtnMoveLeftClick() {
    auto indexes = objList->selectionModel()->selection().indexes();
    if (!indexes.empty()) {
        Backend backend;
        for (auto index = indexes.end() - 1; index >= indexes.begin(); index--) {
            auto row = index->row();
            backend.ModelMoveRightAxis(row, -0.5);
        }
        emit sceneChanged();
    }
}

void ObjectsWidget::onBtnMoveRightClick() {
    auto indexes = objList->selectionModel()->selection().indexes();
    if (!indexes.empty()) {
        Backend backend;
        for (auto index = indexes.end() - 1; index >= indexes.begin(); index--) {
            auto row = index->row();
            backend.ModelMoveRightAxis(row, 0.5);
        }
        emit sceneChanged();
    }
}

void ObjectsWidget::onBtnMoveDownClick() {
    auto indexes = objList->selectionModel()->selection().indexes();
    if (!indexes.empty()) {
        Backend backend;
        for (auto index = indexes.end() - 1; index >= indexes.begin(); index--) {
            auto row = index->row();
            backend.ModelMoveUpAxis(row, -0.5);
        }
        emit sceneChanged();
    }
}

void ObjectsWidget::onBtnMoveBackwardClick() {
    auto indexes = objList->selectionModel()->selection().indexes();
    if (!indexes.empty()) {
        Backend backend;
        for (auto index = indexes.end() - 1; index >= indexes.begin(); index--) {
            auto row = index->row();
            backend.ModelMoveForwardAxis(row, -0.5);
        }
        emit sceneChanged();
    }
}

void ObjectsWidget::onBtnMoveUpClick() {
    auto indexes = objList->selectionModel()->selection().indexes();
    if (!indexes.empty()) {
        Backend backend;
        for (auto index = indexes.end() - 1; index >= indexes.begin(); index--) {
            auto row = index->row();
            backend.ModelMoveUpAxis(row, 0.5);
        }
        emit sceneChanged();
    }
}

void ObjectsWidget::onSceneLoaded() {
    Backend backend;
    auto modelsParams = backend.GetModelsGenerationParams();
    auto model = objList->model();
    objList->selectionModel()->clearSelection();
    model->removeRows(0, model->rowCount());
    for (const auto &param : modelsParams) {
        QString name = QString::number(param.wSections) + "x" + QString::number(param.lSections);
        if (model->insertRow(model->rowCount())) {
            QModelIndex index = model->index(model->rowCount() - 1, 0);
            model->setData(index, "Brick " + name);
        }
    }
}
