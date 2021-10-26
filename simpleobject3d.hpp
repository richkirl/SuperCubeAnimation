#ifndef SIMPLEOBJECT3D_HPP
#define SIMPLEOBJECT3D_HPP
#include <QOpenGLBuffer>
#include <QMatrix4x4>
#include <QOpenGLTexture>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QVector2D>
#include "transformational.hpp"

class QOpenGLTexture;
class QOpenGLFunctions;
class QOpenGLShaderProgram;
struct VertexData
{
    VertexData()
    {

    }
    VertexData(QVector3D p,QVector2D t,QVector3D n):
        pos(p),texCoord(t),normal(n)
    {

    }
    QVector3D pos;
    QVector2D texCoord;
    QVector3D normal;
};
class SimpleObject3D : public Transformational
{
public:
    SimpleObject3D();
    SimpleObject3D(const QVector<VertexData> &vertData, const QVector<GLuint> &indexes, const QImage &texture );
    ~SimpleObject3D();
    void init(const QVector<VertexData> &vertData, const QVector<GLuint> &indexes, const QImage &texture );
    void draw(QOpenGLShaderProgram *program,QOpenGLFunctions *functions);
    void rotate(const QQuaternion &r);
    void translate(const QVector3D &t);
    void scale(const float &s);
    void setGlobalTransform(const QMatrix4x4 &g);

private:
    QOpenGLBuffer vertexBuff,indexBuff;
    //QMatrix4x4 modelMatrix;
    QOpenGLTexture *texture;

    QQuaternion m_rotate;
    QVector3D m_translate;
    float m_scale;
    QMatrix4x4 m_globalTransform;
};

#endif // SIMPLEOBJECT3D_HPP
