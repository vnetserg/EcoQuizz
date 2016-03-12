#ifndef QUESTION_H
#define QUESTION_H

#include <QString>
#include <QList>

class Question
{
public:
    Question();
    Question(QString text, QList<QString> answers, QList<bool> correct);

    QString getText();
    QList<QString> getVariants();
    void setAnswerChecked(int ind, bool checked);
    void commit();
    bool isCommitted();
    bool isUserInputCorrect();
    int nCorrect();
    int nAnswers();

private:
    QString text;
    QList<QString> answers;
    QList<bool> correct;
    QList<bool> checked;
    bool committed;
    bool userInputCorrect;
};

#endif // QUESTION_H
