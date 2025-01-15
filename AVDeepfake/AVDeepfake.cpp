#include "AVDeepfake.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <qDebug>
#include <QIcon>
#include "CardWidget.h"
#include "VideoModificationPage.h"

AVDeepfake::AVDeepfake(QWidget* parent)
    : QMainWindow(parent)
{
    // ���������ڱ���ʹ�С
    this->setWindowTitle("AVDeepfake");
    this->setFixedSize(2050, 1300);
    //this->setStyleSheet("background-color: white;");
    // ===== ������ť��ʽ =====
    QString buttonStyle = R"(
        QPushButton {
            text-align: left;
            padding: 15px;
            font-size: 32px;
            color: #333;
            border: none;
            border-radius: 10px;      /* Բ�� */
            background-color: transparent; /* Ĭ�ϱ���͸�� */
        }
        QPushButton:hover {
            background-color: #F0F0F0; /* ����ʱǳ��ɫ */
        }
        QPushButton:checked {
            background-color: #E0E0E0; /* ѡ��ʱ������ɫ */
            color: #6A0DAD;            /* ѡ��ʱ���ֱ���ɫ */
        }
    )";

    // ��������������岼��
    QWidget* leftBarContainer = new QWidget(this);
    QVBoxLayout* leftBarLayout = new QVBoxLayout(leftBarContainer);
    leftBarLayout->setContentsMargins(10, 10, 10, 10); // ������߾�
    leftBarLayout->setSpacing(20);                     // ���ÿؼ�֮��ļ��


    // ===== ��������Logo �������� =====
    QWidget* topWidget = new QWidget(leftBarContainer);
    QHBoxLayout* topLayout = new QHBoxLayout(topWidget);
    topLayout->setContentsMargins(0, 0, 0, 0); // �����ޱ߾�
    topLayout->setSpacing(5);                 // ���ÿؼ�֮��ļ��Ϊ5
    topLayout->setAlignment(Qt::AlignLeft);   // ���������

    // ���������ͼƬ
    QLabel* artLabel = new QLabel(topWidget);
    artLabel->setPixmap(QPixmap(":/AVDeepfake/appTitle").scaled(294, 56, Qt::KeepAspectRatio)); // �滻Ϊʵ��ͼƬ·��
    topLayout->addWidget(artLabel);
    leftBarLayout->addWidget(topWidget);

    // ===== ������ť���� =====
    QPushButton* button1 = new QPushButton(leftBarContainer);
    button1->setIcon(QIcon(":/AVDeepfake/dashboard")); // �滻Ϊʵ��ͼƬ·��
    button1->setText(u8"��ҳ");
    button1->setIconSize(QSize(36, 36));
    button1->setStyleSheet(buttonStyle);

    QPushButton* button2 = new QPushButton(leftBarContainer);
    button2->setIcon(QIcon(":/AVDeepfake/history")); // �滻Ϊʵ��ͼƬ·��
    button2->setText(u8"��ʷ");
    button2->setIconSize(QSize(36, 36));
    button2->setStyleSheet(buttonStyle);

    QPushButton* button3 = new QPushButton(leftBarContainer);
    button3->setIcon(QIcon(":/AVDeepfake/voice")); // �滻Ϊʵ��ͼƬ·��
    button3->setText(u8"������");
    button3->setIconSize(QSize(36, 36));
    button3->setStyleSheet(buttonStyle);

    leftBarLayout->addWidget(button1);
    leftBarLayout->addWidget(button2);
    leftBarLayout->addWidget(button3);
    leftBarLayout->addStretch(); // ��ӵ��Կռ䣬ʹ��ť��������

    // ���������ӵ�������
    leftBar = new QListWidget(this);
    leftBar->setStyleSheet("margin-top: 21px;");
    leftBar->setMinimumWidth(400);
    leftBar->setMaximumWidth(400);
    leftBar->setLayout(leftBarLayout);

    // ===== ������������ =====
    scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);
    // �Ƴ���������ı߿�
    scrollArea->setStyleSheet("border: none;");

    QWidget* scrollContent = new QWidget(this); // ������������ݴ���
    // ��������ֱ����
    QVBoxLayout* scrollLayout = new QVBoxLayout(scrollContent);
    scrollLayout->setContentsMargins(0, 0, 0, 0);
    scrollLayout->setSpacing(40);

    // ����ͼ��·����������������
    const QStringList iconPaths = {
        ":/AVDeepfake/ViGe",
        ":/AVDeepfake/ViChange",
        ":/AVDeepfake/ViCheck",
        ":/AVDeepfake/AuGE",
        ":/AVDeepfake/AuChange",
        ":/AVDeepfake/AuDetection"
    };

    const QStringList titles = {
        u8"��Ƶ����", u8"��Ƶ�۸�", u8"��Ƶ���",
        u8"��Ƶ����", u8"��Ƶ�۸�", u8"��Ƶ���"
    };

    const QStringList descriptions = {
        u8"���ɸ���������Ƶ���ݡ�",
        u8"����Ƶ���ݽ��д۸Ĵ���",
        u8"�����Ƶ�еĴ۸ĺۼ���",
        u8"���ɸ���������Ƶ���ݡ�",
        u8"����Ƶ���ݽ��д۸Ĵ���",
        u8"�����Ƶ�еĴ۸ĺۼ���"
    };

    // �������п�Ƭ����
    QHBoxLayout* firstRowLayout = new QHBoxLayout(); // ��һ��
    QHBoxLayout* secondRowLayout = new QHBoxLayout(); // �ڶ���

    // ѭ��������Ƭ����ӵ���Ӧ��
    for (int i = 0; i < iconPaths.size(); ++i) {
        CardWidget* card = new CardWidget(iconPaths[i], titles[i], descriptions[i], this);

        int index = i; // ����ǰ����
        connect(card, &CardWidget::cardClicked, this, [this, index]() {
            handleCardClick(index); // ���ݵ�ǰ��Ƭ������
        });

        if (i < 3) {
            firstRowLayout->addWidget(card);
        }
        else {
            secondRowLayout->addWidget(card);
        }
    }

    // �����в�����ӵ�����ֱ����
    scrollLayout->addLayout(firstRowLayout);
    scrollLayout->addLayout(secondRowLayout);

    // ���һ�����Կռ䣬����Ƭ�����Ƶ�����
    scrollLayout->addStretch();

    // ���ù�����������ݲ���
    scrollContent->setLayout(scrollLayout);
    scrollArea->setWidget(scrollContent);


    // ===== �����ڲ��� =====
    //QWidget* centralWidget = new QWidget(this);
    //setCentralWidget(centralWidget);

    stackedWidget = new QStackedWidget(this);
    mainPage = new QWidget(this);

    QHBoxLayout* mainLayout = new QHBoxLayout(mainPage);
    mainLayout->addWidget(leftBar);
    mainLayout->addWidget(scrollArea);

    stackedWidget->addWidget(mainPage);

    // ����������6������ҳ��
    pages[0] = new VideoGenerationPage(this);
    pages[1] = new VideoModificationPage(this);
    pages[2] = new VideoDetectionPage(this);
    pages[3] = new AudioGenerationPage(this);
    pages[4] = new AudioModificationPage(this);
    pages[5] = new AudioDetectionPage(this);

    for     (int i = 0; i < 6; ++i) {
        stackedWidget->addWidget(pages[i]);
    }

    // ����ҳ���л�
    connect(stackedWidget, &QStackedWidget::currentChanged, this, [this](int index) {
        // ����뿪�� VideoModificationPage ҳ�棬��ֹͣ������
        if (stackedWidget->currentWidget() != pages[1]) {
            static_cast<VideoModificationPage*>(pages[1])->stopPlayer();
        }
        if (stackedWidget->currentWidget() == pages[1]) {
            static_cast<VideoModificationPage*>(pages[1])->startPlayer();
        }
    });

    connect(pages[1], SIGNAL(backToHome()), this, SLOT(goToHomePage()));


    setCentralWidget(stackedWidget);
}

AVDeepfake::~AVDeepfake()
{
    // ����ʱ�Զ��ͷ�ָ��
}

// AVDeepfake.cpp
void AVDeepfake::handleCardClick(int index)
{
    if (index >= 0 && index < 6) {
        stackedWidget->setCurrentWidget(pages[index]);
    }
}

void AVDeepfake::goToHomePage() {
    stackedWidget->setCurrentIndex(0);  // ������ҳ
}


