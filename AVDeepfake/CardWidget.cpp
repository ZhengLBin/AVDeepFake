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

    // ����һ���������ڷ������� QLabel
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

    // ����������¼�
    this->setAttribute(Qt::WA_Hover); // ֧����ͣЧ��
    this->setCursor(Qt::PointingHandCursor); // �����ͣʱ�������

    connect(this, &CardWidget::cardClicked, dynamic_cast<AVDeepfake*>(parent), &AVDeepfake::handleCardClick);

}

void CardWidget::enterEvent(QEvent* event)
{
    // ������ʱ���ñ߿򽥱�Ч����ȥ��λ�ñ仯��
    setStyleSheet("border-radius: 10px; border: 2px solid qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 red, stop:1 blue);");

    QWidget::enterEvent(event);
}

void CardWidget::leaveEvent(QEvent* event)
{
    // ����뿪ʱ�ָ��߿���ʽ
    setStyleSheet("border-radius: 10px; border: 2px solid transparent;");

    QWidget::leaveEvent(event);
}


// ��д����¼������ź�
void CardWidget::mousePressEvent(QMouseEvent* event)
{   
    int cardId = 10000;  // �������Ƿ���һ�� ID������Ը���ʵ����������
    emit cardClicked(cardId);  // �������в������ź�
    QWidget::mousePressEvent(event); // ���ø��������¼�����
}
