#ifndef RESULTDIALOG_H
#define RESULTDIALOG_H

#include <QDialog>
#include <QString>
#include <QFileDialog>
#include <QMessageBox>

#include "sessionreport.h"

namespace Ui {
class ResultDialog;
}

class ResultDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ResultDialog(SessionReport report, QString name, QWidget *parent = 0);

    ~ResultDialog();

private slots:
    void on_saveButton_clicked();

private:
    Ui::ResultDialog *ui;
    QString name;
};

#endif // RESULTDIALOG_H
