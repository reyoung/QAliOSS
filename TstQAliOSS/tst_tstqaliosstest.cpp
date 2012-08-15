#include <QString>
#include <QtTest>
#include <QAliOSS/utl.h>
#include <QAliOSS/ossapi.h>
#include <QAliOSS/synchttp.h>

class TstQAliOSSTest : public QObject
{
    Q_OBJECT
    
public:
    TstQAliOSSTest();
    
private Q_SLOTS:
    void testUrlGetAuthorizationCode();
    void testAddParams();
    void testConsForOSSApi();
    void initTestCase();
    void testSyncHttp();
private:
    QString accessId;
    QString secretAccessKey;
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

void TstQAliOSSTest::testAddParams()
{
    {
        QString url="www.notuseful.com";
        QMap<QString,QString> params;
        params.insert("a","b");
        params.insert("acl","");
        params.insert("maxkeys","30");
        QString result = QAliOSS::Utl::appendParam(url,params);
        QVERIFY(result=="www.notuseful.com?a=b&max-keys=30&acl");
    }
}

void TstQAliOSSTest::testConsForOSSApi()
{
    QAliOSS::OSSApi api("www.notuseful.com","xxxfffeee","xxxeeefff");
    QVERIFY(api.getHost()=="www.notuseful.com");
    QVERIFY(api.getAccessID()=="xxxfffeee");
    QVERIFY(api.getSecretAccessKey()=="xxxeeefff");
}

void TstQAliOSSTest::initTestCase()
{
    QFile f("key.txt");
    if(f.open(QFile::ReadOnly)){
        QTextStream tin(&f);
        this->accessId = tin.readLine();
        this->secretAccessKey = tin.readLine();
        f.close();
    }
    qDebug()<<"Test With AccessID="<<accessId
           <<" SecretAccessKey="<<secretAccessKey;
}

QTEST_MAIN(TstQAliOSSTest)

void TstQAliOSSTest::testSyncHttp()
{
    QVERIFY(QCoreApplication::instance()!=0);
    SyncHttp h;
    bool ok = h.syncSetHost("127.0.0.1",80);
    QVERIFY(ok);

    QHttpRequestHeader hd;
    hd.setRequest("GET","/");
    Response r = h.syncRequest(hd,"");
    qDebug()<<r.Header.contentLength();
}

#include "tst_tstqaliosstest.moc"
