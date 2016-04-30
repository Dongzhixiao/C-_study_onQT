#include "log.h"
#include <QDateTime>

/*Logger类内部使用QFile写日志，其构造函数可以指定日志文件名和日志级别，构造函数会尝试打开日志文件，当打开失败是，isValid()会返回false
 * log()方法用来输出日志，它接受可变参数，使用方式和printf()一样！！！  注意学习这种用法！！！！！
 */

static const char * g_levelString[log_level_count] = {
    "CRITICAL",
    "ERROR",
    "WARN",
    "INFO",
    "DEBUG",
    "DEBUG2"
};

Logger::Logger(const QString &strLogFile, int level)
    : m_loglevel(level)
{
    m_file = new QFile(strLogFile);
    if(m_file && !m_file->open(
                QFile::WriteOnly | QFile::Append))
    {
        delete m_file;
        m_file = 0;
    }
}

Logger::~Logger()
{
    if(m_file)
    {
        m_file->close();
        delete m_file;
    }
}

bool Logger::isValid()
{
    return m_file != 0;
}

void Logger::setLogLevel(int level)
{
    if(level < log_critical)
    {
        m_loglevel = log_critical;
    }
    else if(level > log_debug_2)
    {
        m_loglevel = log_debug_2;
    }
    else
    {
        m_loglevel = level;
    }
}

void Logger::log(int level, const char *fmt, ...)
{
    if(level > m_loglevel || !m_file) return;

    char buffer[MAX_LOG_STRING_LEN];
    va_list args;
    va_start(args, fmt);
    vsnprintf(buffer, MAX_LOG_STRING_LEN - 1, fmt, args);
    va_end(args);

    log2file(level, buffer);
}

void Logger::log2file(int level, char *szLog)
{
    QString strLogInfo = QString("%1[%2]: %3\r\n")
            .arg(QDateTime::currentDateTime()
                 .toString("yyyy-MM-dd hh:mm:ss.zzz"))
            .arg(g_levelString[level]).arg(szLog);

    if(m_file->size() >= 1048576 )
    {
        m_file->resize(0);
    }
    m_file->write(strLogInfo.toLatin1());   //写文件方法
    m_file->flush();
}
/*通常QFile和QTextStream组合使用更方便：
 * QFile file("test.txt");
 * file.open(QFile::WriteOnly | QFile::Truncate);
 * QTextStream ts(&file);
 * ts.setCodec("utf-8");
 * ts<<"..."<<... ;
 * ts.flush();
 * file.close();
 *
 * 还有QDataStream用来序列化二进制文件：
 * QFile file("file.dat");
 * file.open(QIODevice::WriteOnly);
 * QDataStream out(&file);   // we will serialize the data into the file
 * out << QString("the answer is");   // serialize a string
 * out << (qint32)42;        // serialize an integer
 *　反序列化：
 * QFile file("file.dat");
 * file.open(QIODevice::ReadOnly);
 * QDataStream in(&file);    // read the data serialized from the file
 * QString str;
 * qint32 a;
 *　in >> str >> a;           // extract "the answer is" and 42
 */
