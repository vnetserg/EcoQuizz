#include "resultdialog.h"
#include "ui_resultdialog.h"

ResultDialog::ResultDialog(SessionReport report, QString name, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ResultDialog)
{
    ui->setupUi(this);

    this->name = name;

    QString text = ui->resultLabel->text();
    text = text.replace("??", QString::number(report.score())).replace("**", QString::number(report.total()));
    ui->resultLabel->setText(text);
    ui->reportText->setPlainText(report.renderReport(name));
}

ResultDialog::~ResultDialog()
{
    delete ui;
}

void ResultDialog::on_saveButton_clicked()
{
    QString path = QFileDialog::getSaveFileName(this, tr("Сохранить отчёт"), name + ".html", tr("Документы html (*.htm *.html)"));
    if (!path.isEmpty())
    {
        QString text = ui->reportText->toHtml();
        text = text.replace("<head>", "<head><meta charset=\"utf-8\">");
        QFile file(path);
        if (!file.open(QFile::WriteOnly))
            return (void)QMessageBox::warning(this, "Ошибка записи", "Не удалось открыть файл для записи.");
        file.write(text.toUtf8());
        file.close();
        QMessageBox::information(this, "Успешно", "Отчёт успешно сохранён.");
    }
}
