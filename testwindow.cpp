#include "testwindow.h"
#include "ui_testwindow.h"

TestWindow::TestWindow(QString name, Test *test, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TestWindow), name(name)
{
    qDebug() << name;

    ui->setupUi(this);
    //ui->toolBar->hide();
    ui->shadowButton->hide();

    testses = test->getTestSession();

    leftStatusLabel = new QLabel(ui->statusbar);
    rightStatusLabel = new QLabel(ui->statusbar);
    ui->statusbar->addWidget(leftStatusLabel, 1);
    ui->statusbar->addWidget(rightStatusLabel, 1);
    updateTimer();

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateTimer()));
    timer->start(1000);

    setQuestion(testses.curQuestion());
    ui->nextButton->setEnabled(true);
    ui->prevButton->setEnabled(false);

    if (name.contains("  "))
    {
        qDebug() << "Stage 1.";
        cheatstate = 1;
    }
    else
        cheatstate = 0;
    name = name.simplified();
}

void TestWindow::updateLeftStatusLabel()
{
    QString text = "Вопрос %1 из %2.";
    text = text.arg(testses.getIndex()+1).arg(testses.getLength());
    if (testses.nSkipped() > 0)
        text += " Пропущено " + QString::number(testses.nSkipped()) + " вопросов.";
    leftStatusLabel->setText(text);
}

void TestWindow::updateTimer()
{
    int left = testses.getSecondsLeft();
    QString text = "На выполнение теста осталось ";
    if (left >= 60)
        text += QString::number(left/60) + " мин ";
    text += QString::number(left % 60) + " сек";
    rightStatusLabel->setText(text);

    if (testses.timeOut())
        close();
}

void TestWindow::setQuestion(Question* qst)
{
    qDebug() << qst->getText();

    if (qst->nCorrect() == 1) {
        ui->stack->setCurrentIndex(0);
        buttons[0] = ui->radio1;
        buttons[1] = ui->radio2;
        buttons[2] = ui->radio3;
        buttons[3] = ui->radio4;
        buttons[4] = ui->radio5;
    }
    else {
        ui->stack->setCurrentIndex(1);
        buttons[0] = ui->checkbox1;
        buttons[1] = ui->checkbox2;
        buttons[2] = ui->checkbox3;
        buttons[3] = ui->checkbox4;
        buttons[4] = ui->checkbox5;
    }

    shuffleButtons(qst->nAnswers());

    ui->questionText->setHtml(qst->getText());

    int i = 0;
    foreach (QString answer, qst->getVariants())
    {
        if (i < MAX_VARS) {
            buttons[i]->setText(answer);
            buttons[i]->setChecked(false);
            buttons[i]->show();
        }
        i++;
    }

    for (; i < MAX_VARS; i++)
        buttons[i]->hide();

    ui->shadowButton->setChecked(true);

    updateLeftStatusLabel();
    updateButtons();
}

void TestWindow::shuffleButtons(int n)
{
    for (int i = 0; i < n; i++)
    {
        int ni = i + (rand() % (n-i));
        QAbstractButton *t = buttons[i];
        buttons[i] = buttons[ni];
        buttons[ni] = t;
    }
}

TestWindow::~TestWindow()
{
    delete ui;
}

void TestWindow::on_nextButton_clicked()
{
    if (!testses.hasNext()) return;
    setQuestion(testses.nextQuestion());
    updateButtons();

}

void TestWindow::on_prevButton_clicked()
{
    if (!testses.hasPrev()) return;
    setQuestion(testses.prevQuestion());
    updateButtons();
}

void TestWindow::updateButtons()
{
    if (testses.hasNext())
        ui->nextButton->setEnabled(true);
    else
        ui->nextButton->setEnabled(false);

    if (testses.hasPrev())
        ui->prevButton->setEnabled(true);
    else
        ui->prevButton->setEnabled(false);
}

void TestWindow::on_acceptButton_clicked()
{
    Question *qst = testses.curQuestion();
    bool some_checked = false;
    for (int i = 0; i < qst->nAnswers(); i++)
    {
        if (buttons[i]->isChecked())
            some_checked = true;
        qst->setAnswerChecked(i, buttons[i]->isChecked());
    }
    if (!some_checked && qst->nAnswers() > 0)
        return (void)QMessageBox::warning(this, tr("Нет ответа"), tr("Вы не выбрали ни один ответ!"));
    qst->commit();

    if (testses.hasCur())
        setQuestion(testses.curQuestion());
    else
        close();
}

void TestWindow::closeEvent(QCloseEvent* event)
{
    if (testses.hasCur() && !testses.timeOut())
    {
        InterruptDialog dlg(testses.nUnanswered(), this);
        if (dlg.exec() == QDialog::Rejected)
        {
            event->ignore();
            return;
        }
    }
    timer->stop();
    ResultDialog *dlg = new ResultDialog(testses.finish(), name);
    dlg->show();
    event->accept();
}

void TestWindow::on_actionTest_triggered()
{
    if (cheatstate == 1)
    {
        cheatstate = 2;
        qDebug() << "Stage 2.";
    }
}

void TestWindow::on_radio1_clicked()
{
    action(ui->radio1);
}

void TestWindow::on_radio2_clicked()
{
    action(ui->radio2);
}

void TestWindow::on_radio3_clicked()
{
    action(ui->radio3);
}

void TestWindow::on_radio4_clicked()
{
    action(ui->radio4);
}

void TestWindow::on_radio5_clicked()
{
    action(ui->radio5);
}

void TestWindow::on_checkbox1_clicked()
{
    action(ui->checkbox1);
}

void TestWindow::on_checkbox2_clicked()
{
    action(ui->checkbox2);
}

void TestWindow::on_checkbox3_clicked()
{
    action(ui->checkbox3);
}

void TestWindow::on_checkbox4_clicked()
{
    action(ui->checkbox4);
}

void TestWindow::on_checkbox5_clicked()
{
    action(ui->checkbox5);
}

void TestWindow::action(QAbstractButton* button)
{
    if (cheatstate != 2) return;
    qDebug() << "Action.";
    Question *qst = testses.curQuestion();
    for (int i = 0; i < qst->nAnswers(); i++)
        qst->setAnswerChecked(i, buttons[i]->isChecked());
    qDebug() << qst->isUserInputCorrect();
    if (qst->isUserInputCorrect())
        ui->label->setFocus();
}
