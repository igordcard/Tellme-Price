#include <QtCore/QCoreApplication>
#include <QTimer>
#include "runner.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QString path;
    qint32 begin = 0;
    qint32 end = 0;

    if(argc < 3) {
        qDebug() << "Syntax: TellmePrice [begin index] <end index> <database path>";
        exit(1);
    }
    else if(argc == 3) {
        end = atoi(argv[1]);
        path = argv[2];
    }
    else if(argc > 3)
    {
        begin = atoi(argv[1]);
        end = atoi(argv[2]);
        path = argv[3];
    }

    Runner *runner = new Runner(&a, begin, end, path);
    QObject::connect(runner, SIGNAL(finished()), &a, SLOT(quit()));
    QTimer::singleShot(0, runner, SLOT(run()));

    return a.exec();
}

void quit()
{
    qDebug() << "Exited due to finished()";
    exit(0);
}
