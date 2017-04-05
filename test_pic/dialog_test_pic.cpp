#include "dialog_test_pic.h"
#include "ui_dialog_test_pic.h"
#include <QTcpSocket>
#include <QHostAddress>
#include <QDateTime>
#include <QFileDialog>

#include <QDebug>

Dialog_test_pic::Dialog_test_pic(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_test_pic)
{
    ui->setupUi(this);
}

Dialog_test_pic::~Dialog_test_pic()
{
    delete ui;
}

void Dialog_test_pic::on_pushButton_connect_clicked()
{
    picArray.clear();  //点击按钮之后重新连接，清空原来读取的数据
    //新建tcp接口
    QTcpSocket *visualTcpSocket = new QTcpSocket(this);
    //加入信号和槽
    connect(visualTcpSocket, SIGNAL(readyRead()), this, SLOT(visualTcp_readClient()));
    connect(visualTcpSocket, SIGNAL(connected()), this, SLOT(visualTcp_OnConnected()));
    connect(visualTcpSocket, SIGNAL(disconnected()), visualTcpSocket, SLOT(deleteLater()));
//    connect(visualTcpSocket,SIGNAL(readChannelFinished()),this,SLOT(test()));
    //TCP连接(直接加上地址和端口)
    visualTcpSocket->connectToHost(ui->lineEdit_IP->text(), ui->lineEdit_port->text().toInt());  //连接摄像头的socket

    ui->label_image_show->setText("正在尝试连接显示设备，请稍等...");
}

void Dialog_test_pic::test()
{
    qDebug()<<"读取完成";
    qDebug()<<"全部数据是："<<picArray.size();

//    char * tem = picArray.data();
//    for(int i = 0 ; i != picArray.size() ; ++i)
//    {
//        qDebug()<< *tem;
//        tem++;
//    }
    pic = QImage::fromData(picArray);
    QImage resultImg = pic.scaled(ui->label_image_show->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
    ui->label_image_show->setPixmap(QPixmap::fromImage(resultImg));
//    qDebug()<<"全部数据是："<<picArray.data();
//    picArray.clear();
}

void Dialog_test_pic::visualTcp_OnConnected()
{
    ui->label_image_show->setText("连接成功，正在等待图片数据");
}

void Dialog_test_pic::visualTcp_readClient()
{
    QTcpSocket *socket = qobject_cast<QTcpSocket*>(sender());

//    qDebug()<<"当前读取前可以读取数据的字节是："<<socket->bytesAvailable();

    QByteArray datagram = socket->readAll();


//    qDebug()<<datagram.data();

//    pic = QSharedPointer<QImage>(new QImage(datagram.data()));

//    qDebug()<<"开始读取";
//    qDebug()<<datagram.data();
    picArray.append(datagram);
//    qDebug()<<"现在picArray的字节是："<<picArray.size();
//    qDebug()<<"读取成功";

    test();
}

void Dialog_test_pic::on_pushButton_save_clicked()
{
    QDateTime time = QDateTime::currentDateTime();//获取系统现在的时间

    QString str = time.toString(tr("hh时mm分")); //设置显示格式
    QString fileName = QFileDialog::getSaveFileName(this,tr("保存文件"),str,tr("bmp文件(*.bmp)"));
    if(fileName.length()==0)
        return;
    QFile imageFile(fileName);
    if (!imageFile.open(QIODevice::WriteOnly))
        return;
//    QDataStream dataStream(&imageFile);

//    dataStream<<pic;
    pic.save(&imageFile);
    qDebug()<<fileName;

}
