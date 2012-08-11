#include "interpreter.h"
#include <QDebug>

QRegExp Interpreter::title_exp = QRegExp("<title>PCDiga - ([\\w\\-\\.\\,/\\&\\; _\(\\)\\+\'\"\\º\\±\\!\\:]+)</title>");
QRegExp Interpreter::price_exp = QRegExp("<span id=\"preco_grelha\" class=\"preco\" style=\"font-size:26px; font-weight:bold; font-family:Arial, Helvetica, sans-serif; line-height:6px\">([0-9,]+) &euro;</span>");

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
