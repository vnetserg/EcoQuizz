#include "sessionreport.h"

SessionReport::SessionReport(int right, int wrong, int skipped, int unseen, QDateTime started, QDateTime finished, QDateTime deadline)
    : right(right), wrong(wrong), skipped(skipped), unseen(unseen), started(started), finished(finished), deadline(deadline)
{

}

int SessionReport::score()
{
    return right;
}

int SessionReport::total()
{
    return right + wrong + skipped + unseen;
}

QString SessionReport::renderReport(QString name)
{
    QString text = "Тест: МТУСИ. Тестирование по безопасности жизнедеятельности.\n" \
            "%1\n" \
            "Тестирование было начато %2\n" \
            "Продолжительность тестирования: %3 при ограничении %4 минут\n" \
            "Задано %5 вопросов из %6 запланированных, %7 вопросов пропущено.\n" \
            "Правильных ответов дано %8 (%9 %)\n" \
            "%10 балл из %11";
    int seen = right + wrong + skipped;
    int total = seen + unseen;

    int secs_elapsed = started.secsTo(finished);
    QString elapsed = QString::number(secs_elapsed % 60) + " сек";
    if (secs_elapsed >= 60)
        elapsed = QString::number(secs_elapsed/60) + " мин " + elapsed;

    text = text.arg(name).arg(started.toString("hh:mm:ss dd.MM.yyyy"))
            .arg(elapsed).arg(started.secsTo(deadline)/60)
            .arg(seen).arg(total).arg(skipped)
            .arg(right).arg(right*100/total)
            .arg(right).arg(total);
    return text;
}
