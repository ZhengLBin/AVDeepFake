#include "VideoModificationPage.h"
#include <QTimer>
#include <QDir>
#include <QFile>
#include <QFileDialog>

VideoModificationPage::VideoModificationPage(QWidget* parent)
    : QWidget(parent), leftPlayer(nullptr), leftVideoWidget(nullptr), rightPlayer(nullptr), rightVideoWidget(nullptr)
{
    setupUI();  // ��ʼ��UI
}

void VideoModificationPage::setupUI()
{
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(10, 10, 10, 10);

    // ���Ⲽ��
    QHBoxLayout* titleLayout = new QHBoxLayout();
    titleLayout->setContentsMargins(10, 20, 0, 0);

    QLabel* titleLabel = new QLabel(u8"��Ƶ�۸�  /  �۸��㷨", this);
    titleLabel->setFixedHeight(70);
    titleLabel->setStyleSheet("font-size: 54px; font-weight: bold;");

    titleLayout->addWidget(titleLabel, 0, Qt::AlignLeft);

    backButton = new QPushButton(u8"��ҳ", this);
    backButton->setFixedSize(100, 70);
    backButton->setStyleSheet("font-size: 24px;margin-right: 10px");

    titleLayout->addStretch();
    titleLayout->addWidget(backButton, 0, Qt::AlignRight);

    descriptionLabel = new QLabel(u8"ֻ��Ҫ�ṩһ��������Ƭ��Դ��Ƶ���Ϳ���ʵ���沿�۸ĵĹ��ܡ�", this);
    descriptionLabel->setFixedHeight(50);
    descriptionLabel->setStyleSheet("font-size: 36px;");
    descriptionLabel->setContentsMargins(10, 0, 0, 0);

    // ��Ƶ���Ŵ���
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
        qDebug() << u8"��Ƶ�ļ�������";
    }
    leftPlayer->setMedia(QUrl::fromLocalFile(videoPath));

    QTimer::singleShot(100, this, [this]() {
        leftPlayer->play();
        });

    // ��ಥ�Ž�����
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

    // �����ư�ť
    QHBoxLayout* leftControlLayout = new QHBoxLayout();
    leftOpenFileButton = new QPushButton(u8"��", this);
    leftPlayPauseButton = new QPushButton(u8"����/��ͣ", this);
    leftStopButton = new QPushButton(u8"ֹͣ", this);
    leftMuteButton = new QPushButton(u8"����", this);
    leftVolumeSlider = new QSlider(Qt::Horizontal, this);
    leftVolumeSlider->setFixedWidth(150);
    leftVolumeSlider->setRange(0, 100);
    leftVolumeSlider->setValue(100);

    leftControlLayout->addWidget(leftOpenFileButton);
    leftControlLayout->addWidget(leftPlayPauseButton);
    leftControlLayout->addWidget(leftStopButton);
    leftControlLayout->addWidget(leftMuteButton);
    leftControlLayout->addWidget(leftVolumeSlider);

    // ����һ��QWidget����Ų���
    QWidget* leftControlWidget = new QWidget(this);
    leftControlWidget->setLayout(leftControlLayout);
    leftControlWidget->setFixedWidth(800);  // ���ÿ��Ϊ800

    // ������岼�֣������� + ������ + ���ư�ť��
    QVBoxLayout* leftSideLayout = new QVBoxLayout();
    leftSideLayout->addWidget(leftProgressWidget);  // ���Ž�����
    leftSideLayout->addWidget(leftControlWidget);   // ���ư�ť

    // �Ҳಥ�Ž�����
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

    // �Ҳ���ư�ť
    QHBoxLayout* rightControlLayout = new QHBoxLayout();
    rightPlayPauseButton = new QPushButton(u8"����/��ͣ", this);
    rightStopButton = new QPushButton(u8"ֹͣ", this);
    rightMuteButton = new QPushButton(u8"����", this);
    rightVolumeSlider = new QSlider(Qt::Horizontal, this);
    rightVolumeSlider->setFixedWidth(150);
    rightVolumeSlider->setRange(0, 100);
    rightVolumeSlider->setValue(100);

    rightControlLayout->addWidget(rightPlayPauseButton);
    rightControlLayout->addWidget(rightStopButton);
    rightControlLayout->addWidget(rightMuteButton);
    rightControlLayout->addWidget(rightVolumeSlider);

    // ����һ��QWidget����Ų���
    QWidget* rightControlWidget = new QWidget(this);
    rightControlWidget->setLayout(rightControlLayout);
    rightControlWidget->setFixedWidth(800);  // ���ÿ��Ϊ800

    // �Ҳ����岼�֣������� + ������ + ���ư�ť��
    QVBoxLayout* rightSideLayout = new QVBoxLayout();
    rightSideLayout->addWidget(rightProgressWidget);  // ���Ž�����
    rightSideLayout->addWidget(rightControlWidget);   // ���ư�ť

    // �������岼�����
    QHBoxLayout* controlLayout = new QHBoxLayout();
    controlLayout->addLayout(leftSideLayout);
    controlLayout->addLayout(rightSideLayout);

    // �����ܲ���
    mainLayout->addLayout(titleLayout);
    mainLayout->addWidget(descriptionLabel);
    mainLayout->addSpacing(20);
    mainLayout->addLayout(videoLayout);   // ��Ƶ����������
    mainLayout->addLayout(controlLayout); // ���ƺͽ���������
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
// ��ಥ���������ļ�
void VideoModificationPage::openFile()
{
    QString filePath = QFileDialog::getOpenFileName(this, u8"ѡ����Ƶ�ļ�", QString(), u8"��Ƶ�ļ� (*.mp4 *.avi *.mkv)");

    if (!filePath.isEmpty()) {
        qDebug() << u8"��ಥ����ѡ�����Ƶ�ļ���" << filePath;
        leftPlayer->setMedia(QUrl::fromLocalFile(filePath));
        leftPlayer->play();
    }
    else {
        qDebug() << u8"��ಥ����δѡ���κ��ļ�";
    }
}

