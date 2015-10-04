#include "recipepane.h"
#include "ui_recipepane.h"

#include "mainwindow.h"
#include "application.h"
#include "item.h"
#include "external/boolinq.h"

using namespace boolinq;

RecipePane::RecipePane(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RecipePane)
{
    ui->setupUi(this);
}

RecipePane::~RecipePane()
{
    delete ui;
}

void RecipePane::initialize(MainWindow* parent) {
    parent_ = parent;
    app_ = parent->application();

    RefreshItems();
}

void RecipePane::RefreshItems() {
    auto items = app_->items();
    QMultiMap<QString, std::shared_ptr<Item>> map;
    for (const std::shared_ptr<Item> &item : items) {
        if (item->name().empty()) continue;
        if (item->frameType() != FRAME_TYPE_RARE) continue;
        if (item->location().type() == ItemLocationType::CHARACTER) continue;
        map.insert(QString::fromStdString(item->name()), item);
    }

    ui->treeWidget->clear();
    QTreeWidgetItem* chanceRoot = new QTreeWidgetItem({"Chance"});
    ui->treeWidget->addTopLevelItem(chanceRoot);
    QTreeWidgetItem* alchRoot = new QTreeWidgetItem({"Alch"});
    ui->treeWidget->addTopLevelItem(alchRoot);
    for (QString name : map.uniqueKeys()) {
        int count = map.count(name);
        QString recipe = "";

        while (count >= 2) {
            recipe = "";
            if (count >= 3) {
                recipe = "Alch";
                count -= 3;
            }
            else {
                recipe = "Chance";
                count -= 2;
            }

            if (recipe.isEmpty()) break;
            QTreeWidgetItem* root = new QTreeWidgetItem({name});
            for (const std::shared_ptr<Item> &item : map.values(name)) {
                QString loc = QString("%1 [%2,%3]").arg(item->location().GetLabel().c_str()).arg(item->location().x()).arg(item->location().y());
                root->addChild(new QTreeWidgetItem({loc}));
            }
            root->setText(0, QString("%1 (%2)").arg(root->text(0)).arg(root->childCount()));
            chanceRoot->addChild(root);
        }
    }

//    QMultiMap<int, std::shared_ptr<Item>> qualityGems;
//    for (auto &item : items) {
//        if (item->frameType() != FRAME_TYPE_GEM) continue;
//        auto qualityProp = item->properties().find("Quality");
//        QString q = QString::fromStdString(qualityProp->second);
//        int quality = 0;
//        if (!q.isEmpty()) {
//            q = q.mid(1, q.length() - 2);
//            quality = q.toInt();
//        }

//        if (quality == 0 || quality == 20) continue;
//        qualityGems.insert(quality, item);
//    }

//    FindGCP(qualityGems);
}
