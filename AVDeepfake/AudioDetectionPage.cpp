#include "AudioDetectionPage.h"
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QPixmap>
#include <QPainter>
#include <QPainterPath>
#include <QFileDialog>

AudioDetectionPage::AudioDetectionPage(QWidget* parent)
    : QWidget(parent)
{
    // 初始化样式
    initStyles();

    // 主布局
    mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);

    // 内容区域
    contentWidget = new QWidget(this);
    contentWidget->setStyleSheet("background-color: #303338;");
    mainLayout->addWidget(contentWidget);

    // 内容布局
    contentLayout = new QVBoxLayout(contentWidget);
    contentLayout->setContentsMargins(0, 0, 0, 0);

    // 初始化上下部分
    initUpperSection();
    initLowerSection();

    // 返回按钮
    backButton = new QPushButton(u8"返回首页", this);
    mainLayout->addWidget(backButton);

    connect(backButton, &QPushButton::clicked, [this]() {
        emit this->parentWidget()->parentWidget()->findChild<QStackedWidget*>()->setCurrentIndex(0);
        });
}

void AudioDetectionPage::initStyles()
{
    setStyleSheet(R"(
        background-color: white;
        QLabel { color: white; }
        QPushButton { 
            color: white; 
            background-color: #409EFF; 
            border-radius: 4px;
            padding: 8px 16px;
        }
    )");
}

