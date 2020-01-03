#pragma once
#include <iostream>
#include <map>
#include <vector>
#include <queue>
#include <string>
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
/* #include "File.h" */
using namespace std;

/* 定义霍夫曼树节点 */
struct HuffmanNode{
    HuffmanNode(char k,int w):key(k),weight(w),lchild(NULL),rchild(NULL){}
    HuffmanNode(){}
    HuffmanNode(int w):weight(w),lchild(NULL),rchild(NULL){}
    char key;
    int weight;
    HuffmanNode *lchild;
    HuffmanNode *rchild;
};


/* 重载优先队列 */
struct cmp{
    bool operator()(HuffmanNode *p1,HuffmanNode *p2)
    {
        return p1->weight >  p2->weight;
    }
};


/* 定义霍夫曼树类 */
class HuffmanTree
{
public:
    HuffmanTree() {}
    ~HuffmanTree() {}
    void buildTree(const map<char,unsigned> &mp,int mode);
    void getStr(HuffmanNode *p,string &str);
    vector<string> getVector();
    vector<string> v = vector<string>(300);
    string str;
    HuffmanNode* p;
};

