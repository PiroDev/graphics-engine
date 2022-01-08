#pragma once
#include <QWidget>
#include <QComboBox>
#include <QItemSelection>
#include <QListView>

class ObjectsWidget : public QWidget {
Q_OBJECT

public:
    explicit ObjectsWidget(QWidget *parent = nullptr);
    ~ObjectsWidget() override = default;

signals:
    void sceneChanged();

public slots:
    void onSceneLoaded();

private slots:
    void onBtnAddClick();
    void onBtnRemoveClick();
    void onBtnRotClockClick();
    void onBtnMoveForwardClick();
    void onBtnRotCounterClockClick();
    void onBtnMoveLeftClick();
    void onBtnMoveRightClick();
    void onBtnMoveDownClick();
    void onBtnMoveBackwardClick();
    void onBtnMoveUpClick();
    void onSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected);

private:
    QComboBox *selectSizeCbx;
    QListView *objList;
};
