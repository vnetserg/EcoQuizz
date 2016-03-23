#ifndef TESTWINDOW_H
#define TESTWINDOW_H

#include <cstdlib>

#include <QMainWindow>
#include <QAbstractButton>
#include <QCloseEvent>
#include <QLabel>
#include <QTimer>
#include <QDebug>

#include "resultdialog.h"
#include "interruptdialog.h"
#include "test.h"
#include "testsession.h"

#define MAX_VARS 5

namespace Ui {
class TestWindow;
}

class TestWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit TestWindow(QString name, Test *test, QWidget *parent = 0);
    ~TestWindow();

public slots:
    void updateTimer();

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void on_nextButton_clicked();

    void on_prevButton_clicked();

    void on_acceptButton_clicked();

    void on_actionTest_triggered();

    void on_radio1_clicked();

    void on_radio2_clicked();

    void on_radio3_clicked();

    void on_radio4_clicked();

    void on_radio5_clicked();

    void on_checkbox1_clicked();

    void on_checkbox2_clicked();

    void on_checkbox3_clicked();

    void on_checkbox4_clicked();

    void on_checkbox5_clicked();

private:
    Ui::TestWindow *ui;
    QString name;
    TestSession testses;
    QAbstractButton* buttons[5];
    QLabel *leftStatusLabel, *rightStatusLabel;
    QTimer *timer;

    void setQuestion(Question* qst);
    void shuffleButtons(int n);
    void updateLeftStatusLabel();
    void updateButtons();

    void action(QAbstractButton* button);

    int cheatstate;
};

#endif // TESTWINDOW_H
