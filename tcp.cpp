#include "tcp.h"
#include "enviroment.h"
#include "loginwindow.h"
#include "userinfo.h"
#include "userlist.h"
#include "chatdialog.h"
#include <QString>
#include <QMessageBox>


Tcp::Tcp()
{
    cache="";
}


void Tcp::connectToHost(QString ip,QString port){
    socket = new QTcpSocket;
    cache="";
    socket->connectToHost(ip,port.toInt());

    //SIGNAL(error(QAbstractSocket::SocketError)
//    connect(socket, &QTcpSocket::error,[=](){
//        Debug("[ERROR] connection error");
//    });

    connect(socket,&QTcpSocket::connected,[=](){
        Debug("connection success");
//        waitingDialog2->hide();
//        connect(&gameI->heartBeat,&QTimer::timeout,[=](){
//            Debug("check heart...");
//            sendInfo("heartbeat");
//            myheart.start(5*1000);
//        });
//        gameI->heartBeat.start(5*1000);

//        connect(&mytime,&QTimer::timeout,[=](){
//            gameI->saveNow("connectionLost.bak");
//            QMessageBox::critical(0,"糟糕,对方连接好像断开了呢","您的游戏已经保存至connectionLost.bak,请重新连接再来吧",QMessageBox::Yes);
//            exit(1);

//        });
//        connect(&myheart,&QTimer::timeout,[=](){
//            gameI->saveNow("connectionLost.bak");
//            QMessageBox::critical(0,"糟糕,对方连接好像断开了呢","您的游戏已经保存至connectionLost.bak,请重新连接再来吧",QMessageBox::Yes);
//            exit(2);
//        });


        Debug("connect success");
        emit tcpConnectSuccess();
    });
    connect(socket,&QTcpSocket::readyRead,[=](){
        receiveInfo();
    });


}


void Tcp::receiveInfo()
{
    while (socket->canReadLine()){
        QString info=socket->readLine();
        if (info.contains("__START__")){
            mytime.start(3*1000);
            cache="";
        }else if (info.contains("__END__")){
            mytime.stop();
            //emit tcpReceiveInfo(cache);
            dealInfo(cache);
            Debug("tcp receive info:"+cache);
            cache="";
        }else{
            cache+=info;
        }
    }

}

void Tcp::sendInfo(QString info){
    Debug("send info: "+info);
    info.replace(" ","@@");
    info.replace("\n","##");
    QString str=info;
    QTextStream(&info)<<"\n\n__START__\n\n"<<str<<"\n\n__END__\n\n";
    QByteArray byte;
    byte.append(info);
    socket->write(byte.data());

}

void Tcp::sendInfo(QString name,int num){
    QString info;
    QTextStream(&info)<<"\n"<<name<<"\n"<<num<<"\n";
    sendInfo(info);
}
void Tcp::sendInfo(QString name, int num1,int num2){
    QString info;
    QTextStream(&info)<<"\n"<<name<<"\n"<<num1<<"\n"<<num2<<"\n";
    tcp->sendInfo(info);
}
void Tcp::sendInfo(QString name,QString str){
    QString info;
    QTextStream(&info)<<"\n"<<name<<"\n"<<str<<"\n";
    tcp->sendInfo(info);
}

void Tcp::sendInfo(QString name,QString info1,QString info2){
    QString info;
    QTextStream(&info)<<"\n"<<name<<"\n"<<info1<<"\n"<<info2<<"\n";
    tcp->sendInfo(info);
}

void Tcp::sendInfoStr(QString name,QString info){
    info.replace(" ","$$");
    info.replace("\n","^^");
    sendInfo(name,info);
}


void Tcp::dealInfo(QString info){
    info.trimmed();
    info.replace("@@"," ");
    info.replace("##","\n");
    Debug("receive: "+info);

    QTextStream stream(&info);
    QString head;
    stream>>head;
    if (head=="connect_success"){
        loginWindow->connectSuccess();
    }else if (head == "reply_login_request"){
        QString result;
        stream>>result;
        if (result=="refuse"){
            qDebug()<<"login refuse";
            QString info;
            stream>>info;
            loginWindow->loginFail(info);
        }else{
            qDebug()<<"login success";
            loginWindow->loginSuccess();

        }
    }else if (head=="nickname"){
        QString nickname;
        stream>>nickname;
        myuser->nickname=nickname;

    }else if (head=="sign"){
        QString sign;
        stream>>sign;
        myuser->sign=sign;
    }else if (head=="picture"){
        int picture;
        stream>>picture;
        myuser->picture=picture;
        //more...
    }else if (head=="reply_require_linkman"){
        int count;
        stream>>count;
        linkMan.clear();
        for (int i=1;i<=count;i++){
            LinkMan link;
            stream>>link.nickname>>link.account;
            linkMan.push_back(link);
        }
        userList->myUpdate();
    }else if (head=="reply_require_newchat"){
        QString result;
        stream>>result;
        if (result=="fail"){
            qDebug()<<"[ERROR] newchat cannot open";
            QMessageBox::about(0,"错误","您不能和对方聊天");
        }else{
            QString account,nickname,sign;
            stream>>account>>nickname>>sign;
            userList->talkTo(account,"");
        }
    }else if (head=="message_from"){
        QString account,info;
        stream>>account,info;
        userList->talkTo(account,encodeStr(info));
    }else if (head=="talking_info"){
        QString account,nickname,sign;
        stream>>account>>nickname>>sign;
        int now=findUser(account);
        if (now!=-1){
            talkingList[now].nickname=nickname;
            talkingList[now].sign=sign;
            for (int i=0;i<chatDialogList.size();i++){
                if (chatDialogList[i]->talkingID){
                    chatDialogList[i]->myUpdate();
                }
            }
        }
    }
}

