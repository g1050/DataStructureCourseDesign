#include "File.h"

string File::getBin(unsigned num)
{
    string tmp = "";
    unsigned mask = 1u << 31;
    while(mask){
        tmp.append(1,(num & mask ? '1' : '0'));
        mask >>= 1;
    }
    return tmp;
}
/* 译码函数，由压缩文件头部的信息解压文件 */
void File::decoding(string src,string des)
{
    string str2;
    char ch;//每次写入一个char
    unsigned int num = 0;
    ifstream in(src,ios::in | ios::binary);
    ofstream out;
    out.open(des,ios::out | ios::binary);
    mapinfo node;
    HuffmanNode *t = p;
    if(!in) cout << "Error";
    if(!out) cout << "Error";

    int flag = 0;//map建立完成之前一直是0,建立完成后改为1 
    int flag2 = 0;//建树前是0,建树后改为1

    long long size = -1;
    int lack0 = -1;
    in.seekg(-12,ios::end);
    in.read((char*)&size,sizeof(long long));
    in.read((char*)&lack0,sizeof(int));

    /* cout << "size = "  << size << endl; */
    /* cout << "lack0 = " << lack0 << endl; */
    in.seekg(ios::beg);
    while(in.peek() != EOF){


        //读取表头信息建立map,通过map建树,
        if(flag == 0){
            in.read((char*)&node,sizeof(node));
            if(node.num == (unsigned)-1){//读到表头信息结束位置
                flag = 1;
            }else
                mp[node.ch] = node.num;
        }
        else if(flag == 1){
            if(!flag2){
                /* cout << "create Tree!" << endl; */
                buildTree(mp,1);
                t = p;
                flag2 = 1;
            }else{
                in.read((char*)&num,4);
                /* cout << "num = "<<num << endl; */
                /* 先将整数转换为01序列 */
                str2 =getBin(num);                
                /* 根据建立的霍夫曼树解析并且写入文件 */
                if(size == in.tellg()){
                    /* cout << "break num = " << num << endl; */
                    break;
                } 
                for(int i = 0;i<(int)str2.size();i++){
                    if(str2[i] == '0'){
                        t = t->lchild;
                    }else{
                        t = t->rchild;
                    }

                    if(!t->lchild && !t->rchild){
                        ch = t->key;
                        out.write(&ch,sizeof(ch));
                        t = p;
                    }
                }

            }


        }
    }

    for(int i = 0;i<(int)str2.size();i++){
        if(str2[i] == '0'){
            t = t->lchild;
        }else{
            t = t->rchild;
        }

        if(!t->lchild && !t->rchild){
            ch = t->key;
            /* cout << "ch =======" << ch << endl; */
            out.write(&ch,sizeof(ch));
            t = p;
        }
    }

    if(lack0 != 0){
        in.read((char*)&num,4);
        /* cout << "num = " << num << endl; */
        str2 = getBin(num);
        for(int i = 0;i<(int)str2.size()-lack0;i++){
            if(str2[i] == '0'){
                t = t->lchild;
            }else{
                t = t->rchild;
            }

            if(!t->lchild && !t->rchild){
                ch = t->key;
                /* cout << "ch =======" << (int)ch << endl; */
                out.write(&ch,sizeof(ch));
                t = p;
            }
        }
    }else{
        out << "\n";//手动加个换行符号
    }
    
    in.close();
    out.close();


    return ;
}

void File::writeHead(string &des)
{
    //创建文件，并且写入260个字符信息
    ofstream crt;
    crt.open(des);
    mapinfo node;
    for(auto it = mp.begin(); it != mp.end();it++){
        node.ch = it->first;
        node.num = it->second;
        crt.write((char*)&node,sizeof(node));
    } 

    node.num = -1;//写入一个特殊nodei作为mapinfo的结束标志
    crt.write((char*)&node,sizeof(node));
    return ;
}

/* 编码函数，根据vector中的新编码方式，重新编码写入文件 */
void File::encoded(string src,string des)
{
    getMap(src);
    buildTree(mp,0);
    //将map信息写入文件头部
    writeHead(des); 

    char ch;//存放每次读取到的一个字符数据
    string tmp = "";//存取链接到的32为字符串
    int num = 0;//记录tmp中的01个数
    int flag = 0;//凑够32位时，用来跳过一次读取,并且记录上次剩余
    int lack0 = 0;
    int pos = 0;
    ifstream in(src,ios::in | ios::binary );
    ofstream out(des,ios::out | ios::binary | ios::app);

    if(!in) cout << "Error" << endl;
    if(!out) cout << "Error" << endl;
    while(in.peek() != EOF){
        if(!flag)//flag非0对应上一个字符超出的情况,flag是的话说明上次tmp中有剩余就不读取了
        {
            ch = in.get();
            pos = (int)ch + 128;
        }


        if(num < 32){
            int lack = 32 - num;//算出差多少个01                


            if(!flag){//当前串从0开始使用
                /* 分两种情况一种下当前字符不足，另一种下一个字符超出 */
                if((int)v[pos].size() <= lack){//不足
                    tmp += v[pos];
                    num += (int)v[pos].size();
                }else{
                    //tmp字符串大于lack时候只要取需要的，做好标记
                    tmp += v[pos].substr(flag,lack);
                    flag = lack;
                    num += lack;
                }

            }else{//上一轮有剩余此时串是空的
                tmp += v[pos].substr(flag);
                num += tmp.size();
                flag = 0;//flag重新置为0
            }
        }
        if(num == 32){//凑够32个字节
            unsigned int w = 0;
            /* out << strToInt(tmp);//转换成整数写入 */

            w = strToInt(tmp);
            /* out << w; *///这样是以字符串的形式写入的
            out.write((char*)(&w),sizeof(w));
            /* cout << "w = " <<  w << endl; */
            tmp.clear();
            num = 0;
        }



    }

    long long size = out.tellp();
    /* 最后不够需要补0补齐 */
    if(num != 0){
        lack0 = 32 - num;
        tmp.append(lack0,'0');
        unsigned int w = 0;
        w = strToInt(tmp);
        /* out << w; */
        out.write((char*)(&w),sizeof(w));
        /* cout << "w = " << w << endl; */
    }

    /* cout << "size = "  << size << endl; */
    /* cout << "lack0 = " << lack0 << endl; */

    out.write((char*)&size,sizeof(long long ));
    out.write((char*)&lack0,sizeof(int));

    in.close();
    out.close();

    return ;

}


/* 获得字符个数对应的表,并且传递给HuffmanTree类 */
map<char,unsigned> File::getMap(const string &s)
{   
    ifstream in;
    char ch;
    /* out.open("tmp.txt",ios::out | ios::binary); */
    in.open(s,ios::in | ios::binary);
    while(in.peek() != EOF){
        ch = in.get();
        /* out <<  ch; */
        /* cout << (int)ch << endl; */
        if(!mp.count(ch)){
            //cout << "ch = " << (int)ch << endl;
            mp[ch] = 1;//初始化
        }else{
            mp[ch]++;
        }
    }
    in.close();

    return mp;
}
