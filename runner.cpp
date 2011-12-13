#include <QDebug>
#include "retriever.h"
#include "runner.h"

QString baseurl = "http://pcdiga.com/pcdiga/Produto.asp?Artigo=";
qint32 max = 9500;
QTextStream out(stdout); // console output stream

Runner::Runner(QObject *parent, qint32 begin) :
    QObject(parent)
{ // TODO: check if all these news are really required...
    iid = begin;
    cnt = 0;
    sqlsaver = new SqlSaver("data.db");
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
        qDebug() << "Total items fetched:" << cnt;
        emit finished();
    }

    retriever = new Retriever(QString(baseurl+QString::number(iid)));
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
