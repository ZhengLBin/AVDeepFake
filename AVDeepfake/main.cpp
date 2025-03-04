#include "AVDeepfake.h"
#include <QtWidgets/QApplication>
#include <QFont>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsProxyWidget>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

    // 设置全局字体为黑体
    QFont font("SimHei");  // 设置字体为黑体
    font.setStyleHint(QFont::SansSerif);
    a.setFont(font);

    // 创建主界面窗口
    AVDeepfake w;

#if __arm__
    // 使用 QGraphicsView 进行旋转
    QGraphicsScene* scene = new QGraphicsScene;
    QGraphicsProxyWidget* proxy = scene->addWidget(&w);
    //proxy->setRotation(270);  // 逆时针旋转 90°

    QGraphicsView* view = new QGraphicsView(scene);
    view->resize(720, 1280); // 调整视图大小

    // 去除滚动条
    view->setRenderHint(QPainter::Antialiasing);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->show();
#else
    w.show();
#endif


    return a.exec();
}
