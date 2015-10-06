#include "filterlistitemwidget.h"
#include "ui_filterlistitemwidget.h"

#include "../lootfilterpane.h"

FilterListItemWidget::FilterListItemWidget(LootFilter filter, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FilterListItemWidget)
{
    ui->setupUi(this);

    // Setup details
    ui->nameLabel->setText(filter.name);
    if (filter.author.isEmpty()) {
        ui->authorLabel->hide();
        ui->label->hide();
    }
    else ui->authorLabel->setText(filter.author);

    if (filter.vMajor == 0 && filter.vMinor == 0) ui->versionLabel->hide();
    else ui->versionLabel->setText(QString("v%1.%2").arg(filter.vMajor).arg(filter.vMinor));

    if (filter.description.isEmpty()) ui->descLabel->hide();
    else ui->descLabel->setText(filter.description);

    if (filter.file.isEmpty()) ui->fileLabel->hide();
    else ui->fileLabel->setText(filter.file);
}

FilterListItemWidget::~FilterListItemWidget()
{
    delete ui;
}
