#ifndef LOOTFILTERPANE_H
#define LOOTFILTERPANE_H

#include <QWidget>

class MainWindow;
class Application;

namespace Ui {
class LootFilterPane;
}

struct LootFilter {
    QString file;
    QString name;
    QString author;
    QString description;
    int vMinor;
    int vMajor;
};

struct LootFilterCondition {

};

struct LootFilterAction {
    enum LootFilterActionType {
        ACTION_SETBORDERCOLOR,
        ACTION_SETTEXTCOLOR,
        ACTION_SETBACKGROUNDCOLOR,
        ACTION_PLAYALERTSOUND,
        ACTION_SETFONTSIZE
    };

    LootFilterActionType type;

    union {
        struct { int r, g, b, a; };
        struct { int id, volume; };
        struct { int fontSize; };
    } value;
};

struct LootFilterBlock {
    bool show;
    QList<LootFilterCondition> conditions;
    QList<LootFilterAction> actions;
};

class LootFilterPane : public QWidget
{
    Q_OBJECT

public:
    explicit LootFilterPane(QWidget *parent = 0);
    ~LootFilterPane();

    void initialize(MainWindow *parent);

    // QPixmap GeneratePixmapForItem(const std::shared_ptr<Item> item);

    //QHash<QString, std::function<bool(const std::shared_ptr<Item>&)> > templateMatchers;
private:
    Ui::LootFilterPane *ui;

    MainWindow* parent_;
    Application* app_;
};

#endif // LOOTFILTERPANE_H
