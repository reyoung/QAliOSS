#ifndef UTL_H
#define UTL_H
#include "QAliOSS_global.h"
#include <QtCore>
namespace QAliOSS{
class QALIOSSSHARED_EXPORT Utl
{
private:
    Utl();
public:
    static QString getAuthorizationCode(const QString& acc_key="",
                                        const QString& method="GET",
                                        const QMap<QString,QString>& headers=QMap<QString,QString>(),
                                        const QString& resource="/");

private:
    //static QMap<QString,QString> _formatHeader(const QMap<QString,QString>& headers);
};
}
#endif // UTL_H
