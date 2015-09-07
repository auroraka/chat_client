#ifndef USERLIST_H
#define USERLIST_H

#include <QWidget>
#include <QTimer>
#include <QListWidgetItem>

namespace Ui {
class UserList;
}

class UserList : public QWidget
{
    Q_OBJECT

public:
    explicit UserList(QWidget *parent = 0);
    ~UserList();
    void myUpdate();
    int loginSuccess;
    void talkTo(QString account,QString info);

public slots:
    void newChat(QListWidgetItem *item);

private:
    Ui::UserList *ui;
    QTimer *timer;
};

extern UserList *userList;
#endif // USERLIST_H
