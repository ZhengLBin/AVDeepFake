#include "VideoModificationPage.h"
#include <QTimer>
#include <QDir>
#include <QFile>
#include <QFileDialog>

VideoModificationPage::VideoModificationPage(QWidget* parent)
    : QWidget(parent), leftPlayer(nullptr), leftVideoWidget(nullptr), rightPlayer(nullptr), rightVideoWidget(nullptr)
{
    setupUI();  // 初始化UI
}

void VideoModificationPage::setupUI()
{
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(10, 10, 10, 10);

    // 标题布局
    QHBoxLayout* titleLayout = new QHBoxLayout();
    titleLayout->setContentsMargins(10, 20, 0, 0);

    QLabel* titleLabel = new QLabel(u8"视频篡改  /  篡改算法", this);
    titleLabel->setFixedHeight(70);
    titleLabel->setStyleSheet("font-size: 54px; font-weight: bold;");

    titleLayout->addWidget(titleLabel, 0, Qt::AlignLeft);

    backButton = new QPushButton(u8"首页", this);
    backButton->setFixedSize(100, 70);
    backButton->setStyleSheet("font-size: 24px;margin-right: 10px");

    titleLayout->addStretch();
    titleLayout->addWidget(backButton, 0, Qt::AlignRight);

    descriptionLabel = new QLabel(u8"只需要提供一张人脸照片和源视频，就可以实现面部篡改的功能。", this);
    descriptionLabel->setFixedHeight(50);
    descriptionLabel->setStyleSheet("font-size: 36px;");
    descriptionLabel->setContentsMargins(10, 0, 0, 0);

    // 视频播放窗口
    QHBoxLayout* videoLayout = new QHBoxLayout();

    leftVideoWidget = new QVideoWidget(this);
    leftVideoWidget->setFixedSize(800, 450);
    leftVideoWidget->setStyleSheet("background-color: black;");

    rightVideoWidget = new QVideoWidget(this);
    rightVideoWidget->setFixedSize(800, 450);
    rightVideoWidget->setStyleSheet("background-color: black;");

    videoLayout->addWidget(leftVideoWidget);
    videoLayout->addWidget(rightVideoWidget);

    leftPlayer = new QMediaPlayer(this);
    leftPlayer->setVideoOutput(leftVideoWidget);

    rightPlayer = new QMediaPlayer(this);
    rightPlayer->setVideoOutput(rightVideoWidget);

    QString videoPath = QDir::toNativeSeparators("F:/AVDeepfake/AVDeepfake/Resource/videoDefault/showDefault1.mp4");
    if (!QFile::exists(videoPath)) {
        qDebug() << u8"视频文件不存在";
    }
    leftPlayer->setMedia(QUrl::fromLocalFile(videoPath));

    QTimer::singleShot(100, this, [this]() {
        leftPlayer->play();
        });

    // 左侧播放进度条
    QHBoxLayout* leftProgressLayout = new QHBoxLayout();
    leftPositionSlider = new QSlider(Qt::Horizontal, this);
    leftPositionSlider->setRange(0, 100);
    leftPositionSlider->setFixedWidth(800);
    leftPositionSlider->setStyleSheet("QSlider { border: none; background-color: transparent; }");
    leftProgressLayout->addWidget(leftPositionSlider);

    QWidget* leftProgressWidget = new QWidget(this);
    leftProgressWidget->setLayout(leftProgressLayout);
    leftProgressWidget->setStyleSheet("border:1px solid black;");
    leftProgressWidget->setFixedWidth(800);

    // 左侧控制按钮
    QHBoxLayout* leftControlLayout = new QHBoxLayout();
    leftOpenFileButton = new QPushButton(u8"打开", this);
    leftPlayPauseButton = new QPushButton(u8"播放/暂停", this);
    leftStopButton = new QPushButton(u8"停止", this);
    leftMuteButton = new QPushButton(u8"静音", this);
    leftVolumeSlider = new QSlider(Qt::Horizontal, this);
    leftVolumeSlider->setFixedWidth(150);
    leftVolumeSlider->setRange(0, 100);
    leftVolumeSlider->setValue(100);

    leftControlLayout->addWidget(leftOpenFileButton);
    leftControlLayout->addWidget(leftPlayPauseButton);
    leftControlLayout->addWidget(leftStopButton);
    leftControlLayout->addWidget(leftMuteButton);
    leftControlLayout->addWidget(leftVolumeSlider);

    // 创建一个QWidget来存放布局
    QWidget* leftControlWidget = new QWidget(this);
    leftControlWidget->setLayout(leftControlLayout);
    leftControlWidget->setFixedWidth(800);  // 设置宽度为800

    // 左侧整体布局（播放器 + 进度条 + 控制按钮）
    QVBoxLayout* leftSideLayout = new QVBoxLayout();
    leftSideLayout->addWidget(leftProgressWidget);  // 播放进度条
    leftSideLayout->addWidget(leftControlWidget);   // 控制按钮

    // 右侧播放进度条
    QHBoxLayout* rightProgressLayout = new QHBoxLayout();
    rightPositionSlider = new QSlider(Qt::Horizontal, this);
    rightPositionSlider->setRange(0, 100);
    rightPositionSlider->setFixedWidth(800);
    rightPositionSlider->setStyleSheet("QSlider { border: none; background-color: transparent; }");
    rightProgressLayout->addWidget(rightPositionSlider);

    QWidget* rightProgressWidget = new QWidget(this);
    rightProgressWidget->setStyleSheet("border:1px solid black;");
    rightProgressWidget->setLayout(rightProgressLayout);
    rightProgressWidget->setFixedWidth(800);

    // 右侧控制按钮
    QHBoxLayout* rightControlLayout = new QHBoxLayout();
    rightPlayPauseButton = new QPushButton(u8"播放/暂停", this);
    rightStopButton = new QPushButton(u8"停止", this);
    rightMuteButton = new QPushButton(u8"静音", this);
    rightVolumeSlider = new QSlider(Qt::Horizontal, this);
    rightVolumeSlider->setFixedWidth(150);
    rightVolumeSlider->setRange(0, 100);
    rightVolumeSlider->setValue(100);

    rightControlLayout->addWidget(rightPlayPauseButton);
    rightControlLayout->addWidget(rightStopButton);
    rightControlLayout->addWidget(rightMuteButton);
    rightControlLayout->addWidget(rightVolumeSlider);

    // 创建一个QWidget来存放布局
    QWidget* rightControlWidget = new QWidget(this);
    rightControlWidget->setLayout(rightControlLayout);
    rightControlWidget->setFixedWidth(800);  // 设置宽度为800

    // 右侧整体布局（播放器 + 进度条 + 控制按钮）
    QVBoxLayout* rightSideLayout = new QVBoxLayout();
    rightSideLayout->addWidget(rightProgressWidget);  // 播放进度条
    rightSideLayout->addWidget(rightControlWidget);   // 控制按钮

    // 左右整体布局组合
    QHBoxLayout* controlLayout = new QHBoxLayout();
    controlLayout->addLayout(leftSideLayout);
    controlLayout->addLayout(rightSideLayout);

    // 最终总布局
    mainLayout->addLayout(titleLayout);
    mainLayout->addWidget(descriptionLabel);
    mainLayout->addSpacing(20);
    mainLayout->addLayout(videoLayout);   // 视频播放器区域
    mainLayout->addLayout(controlLayout); // 控制和进度条区域
    mainLayout->addStretch();

    setLayout(mainLayout);

    connect(backButton, &QPushButton::clicked, [this]() {
        emit backToHome();
        });

    connect(leftOpenFileButton, &QPushButton::clicked, this, &VideoModificationPage::openFile);
    connect(leftPlayPauseButton, &QPushButton::clicked, this, &VideoModificationPage::onLeftPlayPauseClicked);
    connect(leftStopButton, &QPushButton::clicked, this, &VideoModificationPage::onLeftStopClicked);
    connect(leftMuteButton, &QPushButton::clicked, this, &VideoModificationPage::onLeftMuteClicked);
    connect(leftVolumeSlider, &QSlider::valueChanged, this, &VideoModificationPage::onLeftVolumeChanged);

    connect(rightPlayPauseButton, &QPushButton::clicked, this, &VideoModificationPage::onRightPlayPauseClicked);
    connect(rightStopButton, &QPushButton::clicked, this, &VideoModificationPage::onRightStopClicked);
    connect(rightMuteButton, &QPushButton::clicked, this, &VideoModificationPage::onRightMuteClicked);
    connect(rightVolumeSlider, &QSlider::valueChanged, this, &VideoModificationPage::onRightVolumeChanged);
}
// 左侧播放器：打开文件
void VideoModificationPage::openFile()
{
    QString filePath = QFileDialog::getOpenFileName(this, u8"选择视频文件", QString(), u8"视频文件 (*.mp4 *.avi *.mkv)");

    if (!filePath.isEmpty()) {
        qDebug() << u8"左侧播放器选择的视频文件：" << filePath;
        leftPlayer->setMedia(QUrl::fromLocalFile(filePath));
        leftPlayer->play();
    }
    else {
        qDebug() << u8"左侧播放器未选择任何文件";
    }
}

