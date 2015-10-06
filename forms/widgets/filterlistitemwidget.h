#ifndef FILTERLISTITEMWIDGET_H
#define FILTERLISTITEMWIDGET_H

#include <QWidget>

class LootFilter;

namespace Ui {
class FilterListItemWidget;
}

class FilterListItemWidget : public QWidget
{
    Q_OBJECT

public:
    explicit FilterListItemWidget(LootFilter filter, QWidget *parent = 0);
    ~FilterListItemWidget();

private:
    Ui::FilterListItemWidget *ui;
};

#endif // FILTERLISTITEMWIDGET_H
