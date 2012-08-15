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
    //! Create the authorization for OSS based on header input.
    //! You should put it into "Authorization" parameter of header.
    //! @note: port form oss_util.py:get_assign
    static QString getAuthorizationCode(const QString& acc_key="",
                                        const QString& method="GET",
                                        const QMap<QString,QString>& headers=QMap<QString,QString>(),
                                        const QString& resource="/");

    //! set GET params to an url.
    //! @note: port from oss_util.py:append_param
    static QString appendParam(const QString& url,
                               const QMap<QString,QString>& params);

private:
    //static QMap<QString,QString> _formatHeader(const QMap<QString,QString>& headers);
};
}
#endif // UTL_H