// 左侧播放/暂停按钮
void VideoModificationPage::onLeftPlayPauseClicked()
{
    if (leftPlayer->state() == QMediaPlayer::PlayingState) {
        leftPlayer->pause();
    }
    else {
        leftPlayer->play();
    }
}

// 右侧播放/暂停按钮
void VideoModificationPage::onRightPlayPauseClicked()
{
    if (rightPlayer->state() == QMediaPlayer::PlayingState) {
        rightPlayer->pause();
    }
    else {
        rightPlayer->play();
    }
}

// 左侧停止按钮
void VideoModificationPage::onLeftStopClicked()
{
    leftPlayer->stop();
}

// 右侧停止按钮
void VideoModificationPage::onRightStopClicked()
{
    rightPlayer->stop();
}

// 左侧静音按钮
void VideoModificationPage::onLeftMuteClicked()
{
    bool isMuted = leftPlayer->isMuted();
    leftPlayer->setMuted(!isMuted);
}

// 右侧静音按钮
void VideoModificationPage::onRightMuteClicked()
{
    bool isMuted = rightPlayer->isMuted();
    rightPlayer->setMuted(!isMuted);
}

// 左侧音量调节
void VideoModificationPage::onLeftVolumeChanged(int value)
{
    leftPlayer->setVolume(value);
}

