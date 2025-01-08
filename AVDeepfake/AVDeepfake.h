#ifndef AVDEEPFAKE_H
#define AVDEEPFAKE_H

#include <QMainWindow>
#include <QListWidget>
#include <QScrollArea>
#include <QWidget>

class AVDeepfake : public QMainWindow
{
    Q_OBJECT

public:
    AVDeepfake(QWidget* parent = nullptr); // 构造函数
    ~AVDeepfake();                         // 析构函数

private:
    QListWidget* leftBar;     // 左侧栏
    QScrollArea* scrollArea;  // 右侧卡片显示区域
};

#endif // AVDEEPFAKE_H
