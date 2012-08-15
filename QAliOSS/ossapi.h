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


    Response listAllMyBuckets()const;

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