// ��ಥ��/��ͣ��ť
void VideoModificationPage::onLeftPlayPauseClicked()
{
    if (leftPlayer->state() == QMediaPlayer::PlayingState) {
        leftPlayer->pause();
    }
    else {
        leftPlayer->play();
    }
}

// �Ҳಥ��/��ͣ��ť
void VideoModificationPage::onRightPlayPauseClicked()
{
    if (rightPlayer->state() == QMediaPlayer::PlayingState) {
        rightPlayer->pause();
    }
    else {
        rightPlayer->play();
    }
}

// ���ֹͣ��ť
void VideoModificationPage::onLeftStopClicked()
{
    leftPlayer->stop();
}

// �Ҳ�ֹͣ��ť
void VideoModificationPage::onRightStopClicked()
{
    rightPlayer->stop();
}

// ��ྲ����ť
void VideoModificationPage::onLeftMuteClicked()
{
    bool isMuted = leftPlayer->isMuted();
    leftPlayer->setMuted(!isMuted);
}

// �Ҳྲ����ť
void VideoModificationPage::onRightMuteClicked()
{
    bool isMuted = rightPlayer->isMuted();
    rightPlayer->setMuted(!isMuted);
}

// �����������
void VideoModificationPage::onLeftVolumeChanged(int value)
{
    leftPlayer->setVolume(value);
}

// �Ҳ���������
void VideoModificationPage::onRightVolumeChanged(int value)
{
    rightPlayer->setVolume(value);
}

// ������������
void VideoModificationPage::onLeftPositionChanged(int position)
{
    leftPlayer->setPosition(position);
}

// �Ҳ����������
void VideoModificationPage::onRightPositionChanged(int position)
{
    rightPlayer->setPosition(position);
}

// ���ʱ���仯
void VideoModificationPage::onLeftDurationChanged(qint64 duration)
{
    leftPositionSlider->setMaximum(duration);
}

// �Ҳ�ʱ���仯
void VideoModificationPage::onRightDurationChanged(qint64 duration)
{
    rightPositionSlider->setMaximum(duration);
}


// ֹͣ������
void VideoModificationPage::stopPlayer()
{
    if (leftPlayer && leftPlayer->state() == QMediaPlayer::PlayingState) {
        qDebug() << u8"��ͣ����";
        leftPlayer->stop();
    }
}

// ���ò�����
void VideoModificationPage::startPlayer()
{
    if (leftPlayer) {
        if (leftPlayer->state() == QMediaPlayer::PausedState) {
            qDebug() << u8"��������";
            leftPlayer->play();
        }
        else if (leftPlayer->state() == QMediaPlayer::StoppedState) {
            qDebug() << u8"��ͷ��ʼ����";
            leftPlayer->setPosition(0);  // ���ò���λ��
            leftPlayer->play();
        }
        else {
            qDebug() << u8"���ڲ���";
        }
    }
}
