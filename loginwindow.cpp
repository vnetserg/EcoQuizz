#include "loginwindow.h"
#include "ui_loginwindow.h"

LoginWindow::LoginWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
    test = new Test(":/xml/test.xml");

    ui->infoLabel->setText(ui->infoLabel->text().arg(test->getLength()).arg(test->getTimelimit()));
}

LoginWindow::~LoginWindow()
{
    delete ui;
    delete test;
}

void LoginWindow::on_startButton_clicked()
{
    QString name = ui->nameEdit->text().simplified();
    if (name.isEmpty())
        return (void)QMessageBox::warning(this, tr("Нет имени"), tr("Вы не указали своё имя!"));
    TestWindow *testwind = new TestWindow(name, test);
    testwind->showMaximized();
    close();
}
