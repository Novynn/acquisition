#include "lootfilterpane.h"
#include "ui_lootfilterpane.h"

#include "mainwindow.h"

#include <forms/widgets/filterlistitemwidget.h>

LootFilterPane::LootFilterPane(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LootFilterPane)
{
    ui->setupUi(this);
}

LootFilterPane::~LootFilterPane()
{
    delete ui;
}

void LootFilterPane::initialize(MainWindow* parent) {
    parent_ = parent;
    app_ = parent->application();

    const QString path = "E:/Rory/Documents/My Games/Path of Exile/";

    QList<LootFilter> availableFilters = {};
    LootFilter none = {};
    none.name = "None";
    none.description = "The default look of Path of Exile.";
    availableFilters.append(none);

    LootFilter test = {};
    test.name = "Test";
    test.author = "Novynn";
    test.description = "This is a test filter.";
    test.file = "test.filter";
    test.vMajor = 1;
    test.vMinor = 0;
    availableFilters.append(test);

    for (LootFilter filter : availableFilters) {
        FilterListItemWidget* w = new FilterListItemWidget(filter);

        QListWidgetItem* i = new QListWidgetItem;
        i->setSizeHint(w->sizeHint());
        ui->listWidget->addItem(i);
        ui->listWidget->setItemWidget(i, w);
    }
}

#if 0
void LootFilterPane::ParseActiveFilter(const QString &filter) {
    LootFilterBlock block;
    LootFilterAction action;
    for (const QString rawLine : filter.split("\n", QString::SkipEmptyParts)) {
        QString line = rawLine.trimmed();
        if (line == "Show" || line == "Hide") {
            block = {};
            block.show == (line == "Show");
        }
        else if (line.indexOf("SetBorderColor")) {
            action = {};
            action.type = LootFilterAction::ACTION_SETBORDERCOLOR;

            block.actions.append(action);
        } // <Red> <Green> <Blue> [Alpha]	0-255	Sets the border colour of the item box in RGB values from 0-255 with optional Alpha (opacity) value of 0-255
        else if (command == "SetTextColor") {
        } // <Red> <Green> <Blue> [Alpha]	0-255	Sets the text colour of the item box in RGB values from 0-255 with optional Alpha (opacity) value of 0-255
        else if (command == "SetBackgroundColor") {
        } // <Red> <Green> <Blue> [Alpha]	0-255	Sets the colour of the item box in RGB values from 0-255 with optional Alpha (opacity) value of 0-255
        else if (command == "PlayAlertSound") {
        } // <Id> [Volume]	1-9 [0-300]	Plays the specified Alert Sound with optional volume when dropped. Only one sound can be played at a time.
        else if (command == "SetFontSize") {
        } // <FontSize>")
    }
}

QPixmap LootFilterPane::GeneratePixmapForItem(const std::shared_ptr<Item> item) {
    QPixmap pix = QPixmap(80, 22);
    QPainter painter(&pix);
    painter.fillRect(pix.rect(), Qt::Black);
    painter.setPen(Qt::white);
    painter.drawRect(pix.rect());
}
#endif
