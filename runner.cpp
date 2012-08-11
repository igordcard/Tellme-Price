#include <QDebug>
#include "retriever.h"
#include "runner.h"

// TODO: class for reading site formats using *.price files
QString baseurl = "http://www.pcdiga.com/2/%%/product";
QTextStream out(stdout); // console output stream

Runner::Runner(QObject *parent, qint32 begin, qint32 end, QString path) :
    QObject(parent)
{ // TODO: check if all these news are really required...
    iid = begin;
    max = end;
    cnt = 0;
    sqlsaver = new SqlSaver(path);
    connect(this, SIGNAL(currentDone()), this, SLOT(getNext()));
    duration.start();
}

void Runner::run()
{
    emit currentDone();
}

// used for displaying page contents on screen
void Runner::displayContent()
{
    qDebug() << retriever->content();
    emit finished();
}

void Runner::processContent()
{
    QString newContent = retriever->content();
    QString title;
    float price = 0;

    // free current retriever
    retriever->deleteLater();

    Interpreter::parse_item(newContent, &title, &price);
    if(price > 0) { // skip invalid or inexistent products
        sqlsaver->addPrice(iid, title, price);
        cnt++;
    }

    emit currentDone();
}

void Runner::getNext()
{
    while(sqlsaver->exists(++iid) && iid < max);

    out << "\r" << iid << "/" << max << " - " << (qint32)((float)iid / max*100) << "% - count: " << cnt << " - " << format_time(duration.elapsed());
    flush(out);

    if(iid >= max) {
        sqlsaver->close();
        qDebug() << "\nTotal items fetched:" << cnt;
        emit finished();
    }

    QString currenturl = QString(baseurl);
    currenturl.replace("%%", QString::number(iid));
    retriever = new Retriever(currenturl);

    //retriever = new Retriever(QString(baseurl+QString::number(iid)));
    connect(retriever, SIGNAL(contentReady()), this, SLOT(processContent()));
}

QString Runner::format_time(int time)
{
    qint32 s;
    qint32 m;
    qint32 h;
    QString ss;
    QString mm;
    QString hh;
    QString formatted;

    // conversion
    time /= 1000;
    s = time % 60;
    time /= 60;
    m = time % 60;
    h = time / 60;

    /////////////
    if(s < 10)
        ss = "0" + QString::number(s);
    else
        ss = QString::number(s);
    if(m < 10)
        mm = "0" + QString::number(m);
    else
        mm = QString::number(m);
    if(h < 10)
        hh = "0" + QString::number(h);
    else
        hh = QString::number(h);
    /////////////

    formatted = hh + ":" + mm + ":" + ss;

    return formatted;
}
