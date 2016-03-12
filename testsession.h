#ifndef TESTSESSION_H
#define TESTSESSION_H

#include <QVector>
#include <QDateTime>

#include "question.h"
#include "sessionreport.h"

class TestSession
{
public:
    TestSession();
    TestSession(QVector<Question> questions, int mins);

    Question* nextQuestion();
    Question* prevQuestion();
    Question* curQuestion();
    bool hasNext();
    bool hasPrev();
    bool hasCur();
    int getLength();
    int getIndex();
    int nUnanswered();
    int nSkipped();
    QDateTime getStartedTime();
    int getSecondsLeft();
    bool timeOut();
    SessionReport finish();

private:
    QVector<Question> questions;
    QVector<bool> seen;
    int index;
    QDateTime startedTime, deadline;

    Question* getNextUncommitted(int step, int* ind = NULL);
};

#endif // TESTSESSION_H
