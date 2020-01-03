#include "manager.h"

Manager::Manager(QWidget *parent) :
    QWidget(parent)
{
    ui.setupUi(this);
}

Manager::Manager(DataBase *nsdb)
{
    ui.setupUi(this);
    this->setWindowTitle("sky西邮导航系统");
    this->nsdb = nsdb;

    //Init QSqlTableModel
    model = new QSqlTableModel(this);
    model->setTable("ACCOUNT");
    ui.tableView->setModel(model);
    model->select();

    //Hide the unnecessary column.
    ui.tableView->setColumnHidden(2,true);
    ui.tableView->setColumnHidden(4,true);
    ui.tableView->setColumnHidden(5,true);
    ui.tableView->setColumnHidden(6,true);

    //Change name
    model->setHeaderData(0,Qt::Horizontal,"昵称");
    model->setHeaderData(1,Qt::Horizontal,"账号");
    model->setHeaderData(3,Qt::Horizontal,"身份");


    //Init QSqlTableModel
    model2 = new QSqlTableModel(this);
    model2->setTable("ADJVEX");
    ui.tv_adjvex->setModel(model2);
    model2->select();

    //Change name
    model2->setHeaderData(0,Qt::Horizontal,"名字");
    model2->setHeaderData(1,Qt::Horizontal,"描述");
    model2->setHeaderData(2,Qt::Horizontal,"x坐标");
    model2->setHeaderData(3,Qt::Horizontal,"y坐标");

    //Init QSqlTableModel
    model3 = new QSqlTableModel(this);
    model3->setTable("EDGE");
    ui.tv_edge->setModel(model3);
    model3->select();

    //Change name
    model3->setHeaderData(0,Qt::Horizontal,"左端点");
    model3->setHeaderData(1,Qt::Horizontal,"右端点");
    model3->setHeaderData(2,Qt::Horizontal,"距离");
    model3->setHeaderData(3,Qt::Horizontal,"绿化程度");


}

Manager::~Manager()
{
    qDebug() << "Manager deestroy" ;
    emit returnParentUI();
}

void Manager::on_btn_submit_clicked()
{
    //emit returnParentUI();
    model->submitAll();
}

void Manager::on_btn_cancel_clicked()
{
    model->revertAll();
    model->submitAll();
}

void Manager::on_btn_search_clicked()
{
    //1 Get the name we are looking for.
    QString name = ui.ln_search->text();
    //2 Search.
    QString str = QString("NICKNAME = '%1' OR USERNAME = '%2'").arg(name,name);
    model->setFilter(str);
    model->select();
}

void Manager::on_btn_all_clicked()
{
    model->setFilter("");
    model->select();
}

void Manager::on_btn_submit_2_clicked()
{
    model2->submitAll();
}



void Manager::on_btn_cancel_2_clicked()
{
    model2->revertAll();
    model2->submitAll();
}



void Manager::on_btn_all_2_clicked()
{
    model2->setFilter("");
    model2->select();
}

void Manager::on_btn_search_2_clicked()
{
    //1 Get the name we are looking for.
    QString name = ui.ln_search_2->text();
    //2 Search.
    QString str = QString("NAME = '%1'").arg(name);
    model2->setFilter(str);
    model2->select();
}



void Manager::on_btn_add2_clicked()
{
    //创建空记录
    QSqlRecord record = model2->record();
    //获取行号
    int row = model2->rowCount();
    model2->insertRecord(row,record);
}

void Manager::on_btn_delete2_clicked()
{
    //获取选中的数据
    QItemSelectionModel *sModel = ui.tv_adjvex->selectionModel();
    //取出模型中的索引
    QModelIndexList list = sModel->selectedRows();

    //for循环删除所有的行
    for(int i = 0;i<list.size();i++){
        qDebug() << list.at(i).row();
        model2->removeRow( list.at(i).row() );
    }

    model2->setFilter("");
    model2->select();
}

void Manager::on_btn_distance_clicked()
{
    int x1,y1,x2,y2;
    //Judge if the data exist.
    if(nsdb->getCoordinate(x1,y1,ui.ln_st->text()) &&
            nsdb->getCoordinate(x2,y2,ui.ln_ed->text())){
            int res = sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2))/1;
            ui.ln_distance->setText(QString::number(res));
    }else{
        ui.ln_distance->setText("检查景点是否存在");
    }
}

void Manager::on_btn_submit_3_clicked()
{
    model3->submitAll();
}

void Manager::on_btn_cancel_3_clicked()
{
    model3->revertAll();
    model3->submitAll();
}

void Manager::on_btn_all_3_clicked()
{
    model3->setFilter("");
    model3->select();
}

void Manager::on_btn_add3_clicked()
{
    //创建空记录
    QSqlRecord record = model3->record();
    //获取行号
    int row = model3->rowCount();
    model3->insertRecord(row,record);

}

void Manager::on_btn_delete3_clicked()
{
    //获取选中的数据
    QItemSelectionModel *sModel = ui.tv_edge->selectionModel();
    //取出模型中的索引
    QModelIndexList list = sModel->selectedRows();

    //for循环删除所有的行
    for(int i = 0;i<list.size();i++){
        qDebug() << list.at(i).row();
        model3->removeRow( list.at(i).row() );
    }

    model3->setFilter("");
    model3->select();
}

void Manager::on_btn_search_3_clicked()
{
    //1 Get the name we are looking for.
    QString name = ui.ln_search_3->text();
    //2 Search.
    QString str = QString("V1 = '%1' OR V2 = '%2'").arg(name,name);
    model3->setFilter(str);
    model3->select();
}
