#include "account.h"

bool Account::verify(QString username, QString passwd)
{
    QString passwd2;


    passwd2 = nsdb->getPasswdByUsername(username);
    if(passwd2 == passwd){
        return true;
    }else{
        return false;
    }

}

bool Account::ifExist(QString username)
{
    return nsdb->ifExist(username);
}

bool Account::registerr(infomation info)
{
    return nsdb->insert(info);
}

bool Account::verifyQues(infomation info)
{
    infomation info_fetch = nsdb->fetchQues(info.username);
    if(info_fetch.school == info.school && info_fetch.movie == info.movie
            && info_fetch.friendd == info.friendd)
        return true;
    else return false;
}

bool Account::modify(infomation info)
{
    return nsdb->update(info);
}

int Account::getType(QString username)
{
    return nsdb->getType(username);
}

//Account::Account(DataBase &db)
//{
//    nsdb = new DataBase();
//}
