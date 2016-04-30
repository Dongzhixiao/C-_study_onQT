#ifndef TIMECLIENT_H
#define TIMECLIENT_H
#include <QTcpSocket>
/*connectToServer()中描述了QTcpSocket的编程步骤：
 * 1.构造QTcpSocket对象
 * 2.连接connectToHost()连接服务器
 * 3.连接connected()、readyread()、error()等信号，处理数据和错误
 * 4.定义业务相关的逻辑，根据网络交互结果来触发
 */
class TimeClient : public QObject
{
    Q_OBJECT
public:
    TimeClient(QObject * parent = 0);

    void connectToServer(const QString &server, qint16 port=37);

signals:
    void time(QString strTime);

private slots:
    void onConnected();
    void onReadyRead();

private:
    QTcpSocket * m_socket;
};
#endif // TIMECLIENT_H
