#include "ossapi.h"
#include "utl.h"

namespace QAliOSS{
OSSApi::OSSApi(const QString &host, const QString &access_id, const QString &secret_access_key, QObject *parent) :
    QObject(parent),m_host(host),m_accessId(access_id),m_secret_access_key(secret_access_key)
{
}

OSSApi::~OSSApi()
{
}

QString OSSApi::getHost() const
{
    return m_host;
}

void OSSApi::setHost(const QString &host)
{
    this->m_host = host;
}

QString OSSApi::getAccessID() const
{
    return this->m_accessId;
}

void OSSApi::setAccessID(const QString &a_id)
{
    this->m_accessId = a_id;
}

QString OSSApi::getSecretAccessKey() const
{
    return this->m_secret_access_key;
}

void OSSApi::setSecretAccessKey(const QString &k)
{
    this->m_secret_access_key = k;
}


}

Response QAliOSS::OSSApi::listAllMyBuckets() const
{
    QString method = "GET";
    QString url = "/";
    QString resource = "/";
    QLocale loc(QLocale::English,QLocale::UnitedStates);
    QString date =
            loc.toString(QDateTime::currentDateTime().toUTC(),
                         "ddd, dd MMM yyyy hh:mm:ss")+" GMT";
    QMap<QString,QString> headers;
    headers.insert("Date",date);
    headers.insert("Host",this->getHost());
    if (!this->getAccessID().isEmpty()&&!this->getSecretAccessKey().isEmpty()){
        headers.insert("Authorization",this->_createSignForNormalAuth(method,headers,resource));
    } else if(!this->getAccessID().isEmpty()){
        headers.insert("Authorization",this->getAccessID());
    }

    QHttpRequestHeader req(method,url);
    QMapIterator<QString,QString> it(headers);
    while(it.hasNext()){
        it.next();
        req.addValue(it.key(),it.value());
    }
    SyncHttp h;
    bool ok = h.setHost(this->getHost(),80);
    if(!ok){
        Response retv;
        retv.Ok = false;
        return retv;
    }
    return h.syncRequest(req,"");
}

QString QAliOSS::OSSApi::_createSignForNormalAuth(const QString &method, const QMap<QString, QString> &headers, const QString &resource)const
{
    return QString("OSS ")+
            this->getAccessID()+":"
            +QAliOSS::Utl::getAuthorizationCode(this->getSecretAccessKey(),
                                                method,
                                                headers,
                                                resource);
}
