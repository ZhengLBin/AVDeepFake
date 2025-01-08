#include "CardWidget.h"
#include <QEvent>
#include <QPropertyAnimation>

CardWidget::CardWidget(const QString& iconPath, const QString& title, const QString& description, QWidget* parent)
    : QWidget(parent)
{
    this->setFixedSize(480, 300);

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(20, 20, 20, 20);
    mainLayout->setSpacing(5);

    // 创建一个容器用于放置三个 QLabel
    QWidget* labelContainer = new QWidget(this);
    labelContainer->setStyleSheet("background-color: white; border-radius: 10px;");

    QVBoxLayout* labelLayout = new QVBoxLayout(labelContainer);
    labelLayout->setContentsMargins(10, 10, 10, 10);
    labelLayout->setSpacing(5);
    labelLayout->setAlignment(Qt::AlignTop);

    QLabel* logoLabel = new QLabel(labelContainer);
    logoLabel->setPixmap(QPixmap(iconPath).scaled(60, 60, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    logoLabel->setStyleSheet("background: transparent; border: none;");
    labelLayout->addWidget(logoLabel, 0, Qt::AlignLeft);

    QLabel* titleLabel = new QLabel(title, labelContainer);
    titleLabel->setStyleSheet("font-size: 30px; font-weight: bold; color: #333; background: transparent; border: none;");
    labelLayout->addWidget(titleLabel, 0, Qt::AlignLeft);

    QLabel* descriptionLabel = new QLabel(description, labelContainer);
    descriptionLabel->setStyleSheet("font-size: 30px; color: #666; background: transparent; border: none;");
    descriptionLabel->setWordWrap(true);
    descriptionLabel->setFixedWidth(360);
    labelLayout->addWidget(descriptionLabel, 0, Qt::AlignLeft);

    mainLayout->addWidget(labelContainer);
    setLayout(mainLayout);
}

void CardWidget::enterEvent(QEvent* event)
{
    // 鼠标进入时设置边框和悬浮动画
    setStyleSheet("border-radius: 10px; border: 2px solid qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 red, stop:1 blue);");

    QPropertyAnimation* animation = new QPropertyAnimation(this, "geometry");
    animation->setDuration(200);
    animation->setStartValue(geometry());
    animation->setEndValue(QRect(x(), y() - 10, width(), height()));
    animation->setEasingCurve(QEasingCurve::OutQuad);
    animation->start(QAbstractAnimation::DeleteWhenStopped);

    QWidget::enterEvent(event);
}

void CardWidget::leaveEvent(QEvent* event)
{
    // 鼠标离开时恢复样式
    setStyleSheet("border-radius: 10px; border: 2px solid transparent;");

    QPropertyAnimation* animation = new QPropertyAnimation(this, "geometry");
    animation->setDuration(200);
    animation->setStartValue(geometry());
    animation->setEndValue(QRect(x(), y() + 10, width(), height()));
    animation->setEasingCurve(QEasingCurve::OutQuad);
    animation->start(QAbstractAnimation::DeleteWhenStopped);

    QWidget::leaveEvent(event);
}
