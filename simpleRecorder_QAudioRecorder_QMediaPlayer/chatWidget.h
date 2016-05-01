#ifndef CHATWIDGET_H
#define CHATWIDGET_H
#include <QTableWidget>
#include <QPushButton>
#include <QLabel>
#include <QMediaPlayer>
#include <QAudioRecorder>
#include <QAudioEncoderSettings>

class ChatWidget : public QWidget
{
    Q_OBJECT
public:
    ChatWidget(QWidget *parent = 0);
    ~ChatWidget();

    QSize sizeHint() const{ return QSize(480, 800); }

protected:
    bool eventFilter(QObject *, QEvent *);  //重写事件过滤器，为了处理BACK按键。复习：当本身没有焦点时，用此方法可以处理某种事件！

protected slots:
    void onTalkPressed();  //按住说话按钮，即开始录音
    void onTalkReleased(); //松开说话按钮，即结束录音
    void onPlayButton();
    void onPlayStatusChanged(QMediaPlayer::MediaStatus status);
    void onPlayError(QMediaPlayer::Error error);
    void onPlayStateChanged(QMediaPlayer::State state);
    void onRecordDurationChanged(qint64 duration);
    void onRecordStatusChanged(QMediaRecorder::Status);
    void onRecordError(QMediaRecorder::Error);

private:
    bool setupAudioRecorder();
    void setupAudioPlayer();

private:
    QPushButton *m_talkButton;
    QPushButton *m_playButton;
    QLabel *m_stateLabel;
    QAudioRecorder m_recorder;  //负责录音工作，onRecordDurationChanged、onRecordStatusChanged、onRecordError三个槽跟踪它
    QAudioEncoderSettings m_settings;
    QMediaPlayer *m_player;  //用于播放录制好的音频，onPlayStatusChanged、onPlayError、onPlayStateChanged三个槽处理其反馈
    QString m_filePath;
    bool m_bRecorderValid;
    bool m_bRecordSuccess;
};

#endif // CHATWIDGET_H
