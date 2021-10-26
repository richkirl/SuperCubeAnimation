#ifndef WIDGET_H
#define WIDGET_H

#include <QtOpenGLWidgets/QOpenGLWidget>
#include <QMatrix4x4>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QOpenGLBuffer>
#include <QMouseEvent>
#include <QQuaternion>
#include <QWheelEvent>
#include <QBasicTimer>
#include <QtMath>
#include "simpleobject3d.hpp"

class Transformational;
class Group3D;
class Widget : public QOpenGLWidget
{
    Q_OBJECT

public:
    Widget(QOpenGLWidget *parent = nullptr);
    ~Widget();
protected:
    void initializeGL();
    void resizeGL(int w,int h);
    void paintGL();
    void initShaders();
    void initCube(float width);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);
    void timerEvent(QTimerEvent *event);
private:
    QMatrix4x4 m_projectionMatrix;
    QOpenGLShaderProgram m_program;
    QVector2D mousePosition;
    QQuaternion rotation;
    QVector<SimpleObject3D *> objects;
    QVector<Group3D *> groups;
    QVector<Transformational *> m_TransformObjects;
    float m_z;

    QBasicTimer timer;
    float angleObject;
    float angleGroup1;
    float angleGroup2;
    float angleMain;
};
#endif // WIDGET_H
