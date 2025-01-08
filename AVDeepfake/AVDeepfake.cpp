#include "AVDeepfake.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QIcon>
#include "CardWidget.h"

AVDeepfake::AVDeepfake(QWidget* parent)
    : QMainWindow(parent)
{
    // ���������ڱ���ʹ�С
    this->setWindowTitle("AVDeepfake");
    this->setFixedSize(2000, 1100);

    // ��������������岼��
    QWidget* leftBarContainer = new QWidget(this);
    QVBoxLayout* leftBarLayout = new QVBoxLayout(leftBarContainer);
    leftBarLayout->setContentsMargins(10, 10, 10, 10); // ������߾�
    leftBarLayout->setSpacing(20);                     // ���ÿؼ�֮��ļ��


    // ===== ��������Logo �������� =====
    QWidget* topWidget = new QWidget(leftBarContainer);
    QHBoxLayout* topLayout = new QHBoxLayout(topWidget);
    topLayout->setContentsMargins(0, 0, 0, 0); // �����ޱ߾�

    // ���LogoͼƬ
    QLabel* logoLabel = new QLabel(topWidget);
    logoLabel->setPixmap(QPixmap(":/AVDeepfake/appLogo").scaled(80, 80, Qt::KeepAspectRatio)); // �滻Ϊʵ��ͼƬ·��
    topLayout->addWidget(logoLabel);

    // ���������ͼƬ
    QLabel* artLabel = new QLabel(topWidget);
    artLabel->setPixmap(QPixmap(":/AVDeepfake/appTitle").scaled(160, 80, Qt::KeepAspectRatio)); // �滻Ϊʵ��ͼƬ·��
    topLayout->addWidget(artLabel);

    leftBarLayout->addWidget(topWidget);

    // ===== ������ť���� =====
    QPushButton* button1 = new QPushButton(leftBarContainer);
    button1->setIcon(QIcon(":/AVDeepfake/dashboard")); // �滻Ϊʵ��ͼƬ·��
    button1->setText(u8"��ҳ");
    button1->setIconSize(QSize(24, 24));
    button1->setStyleSheet("text-align: left; padding: 8px;"); // �������ֺ�ͼ����뷽ʽ

    QPushButton* button2 = new QPushButton(leftBarContainer);
    button2->setIcon(QIcon(":/AVDeepfake/history")); // �滻Ϊʵ��ͼƬ·��
    button2->setText(u8"��ʷ");
    button2->setIconSize(QSize(24, 24));
    button2->setStyleSheet("text-align: left; padding: 8px;");

    QPushButton* button3 = new QPushButton(leftBarContainer);
    button3->setIcon(QIcon(":/AVDeepfake/voice")); // �滻Ϊʵ��ͼƬ·��
    button3->setText(u8"������");
    button3->setIconSize(QSize(24, 24));
    button3->setStyleSheet("text-align: left; padding: 8px;");

    leftBarLayout->addWidget(button1);
    leftBarLayout->addWidget(button2);
    leftBarLayout->addWidget(button3);
    leftBarLayout->addStretch(); // ��ӵ��Կռ䣬ʹ��ť��������

    // ���������ӵ�������
    leftBar = new QListWidget(this);
    leftBar->setStyleSheet("margin-top: 20px;");
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
    scrollLayout->setSpacing(20);

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
        CardWidget* card = new CardWidget(iconPaths[i], titles[i], descriptions[i], scrollContent);

        if (i < 3) {
            // ǰ������Ƭ��ӵ���һ��
            firstRowLayout->addWidget(card);
        }
        else {
            // ��������Ƭ��ӵ��ڶ���
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
    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QHBoxLayout* mainLayout = new QHBoxLayout(centralWidget);
    mainLayout->addWidget(leftBar);
    mainLayout->addWidget(scrollArea);
}

AVDeepfake::~AVDeepfake()
{
    // ����ʱ�Զ��ͷ�ָ��
}
