#ifndef DIALOG_TEST_PIC_H
#define DIALOG_TEST_PIC_H

#include <QDialog>

namespace Ui {
class Dialog_test_pic;
}

class Dialog_test_pic : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_test_pic(QWidget *parent = 0);
    ~Dialog_test_pic();

private slots:
    void on_pushButton_connect_clicked();  //!< @brief 单击连接按钮进入的槽函数
    //TCP图像设备数据处理相关槽函数
    void visualTcp_readClient(void);  //!< @brief 读取图像设备TCP反馈数据的槽函数 @details 在图像设备TCP建立连接后其@a readyRead() 信号触发时进入的槽函数
    void visualTcp_OnConnected(void);  //!< @brief 读取图像设备TCP反馈数据的槽函数 @details 在图像设备TCP建立连接后其@a connected() 信号触发时进入的槽函数

    void on_pushButton_save_clicked();  //!< @brief 单击保存按钮进入的槽函数

    void test();  //!< @brief 跟新图片并显示的槽函数 @details

private:
    Ui::Dialog_test_pic *ui;
//    QSharedPointer<QImage> pic;   //!< 保存图像的指针
    QByteArray picArray;   //!< @brief 保存图片的字节数组
    QImage pic;            //!< @brief 保存图片并负责保存的图片数据
};

#endif // DIALOG_TEST_PIC_H
