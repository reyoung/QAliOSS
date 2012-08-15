#include <QString>
#include <QtTest>
#include <QAliOSS/utl.h>

class TstQAliOSSTest : public QObject
{
    Q_OBJECT
    
public:
    TstQAliOSSTest();
    
private Q_SLOTS:
    void testUrlGetAuthorizationCode();
};

TstQAliOSSTest::TstQAliOSSTest()
{
}

void TstQAliOSSTest::testUrlGetAuthorizationCode()
{
    {
        QString method = "PUT";
        QString res = "/quotes/nelson";
        QMap<QString,QString> header;
        header.insert("Content-Md5","c8fdb181845a4ca6b8fec737b3581d76");
        header.insert("Content-Type","text/html");
        header.insert("Date","Thu, 17 Nov 2005 18:49:58 GMT");
        header.insert("X-OSS-Meta-Author","foo@bar.com");
        header.insert("X-OSS-Magic","abracadabra");
        QString acc_key="OtxrzxIsfpFjA7SwPzILwy8Bw21TLhquhboDYROV";
        QString result = QAliOSS::Utl::getAuthorizationCode(
                    acc_key,
                    method,
                    header,
                    res
                    );
        QVERIFY(result == "63mwfl+zYIOG6k95yxbgMruQ6QI=");
    }
}

QTEST_APPLESS_MAIN(TstQAliOSSTest)

#include "tst_tstqaliosstest.moc"
