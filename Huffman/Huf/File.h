#pragma once
#include <fstream>
#include "Huffman.h"
#include <cmath>
using namespace std;

struct mapinfo
{
    char ch;
    unsigned num;
};

class File :public HuffmanTree {
public:
    map<char,unsigned> mp;
    unsigned strToInt(const string &tmp){
        unsigned num = 0; 
        for(int i = 0;i<(int)tmp.size();i++){
            if(tmp[i] == '1')
                num += pow(2,31-i);
        }            
        return num;
    }

public:
    File() {}
    ~File() {}
    map<char,unsigned> getMap(const string &s); 
    void encoded(string src,string des);//src是源文件，des是压缩后的文件
    void decoding(string src,string des);//src是压缩文件,des是解压后的文件
    void writeHead(string &des);
    string getBin(unsigned num);
};

