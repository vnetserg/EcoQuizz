#ifndef INTERRUPTDIALOG_H
#define INTERRUPTDIALOG_H

#include <QDialog>

namespace Ui {
class InterruptDialog;
}

class InterruptDialog : public QDialog
{
    Q_OBJECT

public:
    explicit InterruptDialog(int unanswered, QWidget *parent = 0);
    ~InterruptDialog();

private:
    Ui::InterruptDialog *ui;
};

#endif // INTERRUPTDIALOG_H
