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
    // ��������
    setWindowTitle(u8"¼����");
    setFixedSize(500, 500);
    setWindowFlags(Qt::Popup);

    // ��ʼ��¼����
    audioRecorder = new QAudioRecorder(this);
    initAudioRecorder();

    // ��ʱ��
    timer = new QTimer(this);
    timer->setInterval(10); // 10�������һ��
    connect(timer, &QTimer::timeout, this, &RecordingDialog::updateTimer);

    // ������
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    // ʱ����ʾ
    timeLabel = new QLabel("00:00.00");
    timeLabel->setStyleSheet("font-size: 32px; color: #409EFF;");
    timeLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(timeLabel);

    // ��ť����
    QHBoxLayout* buttonLayout = new QHBoxLayout();

    // ��ʼ/��ͣ��ť
    toggleButton = new QPushButton();
    toggleButton->setIcon(QIcon(":/AVDeepfake/startRecord"));
    toggleButton->setCursor(Qt::PointingHandCursor);
    toggleButton->setIconSize(QSize(64, 64));
    toggleButton->setStyleSheet("QPushButton { border: none; }");
    connect(toggleButton, &QPushButton::clicked, this, &RecordingDialog::toggleRecording);

    // ֹͣ��ť
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
    // ������Ƶ��ʽ
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
    // �����ļ���
    QString fileName = QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss") + ".wav";
    QString savePath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation)
        + "/recordings/" + fileName;

    // ����Ŀ¼
    QDir().mkpath(QFileInfo(savePath).absolutePath());

    audioRecorder->setOutputLocation(QUrl::fromLocalFile(savePath));
    audioRecorder->record();

    // ����״̬
    isRecording = true;
    toggleButton->setIcon(QIcon(":/AVDeepfake/stopRecord"));

    recordTimer.start();  // ʹ�� QElapsedTimer ������ʱ
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
    accept(); // �رնԻ���
}

void RecordingDialog::updateTimer()
{
    qint64 elapsed = recordTimer.elapsed();  // ʹ�� QElapsedTimer ��ȡ������ʱ��
    QTime time(0, 0, 0, 0);
    time = time.addMSecs(elapsed);
    timeLabel->setText(time.toString("mm:ss.zzz").left(7)); // ��ʾΪ00:00.00
}
