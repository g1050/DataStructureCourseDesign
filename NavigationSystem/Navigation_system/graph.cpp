#include "graph.h"

Graph::Graph(DataBase *nsdb)
{
    this->nsdb = nsdb;
    this->createGraph();
}


bool Graph::updataAdjvexAndEdge()
{
    destroyOldGraph();
    numEdge = 0;
    numVertex = 0;
    vadjlist.clear();
    vedgenode.clear();

    /*从数据库中读取边信息和点信息*/
    nsdb->getVertexAndEdge(vadjlist,vedgenode);
    numEdge = vedgenode.size();
    numVertex = vadjlist.size();
    /*根据获得的vadjlist和vedgenode创建图*/
    for(int i = 0;i<numVertex;i++){
        adjlist[i].name = vadjlist[i].name;
        adjlist[i].x = vadjlist[i].x;
        adjlist[i].y = vadjlist[i].y;
        adjlist[i].firstEdge = NULL;
        //qDebug() << adjlist[i].name << adjlist[i].x ;
    }

    for(int k = 0;k<numEdge;k++){
        QString v1,v2;
        v1 = vedgenode[k].v1;
        v2 = vedgenode[k].v2;
        int i = local(v1);
        int j = local(v2);

        if(i == -1 || j == -1){
            qDebug() << i << " " << j ;
            qDebug() << "Input error";
            return false;
        }

        /* 最后把边对应的两个定点加入到图中 */
        if(adjlist[i].firstEdge == NULL){//对应孤立节点的情况，没有与任何点相连接
            //申请新节点，直接插入就可以
            EdgeNode *e = new EdgeNode();
            e->adjvex = j;
            e->weight[0] = vedgenode[k].weight[0];
            e->weight[1] = vedgenode[k].weight[1];
            adjlist[i].firstEdge = e;
        }else{//对应已经加入图中的节点
            //指针后移，将新节点插入最后
            EdgeNode *p = adjlist[i].firstEdge;
            while(p->next != NULL){
                p = p->next;
            }
            EdgeNode *e = new EdgeNode();
            e->weight[0] = vedgenode[k].weight[0];
            e->weight[1] = vedgenode[k].weight[1];
            e->adjvex = j;
            p->next = e;
        }
        if(adjlist[j].firstEdge == NULL){//对应孤立节点的情况，没有与任何点相连接
            //申请新节点，直接插入就可以
            EdgeNode *e = new EdgeNode();
            e->adjvex = i;
            e->weight[0] = vedgenode[k].weight[0];
            e->weight[1] = vedgenode[k].weight[1];
            adjlist[j].firstEdge = e;
        }else{//对应已经加入图中的节点
            //指针后移，将新节点插入最后
            EdgeNode *p = adjlist[j].firstEdge;
            while(p->next != NULL){
                p = p->next;
            }
            EdgeNode *e = new EdgeNode();
            e->weight[0] = vedgenode[k].weight[0];
            e->weight[1] = vedgenode[k].weight[1];
            e->adjvex = i;
            p->next = e;
        }

    }
    return true;
}

