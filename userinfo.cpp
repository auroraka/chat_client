#include "userinfo.h"

UserInfo::UserInfo()
{

}

void addUser(){

}
int findUser(QString account){
    for (int i=0;i<talkingList.size();i++){
        if (talkingList[i].account==account)  return i;
    }
    return -1;
}
