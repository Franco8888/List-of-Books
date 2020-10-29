#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QModelIndex>
#include <QStringListModel>
#include <QStringList>
#include <QString>
#include <QMessageBox>
#include <QInputDialog>
#include <QObject>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT
public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_pushButtonAdd_clicked();
    void on_pushButtonDelete_clicked();
    void listChanged();

private:
    Ui::Widget *ui;
    QStringListModel *model;
    QStringList strList;
};

#endif // WIDGET_H
