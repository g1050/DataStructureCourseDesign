#ifndef REGISTER_H
#define REGISTER_H

#include "ui_register.h"
#include "common.h"
#include "account.h"
#include "database.h"

class Register : public QDialog
{
    Q_OBJECT

public:
    explicit Register(QWidget *parent);
    Register(DataBase *nsdb);

private slots:
    void on_btn_reg_clicked();

private:
    DataBase *nsdb;
    Ui::Register ui;
};

#endif // REGISTER_H
