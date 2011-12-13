#include <QtCore/QCoreApplication>
#include <QTimer>
#include "runner.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    qint32 begin = 0;
    if(argc > 1)
        begin = atoi(argv[1]);

    Runner *runner = new Runner(&a, begin);
    QObject::connect(runner, SIGNAL(finished()), &a, SLOT(quit()));
    QTimer::singleShot(0, runner, SLOT(run()));

    return a.exec();
}

void quit()
{
    qDebug() << "Exited due to finished()";
    exit(0);
}
