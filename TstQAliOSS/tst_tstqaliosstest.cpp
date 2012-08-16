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
    void testListAllMyBuckets();
    void testSignUrlAuthWithExpireTime();
    void testGetBucketAcl();
    void testListBucket();
    void testCreateBucket();
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

void TstQAliOSSTest::testListAllMyBuckets()
{
    QAliOSS::OSSApi api("storage.aliyun.com",this->accessId,this->secretAccessKey);
    Response res = api.listAllMyBuckets();
    QVERIFY(res.Ok);
    QVERIFY(res.Header.statusCode()/100 == 2);
    qDebug()<<res.Body;
}

void TstQAliOSSTest::testSignUrlAuthWithExpireTime()
{
    QString method = "GET";
    QString bucket = "test2012-aug-1612-04-24";
    QString object = "test_object";
    QString url = (QString("http://storage.aliyun.com/oss/") + bucket + "/") + object;
    QMap<QString,QString> headers;
    headers.insert("Date","1345089924");
    QString resource = QString("/%1/%2").arg(bucket).arg(object);
    int timeout = 60;
    QAliOSS::OSSApi api("storage.aliyun.com",this->accessId,this->secretAccessKey);
    QString result = api.signUrlAuthWithExpireTime(method,url,headers,resource,timeout);
    qDebug()<<result;
    //! @todo make test more good.
    QUrl target(result);
    QUrl expect("http://storage.aliyun.com/oss/test2012-aug-1612-04-24/test_object?OSSAccessKeyId=gs2x8c4kl1hma3i5p0u69dho&Expires=1345089924&Signature=RVpORQioAEz8Nnpyf5amK00nJ%2BU%3D");
    QList<QPair<QString, QString> > kvs = target.queryItems();
    QListIterator<QPair<QString,QString> > it(kvs);
    while(it.hasNext()){
        QPair<QString,QString> k = it.next();
//        qDebug()<<k.first<<" "<<k.second<<" | "<<expect.queryItemValue(k.first);
        QVERIFY(expect.queryItemValue(k.first)==k.second);
    }
    QVERIFY(expect.host()==target.host());
}

void TstQAliOSSTest::testGetBucketAcl()
{
    QAliOSS::OSSApi api("storage.aliyun.com",this->accessId,this->secretAccessKey);
    Response res = api.getBucketAcl("test_sdk");
    QVERIFY(res.Ok);
    QVERIFY(res.Header.statusCode()/100==2);
    qDebug()<<res.Body;
}

void TstQAliOSSTest::testListBucket()
{
    QAliOSS::OSSApi api("storage.aliyun.com",this->accessId,this->secretAccessKey);
    Response res = api.listBucket("test_sdk");
    QVERIFY(res.Ok);
    QVERIFY(res.Header.statusCode()/100==2);
    qDebug()<<res.Body;
}

void TstQAliOSSTest::testCreateBucket()
{
    QAliOSS::OSSApi api("storage.aliyun.com",this->accessId,this->secretAccessKey);
    Response res = api.createBucket("test_sdk2");
    qDebug()<<res.Header.statusCode();
    QVERIFY(res.Ok);
    QVERIFY(res.Header.statusCode()/100==2);
    res = api.deleteBucket("test_sdk2");
    QVERIFY(res.Ok);
    QVERIFY(res.Header.statusCode()/100==2);
}

#include "tst_tstqaliosstest.moc"
