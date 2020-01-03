#include "find.h"

//find::find(QWidget *parent) :
//    QDialog(parent)
//{

//}

Find::Find(QWidget *parent)
{
    ui.setupUi(this);
}

Find::Find(DataBase *nsdb)
{
    ui.setupUi(this);
    this->nsdb = nsdb;
    this->setWindowTitle("找回密码");
}

void Find::on_pushButton_clicked()
{
    infomation info;
    Account *account = new Account(nsdb);
    info.username = ui.ln_usr->text();
    info.passwd1 = ui.ln_pwd1->text();
    info.passwd2 = ui.ln_pwd2->text();
    info.friendd = ui.ln_friend->text();
    info.school = ui.ln_school->text();
    info.movie = ui.ln_movie->text();

    if(account->ifExist(info.username)){
        if(account->verifyQues(info)){
            /**********************验证两次密码是否一致***************/
            if(info.passwd1 != info.passwd2 || info.passwd1.size() < 6 ){
                QMessageBox::warning(NULL, "warning", "两次密码不一致或密码长度小于6位!", QMessageBox::Yes );
            }else{
                if(account->modify(info)){
                    QMessageBox::information(NULL, "information", "密码修改成功", QMessageBox::Yes);
                    this->close();
                }
            }

        }else{
            QMessageBox::critical(NULL, "critical", "密保答案有误!", QMessageBox::Yes);
        }
    }else{
        QMessageBox::critical(NULL, "critical", "账号不存在", QMessageBox::Yes);
    }
}
