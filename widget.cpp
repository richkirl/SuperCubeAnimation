#include "widget.hpp"
#include <group3d.hpp>
Widget::Widget(QOpenGLWidget *parent)
    : QOpenGLWidget(parent)
{
  m_z = -5.0f;
}

Widget::~Widget()
{

}

void Widget::initializeGL()
{
    glClearColor(0.0f,0.0f,0.0f,1.0f);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    initShaders();
    float step = 6.0f;
    groups.append(new Group3D);
    for(float x = -step; x<= step; x+=step)
      {
        for(float y = -step; y<= step; y+=step)
          {
            for(float z = -step; z<= step; z+=step)
              {

                    initCube(1.5f);
                    objects[objects.size()-1]->translate(QVector3D(x+(-1.2),y+0.0,z+0.0));

                    groups[groups.size()-1]->addObject(objects[objects.size()-1]);
                    initCube(1.5f);
                    objects[objects.size()-1]->translate(QVector3D(x+1.2,y+0.0,z+0.0));

                    groups[groups.size()-1]->addObject(objects[objects.size()-1]);
                    initCube(1.5f);
                    objects[objects.size()-1]->translate(QVector3D(x+(-1.2),y+(-2.4),z+0.0));

                    groups[groups.size()-1]->addObject(objects[objects.size()-1]);
                    initCube(1.5f);
                    objects[objects.size()-1]->translate(QVector3D(x+1.2,y+(-2.4),z+0.0));

                    groups[groups.size()-1]->addObject(objects[objects.size()-1]);
                    initCube(1.5f);
                    objects[objects.size()-1]->translate(QVector3D(x+(-1.2),y+0.0,z+(-2.4)));

                    groups[groups.size()-1]->addObject(objects[objects.size()-1]);
                    initCube(1.5f);
                    objects[objects.size()-1]->translate(QVector3D(x+1.2,y+0.0,z+(-2.4)));

                    groups[groups.size()-1]->addObject(objects[objects.size()-1]);
                    initCube(1.5f);
                    objects[objects.size()-1]->translate(QVector3D(x+(-1.2),y+(-2.4),z+(-2.4)));

                    groups[groups.size()-1]->addObject(objects[objects.size()-1]);
                    initCube(1.5f);
                    objects[objects.size()-1]->translate(QVector3D(x+1.2,y+(-2.4),z+(-2.4)));

                    groups[groups.size()-1]->addObject(objects[objects.size()-1]);

              }
          }
      }
    groups[0]->translate(QVector3D(-4.0f,0.0f,0.0f));
    m_TransformObjects.append(groups[0]);
    qDebug()<<objects.size()<<groups.size()<<m_TransformObjects.size();

    timer.start(30,this);
}

void Widget::resizeGL(int w, int h)
{
    float aspect = w / (float)h;
    m_projectionMatrix.setToIdentity();
    m_projectionMatrix.perspective(45,aspect,0.01f,200.0f);
}

void Widget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    QMatrix4x4 ViewMatrix;
    ViewMatrix.setToIdentity();
    ViewMatrix.translate(0.0,0.0,m_z);
    ViewMatrix.rotate(rotation);
    //ViewMatrix.

    m_program.bind();
    m_program.setUniformValue("u_projectionMaytix", m_projectionMatrix);
    m_program.setUniformValue("u_viewMatrix", ViewMatrix);

    m_program.setUniformValue("u_lightposition",QVector4D(0.0,0.0,0.0,1.0));
    m_program.setUniformValue("u_lightPower",1.0f);


    for(int i = 0;i<m_TransformObjects.size();++i){
        m_TransformObjects[i]->draw(&m_program,context()->functions());
    }

}

void Widget::initShaders()
{
   if(!m_program.addShaderFromSourceFile(QOpenGLShader::Vertex,":/vshader.vert"))
       close();
   if(!m_program.addShaderFromSourceFile(QOpenGLShader::Fragment,":/fshader.frag"))
       close();

   if(!m_program.link()) close();
}

