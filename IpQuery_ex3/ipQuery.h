#ifndef IPQUERY_H
#define IPQUERY_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class IpQuery : public QObject
{
    Q_OBJECT
public:
    IpQuery(QObject *parent = 0);
    ~IpQuery();
    //下面分别接受两种格式的IP地址
    void query(const QString &ip);
    void query(quint32 ip);

signals:
    void finished(bool bOK, QString ip, QString area);

protected slots:
    void onReplyFinished(QNetworkReply *reply); //响应QNetworkAccessManager类的finished()信号

private:
    QNetworkAccessManager m_nam;
    QString m_emptyString;
};

#endif // IPQUERY_H
