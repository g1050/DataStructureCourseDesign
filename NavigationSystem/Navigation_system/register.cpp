#include "register.h"

Register::Register(QWidget *parent) :
    QDialog(parent)
{
    ui.setupUi(this);
    /***********LineEdit****************/
    ui.ln_usr->setClearButtonEnabled(true);
    ui.ln_nickname->setClearButtonEnabled(true);
    ui.ln_friend->setClearButtonEnabled(true);
    ui.ln_movie->setClearButtonEnabled(true);
    ui.ln_pwd->setEchoMode(QLineEdit::Password);
    ui.ln_pwd2->setEchoMode(QLineEdit::Password);
    ui.ln_pwd->setPlaceholderText("密码长度大于6位");
    ui.ln_pwd2->setPlaceholderText("密码长度大于6位");
    /***********LineEdit****************/
}

Register::Register(DataBase *nsdb)
{

    ui.setupUi(this);
    this->setWindowTitle("注册账号");
    this->nsdb = nsdb;
    /***********LineEdit****************/
    ui.ln_usr->setClearButtonEnabled(true);
    ui.ln_nickname->setClearButtonEnabled(true);
    ui.ln_friend->setClearButtonEnabled(true);
    ui.ln_movie->setClearButtonEnabled(true);
    ui.ln_pwd->setEchoMode(QLineEdit::Password);
    ui.ln_pwd2->setEchoMode(QLineEdit::Password);
    ui.ln_pwd->setPlaceholderText("密码长度大于6位");
    ui.ln_pwd2->setPlaceholderText("密码长度大于6位");
    /***********LineEdit****************/
}

void Register::on_btn_reg_clicked()
{
    infomation info;
    info.passwd1 = ui.ln_pwd->text();
    info.passwd2 = ui.ln_pwd2->text();


    info.nickname = ui.ln_nickname->text();
    info.movie = ui.ln_movie->text();
    info.school = ui.ln_school->text();
    info.username = ui.ln_usr->text();
    info.friendd = ui.ln_friend->text();
    Account *account = new Account(nsdb);

    if(info.username == "" | account->ifExist(info.username)){
        /***********该账号已经被注册******************/
        QMessageBox::critical(NULL, "critical", "该账号已经被注册,请重新输入不同账号!", QMessageBox::Yes );

    }else{
        /***********将账号信息写入数据库******************/

        if(info.passwd1 != info.passwd2 || info.passwd1.size() < 6 ){
            QMessageBox::warning(NULL, "warning", "两次密码不一致或密码长度小于6位!", QMessageBox::Yes );
        }else{
            if(info.friendd != "" && info.movie != "" && info.nickname != "" && info.school != "" ){
                if(account->registerr(info)){
                    QString success = "恭喜"+ info.nickname + ",新账号注册成功";
                    QMessageBox::information(NULL, "注册成功", success,
                                               QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
                    this->close();
                }
            }else{
                QMessageBox::critical(NULL, "critical", "请完善所有信息!", QMessageBox::Yes );
            }
        }
    }

}
