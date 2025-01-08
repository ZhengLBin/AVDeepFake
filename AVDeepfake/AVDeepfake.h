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
    AVDeepfake(QWidget* parent = nullptr); // ���캯��
    ~AVDeepfake();                         // ��������

private:
    QListWidget* leftBar;     // �����
    QScrollArea* scrollArea;  // �Ҳ࿨Ƭ��ʾ����
};

#endif // AVDEEPFAKE_H
