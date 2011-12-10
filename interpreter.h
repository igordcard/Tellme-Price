#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <QString>
#include <QRegExp>

class Interpreter
{
private:
    Interpreter();
    static QRegExp title_exp;
    static QRegExp price_exp;

public:
    static void parse_item(QString content, QString *title, float *price);
};

#endif // INTERPRETER_H
