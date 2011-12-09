#ifndef SAVER_H
#define SAVER_H

#include <QFile>
#include <QTextStream>

class Saver
{
public:
    Saver(QString filename);
    void appendLine(QString str);

private:
    QFile *file;
    QTextStream *stream;
};

#endif // SAVER_H
