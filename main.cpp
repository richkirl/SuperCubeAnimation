#include "widget.hpp"

#include <QApplication>

int main(int argc, char *argv[])
{
    //QCoreApplication::setAttribute(Qt::AA_UseDesktopOpenGL);
    QApplication a(argc, argv);

    QSurfaceFormat format;
    format.setSamples(16);
    format.setDepthBufferSize(24);
    QSurfaceFormat::setDefaultFormat(format);

    Widget w;
    w.show();
    return a.exec();
}
