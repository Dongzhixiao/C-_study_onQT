#ifndef NOTE_H
#define NOTE_H

#include <QString>
#include <QList>

#define NEW_NOTE_PREFIX "##NEW-NOTE "
#define NEW_NOTE_PREFIX_LEN  11

class QNote{
public:
    QNote(const QString &title, const QString &content)
        : m_strTitle(title), m_strContent(content)
    {
    }

    QNote(const QNote &n)
        : m_strTitle(n.m_strTitle)
        , m_strContent(n.m_strContent)
    {

    }

    QNote &operator=(const QNote &r)
    {
        if(this != &r)
        {
            m_strTitle = r.m_strTitle;
            m_strContent = r.m_strContent;
        }
        return *this;
    }
    /*下面加载和保存函数使用QFile和QTextStream这对搭档完成.
     * 注意：Android平台上实际qnotepad把qnote.txt保存到应用的files目录(/data/data/an.qt.qnotepad/files)下了.
     * Android权限控制比较严格，如果操作非应用主目录下的其他目录(sd开目录除外),则会因为没有写权限而报错！
     */
    static void loadNotes(QList<QNote*> & notes);   //加载笔记列表
    static void saveNotes(QList<QNote*> & notes);   //保存笔记

    QString m_strTitle;      //保存笔记标题
    QString m_strContent;    //保存笔记内容
};

#endif // NOTE_H
