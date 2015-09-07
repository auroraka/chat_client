#ifndef CHATDIALOG_H
#define CHATDIALOG_H

#include <QWidget>
#include <vector>
using std::vector;

namespace Ui {
class ChatDialog;
}

class ChatDialog : public QWidget
{
    Q_OBJECT

public:
    explicit ChatDialog(QWidget *parent = 0);
    ~ChatDialog();
    void myUpdate();
    void addNewTalkInfo(QString info);

    int talkingID;
    QString nickname,sign,account;

private slots:
    void on_send_pushButton_clicked();

private:
    Ui::ChatDialog *ui;
};

extern vector<ChatDialog*> chatDialogList;

#endif // CHATDIALOG_H
