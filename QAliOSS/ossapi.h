#ifndef OSSAPI_H
#define OSSAPI_H

#include <QObject>
#include "QAliOSS_global.h"
#include "synchttp.h"
namespace QAliOSS{

class QALIOSSSHARED_EXPORT OSSApi : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString Host READ getHost WRITE setHost)
    Q_PROPERTY(QString AccessID READ getAccessID WRITE setAccessID)
    Q_PROPERTY(QString SecretAccessKey READ getSecretAccessKey WRITE setSecretAccessKey)

public:
    OSSApi(const QString& host,
                    const QString& access_id,
                    const QString& secret_access_key="",
                    QObject *parent = 0);
    virtual ~OSSApi();

    QString getHost()const;
    void setHost(const QString& host);

    QString getAccessID()const;
    void setAccessID(const QString& a_id);

    QString getSecretAccessKey()const;

    void setSecretAccessKey(const QString& k);

    //! List all buckets of user
    //! @note port from oss_api.py:list_all_my_buckets
    Response listAllMyBuckets()const;

    //! @note port from oss_api.py:get_service
    inline Response getService()const{
        return this->listAllMyBuckets();
    }

    //! Create the authorization for OSS based on the input method, url, body and headers
    //! @param method, one of PUT,GET,DELETE,HEAD
    //! @param url, HTTP address of bucket or object, eg: http://HOST/bucket/object
    //! @param headers, HTTP header
    //! @param resource,path of bucket or object, eg: /bucket/ or /bucket/object
    //! @param timeout,
    //! @return signature url.
    //! @note port from oss_api.py:sign_url_auth_with_expire_time
    QString signUrlAuthWithExpireTime(
            const QString& method,
            const QString& url,
            const QMap<QString,QString>& h = QMap<QString,QString>(),
            const QString& resource="/",
            int timeout=60
            )const;

signals:
    
public slots:

private:
    QString _createSignForNormalAuth(const QString& method,
                                     const QMap<QString,QString>& headers=QMap<QString,QString>(),
                                     const QString& resource="/")const;



private:
    QString m_host;
    QString m_accessId;
    QString m_secret_access_key;
};

}
#endif // OSSAPI_H
