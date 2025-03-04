#ifndef AUDIODETECTIONPAGE_H
#define AUDIODETECTIONPAGE_H
#include "RecordingDialog.h"

#include <QWidget>
#include <QComboBox>
#include <QPushButton>
#include <QLabel>
#include <QMediaPlayer>
#include <QVector>
#include <QAudioDecoder>

QT_FORWARD_DECLARE_CLASS(QVBoxLayout)
QT_FORWARD_DECLARE_CLASS(QHBoxLayout)

class AudioDetectionPage : public QWidget
{
    Q_OBJECT

public:
    explicit AudioDetectionPage(QWidget* parent = nullptr);

private:
    RecordingDialog* recordingDialog;
    // 控件声明
    QPushButton* backButton;
    QPushButton* detectButton;
    QPushButton* recordButton;
    QPushButton* uploadButton;
    QVector<qint16> audioData;

    QSharedPointer<QAudioDecoder> decoder;

    // 布局声明
    QVBoxLayout* mainLayout;
    QVBoxLayout* contentLayout;

    // 子部件
    QWidget* contentWidget;
    QLabel* formatLabel;

    QLabel* iconLabel;
    QLabel* tipLabel;
    QLabel* waveformDisplay;
    QPushButton* playButton;
    QMediaPlayer* mediaPlayer;
    QString currentAudioPath;
    bool isPlaying = false;

    void initStyles();
    void initUpperSection();
    void initLowerSection();


private slots:
    void handleRecord();
    void handleFileUpload();
    void togglePlayback();
    void loadAndDrawWaveform(const QString& filePath);
    void onRecordingSaved(const QString& filePath);
    void drawWaveform(const QVector<qint16>& samples);
};

#endif // AUDIODETECTIONPAGE_H