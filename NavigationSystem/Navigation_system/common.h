#ifndef COMMON_H
#define COMMON_H

#include <QString>
#include <QDebug>
#include <QMovie>
#include <QTextCodec>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QTime>
#include <QSqlError>
#include <QtDebug>
#include <QSqlDriver>
#include <QSqlRecord>
#include <QMessageBox>
#include <vector>
#include <queue>
#include <cmath>
#include <QMouseEvent>
#include <QCloseEvent>
#include <QPainter>

const int MAXSIZE = 1024;
const int MAXN = 0xffff;

typedef struct{
       QString nickname;
       QString username;
       QString passwd1;
       QString passwd2;
       QString school;
       QString friendd;
       QString movie;
}infomation ;

//边
struct EdgeNode{
    QString v1;
    QString v2;
    int weight[2];
    int adjvex;
    EdgeNode *next;
};

//点
struct AdjList{
    int x;
    int y;
    QString name;
    EdgeNode *firstEdge;
};

/*保存每个节点到源点的最短举例*/
struct Node{
    int pos; //该节点的位置
    int minWeight; //该节点与源定点的距离
    /* 重载运算符，以使最小Node节点出队 */
    friend bool operator<(Node a,Node b){
        return a.minWeight > b.minWeight;
    }
};

struct Coordinate{
    int x;
    int y;
};

#endif // COMMON_H
