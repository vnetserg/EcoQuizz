#include "interruptdialog.h"
#include "ui_interruptdialog.h"

InterruptDialog::InterruptDialog(int unanswered, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InterruptDialog)
{
    ui->setupUi(this);

    ui->label->setText(ui->label->text().arg(unanswered));
}

InterruptDialog::~InterruptDialog()
{
    delete ui;
}
