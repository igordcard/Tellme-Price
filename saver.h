#ifndef SAVER_H
#define SAVER_H

#include <QFile>
#include <QTextStream>

class Saver
{
public:
    Saver(QString filename);
    void appendLine(QString str);
    void flush();

private:
    QFile *file;
    QTextStream *stream;
};

#endif // SAVER_H
