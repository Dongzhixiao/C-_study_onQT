#ifndef TIMECLIENT_H
#define TIMECLIENT_H
#include <QUdpSocket>
/*用QUdpSocket实现客户端编程步骤：
 * 分两种情况讨论:
 * A 又发送又接收
 * 1.从QUdpSocket继承来实现客户端的类（也可聚合一个QUdpSocket的对象）
 * 2.调用bind绑定到一个端口以便接收服务端的数据报
 * 3.调用writeDatagram()发送数据
 * 4.连接readyRead()信号到一个槽，在槽内处理到达的数据报
 *
 * B 只发送
 * 只要实例化一个QUdpSocket对象，调用writeDatagram()方法即可
 */
class TimeClient : public QObject
{
    Q_OBJECT
public:
    TimeClient(QString server, QObject * parent = 0);

signals:
    void time(QString strTime);

private slots:
    void onReadyRead();

private:
    QUdpSocket * m_socket;
};
#endif // TIMECLIENT_H
