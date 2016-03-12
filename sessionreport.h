#ifndef SESSIONREPORT_H
#define SESSIONREPORT_H

#include <QDateTime>

class SessionReport
{
public:
    SessionReport(int right, int wrong, int skipped, int unseen, QDateTime started, QDateTime finished, QDateTime deadline);
    int score();
    int total();
    QString renderReport(QString name);

private:
    int right, wrong, skipped, unseen;
    QDateTime started, finished, deadline;
};

#endif // SESSIONREPORT_H
