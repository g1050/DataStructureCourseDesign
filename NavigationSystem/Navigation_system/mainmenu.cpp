#include "mainmenu.h"


MainMenu::MainMenu(QWidget *parent) :
    QWidget(parent)
{
    ui.setupUi(this);
}

MainMenu::MainMenu(QString username,int type,DataBase *nsdb)
{
    ui.setupUi(this);
    manager = new Manager(nsdb);
    connect(manager,&Manager::returnParentUI,this,&MainMenu::reFresh);

    mypix = new QPixmap();
    mypix->load("/home/gxk/Daily/Qt/"
                "build-Navigation_system-Desktop_Qt_5_8_0_GCC_64bit-Debug/"
                "平面图2.png");
    ui.lb_map->setScaledContents(true);
    ui.lb_map->setPixmap(*mypix);



    /*************Get Vertex to add item****************/
    this->nsdb->getVertex(vadjlist);
    //ui.cb_ed->disconnect();
    ui.cb_st->clear();
    ui.cb_ed->clear();
    for(int i = 0;i<vadjlist.size();i++){
        ui.cb_st->addItem(vadjlist[i].name);
        ui.cb_ed->addItem(vadjlist[i].name);
    }
    /*****************************/

    graph = new Graph(nsdb);
    QString identity = "管理员";
    this->type = type;
    if(this->type != 1){
       identity = "游客";
       ui.btn_manage->hide();
    }

    QString hello = "  " + identity  + username + ",你好!\n" + "欢迎使用sky西邮导航系统";
    ui.label->setText(hello);
    this->setWindowTitle("sky西邮导航系统");
}

/*当点击按钮时获得起点和终点*/
void MainMenu::on_btn_findpath_clicked()
{
    vcoordinate.clear();
    QString st = ui.cb_st->currentText();
    QString ed = ui.cb_ed->currentText();

    int i = graph->local(st);
    int j = graph->local(ed);


    //调用寻找各点到源点的最短距离0
    //1表示寻找最绿路径
    graph->Dijkstra(i,0);
    //寻找最短路的路径
    graph->getPath(j,vcoordinate);

    loadPixture();


}

void MainMenu::on_btn_manage_clicked()
{

    manager->show();

}

void MainMenu::loadPixture()
{
    /*****************DrawBackGround***********************/
    mypix->load("/home/gxk/Daily/Qt/"
                "build-Navigation_system-Desktop_Qt_5_8_0_GCC_64bit-Debug/"
                "平面图2.png");
    QPainter painter;
    painter.begin(mypix);

    QPen pen;
    pen.setWidth(5);
    pen.setColor(Qt::red);
    pen.setStyle(Qt::SolidLine);

    painter.setPen(pen);


    int size = vcoordinate.size();
    qDebug() << "size = " <<size;
    if(size != 0){
       for(int i = 0;i<size-1;i++){
            int x1 = vcoordinate[i].x-10,y1 = vcoordinate[i].y-10;
            int x2 = vcoordinate[i+1].x-10,y2 = vcoordinate[i+1].y-10;
            qDebug() << x1 << " " << y1 << x2 << " " << y2;
            painter.drawLine(x1,y1,x2,y2);
        }
    }

    painter.end();

    ui.lb_map->setScaledContents(true);
    ui.lb_map->setPixmap(*mypix);

    update();
}


void MainMenu::on_btn_clear_clicked()
{
    mypix->load("/home/gxk/Daily/Qt/"
                "build-Navigation_system-Desktop_Qt_5_8_0_GCC_64bit-Debug/"
                "平面图2.png");
    ui.lb_map->setScaledContents(true);
    ui.lb_map->setPixmap(*mypix);

    update();
}

void MainMenu::on_pushButton_clicked()
{
    vcoordinate.clear();
    QString st = ui.cb_st->currentText();
    QString ed = ui.cb_ed->currentText();

    int i = graph->local(st);
    int j = graph->local(ed);


    //调用寻找各点到源点的最短距离0
    //1表示寻找最绿路径
    graph->Dijkstra(i,1);
    //寻找最短路的路径
    graph->getPath(j,vcoordinate);

    loadPixture();
}
