#ifndef ACCOUNT_H
#define ACCOUNT_H
#include "common.h"
#include "database.h"

class Account
{
private:
    DataBase *nsdb;
public:
    bool verify(QString username,QString passwd);
    bool ifExist(QString username);
    bool registerr(infomation info);
    bool verifyQues(infomation info);
    bool modify(infomation info);
    int getType(QString username);
    Account();
    Account(DataBase *db){
      nsdb = db;
    };
};

#endif // ACCOUNT_H
