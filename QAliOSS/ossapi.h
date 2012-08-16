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

    //! Send bucket operation request
    //! @param method, one of PUT, GET, DELETE, HEAD
    //! @param bucket_name
    //! @param headers, HTTP header
    //! @param params, parameters that will be appeded at the end of resource
    //! @return HTTP Response
    //! @note port form oss_api.py:bucket_operation
    Response doBucketOperation(const QString& method,
                               const QString& bucket_name,
                               const QMap<QString,QString>& headers=QMap<QString,QString>(),
                               const QMap<QString,QString>& params=QMap<QString,QString>())const;

    //! Get Access Control Level of bucket
    //! @param bucket name
    //! @return HTTP Response
    //! @note port from oss_api.py:get_bucket_acl
    Response getBucketAcl(const QString& bucket_name)const;
    

    //! List object that in bucket
    //! @return HTTP Response
    //! @note port from oss_api.py:list_bucket
    Response listBucket(const QString& bucket,
                        const QString& prefix="",
                        const QString& marker="",
                        const QString& delimiter="",
                        const QString& maxkeys="",
                        const QMap<QString,QString>& header=QMap<QString,QString>())const;
    //! List object that in bucket
    //! @return HTTP Response
    //! @note port from oss_api.py:get_bucket
    inline Response getBucket(const QString& bucket,
                            const QString& prefix="",
                            const QString& marker="",
                            const QString& delimiter="",
                            const QString& maxkeys="",
                            const QMap<QString,QString>& header=QMap<QString,QString>())const{
        return this->listBucket(bucket,prefix,marker,delimiter,maxkeys,header);
    }

    //! Create bucket
    //! @param acl, "" or "private"
    //! @return HTTP Response
    //! @note port from oss_api.py:create_bucket
    inline Response createBucket(const QString& bucket_name,const QString& acl="",const QMap<QString,QString>& headers = QMap<QString,QString>())const {
        return this->putBucket(bucket_name,acl,headers);
    }

    //! Create bucket
    //! @param acl, "" or "private"
    //! @return HTTP Response
    //! @note port from oss_api.py:put_bucket
    Response putBucket(const QString& bucket_name,const QString& acl="",QMap<QString,QString> headers = QMap<QString,QString>())const;

    //! Delete bucket
    //! @return Http response
    //! @note port from oss_api.py:delete_bucket
    inline Response deleteBucket(const QString& bucket_name)const{
        return this->doBucketOperation("DELETE",bucket_name);
    }


public slots:

private:
    QString _createSignForNormalAuth(const QString& method,
                                     const QMap<QString,QString>& headers=QMap<QString,QString>(),
                                     const QString& resource="/")const;

    QString getGMT() const;

    void insertAuthorization(QString method, QMap<QString,QString>& headers, QString resource) const;
    QHttpRequestHeader buildRequest(QString url, QString method, QMap<QString,QString> headers) const;

private:
    QString m_host;
    QString m_accessId;
    QString m_secret_access_key;
};

}
#endif // OSSAPI_H
