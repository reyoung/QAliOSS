#include "utl.h"
namespace QAliOSS{

static QString hmacSha1(QByteArray key, QByteArray baseString)
{
    int blockSize = 64; // HMAC-SHA-1 block size, defined in SHA-1 standard
    if (key.length() > blockSize) { // if key is longer than block size (64), reduce key length with SHA-1 compression
        key = QCryptographicHash::hash(key, QCryptographicHash::Sha1);
    }

    QByteArray innerPadding(blockSize, char(0x36)); // initialize inner padding with char "6"
    QByteArray outerPadding(blockSize, char(0x5c)); // initialize outer padding with char "\"
    // ascii characters 0x36 ("6") and 0x5c ("\") are selected because they have large
    // Hamming distance (http://en.wikipedia.org/wiki/Hamming_distance)

    for (int i = 0; i < key.length(); i++) {
        innerPadding[i] = innerPadding[i] ^ key.at(i); // XOR operation between every byte in key and innerpadding, of key length
        outerPadding[i] = outerPadding[i] ^ key.at(i); // XOR operation between every byte in key and outerpadding, of key length
    }

    // result = hash ( outerPadding CONCAT hash ( innerPadding CONCAT baseString ) ).toBase64
    QByteArray total = outerPadding;
    QByteArray part = innerPadding;
    part.append(baseString);
    total.append(QCryptographicHash::hash(part, QCryptographicHash::Sha1));
    QByteArray hashed = QCryptographicHash::hash(total, QCryptographicHash::Sha1);
    return hashed.toBase64();
}



static const QString self_define_header_prefix = "x-oss-";

static inline QMap<QString, QString> _formatHeader(const QMap<QString, QString> &headers)
{
    QMap<QString,QString> retv ;
    typedef QPair<QString,QString > AUX_TYPE ;
    QMapIterator<QString,QString> it(headers);
    it.toFront();
    while(it.hasNext()){
        it.next();
        if(it.key().toLower().startsWith(self_define_header_prefix)){
            retv.insert(it.key().toLower(),it.value());
        } else {
            retv.insert(it.key(),it.value());
        }
    }
    return retv;
}



Utl::Utl()
{
}

QString Utl::getAuthorizationCode(const QString &acc_key, const QString &method, const QMap<QString, QString> &headers, const QString &resource)
{
    QString content_md5 = headers.value("Content-Md5","");
    QString content_type = headers.value("Content-Type","");
    QString date = headers.value("Date","");
    QString canonicalized_resource = resource;
    QString canonicalized_oss_headers = "";
    QMap<QString,QString> tmp_headers = _formatHeader(headers);
    if (tmp_headers.size()>0){
        QMapIterator<QString,QString> it(tmp_headers);
        while(it.hasNext()){
            it.next();
            if (it.key().startsWith(self_define_header_prefix)){
                canonicalized_oss_headers+=it.key()+":"+it.value()+"\n";
            }
        }
    }
    QString string_to_sign=method + "\n" + content_md5 + "\n" + content_type + "\n" + date + "\n" + canonicalized_oss_headers + canonicalized_resource;

//    qDebug()<<canonicalized_oss_headers;
    return hmacSha1(acc_key.toLocal8Bit(),string_to_sign.toLocal8Bit());
}



}
