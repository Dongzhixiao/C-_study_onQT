#ifndef MUSICWIDGET_H
#define MUSICWIDGET_H
#include <QWidget>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QSensorGesture>
#include <QTableWidget>
#include "../imageButton.h"
#include <QSlider>
#include <QLabel>
#include <QPushButton>

/*使用传感器手势的步骤:
 * 1.构造QSensorGestureManager对象
 * 2.调用QSensorGestureManager的gestureIds()获取手势列表
 * 3.查询手势列表中是否包含你感兴趣的手势id
 * 4.以手势id为参数构造QSensorGesture对象并连接对应的手势信号到你实现的槽上
 * 5.在合适的时候调用QSensorGesture的startDetction()方法
 * 6.在响应手势信号的槽内实现你的业务逻辑
 */

class MusicWidget : public QWidget
{
    Q_OBJECT

public:
    MusicWidget(QWidget *parent = 0);
    ~MusicWidget();

    void playFile(QString strFile, QString strPath
                                 , QStringList &files);
#ifndef ANDROID
    QSize sizeHint() const { return QSize(320, 480);}
#endif

signals:
    void selectSong();

protected slots:
    void onTurnover();
    void onMediaStatusChanged(QMediaPlayer::MediaStatus status);
    void onCurrentMediaIndexChanged(int pos);
    void onError(QMediaPlayer::Error error);
    void onDurationChanged(qint64 duration);
    void onPositionChanged(qint64 position);
    void onSeekableChanged(bool seekable);
    void onStateChanged(QMediaPlayer::State state);
    void onPlayPauseButton();
    void onStopButton();
    void onSliderPressed();
    void onSliderReleased();
    void onCellClicked(int row, int column);
    void onMuteButtonStateChanged(int state);
    void onPlayModeButton();

protected:
    void paintEvent(QPaintEvent *e);
    void timerEvent(QTimerEvent *e);  //收到播放状态转换为停止状态时启动定时器来切歌

private:
    void setupGUI();
    void initPlayer();
    void setupSensors();
    void playNext(int step);
    void gotoSong(int index);

private:
    QString m_strPath;
    QMediaPlayer *m_player;     //存放独单一首音乐
    QMediaPlaylist *m_playlist;  //存放一系列音乐列表
    QSensorGesture *m_shakeGesture;
    QSensorGesture *m_turnoverGesture;
    QTableWidget *m_playlistView;
    QLabel * m_currentSongLabel;
    ImageButton * m_folderButton;
    ImageButton * m_prevButton;
    ImageButton * m_playpauseButton;
    ImageButton * m_stopButton;
    ImageButton * m_nextButton;
    QPushButton * m_playModeButton;
    QSlider *m_playProgress;
    bool m_bSliderCanUpdate;
    QPixmap m_bkgndLogo;
    QLabel * m_positionLabel;
    QLabel * m_durationLabel;
    int m_nAutoNextTimer;
};

#endif // MUSICWIDGET_H
