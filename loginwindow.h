#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QWidget>

namespace Ui {
class LoginWindow;
}

class LoginWindow : public QWidget
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = 0);
    ~LoginWindow();
    void showAccountLogin();
    void hideAccountLogin();
    void showConnectLogin();
    void hideConnectLogin();


public slots:
    void connectSuccess();
    void loginSuccess();
    void loginFail(QString info="");

private slots:

    void on_connect_pushButton_clicked();

    void on_login_pushButton_clicked();

private:
    Ui::LoginWindow *ui;
};

extern LoginWindow *loginWindow;
#endif // LOGINWINDOW_H
