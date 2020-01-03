#ifndef MANAGER_H
#define MANAGER_H

#include <QSqlTableModel>
#include <QSqlRecord>
#include "ui_manager.h"
#include "database.h"
#include <QMainWindow>

class Manager : public QWidget
{
    Q_OBJECT

public:
    explicit Manager(QWidget *parent = 0);
    Manager(DataBase *nsdb);
    ~Manager();
    void closeEvent(QCloseEvent *event)
    {
        //|窗口关闭之前需要的操作~
        emit returnParentUI();
    }
    void mousePressEvent(QMouseEvent *event)
    {
       QString msg=QString("鼠标位置:%1,%2").arg(event->pos().x()).arg(event->pos().y());
//       QPoint point = event->pos();
//       qDebug() << point;
//       x1+=10;
//       y2+=10;
//       update();
      this->ui.ln_mouse->setText(msg);
      this->ui.lb_mouse2->setText(msg);
      //qDebug() << msg ;
      update();
    }
signals:
    void returnParentUI();
private:
    DataBase *nsdb;
private slots:


    void on_btn_submit_clicked();

    void on_btn_cancel_clicked();

    void on_btn_search_clicked();

    void on_btn_all_clicked();

    void on_btn_submit_2_clicked();

    void on_btn_cancel_2_clicked();

    void on_btn_all_2_clicked();

    void on_btn_search_2_clicked();

    void on_btn_add2_clicked();

    void on_btn_delete2_clicked();

    void on_btn_distance_clicked();


    void on_btn_submit_3_clicked();

    void on_btn_cancel_3_clicked();

    void on_btn_all_3_clicked();

    void on_btn_add3_clicked();

    void on_btn_delete3_clicked();

    void on_btn_search_3_clicked();

private:
    QSqlTableModel * model;
    QSqlTableModel * model2;
    QSqlTableModel * model3;
    Ui::Manager ui;
};

#endif // MANAGER_H
