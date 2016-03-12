#include "testsession.h"
#include <QDebug>

TestSession::TestSession()
{
}

TestSession::TestSession(QVector<Question> questions, int mins)
{
    qDebug() << "Questions length: " << questions.length();
    this->questions = questions;
    startedTime = QDateTime::currentDateTime();
    deadline = startedTime.addSecs(60*mins);
    index = 0;

    for (int i = 0; i < questions.length(); i++)
        seen << false;

    if (questions.length() == 0)
        qDebug() << "WARNING: empty TestSession!";
}

int TestSession::getIndex()
{
    return index;
}

int TestSession::getLength()
{
    return questions.length();
}

int TestSession::nUnanswered()
{
    int res = 0;
    foreach (Question qst, questions)
        if (!qst.isCommitted())
            res += 1;
    return res;
}

int TestSession::nSkipped()
{
    int res = 0;
    for (int i = 0; i < index; i++)
        if (!questions[i].isCommitted())
            res += 1;
    return res;
}

SessionReport TestSession::finish()
{
    int right = 0, wrong = 0, skipped = 0, unseen = 0;
    for (int i = 0; i < questions.length(); i++)
        if (seen[i])
        {
            if (questions[i].isCommitted())
                if (questions[i].isUserInputCorrect())
                    right += 1;
                else
                    wrong += 1;
            else
                skipped += 1;
        }
        else
            unseen += 1;
    return SessionReport(right, wrong, skipped, unseen, startedTime, QDateTime::currentDateTime(), deadline);
}

Question* TestSession::curQuestion()
{
    if (index < 0 || index >= questions.length())
        return NULL;

    if (!questions[index].isCommitted())
    {
        seen[index] = true;
        return &questions[index];
    }

    Question *cur = getNextUncommitted(1, &index);
    if (cur != NULL) {
        seen[index] = true;
        return cur;
    }
    cur = getNextUncommitted(-1, &index);
    if (cur != NULL)
        seen[index] = true;
    return cur;
}

Question* TestSession::nextQuestion()
{
    Question *next = getNextUncommitted(1, &index);
    if (next != NULL)
        seen[index] = true;
    return next;
}

Question* TestSession::prevQuestion()
{
    Question *prev = getNextUncommitted(-1, &index);
    if (prev != NULL)
        seen[index] = true;
    return prev;
}

bool TestSession::hasNext()
{
    return getNextUncommitted(1) != NULL;
}

bool TestSession::hasPrev()
{
    return getNextUncommitted(-1) != NULL;
}

bool TestSession::hasCur()
{
    if (!questions[index].isCommitted())
        return true;
    return (getNextUncommitted(1) != NULL) || (getNextUncommitted(-1) != NULL);
}

Question* TestSession::getNextUncommitted(int step, int *ind)
{
    for (int i = index+step; i >= 0 && i < questions.length(); i += step)
        if (!questions[i].isCommitted())
        {
            if (ind != NULL)
                *ind = i;
            return &questions[i];
        }
    return NULL;
}

int TestSession::getSecondsLeft()
{
    return QDateTime::currentDateTime().secsTo(deadline);
}

bool TestSession::timeOut()
{
    return deadline <= QDateTime::currentDateTime();
}
