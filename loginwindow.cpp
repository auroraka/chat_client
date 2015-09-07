#include "loginwindow.h"
#include "tcp.h"
#include "switcher.h"
#include "userlist.h"
#include "ui_loginwindow.h"


LoginWindow::LoginWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
    ui->passwordInput_lineEdit->setEchoMode(QLineEdit::Password);
    ui->loginNotice_label->setText("");

    hideAccountLogin();

    showConnectLogin();

    //---------Debug model----------
    ui->accountInput_lineEdit->clear();
    ui->passwordInput_lineEdit->clear();
    ui->ipInput_lineEdit->clear();
    ui->portInput_lineEdit->clear();
    ui->ipInput_lineEdit->setText("127.0.0.1");
    ui->portInput_lineEdit->setText("10086");
    ui->accountInput_lineEdit->setText("admin");
    ui->passwordInput_lineEdit->setText("admin");
    //-------------------
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::loginSuccess(){
    ui->loginNotice_label->setText("登陆成功");
    userList->loginSuccess=1;
    tcp->sendInfo("require_linkman");
    switcher->showInterface("userList");
}

void LoginWindow::loginFail(QString info){
    ui->loginNotice_label->setText(QString("登陆失败: %1").arg(info));
}

void LoginWindow::hideAccountLogin(){
    ui->logo_label->hide();
    ui->passwordInput_lineEdit->hide();
    ui->accountInput_lineEdit->hide();
    ui->login_pushButton->hide();
    ui->registerAccount_pushButton->hide();
    ui->retrievePassword_pushButton->hide();
    ui->registerAccount_pushButton->hide();
    ui->picture_label->hide();
    ui->autoLogin_checkBox->hide();
    ui->rememberPassword_checkBox->hide();
    ui->accountList_comboBox->hide();
}

void LoginWindow::showAccountLogin(){
    ui->logo_label->show();
    ui->passwordInput_lineEdit->show();
    ui->accountInput_lineEdit->show();
    ui->login_pushButton->show();
    ui->registerAccount_pushButton->show();
    ui->retrievePassword_pushButton->show();
    ui->registerAccount_pushButton->show();
    ui->picture_label->show();
    ui->autoLogin_checkBox->show();
    ui->rememberPassword_checkBox->show();
    ui->accountList_comboBox->show();
}

void LoginWindow::showConnectLogin(){
    ui->ipInput_lineEdit->show();
    ui->portInput_lineEdit->show();
    ui->connect_pushButton->show();
    ui->connectNotice_label->show();
}

void LoginWindow::hideConnectLogin(){
    ui->ipInput_lineEdit->hide();
    ui->portInput_lineEdit->hide();
    ui->connect_pushButton->hide();
    ui->connectNotice_label->hide();
}

void LoginWindow::on_connect_pushButton_clicked()
{
    // more ... check ip and port
    QString ip=ui->ipInput_lineEdit->text();
    QString port=ui->portInput_lineEdit->text();
    qDebug()<<"try connect :"<<ip<<" "<<port;
    tcp->connectToHost(ip,port);
    ui->connectNotice_label->setText("正在连接...");
}

void LoginWindow::connectSuccess(){
    hideConnectLogin();
    showAccountLogin();
}


void LoginWindow::on_login_pushButton_clicked()
{
    QString account=ui->accountInput_lineEdit->text();
    QString password  = ui->passwordInput_lineEdit->text();

    tcp->sendInfo("login_request","\n"+account+"\n"+password+"\n");
}
