#ifndef VIDEOMODIFICATIONPAGE_H
#define VIDEOMODIFICATIONPAGE_H

#include <QWidget>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QSlider>

class VideoModificationPage : public QWidget
{
    Q_OBJECT

public:
    explicit VideoModificationPage(QWidget* parent = nullptr);
    void stopPlayer();
    void startPlayer();

signals:
    void backToHome();

private slots:
    // ��ಥ�����ۺ���
    void onLeftPlayPauseClicked();
    void onLeftStopClicked();
    void onLeftMuteClicked();
    void onLeftVolumeChanged(int value);
    void onLeftPositionChanged(int position);
    void onLeftDurationChanged(qint64 duration);

    // �Ҳಥ�����ۺ���
    void onRightPlayPauseClicked();
    void onRightStopClicked();
    void onRightMuteClicked();
    void onRightVolumeChanged(int value);
    void onRightPositionChanged(int position);
    void onRightDurationChanged(qint64 duration);

private:
    void setupUI();
    void openFile();

    // ��ಥ�������ؼ�
    QMediaPlayer* leftPlayer;
    QVideoWidget* leftVideoWidget;
    QPushButton* leftPlayPauseButton;
    QPushButton* leftStopButton;
    QPushButton* leftMuteButton;
    QSlider* leftVolumeSlider;
    QSlider* leftPositionSlider;
    QPushButton* leftOpenFileButton;

    // �Ҳಥ�������ؼ�
    QMediaPlayer* rightPlayer;
    QVideoWidget* rightVideoWidget;
    QPushButton* rightPlayPauseButton;
    QPushButton* rightStopButton;
    QPushButton* rightMuteButton;
    QSlider* rightVolumeSlider;
    QSlider* rightPositionSlider;

    // �����ؼ�
    QPushButton* backButton;
    QLabel* descriptionLabel;
};

#endif // VIDEOMODIFICATIONPAGE_H
