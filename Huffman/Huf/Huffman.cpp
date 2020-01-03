#include "Huffman.h"
typedef pair<char,int> Element;

/* 返回得到的新的编码表 */
vector<string> HuffmanTree::getVector(){
    int cnt = 0;
    int vsize = 0;

    for(int i = 0;i<(int)v.size();i++){
        int size = v[i].size();
        if(size > 0){
            vsize++;
            cnt += v[i].size();
        }
    }
    /* cout << cnt << endl; */
    /* cout << vsize << endl; */
    /* cout << BLUE <<  "平均码长:" << cnt*1.0/vsize << endl; */
    cout << YELLOW << "压缩比:" << (8-(cnt*1.0/vsize))/8 * 100 << "%" << endl;

    return v;

}
/* 根据霍夫曼树获得相应字符的编码 */
void HuffmanTree::getStr(HuffmanNode *p,string &str)
{
    static int cnt = 0;
    //cout << cnt << endl;
    if(!p->lchild && !p->rchild){
        int pos = (int)p->key+128;
        //cout << cnt++ << endl;
        //cout << "p->key = " << pos << endl;
        //cout << "str = " << str << endl;
        v[pos] = str;
        /* cout << p->key << " " << v[p->key] << endl; */
        return ;
    }

    str.push_back('0');
    getStr(p->lchild,str);

    str.pop_back();
    str.push_back('1');
    getStr(p->rchild,str);
    str.pop_back();

    return ;

}

/* 根据传入的map建立一颗霍夫曼树 */
void HuffmanTree::buildTree(const map<char,unsigned> &mp,int mode)
{
    priority_queue<HuffmanNode *,vector<HuffmanNode *>,cmp> q;
    for(auto it = mp.begin(); it != mp.end();it++){
        //把map集合中的元素转化成一个个节点存入优先队列当中去
        HuffmanNode *p = new HuffmanNode(it->first,it->second);
        //cout << (int)it->first << "  " << it->second << endl;
        q.push(p);
    }


    while(q.size() >= 2){

        /* cout << q.top()->key << " " << q.top()->weight << endl; */  
        /* q.pop(); */

        HuffmanNode* p1 = q.top();
        q.pop();
        HuffmanNode* p2 = q.top();
        q.pop();
        p = new HuffmanNode(p1->weight+p2->weight);
        p->lchild = p1;
        p->rchild = p2;
        q.push(p);
        //最后p中保留的是根节点
    }
    if(mode == 0)
        getStr(p,str); 
    return ;
}