bool Graph::createGraph()
{
    /*从数据库中读取边信息和点信息*/
    nsdb->getVertexAndEdge(vadjlist,vedgenode);
    numEdge = vedgenode.size();
    numVertex = vadjlist.size();
    /*根据获得的vadjlist和vedgenode创建图*/
    for(int i = 0;i<numVertex;i++){
        adjlist[i].name = vadjlist[i].name;
        adjlist[i].x = vadjlist[i].x;
        adjlist[i].y = vadjlist[i].y;
        adjlist[i].firstEdge = NULL;
        //qDebug() << adjlist[i].name << adjlist[i].x ;
    }

    for(int k = 0;k<numEdge;k++){
        QString v1,v2;
        v1 = vedgenode[k].v1;
        v2 = vedgenode[k].v2;
        int i = local(v1);
        int j = local(v2);

        if(i == -1 || j == -1){
            qDebug() << i << " " << j ;
            qDebug() << "Input error";
            return false;
        }

        /* 最后把边对应的两个定点加入到图中 */
        if(adjlist[i].firstEdge == NULL){//对应孤立节点的情况，没有与任何点相连接
            //申请新节点，直接插入就可以
            EdgeNode *e = new EdgeNode();
            e->adjvex = j;
            e->weight[0] = vedgenode[k].weight[0];
            e->weight[1] = vedgenode[k].weight[1];
            adjlist[i].firstEdge = e;
        }else{//对应已经加入图中的节点
            //指针后移，将新节点插入最后
            EdgeNode *p = adjlist[i].firstEdge;
            while(p->next != NULL){
                p = p->next;
            }
            EdgeNode *e = new EdgeNode();
            e->weight[0] = vedgenode[k].weight[0];
            e->weight[1] = vedgenode[k].weight[1];
            e->adjvex = j;
            p->next = e;
        }
        if(adjlist[j].firstEdge == NULL){//对应孤立节点的情况，没有与任何点相连接
            //申请新节点，直接插入就可以
            EdgeNode *e = new EdgeNode();
            e->adjvex = i;
            e->weight[0] = vedgenode[k].weight[0];
            e->weight[1] = vedgenode[k].weight[1];
            adjlist[j].firstEdge = e;
        }else{//对应已经加入图中的节点
            //指针后移，将新节点插入最后
            EdgeNode *p = adjlist[j].firstEdge;
            while(p->next != NULL){
                p = p->next;
            }
            EdgeNode *e = new EdgeNode();
            e->weight[0] = vedgenode[k].weight[0];
            e->weight[1] = vedgenode[k].weight[1];
            e->adjvex = i;
            p->next = e;
        }

    }
    return true;

}

void Graph::Dijkstra(int st,int mode)
{

    /* 每次调用该函数都要初始化 */
    for(int i = 0;i<numVertex;i++){
        node[i].pos = i;
        node[i].minWeight = MAXN;//初始状态每个点到源点的距离无限大
        parent[i] = -1; //每个节点都没有父亲节点
        visit[i] = false;
    }

    node[st].minWeight = 0;//到自己的最短距离就是0
    q.push(node[st]);

    while(!q.empty()){

        Node tp = q.top();
        q.pop();
        int pos = tp.pos;//获取队首元素的值

        if(visit[pos])  continue;
        visit[pos] = true;
        EdgeNode *p = adjlist[pos].firstEdge ;
        while(p){//遍历所有与p相连的节点
            int cur = p->adjvex;//获取当前节点的位置
            //后期优化的点weight数组
            if(!visit[cur] && node[cur].minWeight > node[pos].minWeight + p->weight[mode]){//整个算法的核心的

                node[cur].minWeight = node[pos].minWeight + p->weight[mode];//更新值
                qDebug() << "Min_weight" << node[cur].minWeight;
                parent[cur] = pos;
                q.push(node[cur]);
            }
            p = p->next;
        }

    }

}



bool Graph::getPath(int ed,std::vector<Coordinate> &vcoordinate)
{
    Coordinate coordinate;


    //寻找终点的最短距离
    if(node[ed].minWeight != MAXN){
        coordinate.x = adjlist[ed].x;
        coordinate.y = adjlist[ed].y;
        //qDebug() << coordinate.x << coordinate.y << "Coordinate";
        vcoordinate.push_back(coordinate);
        int q = parent[ed];
        while(q != -1){
            //std::cout << "(" << adjlist[q].coordinate.x << "," << adjlist[q].coordinate.y << ")" << std::endl;
            coordinate.x = adjlist[q].x;
            coordinate.y = adjlist[q].y;
            vcoordinate.push_back(coordinate);
            //qDebug() << coordinate.x << coordinate.y << "Coordinate";
            //qDebug() << q;
            /* 向上一节点转移 */
            q = parent[q];
        }

        qDebug() << "The shortest path is " << node[ed].minWeight ;
        return true;
    }else{
        qDebug() << "Not find." ;
        return false;
    }

}

void Graph::destroyOldGraph()
{
    EdgeNode* p = NULL;

    for(int i = 0;i<numVertex;i++){
        p = adjlist[i].firstEdge;
        while(p){
            EdgeNode *tmp = p;
            p = p->next;
            delete tmp;
        }
        adjlist[i].firstEdge = NULL;
    }
    return ;

}
