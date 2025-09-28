#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlDatabase>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    model = new QStandardItemModel(0, 2, this);
    model->setHorizontalHeaderLabels({"Имя", "Телефон"});
    ui->tableView->setModel(model);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    setFixedSize(250, 515);

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("records.db");
    db.open();

    QSqlQuery query;
    query.exec("CREATE TABLE IF NOT EXISTS records (id INTEGER PRIMARY KEY, name TEXT, phone TEXT)");
    query.exec("SELECT * FROM records");
    while (query.next())
    {
        int row = model->rowCount();
        model->insertRow(row);
        model->setData(model->index(row, 0), query.value("name").toString());
        model->setData(model->index(row, 1), query.value("phone").toString());
    }
}

MainWindow::~MainWindow()
{
    QSqlQuery query;
    query.exec("DELETE FROM records");

    for (int row = 0; row < model->rowCount(); ++row) {
        QString name = model->data(model->index(row, 0)).toString();
        QString phone = model->data(model->index(row, 1)).toString();

        query.prepare("INSERT INTO records (name, phone) VALUES (?, ?)");
        query.addBindValue(name);
        query.addBindValue(phone);
        query.exec();
    }

    delete ui;
    delete model;
    db.close();
}

void MainWindow::on_saveButton_clicked()
{
    if (ui->nameField->text().size() > 0 && ui->phoneField->text().size() > 0)
    {
        int row;
        if (ui->tableView->currentIndex().row() >= 0)
            row = ui->tableView->currentIndex().row();
        else
        {
            row = model->rowCount();
            model->insertRow(row);
        }
        model->setData(model->index(row, 0), ui->nameField->text());
        model->setData(model->index(row, 1), ui->phoneField->text());

        ui->nameField->setText("");
        ui->phoneField->setText("");
    }
}


void MainWindow::on_deleteButton_clicked()
{
    model->removeRow(ui->tableView->currentIndex().row());
}



void MainWindow::on_tableView_doubleClicked(const QModelIndex &index)
{
    int row = ui->tableView->currentIndex().row();
    ui->nameField->setText(model->data(model->index(row, 0)).toString());
    ui->phoneField->setText(model->data(model->index(row, 1)).toString());
}

