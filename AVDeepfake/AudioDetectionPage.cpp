#include "AudioDetectionPage.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QStackedWidget>

AudioDetectionPage::AudioDetectionPage(QWidget* parent)
    : QWidget(parent)
{
    QVBoxLayout* layout = new QVBoxLayout(this);
    QLabel* label = new QLabel(u8"������Ƶ���ҳ��", this);
    layout->addWidget(label);

    QPushButton* backButton = new QPushButton(u8"������ҳ", this);
    layout->addWidget(backButton);

    connect(backButton, &QPushButton::clicked, [this]() {
        emit this->parentWidget()->parentWidget()->findChild<QStackedWidget*>()->setCurrentIndex(0);
        });
}