void AudioDetectionPage::initUpperSection()
{
    QWidget* upperPart = new QWidget();
    QVBoxLayout* upperLayout = new QVBoxLayout(upperPart);
    upperLayout->setAlignment(Qt::AlignCenter);

    // 图标（初始可见）
    iconLabel = new QLabel();
    iconLabel->setPixmap(QPixmap(":/AVDeepfake/micro").scaled(64, 64, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    iconLabel->setVisible(true); // 默认显示
    upperLayout->addWidget(iconLabel, 0, Qt::AlignCenter);

    // 提示文字（初始可见）
    tipLabel = new QLabel(u8"点击下方【录制】或【本地上传】后点击【检测】验证策略效果");
    tipLabel->setStyleSheet("font-size: 24px; margin-top: 10px;color: white;");
    tipLabel->setAlignment(Qt::AlignCenter);
    tipLabel->setVisible(true); // 默认显示
    upperLayout->addWidget(tipLabel);

    // 波形展示区（初始隐藏）
    waveformDisplay = new QLabel(this);
    waveformDisplay->setStyleSheet("border-radius: 8px;");
    waveformDisplay->setAlignment(Qt::AlignCenter);
    waveformDisplay->setFixedHeight(600);
    waveformDisplay->setFixedWidth(1900);
    waveformDisplay->setVisible(false); // 初始隐藏
    upperLayout->addWidget(waveformDisplay);


    // 播放控制按钮（初始隐藏）
    QWidget* playControl = new QWidget();
    QHBoxLayout* playLayout = new QHBoxLayout(playControl);
    playLayout->setContentsMargins(0, 20, 0, 0);

    playButton = new QPushButton(u8"播放");
    playButton->setFixedSize(200, 46);
    playButton->setStyleSheet("background-color: #2468F2; color: white;");
    playButton->setVisible(false);
    connect(playButton, &QPushButton::clicked, this, &AudioDetectionPage::togglePlayback);

    playLayout->addWidget(playButton, 0, Qt::AlignCenter);
    upperLayout->addWidget(playControl);

    contentLayout->addWidget(upperPart);
}

void AudioDetectionPage::initLowerSection()
{
    QWidget* lowerPart = new QWidget();
    lowerPart->setStyleSheet("background-color: black;");
    lowerPart->setFixedHeight(100);
    QHBoxLayout* lowerLayout = new QHBoxLayout(lowerPart);
    lowerLayout->setContentsMargins(0, 0, 0, 0);

    // 格式说明
    formatLabel = new QLabel(
        u8"仅限效果测试，支持MP3、WAV、AAC、AMR、M4A格式，小于10MB、5分钟的音频"
    );
    formatLabel->setStyleSheet("font-size: 20px;color: white;");
    lowerLayout->addWidget(formatLabel, 0, Qt::AlignLeft);

    // 按钮组
    QWidget* buttonGroup = new QWidget();
    QHBoxLayout* buttonLayout = new QHBoxLayout(buttonGroup);
    buttonLayout->setSpacing(10);

    detectButton = new QPushButton(u8"检测");
    recordButton = new QPushButton(u8"录制");
    uploadButton = new QPushButton(u8"本地上传");

    for (auto btn : { detectButton, recordButton, uploadButton }) {
        btn->setFixedSize(200, 36);
        btn->setStyleSheet("color: white;background-color:#2468F2;");
        btn->setCursor(Qt::PointingHandCursor);

    }

    connect(recordButton, &QPushButton::clicked, this, &AudioDetectionPage::handleRecord);
    connect(uploadButton, &QPushButton::clicked, this, &AudioDetectionPage::handleFileUpload);


    buttonLayout->addWidget(detectButton);
    buttonLayout->addWidget(recordButton);
    buttonLayout->addWidget(uploadButton);
    lowerLayout->addWidget(buttonGroup, 0, Qt::AlignRight | Qt::AlignBottom);

    contentLayout->addWidget(lowerPart);
}

void AudioDetectionPage::handleRecord()
{
    recordingDialog = new RecordingDialog(this);

    // 计算居中位置
    QPoint centerPos = mapToGlobal(rect().center())
        - QPoint(250, 250); // 对话框大小500x500
    recordingDialog->move(centerPos);

    connect(recordingDialog, &RecordingDialog::recordingSaved,
        this, &AudioDetectionPage::onRecordingSaved);

    recordingDialog->exec();
}

void AudioDetectionPage::handleFileUpload()
{
    // 打开文件选择对话框，允许选择音频文件
    QString filePath = QFileDialog::getOpenFileName(this, u8"选择音频文件", "", u8"音频文件 (*.mp3 *.wav *.aac *.amr *.m4a)");

    if (filePath.isEmpty()) {
        return; // 如果没有选择文件，返回
    }

    // 保存选择的文件路径
    currentAudioPath = filePath;
    qDebug() << u8"选择的音频文件路径：" << filePath;

    // 切换界面元素
    iconLabel->hide();
    tipLabel->hide();
    waveformDisplay->show();
    playButton->show();
    // 加载并绘制波形
    loadAndDrawWaveform(filePath);
}


void AudioDetectionPage::onRecordingSaved(const QString& filePath)
{
    currentAudioPath = filePath;
    qDebug() << u8"录音文件已保存至：" << filePath;

    // 关闭录音对话框
    if (recordingDialog) {
        recordingDialog->close();
        recordingDialog->deleteLater();
        recordingDialog = nullptr;
    }

    // 切换界面元素
    iconLabel->hide();
    tipLabel->hide();
    waveformDisplay->show();
    playButton->show();

    // 加载并绘制波形
    loadAndDrawWaveform(filePath);
}

void AudioDetectionPage::togglePlayback()
{
    if (!mediaPlayer) {
        mediaPlayer = new QMediaPlayer(this);
        mediaPlayer->setMedia(QUrl::fromLocalFile(currentAudioPath));
    }

    if (isPlaying) {
        mediaPlayer->pause();
        playButton->setText(u8"播放");
    }
    else {
        mediaPlayer->play();
        playButton->setText(u8"暂停");
    }
    isPlaying = !isPlaying;
}

void AudioDetectionPage::loadAndDrawWaveform(const QString& filePath) {
    audioData.clear();
    audioData.reserve(100000);

    decoder.reset(new QAudioDecoder(this)); // 重置智能指针
    decoder->setSourceFilename(filePath);

    connect(decoder.data(), &QAudioDecoder::bufferReady, [this]() {
        QAudioBuffer buffer = decoder->read();
        if (buffer.isValid()) {
            const qint16* data = buffer.constData<qint16>();
            for (int i = 0; i < buffer.sampleCount(); ++i) {
                this->audioData.append(data[i]);
            }
        }
        });

    connect(decoder.data(), &QAudioDecoder::finished, [this]() {
        drawWaveform(this->audioData);
        decoder.reset(); // 释放资源
        });

    decoder->start();
}

void AudioDetectionPage::drawWaveform(const QVector<qint16>& samples)
{
    // 创建绘图设备
    QPixmap pixmap(waveformDisplay->size());
    pixmap.fill(QColor("#303338"));

    QPainter painter(&pixmap);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(QPen(Qt::white, 2));

    if (samples.isEmpty()) return;

    const int width = pixmap.width();
    const int height = pixmap.height();
    const int centerY = height / 2;

    // 简化波形绘制（实际可优化为采样显示）
    QPainterPath path;
    path.moveTo(0, centerY);

    const int step = samples.size() / width;
    for (int x = 0; x < width; x++) {
        int index = x * step;
        if (index >= samples.size()) break;

        qreal y = centerY + (samples[index] / 32768.0) * (height / 2);
        path.lineTo(x, y);
    }

    painter.drawPath(path);
    qDebug() << "Starting waveform drawing...";
    waveformDisplay->setPixmap(pixmap);
    qDebug() << "Waveform drawn.";
}