#pragma once
#ifndef CARDWIDGET_H
#define CARDWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPixmap>

class CardWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CardWidget(const QString& iconPath, const QString& title, const QString& description, QWidget* parent = nullptr);

protected:
    void enterEvent(QEvent* event) override;
    void leaveEvent(QEvent* event) override;

private:
    QLabel* logoLabel;
    QLabel* titleLabel;
    QLabel* descriptionLabel;
};

#endif // CARDWIDGET_H
