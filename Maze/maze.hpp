#pragma once
#include <iostream>
#include <cstring>
#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */
#define RED     "\033[31m"      /* Red */

const int WALL = 1;
const int ROAD = 0;
const int STEP = 2;
const int MAXSIZE = 102400;

int direction[4][2] = {
    {-1,0},{1,0},{0,-1},{0,1}
};

struct Point{
    Point(){

    }
    Point(int x,int y){
        this->x = x;
        this->y = y;
    }
    int x,y;
};

class Maze{
private:
    int row,column;
    int **matrix;

    Point point[MAXSIZE];
    bool visit[10240][10240];
    int parent[MAXSIZE];
    
public:
    Maze(int row,int column){
        this->row = row;
        this->column = column;
        srand(unsigned(time(NULL)));//种下种子
        matrix = new int*[row];
        for(int i = 0;i<row;i++){
            matrix[i] = new int[column];
            //初始状态全部为路
            memset(matrix[i],ROAD,sizeof(int)*column);
        }
        memset(point,0,sizeof(point));
        memset(visit,false,sizeof(visit));
    }

    void print(){
        for(int i = 0;i<row;i++){
            for(int j = 0;j < column;j++){
                std::cout << matrix[i][j] ;
            }
            std::cout << "\n";
        }
    }

    void printMaze(){
        for(int i = 0;i<row;i++){
            for(int j = 0;j<column;j++){
                if(matrix[i][j] == WALL)
                    std::cout << BLUE <<  "▇▇" ;
                else if(matrix[i][j] == ROAD)std::cout << "  ";
                else if(matrix[i][j] == STEP) std::cout  << YELLOW << "@@";
            }
            std::cout << "\n";

        }
    }
    void init();
    void createMaze(int x1,int y1,int x2,int y2);
    void findPath();
};

void Maze::init(){
    //初始化四面围墙
    for(int i = 0;i<row;i++){
        matrix[i][0] = WALL;
        matrix[i][column-1] = WALL;
    }
    for(int i = 0;i<column;i++){
        matrix[0][i] = WALL;
        matrix[row-1][i] = WALL;
    }
    matrix[1][0] = ROAD;
    matrix[row-2][column-1] = ROAD;
}

void Maze::createMaze(int x1,int y1,int x2,int y2){
    /* printMaze(); */
    /* 递归结束的出口 */
    if(x2 - x1 <= 1 || y2 - y1 <= 1)
        return ;

    /* [a,b] rand%(b-a+1)+a */
    /* 在[x1+1,x2-1]和[y1+1,y2-1]之间产生随机数 */
    int x = x1 + rand()%(x2-x1-1) + 1;
    int y = y1 + rand()%(y2-y1-1) + 1;

    /* std::cout << x << "  " << y << std::endl; */
    /* 以产生的随机数为中心,上下左右四个方向,画出四面墙 */
    for(int i = x1;i<=x2;i++)//竖直方向
        matrix[i][y] = WALL;
    for(int i = y1;i<=y2;i++)//水平方向
        matrix[x][i] = WALL;

    /* 继续递归分割 */
    createMaze(x1,y1,x-1,y-1);//左上
    createMaze(x1,y+1,x-1,y2);//右上
    createMaze(x+1,y1,x2,y-1);//左下
    createMaze(x+1,y+1,x2,y2);//右下

    /* printMaze(); */
    /* int num; */
    /* std::cin >> num; */

    int dir[4] = {0,0,0,0};
    /* [0,3] */ 
    dir[rand()%4] = 1;
    /* 在四面墙上任选三面随机开洞 */
    for(int i = 0;i<4;i++){
        if(!dir[i]){
            int rx = x;//每次都要初始化为x,y
            int ry = y;
            switch(i){
                case 0://在上面开洞
                    do{
                        /* y固定等于y x的范围[x1,x-1] */
                        rx = x1 + rand()%(x-x1);
                    }while(matrix[rx-1][ry] + matrix[rx+1][ry] + matrix[rx][ry-1] + matrix[rx][ry+1] > 2*WALL);
                    break;
                case 1://在下面开洞
                    do{
                        /* [x+1,x2] */
                        rx = x + 1 + rand()%(x2-x);
                    }while(matrix[rx-1][ry] + matrix[rx+1][ry] + matrix[rx][ry-1] + matrix[rx][ry+1] > 2*WALL);
                    break;
                case 2://左
                    do{
                        /* x固定,y的范围[y1,y-1] */
                        ry = y1 + rand()%(y-y1);
                    }while(matrix[rx-1][ry] + matrix[rx+1][ry] + matrix[rx][ry-1] + matrix[rx][ry+1] >  2*WALL);
                    break;
                case 3://右
                    do{
                        /* [y+1,y2] */
                        ry = y + 1 + rand()%(y2-y);
                    }while(matrix[rx-1][ry] + matrix[rx+1][ry] + matrix[rx][ry-1] + matrix[rx][ry+1] >  2*WALL);
                    break;
            }
        matrix[rx][ry] = ROAD;
        }
     }

}

void Maze::findPath(){
    
    int front = 0; 
    int last = front + 1;
    //起点位置matrix[1][0]
    Point p(1,0);
    point[front] = p;
    visit[1][0] = true;
    parent[front] = -1;

    while(front < last){

        Point tmp = point[front];
        /* 终点是(row-2,column-1) */
        if(tmp.x == row-2 && tmp.y == column-1)
            break;
        /* 向四个方向拓展 */
        for(int i = 0;i<4;i++){
            Point t;
            t.x = tmp.x + direction[i][0];
            t.y = tmp.y + direction[i][1];
            if(!visit[t.x][t.y] && t.x > 0 && t.x < row && t.y > 0 && t.y < column && matrix[t.x][t.y] == ROAD ){
                point[last] = t;
                parent[last++] = front;
                visit[t.x][t.y] = true;
            }
        }
        front++;

    }

    matrix[row-2][column-1] = STEP;
    int pos = parent[front];
    while(pos != -1){
        matrix[point[pos].x][point[pos].y] = STEP;
        pos = parent[pos];
    }
    /* std::cout << point[pos].x << " " << point[pos].y << std::endl; */

}

