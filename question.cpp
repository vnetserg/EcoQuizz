#include "question.h"
#include <QDebug>

Question::Question()
{

}

Question::Question(QString text, QList<QString> answers, QList<bool> correct)
{
    this->text = text;
    this->answers = answers;
    this->correct = correct;
    for (int i = 0; i < correct.length(); i++)
        checked << false;
    committed = false;

    if (answers.length() != correct.length())
        qDebug() << "WARNING: answers.length() != correct.length()";
}

int Question::nCorrect()
{
    int res = 0;
    foreach (bool cor, correct)
        if (cor)
            res += 1;
    return res;
}

int Question::nAnswers()
{
    return answers.length();
}

QString Question::getText()
{
    return text;
}

QList<QString> Question::getVariants()
{
    return answers;
}

bool Question::isCommitted()
{
    return committed;
}

void Question::setAnswerChecked(int ind, bool checked)
{
    if (committed)
        qDebug() << "WARNING: trying to edit answers on committed question!";
    else
        this->checked[ind] = checked;
}

void Question::commit()
{
    qDebug() << text;
    for (int i = 0; i < answers.length(); i++)
        qDebug() << (i+1) << ") " << answers[i] << "[correct: " << correct[i]
                  << ", user: " << checked[i] << "];";

    /*
    userInputCorrect = true;
    for (int i = 0; i < answers.length(); i++)
        if (correct[i] != checked[i])
            userInputCorrect = false;
    */
    committed = true;
}

bool Question::isUserInputCorrect()
{
    userInputCorrect = true;
    for (int i = 0; i < answers.length(); i++)
        if (correct[i] != checked[i])
            userInputCorrect = false;
    return userInputCorrect;
}
