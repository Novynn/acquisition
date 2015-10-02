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

    // RefreshItems();
}

/*
 * def subset_sum(numbers, target, partial=[]):
    s = sum(partial)

    # check if the partial sum is equals to target
    if s == target:
        print "sum(%s)=%s" % (partial, target)
    if s >= target:
        return  # if we reach the number why bother to continue

    for i in range(len(numbers)):
        n = numbers[i]
        remaining = numbers[i+1:]
        subset_sum(remaining, target, partial + [n])
*/

void RecipePane::FindQuality(QList<int> *qualities, QList<int> partials, QList<QList<int>> *combinations, int goal) {
    int sum = from(partials.toStdList()).sum();

    if (sum == goal) {
        combinations->append(partials);

        for (int i : partials) {
            qualities->removeOne(i);
        }
        return;
    }
    else if (sum > goal) {
        return;
    }

    for(int quality = 1; quality < 20; quality++) {
        if (!qualities->contains(quality)) continue;
        QList<int> current = partials;
        current.append(quality);
        FindQuality(qualities, current, combinations, goal);
    }
}

void RecipePane::FindGCP(QMultiMap<int, std::shared_ptr<Item>> qualities) {
    QList<QList<int>> result;

    QList<int> keys = qualities.keys();

    for (int i = 40; i < 46; i++) {
        qDebug() << "Finding gems that add to " << i << " out of " << keys;
        FindQuality(&keys, {}, &result, i);

        while (!result.isEmpty()) {
            QList<int> r = result.takeFirst();
            int sum = from(r.toStdList()).sum();
            qDebug() << qPrintable("\tGems that add to " + QString::number(sum) + "%:");
            for (int q : r) {
                std::shared_ptr<Item> item = qualities.value(q);
                if (item != 0) {
                    qualities.remove(q, item);
                    qDebug() << qPrintable("\t\t" + QString::fromStdString(item->typeLine()) + " (+" + QString::number(q) + "%)");
                }
                else {
                    qDebug() << "\t\tFailed on result: " << r;
                    break;
                }
            }

//            FindQuality(qualities.keys(), {}, &result, i);
        }
    }
}

void RecipePane::RefreshItems() {
    return;
    auto items = app_->items();
    QMultiMap<QString, std::shared_ptr<Item>> map;
    for (auto &item : items) {
        if (item->name().empty()) continue;
        //if (item->frameType() != FRAME_TYPE_RARE) continue;
        map.insert(QString::fromStdString(item->name()), item);
    }

    ui->listWidget->clear();
    for (QString name : map.uniqueKeys()) {
        int count = map.count(name);
        QString recipe = "";

        while (count > 0) {
            recipe = "";
            if (count >= 3) {
                recipe = "Alch";
                count -= 3;
            }
            else if (count >= 2) {
                recipe = "Chance";
                count -= 2;
            }

            if (recipe.isEmpty()) break;
            ui->listWidget->addItem(QString("%1 [%2]").arg(name).arg(recipe));
        }
    }

    QMultiMap<int, std::shared_ptr<Item>> qualityGems;
    for (auto &item : items) {
        if (item->frameType() != FRAME_TYPE_GEM) continue;
        auto qualityProp = item->properties().find("Quality");
        QString q = QString::fromStdString(qualityProp->second);
        int quality = 0;
        if (!q.isEmpty()) {
            q = q.mid(1, q.length() - 2);
            quality = q.toInt();
        }

        if (quality == 0 || quality == 20) continue;
        qualityGems.insert(quality, item);
    }

    FindGCP(qualityGems);
}
