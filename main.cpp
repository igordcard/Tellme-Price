#include <QtCore>
#include <QtGui/QApplication>
#include <QTimer>
#include "mainwindow.h"
#include "runner.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QString path;
    qint32 begin = 0;
    qint32 end = 0;
    QString source;

    if(argc < 4) {
        qDebug() << "Syntax: TellmePrice [begin index] <end index> <database path> <source file>";
        MainWindow mw;
        mw.show();
        return a.exec();
    }
    else {
        if(argc == 4) {
            end = atoi(argv[1]);
            path = argv[2];
            source = argv[3];
        }
        else
        {
            begin = atoi(argv[1]);
            end = atoi(argv[2]);
            path = argv[3];
            source = argv[4];
        }
        Runner *runner = new Runner(&a, begin, end, path, source);
        QObject::connect(runner, SIGNAL(finished()), &a, SLOT(quit()));
        QTimer::singleShot(0, runner, SLOT(run()));
        return a.exec();
    }
}
