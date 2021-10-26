#ifndef GROUP3D_HPP
#define GROUP3D_HPP
#include "transformational.hpp"
//class QQuaternion;

class Group3D : public Transformational
{
public:
  Group3D();
  void draw(QOpenGLShaderProgram *program,QOpenGLFunctions *functions);
  void rotate(const QQuaternion &r);
  void translate(const QVector3D &t);
  void scale(const float &s);
  void setGlobalTransform(const QMatrix4x4 &g);

  void addObject(Transformational *obj);
private:
  QQuaternion m_rotate;
  QVector3D m_translate;
  float m_scale;
  QMatrix4x4 m_globalTransform;

  QVector<Transformational *> m_objects;
};

#endif // GROUP3D_HPP
