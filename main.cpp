#include "loginwindow.h"
#include "userlist.h"
#include "chatdialog.h"
#include "tcp.h"
#include "switcher.h"
#include "userinfo.h"
#include "enviroment.h"
#include <QApplication>

Switcher *switcher;
QTextEdit *debugWindow;

UserList *userList;
LoginWindow *loginWindow;
Tcp *tcp;
UserInfo *myuser;
vector<UserInfo>  userL;
vector<LinkMan> linkMan;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    switcher = new Switcher;
    debugWindow = new QTextEdit;
    makeDebugWindow();

    tcp = new Tcp;
    myuser = new UserInfo;
    userList  = new UserList;
    loginWindow = new LoginWindow;

    //-------------
    loginWindow->move(600,450);
    //--------------

    switcher->add("userList",userList);
    //switcher->add("chatDialog",chatDialog);
    switcher->add("loginWindow",loginWindow);

    switcher->showInterface("loginWindow");

    return a.exec();
}
