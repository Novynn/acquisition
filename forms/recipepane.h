#ifndef RECIPEPANE_H
#define RECIPEPANE_H

#include <QWidget>
#include <item.h>

class MainWindow;
class Application;

#include "memory"

namespace Ui {
class RecipePane;
}

class RecipePane : public QWidget
{
    Q_OBJECT

public:
    explicit RecipePane(QWidget *parent = 0);
    ~RecipePane();

    void initialize(MainWindow *parent);
    void RefreshItems();
    void FindQuality(QList<int> *qualities, QList<int> partials, QList<QList<int> > *combinations, int goal=40);
private:
    Ui::RecipePane *ui;

    MainWindow* parent_;
    Application* app_;
    void FindGCP(QMultiMap<int, std::shared_ptr<Item> > qualities);
};

#endif // RECIPEPANE_H
