#ifndef USERINFO_H
#define USERINFO_H

#include <QString>
#include <vector>
using std::vector;

class UserInfo
{
public:
    UserInfo();
    QString account;
    QString password;
    QString nickname;
    QString sign;
    int picture;
};

extern UserInfo  *myuser;
extern vector<UserInfo> talkingList;

int findUser(QString account);



class LinkMan{
public:
    QString account;
    QString nickname;
};

extern vector<LinkMan> linkMan;


#endif // USERINFO_H
