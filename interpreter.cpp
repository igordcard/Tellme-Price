#include "interpreter.h"
#include <QDebug>

QRegExp Interpreter::title_exp = QRegExp("<a href=\"Produto.asp\\?Artigo\\=[0-9]+\" class=\"LetraLaranja\">([\\w\\-\\.\\,/\\&\\; _\(\\)\\+\'\"\\º\\±]+)</a>");
QRegExp Interpreter::price_exp = QRegExp("<strong>[ \t\r\n]*&euro; ([0-9,]+)[ \t\r\n]*</strong>");

Interpreter::Interpreter()
{
}

void Interpreter::parse_item(QString content, QString *title, float *price)
{
    if(content.length() > 1024) {
        title_exp.indexIn(content);
        price_exp.indexIn(content);
        *title = title_exp.cap(1);
        *price = price_exp.cap(1).replace(",",".").toFloat();
    }
}
