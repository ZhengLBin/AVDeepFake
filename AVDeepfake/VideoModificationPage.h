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
    // ×ó²à²¥·ÅÆ÷²Ûº¯Êý
    void onLeftPlayPauseClicked();
    void onLeftStopClicked();
    void onLeftMuteClicked();
    void onLeftVolumeChanged(int value);
    void onLeftPositionChanged(int position);
    void onLeftDurationChanged(qint64 duration);

    // ÓÒ²à²¥·ÅÆ÷²Ûº¯Êý
    void onRightPlayPauseClicked();
    void onRightStopClicked();
    void onRightMuteClicked();
    void onRightVolumeChanged(int value);
    void onRightPositionChanged(int position);
    void onRightDurationChanged(qint64 duration);

private:
    void setupUI();
    void openFile();

    // ×ó²à²¥·ÅÆ÷¼°¿Ø¼þ
    QMediaPlayer* leftPlayer;
    QVideoWidget* leftVideoWidget;
    QPushButton* leftPlayPauseButton;
    QPushButton* leftStopButton;
    QPushButton* leftMuteButton;
    QSlider* leftVolumeSlider;
    QSlider* leftPositionSlider;
    QPushButton* leftOpenFileButton;

    // ÓÒ²à²¥·ÅÆ÷¼°¿Ø¼þ
    QMediaPlayer* rightPlayer;
    QVideoWidget* rightVideoWidget;
    QPushButton* rightPlayPauseButton;
    QPushButton* rightStopButton;
    QPushButton* rightMuteButton;
    QSlider* rightVolumeSlider;
    QSlider* rightPositionSlider;

    // ¹«¹²¿Ø¼þ
    QPushButton* backButton;
    QLabel* descriptionLabel;
};

#endif // VIDEOMODIFICATIONPAGE_H
