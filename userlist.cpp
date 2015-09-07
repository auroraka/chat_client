#include "userlist.h"
#include "userinfo.h"
#include "tcp.h"
#include "ui_userlist.h"
#include "chatdialog.h"
#include <QListWidget>

UserList::UserList(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserList)
{
    ui->setupUi(this);
    move(100,100);
    connect(ui->linkmanList_listWidget,SIGNAL(itemDoubleClicked(QListWidgetItem*)),this,SLOT(newChat(QListWidgetItem*)));

    timer = new QTimer;
    //timer->start(10*1000);   //Debug!!!!!!!!!!!
    connect(timer,&QTimer::timeout,[=](){
        if (loginSuccess){
            tcp->sendInfo("require_linkman");
            myUpdate();
        }
    });
    loginSuccess =0;
}

UserList::~UserList()
{
    delete ui;
}


void UserList::myUpdate(){
    ui->nickname_label->setText(myuser->nickname);
    ui->sign_label->setText(myuser->sign);
    ui->linkmanList_listWidget->clear();
    for (int i=0;i<linkMan.size();i++){
        ui->linkmanList_listWidget->addItem(linkMan[i].nickname+" "+linkMan[i].account+"");
    }

    //ui->linkMan_lineEdit
    //ui->picture_labal
}

void UserList::newChat(QListWidgetItem *item){
    qDebug()<<"doule clicked!";
    QString str=item->text();
    QTextStream stream(&str);
    QString nickname,account;
    stream>>nickname>>account;
    qDebug()<<myuser->nickname+" want making new chat to: "<<nickname;

    tcp->sendInfo("require_newchat",account);
}


void UserList::talkTo(QString account,QString info){
    qDebug()<<"creat talk";
    int now=findUser(account);
    if (now==-1){
        UserInfo user;
        user.account=account;
        talkingList.push_back(user);
        tcp->sendInfo("require_talking_userInfo",account);
        ChatDialog *newchat = new ChatDialog;
        chatDialogList.push_back(newchat);
        newchat->talkingID=chatDialogList.size()-1;
        newchat->addNewTalkInfo(info);
        newchat->myUpdate();
        newchat->show();
    }else{
        chatDialogList[now]->myUpdate();
        chatDialogList[now]->show();
    }
    qDebug()<<"tot userList: "<<talkingList.size();
}
