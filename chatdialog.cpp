#include "chatdialog.h"
#include "userinfo.h"
#include "ui_chatdialog.h"
#include "enviroment.h"
#include "tcp.h"
#include <QDateTime>
#include <QDebug>

ChatDialog::ChatDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChatDialog)
{
    ui->setupUi(this);
}

ChatDialog::~ChatDialog()
{
    delete ui;
}

void ChatDialog::myUpdate(){
    nickname=talkingList[talkingID].nickname;
    sign=talkingList[talkingID].sign;
    account=talkingList[talkingID].account;
    setWindowTitle(nickname);
    ui->nickname_label->setText(nickname);
    ui->sign_label->setText(sign);

}

void ChatDialog::addNewTalkInfo(QString info){
    ui->messageBox_textEdit->append(info);

}

void ChatDialog::on_send_pushButton_clicked()
{
    QString str=ui->messageEdit_textEdit->toPlainText();
    QString info;
    QTextStream stream(&info);
    stream<<nickname<<" "<<QDateTime::currentDateTime().toString("yyyy/M/d hh:mm:ss")<<"\n";
    stream<<str;
    tcp->sendInfo("talking_message",account,codeStr(info));
    addNewTalkInfo(info);
    ui->messageEdit_textEdit->clear();
}
