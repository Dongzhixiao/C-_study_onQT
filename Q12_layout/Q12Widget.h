#ifndef Q12WIDGET_H
#define Q12WIDGET_H

#include <QWidget>
#include <QComboBox>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();

protected:
    void setupUI();   //注意这个初始化函数的实现，非常好的参考作用

protected slots:
    void onSubmit();

private:    //只有其他函数还需要用的变量才放在私有成员函数里面，好多界面可以不用再定义私有成员变量了，注意学习这种方法！！！
    QComboBox ** m_scores;
    int m_nQuestionCount;
};

#endif // Q12WIDGET_H