// 右侧音量调节
void VideoModificationPage::onRightVolumeChanged(int value)
{
    rightPlayer->setVolume(value);
}

// 左侧进度条调整
void VideoModificationPage::onLeftPositionChanged(int position)
{
    leftPlayer->setPosition(position);
}

// 右侧进度条调整
void VideoModificationPage::onRightPositionChanged(int position)
{
    rightPlayer->setPosition(position);
}

// 左侧时长变化
void VideoModificationPage::onLeftDurationChanged(qint64 duration)
{
    leftPositionSlider->setMaximum(duration);
}

// 右侧时长变化
void VideoModificationPage::onRightDurationChanged(qint64 duration)
{
    rightPositionSlider->setMaximum(duration);
}


// 停止播放器
void VideoModificationPage::stopPlayer()
{
    if (leftPlayer && leftPlayer->state() == QMediaPlayer::PlayingState) {
        qDebug() << u8"暂停播放";
        leftPlayer->stop();
    }
}

// 重置播放器
void VideoModificationPage::startPlayer()
{
    if (leftPlayer) {
        if (leftPlayer->state() == QMediaPlayer::PausedState) {
            qDebug() << u8"继续播放";
            leftPlayer->play();
        }
        else if (leftPlayer->state() == QMediaPlayer::StoppedState) {
            qDebug() << u8"从头开始播放";
            leftPlayer->setPosition(0);  // 重置播放位置
            leftPlayer->play();
        }
        else {
            qDebug() << u8"正在播放";
        }
    }
}
