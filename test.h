#ifndef TEST_H
#define TEST_H

#include <cstdlib>
#include <time.h>

#include <QFile>
#include <QList>
#include <QVector>
#include <QXmlStreamReader>
#include <QRegularExpression>

#include "testsession.h"
#include "question.h"

class Test
{
public:
    Test(QString xmlfilepath);
    TestSession getTestSession();
    int getLength();
    int getTimelimit();

private:
    QVector< QVector<Question> > sections;
    int length, timelimit;

    QString preprocess(QString text);

public slots:
};

#endif // TEST_H
