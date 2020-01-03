#ifndef FIND_H
#define FIND_H

#include "ui_find.h"
#include "common.h"
#include "account.h"
#include "database.h"

class Find : public QDialog
{
    Q_OBJECT

public:
    explicit Find(QWidget *parent = 0);
    Find(DataBase *nsdb);

private slots:
    void on_pushButton_clicked();

private:
    DataBase *nsdb;
    Ui::find ui;
};

#endif // FIND_H
