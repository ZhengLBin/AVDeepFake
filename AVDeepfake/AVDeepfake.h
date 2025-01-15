#ifndef AVDEEPFAKE_H
#define AVDEEPFAKE_H

#include <QMainWindow>
#include <QListWidget>
#include <QScrollArea>
#include <QWidget>
#include <QStackedWidget>

#include "VideoGenerationPage.h"
#include "VideoModificationPage.h"
#include "VideoDetectionPage.h"
#include "AudioGenerationPage.h"
#include "AudioModificationPage.h"
#include "AudioDetectionPage.h"


class AVDeepfake : public QMainWindow
{
    Q_OBJECT

public:
    AVDeepfake(QWidget* parent = nullptr); // 构造函数
    ~AVDeepfake();                         // 析构函数

public slots:
    void handleCardClick(int index);
    void goToHomePage();
    

private:
    QListWidget* leftBar;     // 左侧栏
    QScrollArea* scrollArea;  // 右侧卡片显示区域

private:
    QStackedWidget* stackedWidget;
    QWidget* mainPage;
    QWidget* pages[6];
};

#endif // AVDEEPFAKE_H
