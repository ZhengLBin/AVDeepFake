#include "CardWidget.h"
#include "AVDeepfake.h"
#include <QEvent>
#include <QMouseEvent>
#include <QPropertyAnimation>

CardWidget::CardWidget(const QString& iconPath, const QString& title, const QString& description, QWidget* parent)
    : QWidget(parent)
{
    this->setFixedSize(450, 330);

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(20, 20, 20, 20);
    mainLayout->setSpacing(15);

    // ����һ���������ڷ������� QLabel
    QWidget* labelContainer = new QWidget(this);
    labelContainer->setStyleSheet("border-radius: 10px; border: 2px solid qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 red, stop:1 blue);");

    QVBoxLayout* labelLayout = new QVBoxLayout(labelContainer);
    labelLayout->setSpacing(20);
    labelLayout->setContentsMargins(10, 10, 10, 10);

    // ʹ�� QHBoxLayout �� logoLabel �� titleLabel ����ͬһ��
    QHBoxLayout* logoTitleLayout = new QHBoxLayout();
    logoTitleLayout->setSpacing(20); // ���� logo �� title ֮��ļ��
    logoTitleLayout->setContentsMargins(0, 0, 0, 0); // ���ñ߾�Ϊ 0

    logoTitleLayout->addStretch();

    QLabel* logoLabel = new QLabel(labelContainer);
    logoLabel->setPixmap(QPixmap(iconPath).scaled(80, 80, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    logoLabel->setStyleSheet("background: transparent; border: none;");
    logoTitleLayout->addWidget(logoLabel, 0, Qt::AlignLeft);

    QLabel* titleLabel = new QLabel(title, labelContainer);
    titleLabel->setStyleSheet("font-size: 50px; font-weight: bold;color: #333; background: transparent; border: none;");
    logoTitleLayout->addWidget(titleLabel, 0, Qt::AlignLeft);

    // ���һ�������ȷ�� logo �� title ���忿��
    logoTitleLayout->addStretch();

    // �� logoTitleLayout ��ӵ� labelLayout ��
    labelLayout->addLayout(logoTitleLayout);

    QLabel* descriptionLabel = new QLabel(description, labelContainer);
    descriptionLabel->setStyleSheet("font-size: 30px; color: #666; background: transparent; border: none;");
    descriptionLabel->setWordWrap(true);
    descriptionLabel->setFixedWidth(360);
    descriptionLabel->setAlignment(Qt::AlignHCenter); // ���� descriptionLabel ˮƽ����
    labelLayout->addWidget(descriptionLabel, 0, Qt::AlignHCenter);

    mainLayout->addWidget(labelContainer);
    setLayout(mainLayout);

    // ����������¼�
    this->setAttribute(Qt::WA_Hover); // ֧����ͣЧ��
    this->setCursor(Qt::PointingHandCursor); // �����ͣʱ�������

    connect(this, &CardWidget::cardClicked, dynamic_cast<AVDeepfake*>(parent), &AVDeepfake::handleCardClick);
}


// ��д����¼������ź�
void CardWidget::mousePressEvent(QMouseEvent* event)
{
    int cardId = 10000;  // �������Ƿ���һ�� ID������Ը���ʵ����������
    emit cardClicked(cardId);  // �������в������ź�
    QWidget::mousePressEvent(event); // ���ø��������¼�����
}