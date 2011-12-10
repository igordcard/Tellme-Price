#include "saver.h"

Saver::Saver(QString filename)
{    
    file = new QFile(filename);
    file->open(QIODevice::WriteOnly | QIODevice::Text);
    stream = new QTextStream(file);
}

void Saver::appendLine(QString str)
{
    *stream << str+"\n";
    //flush(); // optional
}

void Saver::flush()
{
    stream->flush();
}
