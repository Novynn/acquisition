#ifndef STASHPANE_H
#define STASHPANE_H

#include <QGraphicsScene>
#include <QTabBar>
#include <QWidget>

class MainWindow;
class Application;
class ImageCache;

namespace Ui {
class StashPane;
}

class StashPane : public QWidget
{
    Q_OBJECT

public:
    explicit StashPane(QWidget *parent = 0);
    ~StashPane();

    void initialize(MainWindow *parent);
    void RefreshItems();
private:
    Ui::StashPane *ui;

    MainWindow* parent_;
    Application* app_;

    QTabBar* tabBar_;
    QGraphicsScene* scene_;
    ImageCache* image_cache_;
};

#endif // STASHPANE_H
