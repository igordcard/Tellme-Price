#ifndef RETRIEVER_H
#define RETRIEVER_H

#include <QObject>
#include <QtNetwork>
#include <QUrl>

class Retriever : public QObject
{
    Q_OBJECT

public:
    Retriever(QString urlstr, QObject *parent = 0);
    QString content();

signals:
    void contentReady();

private:
    QNetworkAccessManager *nam;
    QUrl url;
    QNetworkRequest *request;
    QNetworkReply *reply;
    QString urlstr;
    QString content_var;

private slots:
    void logResponse();
    void emitResponse();
};

#endif // RETRIEVER_H
