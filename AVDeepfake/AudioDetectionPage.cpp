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
    // ��ʼ����ʽ
    initStyles();

    // ������
    mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);

    // ��������
    contentWidget = new QWidget(this);
    contentWidget->setStyleSheet("background-color: #303338;");
    mainLayout->addWidget(contentWidget);

    // ���ݲ���
    contentLayout = new QVBoxLayout(contentWidget);
    contentLayout->setContentsMargins(0, 0, 0, 0);

    // ��ʼ�����²���
    initUpperSection();
    initLowerSection();

    // ���ذ�ť
    backButton = new QPushButton(u8"������ҳ", this);
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

    // ͼ�꣨��ʼ�ɼ���
    iconLabel = new QLabel();
    iconLabel->setPixmap(QPixmap(":/AVDeepfake/micro").scaled(64, 64, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    iconLabel->setVisible(true); // Ĭ����ʾ
    upperLayout->addWidget(iconLabel, 0, Qt::AlignCenter);

    // ��ʾ���֣���ʼ�ɼ���
    tipLabel = new QLabel(u8"����·���¼�ơ��򡾱����ϴ�����������⡿��֤����Ч��");
    tipLabel->setStyleSheet("font-size: 24px; margin-top: 10px;color: white;");
    tipLabel->setAlignment(Qt::AlignCenter);
    tipLabel->setVisible(true); // Ĭ����ʾ
    upperLayout->addWidget(tipLabel);

    // ����չʾ������ʼ���أ�
    waveformDisplay = new QLabel(this);
    waveformDisplay->setStyleSheet("border-radius: 8px;");
    waveformDisplay->setAlignment(Qt::AlignCenter);
    waveformDisplay->setFixedHeight(600);
    waveformDisplay->setFixedWidth(1900);
    waveformDisplay->setVisible(false); // ��ʼ����
    upperLayout->addWidget(waveformDisplay);


    // ���ſ��ư�ť����ʼ���أ�
    QWidget* playControl = new QWidget();
    QHBoxLayout* playLayout = new QHBoxLayout(playControl);
    playLayout->setContentsMargins(0, 20, 0, 0);

    playButton = new QPushButton(u8"����");
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

    // ��ʽ˵��
    formatLabel = new QLabel(
        u8"����Ч�����ԣ�֧��MP3��WAV��AAC��AMR��M4A��ʽ��С��10MB��5���ӵ���Ƶ"
    );
    formatLabel->setStyleSheet("font-size: 20px;color: white;");
    lowerLayout->addWidget(formatLabel, 0, Qt::AlignLeft);

    // ��ť��
    QWidget* buttonGroup = new QWidget();
    QHBoxLayout* buttonLayout = new QHBoxLayout(buttonGroup);
    buttonLayout->setSpacing(10);

    detectButton = new QPushButton(u8"���");
    recordButton = new QPushButton(u8"¼��");
    uploadButton = new QPushButton(u8"�����ϴ�");

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

    // �������λ��
    QPoint centerPos = mapToGlobal(rect().center())
        - QPoint(250, 250); // �Ի����С500x500
    recordingDialog->move(centerPos);

    connect(recordingDialog, &RecordingDialog::recordingSaved,
        this, &AudioDetectionPage::onRecordingSaved);

    recordingDialog->exec();
}

void AudioDetectionPage::handleFileUpload()
{
    // ���ļ�ѡ��Ի�������ѡ����Ƶ�ļ�
    QString filePath = QFileDialog::getOpenFileName(this, u8"ѡ����Ƶ�ļ�", "", u8"��Ƶ�ļ� (*.mp3 *.wav *.aac *.amr *.m4a)");

    if (filePath.isEmpty()) {
        return; // ���û��ѡ���ļ�������
    }

    // ����ѡ����ļ�·��
    currentAudioPath = filePath;
    qDebug() << u8"ѡ�����Ƶ�ļ�·����" << filePath;

    // �л�����Ԫ��
    iconLabel->hide();
    tipLabel->hide();
    waveformDisplay->show();
    playButton->show();
    // ���ز����Ʋ���
    loadAndDrawWaveform(filePath);
}


void AudioDetectionPage::onRecordingSaved(const QString& filePath)
{
    currentAudioPath = filePath;
    qDebug() << u8"¼���ļ��ѱ�������" << filePath;

    // �ر�¼���Ի���
    if (recordingDialog) {
        recordingDialog->close();
        recordingDialog->deleteLater();
        recordingDialog = nullptr;
    }

    // �л�����Ԫ��
    iconLabel->hide();
    tipLabel->hide();
    waveformDisplay->show();
    playButton->show();

    // ���ز����Ʋ���
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
        playButton->setText(u8"����");
    }
    else {
        mediaPlayer->play();
        playButton->setText(u8"��ͣ");
    }
    isPlaying = !isPlaying;
}

void AudioDetectionPage::loadAndDrawWaveform(const QString& filePath) {
    audioData.clear();
    audioData.reserve(100000);

    decoder.reset(new QAudioDecoder(this)); // ��������ָ��
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
        decoder.reset(); // �ͷ���Դ
        });

    decoder->start();
}

void AudioDetectionPage::drawWaveform(const QVector<qint16>& samples)
{
    // ������ͼ�豸
    QPixmap pixmap(waveformDisplay->size());
    pixmap.fill(QColor("#303338"));

    QPainter painter(&pixmap);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(QPen(Qt::white, 2));

    if (samples.isEmpty()) return;

    const int width = pixmap.width();
    const int height = pixmap.height();
    const int centerY = height / 2;

    // �򻯲��λ��ƣ�ʵ�ʿ��Ż�Ϊ������ʾ��
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