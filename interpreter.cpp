#include "interpreter.h"
#include <QDebug>
#include <QFile>

Interpreter::Interpreter(QString source)
{
    QFile file(source);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&file);

    base_url = in.readLine();
    min_length = in.readLine().toInt();
    title_exp = QRegExp(in.readLine());
    price_exp = QRegExp(in.readLine());
    reserved = in.readLine().toInt();
}

void Interpreter::parse_item(QString content, QString *title, float *price)
{
    if(content.length() > min_length) {
        title_exp.indexIn(content);
        price_exp.indexIn(content);
        *title = title_exp.cap(1);
        *price = price_exp.cap(1).replace(",",".").toFloat();
    }
}

QString Interpreter::getBaseURL() {
    return base_url;
}
