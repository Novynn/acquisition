#include "stashpane.h"
#include "ui_stashpane.h"
#include "mainwindow.h"
#include "application.h"

#include "imagecache.h"
#include "itemconstants.h"
#include "filesystem.h"

#include <QGraphicsEffect>
#include <QGraphicsPixmapItem>

StashPane::StashPane(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StashPane)
{
    ui->setupUi(this);

    tabBar_ = new QTabBar(this);
    ui->verticalLayout->insertWidget(0, tabBar_);

    scene_ = new QGraphicsScene(0, 0, PIXELS_PER_SLOT * 12, PIXELS_PER_SLOT * 12, this);
    image_cache_ = new ImageCache(Filesystem::UserDir() + "/cache");

    scene_->setBackgroundBrush(Qt::black);
    ui->graphicsView->setScene(scene_);
}

StashPane::~StashPane()
{
    delete ui;
}

void StashPane::RefreshItems() {
    while (tabBar_->count() > 0) {
        tabBar_->removeTab(0);
    }
    scene_->clear();

    for (std::string tab : app_->tabs()) {
        QString tabName = QString::fromStdString(tab);
        tabBar_->addTab(tabName);
    }

    const QString tab = "$";
    for (const std::shared_ptr<Item> &item : app_->items()) {
        if (item->location().GetLabel() != tab.toStdString()) continue;
        QGraphicsPixmapItem* pix = 0;
        if (image_cache_->Exists(item->icon())) {
            QImage image = image_cache_->Get(item->icon());
            pix = scene_->addPixmap(QPixmap::fromImage(image));
        }
        else {
            QPixmap pixmap(item->w() * PIXELS_PER_SLOT, item->h() * PIXELS_PER_SLOT);
            pixmap.fill(Qt::white);
            pix = scene_->addPixmap(pixmap);
        }
        if (item->location().y() < 5) {
            pix->setOpacity(0.5);
        }
        pix->setPos(item->location().x() * PIXELS_PER_SLOT, item->location().y() * PIXELS_PER_SLOT);
    }
}

void StashPane::initialize(MainWindow* parent) {
    parent_ = parent;
    app_ = parent->application();

    RefreshItems();
}
