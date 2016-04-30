#ifndef TIMESERVICE_H
#define TIMESERVICE_H
#include <QTcpServer>
/*QTcpServer服务器编程步骤：
 * 1.从QTcpServer继承来实现代表服务的类（也可用通过聚合方式把QTcpServer的对象放在服务器类中）
 * 2.调用QTcpServer：listen()监听服务端口，等待客户端连接
 * 3.连接newConnection()信号或者重写incomingConnection()方法，使用QTcpSocket与传入连接交互
 *
 * 注意：incomingConnection()在多线程服务器编程模型下必须重写，因为QTcpSocket的默认实现，在构造QTcpSocket对象是指定其父为QTcpServer，
 * 于是QTcpSocket的对象就不能使用其他线程的事件循环来获取网络事件处理数据收发。而通过把sokcet描述符以事件的方式发送给工作线程，工作线程在自
 * 己的线程环境中构造QTcpSocket对象，就可以利用工作线程的事件循环来处理网络数据了
 */
class TimeServer : public QTcpServer
{
    Q_OBJECT
public:
    TimeServer(QObject * parent = 0);

protected slots:
    void onNewConnection();

protected:
    void sendTime(QTcpSocket *socket);
/*
private:
    void incomingConnection(int sock);
    */
};

#endif // TIMESERVICE_H
