#include "retriever.h"
#include <QDebug>

Retriever::Retriever(QString urlstr, QObject *parent) :
                     QObject(parent)
{
    this->urlstr = urlstr;
    nam = new QNetworkAccessManager(this);
    request = new QNetworkRequest(urlstr);
    reply = nam->get(*request);
    connect(reply, SIGNAL(readyRead()), this, SLOT(logResponse()));
    connect(reply, SIGNAL(finished()), this, SLOT(emitResponse()));
}

QString Retriever::content()
{
    return content_var;
}

void Retriever::logResponse()
{
    content_var += QString(reply->readAll());
}

void Retriever::emitResponse()
{
    emit contentReady();
}
