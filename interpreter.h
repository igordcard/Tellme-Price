#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <QString>
#include <QRegExp>

class Interpreter
{
public:
    Interpreter(QString source);
    void parse_item(QString content, QString *title, float *price);
    QString getBaseURL();
private:
    QString base_url;
    qint32 min_length;
    QRegExp title_exp;
    QRegExp price_exp;
    qint32 reserved;
};

#endif // INTERPRETER_H
