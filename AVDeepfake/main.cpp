#include "AVDeepfake.h"
#include <QtWidgets/QApplication>
#include <QFont>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsProxyWidget>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

    // ����ȫ������Ϊ����
    QFont font("SimHei");  // ��������Ϊ����
    font.setStyleHint(QFont::SansSerif);
    a.setFont(font);

    // ���������洰��
    AVDeepfake w;

#if __arm__
    // ʹ�� QGraphicsView ������ת
    QGraphicsScene* scene = new QGraphicsScene;
    QGraphicsProxyWidget* proxy = scene->addWidget(&w);
    //proxy->setRotation(270);  // ��ʱ����ת 90��

    QGraphicsView* view = new QGraphicsView(scene);
    view->resize(720, 1280); // ������ͼ��С

    // ȥ��������
    view->setRenderHint(QPainter::Antialiasing);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->show();
#else
    w.show();
#endif


    return a.exec();
}
