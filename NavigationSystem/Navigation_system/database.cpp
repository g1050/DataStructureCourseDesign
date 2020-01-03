#include "database.h"

DataBase::DataBase()
{
    this->createConnection();
}

DataBase::~DataBase()
{
    QSqlDatabase::removeDatabase("NSDB.db");
    db.close();
}

QString DataBase::getPasswdByUsername(QString username)
{
    QSqlQuery query;
    QString passwd = "";
    QString sql = QString("select * from ACCOUNT where USERNAME = '%1'").arg(username);
    query.exec(sql);
    while(query.next())
    {
        passwd = query.value("PASSWD").toString() ;
        //qDebug() << "passwd = " << passwd ;
    }
    return passwd;

}

bool DataBase::ifExist(QString username)
{
    QSqlQuery query;
    QString sql = QString("select * from ACCOUNT where USERNAME = '%1'").arg(username);
    query.exec(sql);
    while(query.next())
    {
        return true;
    }
    return false;
}

bool DataBase::createConnection()
{

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("NSDB.db");
    if( !db.open())
    {
        QMessageBox::critical(NULL, "critical", "无法建立数据库连接", QMessageBox::Yes);
        //qDebug() << "无法建立数据库连接";
        return false;
    }else{
        return true;
        //qDebug() << "成功连接数据库";
    }

}

bool DataBase::insert(infomation info)
{
    QSqlQuery query;
    query.prepare("insert into ACCOUNT(USERNAME,PASSWD,TYPE,NICKNAME,FRIEND,MOVIE,SCHOOL) values(:USERNAME,:PASSWD,:TYPE,:NICKNAME,:FRIEND,:MOVIE,:SCHOOL)");

    query.bindValue(":USERNAME",info.username);
    query.bindValue(":PASSWD",info.passwd1);
    query.bindValue(":TYPE",0);
    query.bindValue(":NICKNAME",info.nickname);
    query.bindValue(":FRIEND",info.friendd);
    query.bindValue(":MOVIE",info.movie);
    query.bindValue(":SCHOOL",info.school);


    return query.exec();
}

infomation DataBase::fetchQues(QString username)
{
    infomation info;
    QSqlQuery query;
    QString sql = QString("select * from ACCOUNT where USERNAME = '%1'").arg(username);
    query.exec(sql);
    while(query.next())
    {
        info.friendd = query.value("FRIEND").toString();
        info.school = query.value("SCHOOL").toString();
        info.movie = query.value("MOVIE").toString();
    }
    return info;
}

bool DataBase::update(infomation info)
{
    QSqlQuery query;
    QString sql = QString("update ACCOUNT set PASSWD = '%1' where USERNAME = '%2'").arg(info.passwd1,info.username);
    return query.exec(sql);
}

int DataBase::getType(QString username)
{
    QSqlQuery query;
    QString sql = QString("select * from ACCOUNT where USERNAME = '%1'").arg(username);
    query.exec(sql);
    while(query.next())
    {
        return query.value("TYPE").toInt();
    }
}

bool DataBase::getVertexAndEdge(std::vector<AdjList> &vadjlist, std::vector<EdgeNode> &vedgenode)
{
    AdjList adjlist;
    EdgeNode edgenode;

    QSqlQuery query;
    QString sql = QString("select * from ADJVEX");
    query.exec(sql);
    while(query.next())
    {
        adjlist.name = query.value("NAME").toString();
        adjlist.x = query.value("COORDINATEX").toInt();
        adjlist.y = query.value("COORDINATEY").toInt();
        vadjlist.push_back(adjlist);
        //qDebug() << adjlist.name << adjlist.x << adjlist.y;
    }

    sql = QString("select * from EDGE");
    query.exec(sql);
    while(query.next())
    {
        edgenode.v1 = query.value("V1").toString();
        edgenode.v2 = query.value("V2").toString();
        edgenode.weight[0] = query.value("DISTANCE").toInt();
        edgenode.weight[1] = query.value("GREEN").toInt();
        vedgenode.push_back(edgenode);
        //qDebug() << edgenode.v1 << edgenode.v2;
    }
    return true;
}

bool DataBase::getVertex(std::vector<AdjList> &vadjlist)
{
    AdjList adjlist;
    QSqlQuery query;
    QString sql = QString("select * from ADJVEX");
    query.exec(sql);
    while(query.next())
    {
        adjlist.name = query.value("NAME").toString();
        adjlist.x = query.value("COORDINATEX").toInt();
        adjlist.y = query.value("COORDINATEY").toInt();
        if(query.value("DESCRIPTION").toString() != "")
            vadjlist.push_back(adjlist);
        //qDebug() << adjlist.name << adjlist.x << adjlist.y;
    }

}

bool DataBase::getCoordinate(int &x, int &y, QString name)
{
    QSqlQuery query;
    QString sql = QString("select * from ADJVEX where NAME = '%1'").arg(name);
    query.exec(sql);
    while(query.next())
    {
        x =  query.value("COORDINATEX").toInt();
        y = query.value("COORDINATEy").toInt();
        //qDebug() << x << " " << y ;
        return true;
    }
    return false;
}
