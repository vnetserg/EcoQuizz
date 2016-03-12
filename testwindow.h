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
};

#endif // TESTWINDOW_H