void Widget::initCube(float width)
{
    float width_div_2 = width/2.0f;
    QVector<VertexData> vertexes;

    vertexes.append(VertexData(QVector3D(-width_div_2, width_div_2,width_div_2),QVector2D(0.0,1.0),QVector3D(0.0,0.0,1.0)));
    vertexes.append(VertexData(QVector3D(-width_div_2,-width_div_2,width_div_2),QVector2D(0.0,0.0),QVector3D(0.0,0.0,1.0)));
    vertexes.append(VertexData(QVector3D( width_div_2, width_div_2,width_div_2),QVector2D(1.0,1.0),QVector3D(0.0,0.0,1.0)));
    vertexes.append(VertexData(QVector3D( width_div_2,-width_div_2,width_div_2),QVector2D(1.0,0.0),QVector3D(0.0,0.0,1.0)));

    vertexes.append(VertexData(QVector3D(width_div_2, width_div_2, width_div_2),QVector2D(0.0,1.0),QVector3D(1.0,0.0,0.0)));
    vertexes.append(VertexData(QVector3D(width_div_2,-width_div_2, width_div_2),QVector2D(0.0,0.0),QVector3D(1.0,0.0,0.0)));
    vertexes.append(VertexData(QVector3D(width_div_2, width_div_2,-width_div_2),QVector2D(1.0,1.0),QVector3D(1.0,0.0,0.0)));
    vertexes.append(VertexData(QVector3D(width_div_2,-width_div_2,-width_div_2),QVector2D(1.0,0.0),QVector3D(1.0,0.0,0.0)));

    vertexes.append(VertexData(QVector3D( width_div_2,width_div_2, width_div_2),QVector2D(0.0,1.0),QVector3D(0.0,1.0,0.0)));
    vertexes.append(VertexData(QVector3D( width_div_2,width_div_2,-width_div_2),QVector2D(0.0,0.0),QVector3D(0.0,1.0,0.0)));
    vertexes.append(VertexData(QVector3D(-width_div_2,width_div_2, width_div_2),QVector2D(1.0,1.0),QVector3D(0.0,1.0,0.0)));
    vertexes.append(VertexData(QVector3D(-width_div_2,width_div_2,-width_div_2),QVector2D(1.0,0.0),QVector3D(0.0,1.0,0.0)));

    vertexes.append(VertexData(QVector3D( width_div_2, width_div_2,-width_div_2),QVector2D(0.0,1.0),QVector3D(0.0,0.0,-1.0)));
    vertexes.append(VertexData(QVector3D( width_div_2,-width_div_2,-width_div_2),QVector2D(0.0,0.0),QVector3D(0.0,0.0,-1.0)));
    vertexes.append(VertexData(QVector3D(-width_div_2, width_div_2,-width_div_2),QVector2D(1.0,1.0),QVector3D(0.0,0.0,-1.0)));
    vertexes.append(VertexData(QVector3D(-width_div_2,-width_div_2,-width_div_2),QVector2D(1.0,0.0),QVector3D(0.0,0.0,-1.0)));

    vertexes.append(VertexData(QVector3D(-width_div_2, width_div_2, width_div_2),QVector2D(0.0,1.0),QVector3D(-1.0,0.0,0.0)));
    vertexes.append(VertexData(QVector3D(-width_div_2, width_div_2,-width_div_2),QVector2D(0.0,0.0),QVector3D(-1.0,0.0,0.0)));
    vertexes.append(VertexData(QVector3D(-width_div_2,-width_div_2, width_div_2),QVector2D(1.0,1.0),QVector3D(-1.0,0.0,0.0)));
    vertexes.append(VertexData(QVector3D(-width_div_2,-width_div_2,-width_div_2),QVector2D(1.0,0.0),QVector3D(-1.0,0.0,0.0)));

    vertexes.append(VertexData(QVector3D(-width_div_2,-width_div_2, width_div_2),QVector2D(0.0,1.0),QVector3D(0.0,-1.0,0.0)));
    vertexes.append(VertexData(QVector3D(-width_div_2,-width_div_2,-width_div_2),QVector2D(0.0,0.0),QVector3D(0.0,-1.0,0.0)));
    vertexes.append(VertexData(QVector3D( width_div_2,-width_div_2, width_div_2),QVector2D(1.0,1.0),QVector3D(0.0,-1.0,0.0)));
    vertexes.append(VertexData(QVector3D( width_div_2,-width_div_2,-width_div_2),QVector2D(1.0,0.0),QVector3D(0.0,-1.0,0.0)));

    QVector<GLuint> indexes;

    for(int i=0;i<24;i+=4){
    indexes.append(i+0);
    indexes.append(i+1);
    indexes.append(i+2);

    indexes.append(i+2);
    indexes.append(i+1);
    indexes.append(i+3);
    }

    objects.append(new SimpleObject3D(vertexes,indexes,QImage(":/img1.png")));

}

void Widget::mousePressEvent(QMouseEvent *event)
{
    if(event->buttons()==Qt::LeftButton){
    mousePosition = QVector2D(event->localPos());
    }
    event->accept();
}

void Widget::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons()!=Qt::LeftButton){
        return;
    }
    QVector2D diff = QVector2D(event->localPos())-mousePosition;
    mousePosition = QVector2D(event->localPos());

    float angle = diff.length()/2.0;

    QVector3D axis = QVector3D(diff.y(),diff.x(),0.0);
    rotation = QQuaternion::fromAxisAndAngle(axis,angle) * rotation;
    update();

}

void Widget::wheelEvent(QWheelEvent *event)
{

      if (event->angleDelta().x() < 0 || event->angleDelta().y()<0) {

          m_z += 0.25f;
      } else if (event->angleDelta().x() > 0 || event->angleDelta().y()>0) {

          m_z -=0.25f;
      }

      update();
}

void Widget::timerEvent(QTimerEvent *event)
{
  for(int i = 0; i< objects.size();++i)
    {
      if(i%2 == 0)
        {
          objects[i]->rotate(QQuaternion::fromAxisAndAngle(1.0f,0.0f,0.0f,qSin(angleObject)));
          objects[i]->rotate(QQuaternion::fromAxisAndAngle(0.0f,1.0f,0.0f,qCos(angleObject)));
        }
      else
        {
          objects[i]->rotate(QQuaternion::fromAxisAndAngle(0.0f,1.0f,0.0f,qSin(angleObject)));
          objects[i]->rotate(QQuaternion::fromAxisAndAngle(1.0f,0.0f,0.0f,qCos(angleObject)));
        }
    }
  groups[0]->rotate(QQuaternion::fromAxisAndAngle(0.0f,0.0f,1.0f,qSin(angleGroup1)));
  groups[0]->rotate(QQuaternion::fromAxisAndAngle(0.0f,1.0f,0.0f,-qSin(angleGroup1)));

  angleObject += M_PI / 180.0f;
  angleGroup1 += M_PI / 360.0f;
  update();
}

