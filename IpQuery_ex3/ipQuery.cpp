/*QJsonDocument
 *QJsonDocument既可以从一个基于文本表示的UTF-8编码，又可以从Qt自己的二进制格式读取和写入这个文件。
 *JSON文档可以从它的基于文本的表示使用QJsonDocument::fromJson()转换为QJsonDocument，用.toJSON()将其转换回文字。解析器非常快速和高效，将JSON转换为二进制表示。
 *QJsonObject
 *QJsonObject类用于封装JSON对象。
 *JSON对象是键值对，其中键是唯一的字符串，其值由QJsonValue代表。一个QJsonObject可以从QVariantMap转换/被转换。
 *QJsonArray
 *QJsonArray类用于封装JSON数组。
 *一个JSON数组列表值。该列表可以通过从阵列插入和移除QJsonValue的操纵。一个QJsonArray可以从QVariantList转换为/被转换。
 */
#include "ipQuery.h"
#include <QJsonDocument>
#include <QByteArray>
#include <QHostAddress>
#include <QJsonObject>
#include <QNetworkRequest>
#include <QJsonArray>
#include <QTextCodec>
#include <QDebug>
/*
 * http://opendata.baidu.com/api.php?query=36.57.177.187&co=&resource_id=6006&t=1401346439107&ie=utf8&oe=gbk&cb=op_aladdin_callback&format=json&tn=baidu&cb=jQuery11020322038795100525_1401343864465&_=1401343864504
 */

/*
 * jQuery11020322038795100525_1401343864465
( --remove
  { --> object
    "status":"0",
    "t":"1401346439107",
    "data":[ -->array
      { --> object
        "location":"安徽省宿州市 电信",
        "titlecont":"IP地址查询",
        "origip":"36.57.177.187",
        "origipquery":"36.57.177.187",
        "showlamp":"1",
        "showLikeShare":1,
        "shareImage":1,
        "ExtendedLocation":"",
        "OriginQuery":"36.57.177.187",
        "tplt":"ip",
        "resourceid":"6006",
        "fetchkey":"36.57.177.187",
        "appinfo":"", "role_id":0, "disp_type":0
      }
    ]
  }
);
 */
IpQuery::IpQuery(QObject *parent)
    : QObject(parent)
    , m_nam(this)
{
    connect(&m_nam, SIGNAL(finished(QNetworkReply*)), this, SLOT(onReplyFinished(QNetworkReply*)));
}

IpQuery::~IpQuery()
{

}
/*下一个函数展示了QNetworkAccessManager进行http下载的基本步骤：
 * 1.使用QNetworkRequest构造请求(包括URL和http header)
 * 2.调用QNetworkAccessManager的get()方法提交下载请求
 * 3.使用QNetworkReply,保存与下载有关的一些属性，setProperty()可以动态生成属性,而property()可以把属性取出来
 * 4.响应QNetworkAccessManager的finished()信号处理网络反馈(也可连接QNetworkReply的readyReady()、downloadProgress()、error()、
 * finished()等信号进行更为详细的下载控制)
 */
void IpQuery::query(const QString &ip)
{
    QString strUrl = QString("http://opendata.baidu.com/api.php?query=%1&resource_id=6006&ie=utf8&format=json").arg(ip);
    QUrl url(strUrl);
    QNetworkRequest req(url);
    req.setRawHeader("Accept", "text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8");
    req.setHeader(QNetworkRequest::UserAgentHeader, "Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/35.0.1916.114 Safari/537.36");
    QNetworkReply *reply = m_nam.get(req);
    reply->setProperty("string_ip", ip);
}

void IpQuery::query(quint32 ip)
{
    QHostAddress addr(ip);
    query(addr.toString());
}
/*下一个函数做了一下几个事情：
 * 1.取出提交下载请求时设置的属性(字符串格式的ip地址)
 * 2.调用QNetworkReply::error()检查是否出错
 * 3.调用QNetworkReply::attribute()或者http状态码,查看http协议本身是否报错(如404/403/500等)
 * 4.读取数据
 * 5.调用QNetworkReply::header()方法获取Content-Type头部,查看字符编码,如果是GBK或者GB2312则转换成UTF-8(QJsonDocument解析时需要
 * UTF-8格式)
 * 6.解析Json数据
 *
 * 注意，其中第5部可分解为一下几步：
 * 1.使用QTextCode的静态方法codecForName()获取指定编码格式的QTextCcodec实例
 * 2.调用QTextCodec的toUnicode()方法转换为unicode编码的QString对象
 * 3.调用QString的toUtf8()方法转换为UTF-8格式
 */
void IpQuery::onReplyFinished(QNetworkReply *reply)
{
    reply->deleteLater();
    QString strIp = reply->property("string_ip").toString();
    if(reply->error() != QNetworkReply::NoError)
    {
        qDebug() << "IpQuery, error - " << reply->errorString();
        emit finished(false, strIp, m_emptyString);
        return;
    }

    int status = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    //qDebug() << "IpQuery, status - " << status ;
    if(status != 200)
    {
        emit finished(false, strIp, m_emptyString);
        return;
    }

    QByteArray data = reply->readAll();
    QString contentType = reply->header(QNetworkRequest::ContentTypeHeader).toString();
    //qDebug() << "contentType - " << contentType;
    int charsetIndex = contentType.indexOf("charset=");
    if(charsetIndex > 0)
    {
        charsetIndex += 8;
        QString charset = contentType.mid(charsetIndex).trimmed().toLower();
        if(charset.startsWith("gbk") || charset.startsWith("gb2312"))
        {
            QTextCodec *codec = QTextCodec::codecForName("GBK");
            if(codec)
            {
                data = codec->toUnicode(data).toUtf8();
            }
        }
    }

    int parenthesisLeft = data.indexOf('(');
    int parenthesisRight = data.lastIndexOf(')');
    if(parenthesisLeft >=0 && parenthesisRight >=0)
    {
        parenthesisLeft++;
        data = data.mid(parenthesisLeft, parenthesisRight - parenthesisLeft);
    }
    //第5步：
    //下面两行根据数据生成QJsonDocument对象
    QJsonParseError err;
    QJsonDocument json = QJsonDocument::fromJson(data, &err);
    if(err.error != QJsonParseError::NoError)
    {
        qDebug() << "IpQuery, json error - " << err.errorString();
        emit finished(false, strIp, m_emptyString);
        return;
    }
    //下两行找到根对象名为“data”的key对应的值
    QJsonObject obj = json.object();
    QJsonObject::const_iterator it = obj.find("data");
    if(it != obj.constEnd())
    {
        QJsonArray dataArray = it.value().toArray();  //找的data对应值，使用toArray()转换为QJsonArray
        QJsonObject info = dataArray.first().toObject();  //使用QJsonArray的first()方法取第一个元素,使用toObject()转换为QJsonObject
        QString area = info.find("location").value().toString();  //使用find()方法,以"location"为key值进行查找，结果转为String类
        emit finished(true, strIp, area);
    }
}
