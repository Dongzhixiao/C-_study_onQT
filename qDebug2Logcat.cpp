//#define ANDROID
#if defined(ANDROID)
#include "qDebug2Logcat.h"
#include <android/log.h>
#include <QDebug>
#include <QByteArray>

static const char *g_TAG = 0;
static void messageOutput2Logcat(QtMsgType type,
    const QMessageLogContext &context,
    const QString &msg)
{//将Qt的调试消息级别映射到Android的日志级别上
    int prio = ANDROID_LOG_VERBOSE;
    QByteArray localMsg = msg.toLocal8Bit();
    switch (type) {
    case QtDebugMsg:
        prio = ANDROID_LOG_DEBUG;
        break;
    case QtWarningMsg:
        prio = ANDROID_LOG_WARN;
        break;
    case QtCriticalMsg:
        prio = ANDROID_LOG_INFO;
        break;
    case QtFatalMsg:
        prio = ANDROID_LOG_FATAL;
        abort();
    }
    __android_log_write(prio, g_TAG, localMsg.data());  //此函数将日志信息写入Android日志系统
}

void installLogcatMessageHandler(const char *TAG)
{
    g_TAG = (TAG == 0 ? "QDebug" : TAG);
    qInstallMessageHandler(messageOutput2Logcat);  //此函数注册自己的消息处理器，替换Qt框架提供的默认消息处理器
}

#endif
