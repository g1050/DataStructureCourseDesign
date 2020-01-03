#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{

    ui.setupUi(this);
    this->setWindowTitle("sky西邮导航系统");
    nsdb = new DataBase();
    account = new Account(nsdb);

    /***********LineEdit****************/
    ui.ln_usr->setClearButtonEnabled(true);
    ui.ln_usr->setPlaceholderText("账号");
    ui.ln_pwd->setEchoMode(QLineEdit::Password);
    ui.ln_pwd->setPlaceholderText("密码");
    /***********LineEdit****************/

//    QMovie* movie = new QMovie("/home/gxk/图片/视频/星空.gif");

//    ui.label_2->setMovie(movie);
//    movie->start();

}

void MainWindow::on_login_clicked()
{
    QString username = ui.ln_usr->text();
    QString passwd   = ui.ln_pwd->text();
//    qDebug() << username ;
//    qDebug() << passwd   ;
    if(account->verify(username,passwd)){
        this->mainmenu = new MainMenu(username,account->getType(username),nsdb);
        this->close();
        mainmenu->show();
        //qDebug() << "Yes" ;
    }else{
        QMessageBox::critical(NULL, "critical", "密码错误", QMessageBox::Yes);
        qDebug() << "Wrong password";
    }
}

void MainWindow::on_link_reg_clicked()
{
    Register reg(nsdb);
    reg.exec();
}

void MainWindow::on_link_find_clicked()
{
    Find find(nsdb);
    find.exec();
}
