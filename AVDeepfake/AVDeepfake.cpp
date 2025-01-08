#include "AVDeepfake.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QIcon>
#include "CardWidget.h"

AVDeepfake::AVDeepfake(QWidget* parent)
    : QMainWindow(parent)
{
    // 设置主窗口标题和大小
    this->setWindowTitle("AVDeepfake");
    this->setFixedSize(2000, 1100);

    // 创建左侧栏的整体布局
    QWidget* leftBarContainer = new QWidget(this);
    QVBoxLayout* leftBarLayout = new QVBoxLayout(leftBarContainer);
    leftBarLayout->setContentsMargins(10, 10, 10, 10); // 设置外边距
    leftBarLayout->setSpacing(20);                     // 设置控件之间的间距


    // ===== 顶部区域：Logo 和艺术字 =====
    QWidget* topWidget = new QWidget(leftBarContainer);
    QHBoxLayout* topLayout = new QHBoxLayout(topWidget);
    topLayout->setContentsMargins(0, 0, 0, 0); // 设置无边距

    // 添加Logo图片
    QLabel* logoLabel = new QLabel(topWidget);
    logoLabel->setPixmap(QPixmap(":/AVDeepfake/appLogo").scaled(80, 80, Qt::KeepAspectRatio)); // 替换为实际图片路径
    topLayout->addWidget(logoLabel);

    // 添加艺术字图片
    QLabel* artLabel = new QLabel(topWidget);
    artLabel->setPixmap(QPixmap(":/AVDeepfake/appTitle").scaled(160, 80, Qt::KeepAspectRatio)); // 替换为实际图片路径
    topLayout->addWidget(artLabel);

    leftBarLayout->addWidget(topWidget);

    // ===== 导航按钮区域 =====
    QPushButton* button1 = new QPushButton(leftBarContainer);
    button1->setIcon(QIcon(":/AVDeepfake/dashboard")); // 替换为实际图片路径
    button1->setText(u8"首页");
    button1->setIconSize(QSize(24, 24));
    button1->setStyleSheet("text-align: left; padding: 8px;"); // 设置文字和图标对齐方式

    QPushButton* button2 = new QPushButton(leftBarContainer);
    button2->setIcon(QIcon(":/AVDeepfake/history")); // 替换为实际图片路径
    button2->setText(u8"历史");
    button2->setIconSize(QSize(24, 24));
    button2->setStyleSheet("text-align: left; padding: 8px;");

    QPushButton* button3 = new QPushButton(leftBarContainer);
    button3->setIcon(QIcon(":/AVDeepfake/voice")); // 替换为实际图片路径
    button3->setText(u8"声音库");
    button3->setIconSize(QSize(24, 24));
    button3->setStyleSheet("text-align: left; padding: 8px;");

    leftBarLayout->addWidget(button1);
    leftBarLayout->addWidget(button2);
    leftBarLayout->addWidget(button3);
    leftBarLayout->addStretch(); // 添加弹性空间，使按钮贴近顶部

    // 将左侧栏添加到主布局
    leftBar = new QListWidget(this);
    leftBar->setStyleSheet("margin-top: 20px;");
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
    scrollLayout->setSpacing(20);

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
        CardWidget* card = new CardWidget(iconPaths[i], titles[i], descriptions[i], scrollContent);

        if (i < 3) {
            // 前三个卡片添加到第一行
            firstRowLayout->addWidget(card);
        }
        else {
            // 后三个卡片添加到第二行
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
    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QHBoxLayout* mainLayout = new QHBoxLayout(centralWidget);
    mainLayout->addWidget(leftBar);
    mainLayout->addWidget(scrollArea);
}

AVDeepfake::~AVDeepfake()
{
    // 析构时自动释放指针
}
