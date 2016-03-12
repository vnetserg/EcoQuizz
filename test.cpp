#include "test.h"
#include <QDebug>

Test::Test(QString xmlfilepath)
{
    QFile xmlfile(xmlfilepath);
    bool ok = xmlfile.open(QIODevice::ReadOnly | QIODevice::Text);
    //QByteArray all = xmlfile.readAll();
    qDebug() << "XML file open status: " << ok;
    QXmlStreamReader xml(&xmlfile);

    QString text; // текст текущего вопроса
    QList<QString> answers; // список вариантов ответа текущего вопроса
    QList<bool> correct; // массив меток о том, является ли вариант правильным

    while (!xml.atEnd() && !xml.hasError())
    {
        QXmlStreamReader::TokenType token = xml.readNext();
        qDebug() << "tag: " << xml.name();
        if (token == QXmlStreamReader::StartElement)
        {
            qDebug() << "Start Element" << xml.name();
            if (xml.name() == "test") {
                QXmlStreamAttributes attrib = xml.attributes();
                timelimit = attrib.value("timelimit").toInt();
                length = attrib.value("questions").toInt();
            }
            else if (xml.name() == "section") {
                qDebug() << "Section captured";
                sections << QVector<Question>();
            }
            else if (xml.name() == "text") {
                token = xml.readNext();
                text = preprocess(xml.text().toString());
                qDebug() << "Question text captured: " << text;
            }
            else if (xml.name() == "answer") {
                QXmlStreamAttributes attrib = xml.attributes();
                if (attrib.hasAttribute("correct") && attrib.value("correct").toString() == "1")
                    correct << true;
                else
                    correct << false;
                token = xml.readNext();
                answers << xml.text().toString();
                qDebug() << "Answer text captured: " << answers[answers.length()-1]
                         << "(" << correct[correct.length()-1] << ")";
            }
        }
        else if (token == QXmlStreamReader::EndElement)
        {
            qDebug() << "End Element" << xml.name();
            if (xml.name() == "question") {
                qDebug() << "Question flushed";
                sections[sections.length()-1] << Question(text, answers, correct);
                answers.clear();
                correct.clear();
            }
        }
    }
}

QString Test::preprocess(QString text)
{
    QRegularExpression re("<img src=[',\"](.*)[',\"]");
    qDebug() << "re status: " << re.isValid();
    return text.replace(re, "<img src=':/img/img/\\1'");
}

TestSession Test::getTestSession()
{
    QVector<Question> questions;
    for (int i = 0; i < sections.length(); i++)
    {
        int ni = i + (rand() % (sections.length() - i));
        QVector<Question> t = sections[i];
        sections[i] = sections[ni];
        sections[ni] = t;
    }
    for (int i = 0; i < sections.length(); i++)
    {
        for (int j = 0; j < sections[i].length(); j++)
        {
            int nj = j + (rand() % (sections[i].length() - j));
            Question t = sections[i][j];
            sections[i][j] = sections[i][nj];
            sections[i][nj] = t;
        }
        int count = length / sections.length() + ((i < length % sections.length()) ? 1 : 0);
        for (int j = 0; j < count && j < sections[i].length(); j++)
            questions << sections[i][j];
    }
    return TestSession(questions, timelimit);
}

int Test::getLength()
{
    return length;
}

int Test::getTimelimit()
{
    return timelimit;
}
