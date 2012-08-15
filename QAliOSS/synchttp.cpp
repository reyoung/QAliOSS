#include "synchttp.h"

SyncHttp::SyncHttp(QObject *parent) :
    QHttp(parent)
{
}

Response SyncHttp::syncRequest(const QHttpRequestHeader &header, const QByteArray &data)
{
    this->connect(this,SIGNAL(requestFinished(int,bool)),this,
                  SLOT(onRequestFinished(int,bool)));
    this->connect(this,SIGNAL(readyRead(QHttpResponseHeader)),
                  this,SLOT(onReadyRead(QHttpResponseHeader)));

    this->m_currentID = this->request(header,data);

    this->loop.exec();

    this->disconnect(this,SLOT(onReadyRead(QHttpResponseHeader)));
    this->disconnect(this,SLOT(onRequestFinished(int,bool)));
    return this->m_respose;
}

void SyncHttp::onRequestFinished(int id, bool error)
{
    if(this->m_currentID == id){
        this->m_respose.Ok = !error;
        this->loop.exit();
    }
}

void SyncHttp::onReadyRead(const QHttpResponseHeader& header)
{
    this->m_respose.Header = header;
    this->m_respose.Body = this->readAll();
}

bool SyncHttp::syncSetHost(const QString &host, quint16 port)
{
    this->connect(this,SIGNAL(requestFinished(int,bool)),this,
                  SLOT(onRequestFinished(int,bool)));

    this->m_currentID = this->setHost(host,port);
    this->loop.exec();
    this->disconnect(this,SLOT(onRequestFinished(int,bool)));

    return this->m_respose.Ok;
}
