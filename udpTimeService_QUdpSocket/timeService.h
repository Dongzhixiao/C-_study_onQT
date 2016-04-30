#ifndef TIMESERVICE_H
#define TIMESERVICE_H
#include <QUdpSocket>
/*用QUdpSocket实现服务器编程步骤：
 * 1.从QUdpSocket继承来实现代表服务的类（也可用通过聚合方式把QUdpSocket的对象放在服务器类中）
 * 2.调用bind绑定到一个端口等待数据报到来
 * 3.连接readyRead()信号处理到达的数据报
 */
class TimeServer : public QUdpSocket
{
    Q_OBJECT
public:
    TimeServer(QObject * parent = 0);

protected slots:
    void onReadyRead();
};

#endif // TIMESERVICE_H
