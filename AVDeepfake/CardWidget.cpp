#include "CardWidget.h"
#include <QEvent>
#include <QMouseEvent>
#include "AVDeepfake.h"
#include <QPropertyAnimation>

CardWidget::CardWidget(const QString& iconPath, const QString& title, const QString& description, QWidget* parent)
    : QWidget(parent)
{
    this->setFixedSize(500, 360);

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(20, 20, 20, 20);
    mainLayout->setSpacing(15);

    // 创建一个容器用于放置三个 QLabel
    QWidget* labelContainer = new QWidget(this);
    labelContainer->setStyleSheet("background-color: white; border-radius: 10px;");

    QVBoxLayout* labelLayout = new QVBoxLayout(labelContainer);
    labelLayout->setSpacing(20);
    labelLayout->setContentsMargins(10, 10, 10, 10);
    labelLayout->setAlignment(Qt::AlignTop);

    QLabel* logoLabel = new QLabel(labelContainer);
    logoLabel->setPixmap(QPixmap(iconPath).scaled(80, 80, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    logoLabel->setStyleSheet("background: transparent; border: none;");
    labelLayout->addWidget(logoLabel, 0, Qt::AlignLeft);

    QLabel* titleLabel = new QLabel(title, labelContainer);
    titleLabel->setStyleSheet("font-size: 40px; font-weight: bold; color: #333; background: transparent; border: none;");
    labelLayout->addWidget(titleLabel, 0, Qt::AlignLeft);

    QLabel* descriptionLabel = new QLabel(description, labelContainer);
    descriptionLabel->setStyleSheet("font-size: 30px; color: #666; background: transparent; border: none;");
    descriptionLabel->setWordWrap(true);
    descriptionLabel->setFixedWidth(360);
    labelLayout->addWidget(descriptionLabel, 0, Qt::AlignLeft);

    mainLayout->addWidget(labelContainer);
    setLayout(mainLayout);

    // 设置鼠标点击事件
    this->setAttribute(Qt::WA_Hover); // 支持悬停效果
    this->setCursor(Qt::PointingHandCursor); // 鼠标悬停时变成手型

    connect(this, &CardWidget::cardClicked, dynamic_cast<AVDeepfake*>(parent), &AVDeepfake::handleCardClick);

}

void CardWidget::enterEvent(QEvent* event)
{
    // 鼠标进入时设置边框渐变效果（去掉位置变化）
    setStyleSheet("border-radius: 10px; border: 2px solid qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 red, stop:1 blue);");

    QWidget::enterEvent(event);
}

void CardWidget::leaveEvent(QEvent* event)
{
    // 鼠标离开时恢复边框样式
    setStyleSheet("border-radius: 10px; border: 2px solid transparent;");

    QWidget::leaveEvent(event);
}


// 重写鼠标事件触发信号
void CardWidget::mousePressEvent(QMouseEvent* event)
{   
    int cardId = 10000;  // 假设我们发送一个 ID，你可以根据实际需求设置
    emit cardClicked(cardId);  // 发出带有参数的信号
    QWidget::mousePressEvent(event); // 调用父类的鼠标事件处理
}
