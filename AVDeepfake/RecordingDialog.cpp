#include "RecordingDialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QIcon>
#include <QStandardPaths>
#include <QDebug>
#include <QMessageBox>
#include <QDir>
#include <QFileInfo>
#include <QUrl>  
#include <QDateTime>

RecordingDialog::RecordingDialog(QWidget* parent)
    : QDialog(parent)
{
    // 窗口设置
    setWindowTitle(u8"录音中");
    setFixedSize(500, 500);
    setWindowFlags(Qt::Popup);

    // 初始化录音器
    audioRecorder = new QAudioRecorder(this);
    initAudioRecorder();

    // 计时器
    timer = new QTimer(this);
    timer->setInterval(10); // 10毫秒更新一次
    connect(timer, &QTimer::timeout, this, &RecordingDialog::updateTimer);

    // 主布局
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    // 时间显示
    timeLabel = new QLabel("00:00.00");
    timeLabel->setStyleSheet("font-size: 32px; color: #409EFF;");
    timeLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(timeLabel);

    // 按钮区域
    QHBoxLayout* buttonLayout = new QHBoxLayout();

    // 开始/暂停按钮
    toggleButton = new QPushButton();
    toggleButton->setIcon(QIcon(":/AVDeepfake/startRecord"));
    toggleButton->setCursor(Qt::PointingHandCursor);
    toggleButton->setIconSize(QSize(64, 64));
    toggleButton->setStyleSheet("QPushButton { border: none; }");
    connect(toggleButton, &QPushButton::clicked, this, &RecordingDialog::toggleRecording);

    // 停止按钮
    stopButton = new QPushButton();
    stopButton->setIcon(QIcon(":/AVDeepfake/endRecord"));
    stopButton->setCursor(Qt::PointingHandCursor);
    stopButton->setIconSize(QSize(64, 64));
    stopButton->setStyleSheet("QPushButton { border: none; }");
    connect(stopButton, &QPushButton::clicked, this, &RecordingDialog::stopRecording);

    buttonLayout->addStretch();
    buttonLayout->addWidget(toggleButton);
    buttonLayout->addWidget(stopButton);
    buttonLayout->addStretch();

    mainLayout->addLayout(buttonLayout);
}

void RecordingDialog::initAudioRecorder()
{
    // 设置音频格式
    QAudioEncoderSettings audioSettings;
    audioSettings.setCodec("audio/pcm");
    audioSettings.setSampleRate(16000);
    audioSettings.setBitRate(128000);
    audioSettings.setQuality(QMultimedia::HighQuality);

    audioRecorder->setEncodingSettings(audioSettings);
    audioRecorder->setContainerFormat("wav");
}

void RecordingDialog::toggleRecording()
{
    if (!isRecording) {
        startRecording();
    }
    else {
        pauseRecording();
    }
}

void RecordingDialog::startRecording()
{
    // 生成文件名
    QString fileName = QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss") + ".wav";
    QString savePath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation)
        + "/recordings/" + fileName;

    // 创建目录
    QDir().mkpath(QFileInfo(savePath).absolutePath());

    audioRecorder->setOutputLocation(QUrl::fromLocalFile(savePath));
    audioRecorder->record();

    // 更新状态
    isRecording = true;
    toggleButton->setIcon(QIcon(":/AVDeepfake/stopRecord"));

    recordTimer.start();  // 使用 QElapsedTimer 启动计时
    timer->start();
}


void RecordingDialog::pauseRecording()
{
    audioRecorder->pause();
    timer->stop();
    toggleButton->setIcon(QIcon(":/AVDeepfake/startRecord"));
    isRecording = false;
}

void RecordingDialog::stopRecording()
{
    if (audioRecorder->state() != QMediaRecorder::StoppedState) {
        audioRecorder->stop();
        savedFilePath = audioRecorder->outputLocation().toLocalFile();
        emit recordingSaved(savedFilePath);
    }
    accept(); // 关闭对话框
}

void RecordingDialog::updateTimer()
{
    qint64 elapsed = recordTimer.elapsed();  // 使用 QElapsedTimer 获取经过的时间
    QTime time(0, 0, 0, 0);
    time = time.addMSecs(elapsed);
    timeLabel->setText(time.toString("mm:ss.zzz").left(7)); // 显示为00:00.00
}
