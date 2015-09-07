#ifndef CHATDIALOG_H
#define CHATDIALOG_H

#include <QWidget>
#include <map>
using std::map;

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

    QString nickname,sign,account;

private slots:
    void on_send_pushButton_clicked();

private:
    Ui::ChatDialog *ui;
};


#endif // CHATDIALOG_H
