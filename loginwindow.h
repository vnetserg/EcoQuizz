#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>

#include "testwindow.h"
#include "test.h"

namespace Ui {
class LoginWindow;
}

class LoginWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = 0);
    ~LoginWindow();

private slots:
    void on_startButton_clicked();

private:
    Ui::LoginWindow *ui;
    Test *test;
};

#endif // LOGINWINDOW_H
