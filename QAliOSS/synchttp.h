#ifndef SYNCHTTP_H
#define SYNCHTTP_H

#include <QtNetwork>
#include <QtCore>
#include "QAliOSS_global.h"
struct Response{
    QHttpResponseHeader Header;
    QByteArray Body;
    bool Ok;
};


class QALIOSSSHARED_EXPORT SyncHttp : public QHttp
{
    Q_OBJECT
public:
    explicit SyncHttp(QObject *parent = 0);

    Response syncRequest(const QHttpRequestHeader &header,
                         const QByteArray& data);

    bool syncSetHost(const QString& host,
                     quint16 port);

private slots:
    void onRequestFinished(int ,bool);
    void onReadyRead(const QHttpResponseHeader& );
private:
    QEventLoop loop;
    int m_currentID;
    Response m_respose;
};

#endif // SYNCHTTP_H
