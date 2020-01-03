#ifndef GRAPH_H
#define GRAPH_H
#include "database.h"
#include "common.h"

class Graph
{
public:
    Graph(DataBase *nsdb);
    bool createGraph();
    void Dijkstra(int st,int mode);
    bool updataAdjvexAndEdge();
    bool getPath(int ed, std::vector<Coordinate> &vcoordinate);
    /* 查找某个定点所在的位置 */
    int local(QString val){
        for(int i = 0;i<numVertex;i++){
            if(adjlist[i].name == val){
                return i;
            }
        }
        return -1;
    }
private:
    int numVertex;
    int numEdge;
    int parent[MAXSIZE];
    bool visit[MAXSIZE];
    Node node[MAXSIZE];
    std::priority_queue<Node> q;
    DataBase *nsdb;
    AdjList adjlist[MAXSIZE];
    std::vector<AdjList> vadjlist;
    std::vector<EdgeNode> vedgenode;
    void destroyOldGraph();



};

#endif // GRAPH_H
