#ifndef RETRIEVER_H
#define RETRIEVER_H

#include <QtNetwork/QNetworkAccessManager>
#include <QUrl>

class Retriever : QObject
{
    Q_OBJECT

public:
    Retriever();
private:
    QUrl url;
    QNetworkAccessManager nam;
    QNetworkReply *reply;
};

#endif // RETRIEVER_H
