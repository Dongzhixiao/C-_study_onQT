/*为什么需要日志：
 * 1.调试需要：Release版本出现的Bug极有可能在Debug版本进行调试时不会出现，这时我们需要日志来猜测程序行为
 * 2.有些程序行为不允许被调试打断，如“基于网络的一些应用：下载软件(当你调试某个网络连接过程时可能带来超时导致正常的业务逻辑受到干扰)、
 * 使用多线程的软件(当你调试某个线程中的代码时也可能导致需要等待这个线程的其他线程出现问题或线程同步出错)”
 * 3.软件分析：某些下载软件需要记录下载速度以便测量下载性能、某些日志中记录关键业务逻辑节点以便上报给专门的统计服务器来分析用户行为
 */
/*Qt提供了4个全局函数用于输出调试或警告信息：
 * 1.qDebug(),用于输出以调试为目的的信息(可用printf()形式或者"<<"形式)
 * 2.qWarning(),用于报告程序的可恢复性错误(可用printf()形式或者"<<"形式)
 * 3.qCritical(),用于输出严重的错误信息和报告系统错误(可用printf()形式或者"<<"形式)
 * 4.qFatal(),用于在应用退出前输出一些简短的致命错误信息(可用printf()形式,同时默认会结束你的应用！)
 */

//#define ANDROID

#ifndef QDEBUG2LOGCAT_H
#define QDEBUG2LOGCAT_H

#ifdef ANDROID
void installLogcatMessageHandler(const char *TAG);
#else
#define installLogcatMessageHandler(TAG)
#endif

#endif // QDEBUG2LOGCAT_H
