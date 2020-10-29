#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    //create model
    model = new QStringListModel(this);

    //allow for widget to be edited durign runtime
    //by clicking on it
    ui->listView->setEditTriggers(QAbstractItemView::AnyKeyPressed \
                                  | QAbstractItemView::DoubleClicked);

    model = new QStringListModel(this);
    ui->listView->setModel(model);

    connect(ui->listView->model(), SIGNAL(dataChanged(QModelIndex,QModelIndex)), this, SLOT(listChanged()));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButtonAdd_clicked()
{
    //check to see if book is already in list
    QString book = ui->lineEdit->text();
    if(strList.contains(book))
    {
        //if book is already in list warn user
        QMessageBox::warning(0,"Book already exist", "Book was not inserted");
    }
    else
    {
        //else add the book to this list

        //add the title to the QStringList
        strList.append(ui->lineEdit->text());

        //note we have to order QStringList as well since because we using list to
        //delete entries and it doesn't correspond with QStringList unless both is ordered
        strList.sort();

        //set the model to the QStringList
        model->setStringList(strList);

        //sort the model, this is not neccesarry since we sorting the QStringList
        //model->sort(0);

        //glue model and view:
        ui->listView->setModel(model);
    }
}

void Widget::on_pushButtonDelete_clicked()
{
    //get row which is selected
    int row = ui->listView->currentIndex().row();
    //note: 'ui->listView->currentIndex().row()' returns the row that is selected
    //on the list view.

    QString book = strList[row];    //get book name at the selected row

    //find out if the user actually wants to delete the book title
    int choice = QInputDialog::getInt(this,"Remove",QString("Are \
you sure you want to delete: %1\n'1' for YES, '0' for NO").arg(book));

    if(choice == 1)
    {   //if user confirmed deletion then delete object

        //remove from the QStringList
        strList.removeAt(row);

        //set the model to the QStringList
        model->setStringList(strList);

        //glue model and view:
        ui->listView->setModel(model);
    }

}

void Widget::listChanged()
{
    //get the row that was selected
    int row = ui->listView->currentIndex().row();

    //get what was changed and convert
    QModelIndex item = ui->listView->currentIndex();    //get item that was changed
    QString itemText = item.data().toString();

    if(strList.contains(itemText))
    {
        //if book is already in list warn user adn do not alter
        QMessageBox::warning(0,"Book already exist", "Change will be reverted");

        //we need to revert the change that has been made, so set
        //the listView back to the QStringList

        //set the model to the QStringList
        model->setStringList(strList);
        //glue model and view:
        ui->listView->setModel(model);
    }
    else
    {
        //delete the item that was changed
        strList.removeAt(row);
        //insert it to the QStringList at correct position
        strList.insert(row, itemText);
        //sort the list
        strList.sort();
        //set the model to the QStringList
        model->setStringList(strList);
        //glue model and view:
        ui->listView->setModel(model);
    }
}

