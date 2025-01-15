#include "VideoGenerationPage.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QStackedWidget>
#include <QPushButton>

VideoGenerationPage::VideoGenerationPage(QWidget* parent)
    : QWidget(parent)
{
    QVBoxLayout* layout = new QVBoxLayout(this);

    QLabel* label = new QLabel(u8"这是视频生成页面", this);
    layout->addWidget(label);

    QPushButton* backButton = new QPushButton(u8"返回首页", this);
    layout->addWidget(backButton);

    connect(backButton, &QPushButton::clicked, [this]() {
        emit this->parentWidget()->parentWidget()->findChild<QStackedWidget*>()->setCurrentIndex(0);
    });
}
