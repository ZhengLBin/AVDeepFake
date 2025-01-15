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
    // 设置主窗口标题和大小
    this->setWindowTitle("AVDeepfake");
    this->setFixedSize(2050, 1300);
    //this->setStyleSheet("background-color: white;");
    // ===== 导航按钮样式 =====
    QString buttonStyle = R"(
        QPushButton {
            text-align: left;
            padding: 15px;
            font-size: 32px;
            color: #333;
            border: none;
            border-radius: 10px;      /* 圆角 */
            background-color: transparent; /* 默认背景透明 */
        }
        QPushButton:hover {
            background-color: #F0F0F0; /* 悬浮时浅灰色 */
        }
        QPushButton:checked {
            background-color: #E0E0E0; /* 选中时高亮灰色 */
            color: #6A0DAD;            /* 选中时文字变紫色 */
        }
    )";

    // 创建左侧栏的整体布局
    QWidget* leftBarContainer = new QWidget(this);
    QVBoxLayout* leftBarLayout = new QVBoxLayout(leftBarContainer);
    leftBarLayout->setContentsMargins(10, 10, 10, 10); // 设置外边距
    leftBarLayout->setSpacing(20);                     // 设置控件之间的间距


    // ===== 顶部区域：Logo 和艺术字 =====
    QWidget* topWidget = new QWidget(leftBarContainer);
    QHBoxLayout* topLayout = new QHBoxLayout(topWidget);
    topLayout->setContentsMargins(0, 0, 0, 0); // 设置无边距
    topLayout->setSpacing(5);                 // 设置控件之间的间距为5
    topLayout->setAlignment(Qt::AlignLeft);   // 设置左对齐

    // 添加艺术字图片
    QLabel* artLabel = new QLabel(topWidget);
    artLabel->setPixmap(QPixmap(":/AVDeepfake/appTitle").scaled(294, 56, Qt::KeepAspectRatio)); // 替换为实际图片路径
    topLayout->addWidget(artLabel);
    leftBarLayout->addWidget(topWidget);

    // ===== 导航按钮区域 =====
    QPushButton* button1 = new QPushButton(leftBarContainer);
    button1->setIcon(QIcon(":/AVDeepfake/dashboard")); // 替换为实际图片路径
    button1->setText(u8"首页");
    button1->setIconSize(QSize(36, 36));
    button1->setStyleSheet(buttonStyle);

    QPushButton* button2 = new QPushButton(leftBarContainer);
    button2->setIcon(QIcon(":/AVDeepfake/history")); // 替换为实际图片路径
    button2->setText(u8"历史");
    button2->setIconSize(QSize(36, 36));
    button2->setStyleSheet(buttonStyle);

    QPushButton* button3 = new QPushButton(leftBarContainer);
    button3->setIcon(QIcon(":/AVDeepfake/voice")); // 替换为实际图片路径
    button3->setText(u8"声音库");
    button3->setIconSize(QSize(36, 36));
    button3->setStyleSheet(buttonStyle);

    leftBarLayout->addWidget(button1);
    leftBarLayout->addWidget(button2);
    leftBarLayout->addWidget(button3);
    leftBarLayout->addStretch(); // 添加弹性空间，使按钮贴近顶部

    // 将左侧栏添加到主布局
    leftBar = new QListWidget(this);
    leftBar->setStyleSheet("margin-top: 21px;");
    leftBar->setMinimumWidth(400);
    leftBar->setMaximumWidth(400);
    leftBar->setLayout(leftBarLayout);

    // ===== 创建滚动区域 =====
    scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);
    // 移除滚动区域的边框
    scrollArea->setStyleSheet("border: none;");

    QWidget* scrollContent = new QWidget(this); // 滚动区域的内容窗口
    // 创建主垂直布局
    QVBoxLayout* scrollLayout = new QVBoxLayout(scrollContent);
    scrollLayout->setContentsMargins(0, 0, 0, 0);
    scrollLayout->setSpacing(40);

    // 定义图标路径和文字描述数组
    const QStringList iconPaths = {
        ":/AVDeepfake/ViGe",
        ":/AVDeepfake/ViChange",
        ":/AVDeepfake/ViCheck",
        ":/AVDeepfake/AuGE",
        ":/AVDeepfake/AuChange",
        ":/AVDeepfake/AuDetection"
    };

    const QStringList titles = {
        u8"视频生成", u8"视频篡改", u8"视频检测",
        u8"音频生成", u8"音频篡改", u8"音频检测"
    };

    const QStringList descriptions = {
        u8"生成高质量的视频内容。",
        u8"对视频内容进行篡改处理。",
        u8"检测视频中的篡改痕迹。",
        u8"生成高质量的音频内容。",
        u8"对音频内容进行篡改处理。",
        u8"检测音频中的篡改痕迹。"
    };

    // 创建两行卡片布局
    QHBoxLayout* firstRowLayout = new QHBoxLayout(); // 第一行
    QHBoxLayout* secondRowLayout = new QHBoxLayout(); // 第二行

    // 循环创建卡片并添加到相应行
    for (int i = 0; i < iconPaths.size(); ++i) {
        CardWidget* card = new CardWidget(iconPaths[i], titles[i], descriptions[i], this);

        int index = i; // 捕获当前索引
        connect(card, &CardWidget::cardClicked, this, [this, index]() {
            handleCardClick(index); // 传递当前卡片的索引
        });

        if (i < 3) {
            firstRowLayout->addWidget(card);
        }
        else {
            secondRowLayout->addWidget(card);
        }
    }

    // 将两行布局添加到主垂直布局
    scrollLayout->addLayout(firstRowLayout);
    scrollLayout->addLayout(secondRowLayout);

    // 添加一个弹性空间，将卡片布局推到顶部
    scrollLayout->addStretch();

    // 设置滚动区域的内容布局
    scrollContent->setLayout(scrollLayout);
    scrollArea->setWidget(scrollContent);


    // ===== 主窗口布局 =====
    //QWidget* centralWidget = new QWidget(this);
    //setCentralWidget(centralWidget);

    stackedWidget = new QStackedWidget(this);
    mainPage = new QWidget(this);

    QHBoxLayout* mainLayout = new QHBoxLayout(mainPage);
    mainLayout->addWidget(leftBar);
    mainLayout->addWidget(scrollArea);

    stackedWidget->addWidget(mainPage);

    // 创建并加载6个独立页面
    pages[0] = new VideoGenerationPage(this);
    pages[1] = new VideoModificationPage(this);
    pages[2] = new VideoDetectionPage(this);
    pages[3] = new AudioGenerationPage(this);
    pages[4] = new AudioModificationPage(this);
    pages[5] = new AudioDetectionPage(this);

    for     (int i = 0; i < 6; ++i) {
        stackedWidget->addWidget(pages[i]);
    }

    // 监听页面切换
    connect(stackedWidget, &QStackedWidget::currentChanged, this, [this](int index) {
        // 如果离开了 VideoModificationPage 页面，则停止播放器
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
    // 析构时自动释放指针
}

// AVDeepfake.cpp
void AVDeepfake::handleCardClick(int index)
{
    if (index >= 0 && index < 6) {
        stackedWidget->setCurrentWidget(pages[index]);
    }
}

void AVDeepfake::goToHomePage() {
    stackedWidget->setCurrentIndex(0);  // 返回首页
}


