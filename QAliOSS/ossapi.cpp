#include "ossapi.h"
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
