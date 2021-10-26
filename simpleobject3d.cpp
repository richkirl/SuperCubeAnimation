#include "simpleobject3d.hpp"

SimpleObject3D::SimpleObject3D()
    :indexBuff(QOpenGLBuffer::IndexBuffer),texture(0)
{
  m_scale = 1.0f;
}

SimpleObject3D::SimpleObject3D(const QVector<VertexData> &vertData, const QVector<GLuint> &indexes, const QImage &texture)
:indexBuff(QOpenGLBuffer::IndexBuffer),texture(0)
{
  m_scale = 1.0f;
  init(vertData,indexes,texture);
}

SimpleObject3D::~SimpleObject3D()
{
    if(vertexBuff.isCreated())
        vertexBuff.destroy();
    if(indexBuff.isCreated())
        indexBuff.destroy();
    if(texture !=0){
        if(texture->isCreated())
            texture->destroy();
    }
}

void SimpleObject3D::init(const QVector<VertexData> &vertData, const QVector<GLuint> &indexes, const QImage &textures)
{
    if(vertexBuff.isCreated())
        vertexBuff.destroy();
    if(indexBuff.isCreated())
        indexBuff.destroy();
    if(texture !=0){
        if(texture->isCreated()){
            delete texture;
            texture = 0;
          }
      }

    vertexBuff.create();
    vertexBuff.bind();
    vertexBuff.allocate(vertData.constData(),vertData.size()*sizeof(VertexData));
    vertexBuff.release();

    indexBuff.create();
    indexBuff.bind();
    indexBuff.allocate(indexes.constData(),indexes.size()*sizeof(GLuint));
    indexBuff.release();

    this->texture = new QOpenGLTexture(textures.mirrored());
    this->texture->setMinificationFilter(QOpenGLTexture::Nearest);
    this->texture->setMagnificationFilter(QOpenGLTexture::Filter::LinearMipMapLinear);
    this->texture->setWrapMode(QOpenGLTexture::Repeat);

    //modelMatrix.setToIdentity();
}

void SimpleObject3D::draw(QOpenGLShaderProgram *program, QOpenGLFunctions *functions)
{
    if(!vertexBuff.isCreated() || !indexBuff.isCreated()) return;

    QMatrix4x4 modelMatrix;
    modelMatrix.setToIdentity();
    modelMatrix.translate(m_translate);
    modelMatrix.rotate(m_rotate);
    modelMatrix.scale(m_scale);
    modelMatrix = m_globalTransform * modelMatrix;
    texture->bind(0);
    program->setUniformValue("u_texture",0);
    program->setUniformValue("u_modelMatrix",modelMatrix);

    vertexBuff.bind();
    int offset = 0;

    int vertLoc = program->attributeLocation("a_position");
    program->enableAttributeArray(vertLoc);
    program->setAttributeBuffer(vertLoc,GL_FLOAT,offset,3,sizeof(VertexData));

    offset += sizeof(QVector3D);

    int texLoc = program->attributeLocation("a_texcoord");

    program->enableAttributeArray(texLoc);
    program->setAttributeBuffer(texLoc,GL_FLOAT,offset,2,sizeof(VertexData));

    offset += sizeof(QVector2D);

    int normaLoc = program->attributeLocation("a_normal");

    program->enableAttributeArray(normaLoc);
    program->setAttributeBuffer(normaLoc,GL_FLOAT,offset,3,sizeof(VertexData));


    indexBuff.bind();

    functions->glDrawElements(GL_TRIANGLES,indexBuff.size(),GL_UNSIGNED_INT,0);

    vertexBuff.release();
    indexBuff.release();
    texture->release();
}

void SimpleObject3D::rotate(const QQuaternion &r)
{
  m_rotate = r * m_rotate;
}

void SimpleObject3D::translate(const QVector3D &translateVector)
{
  m_translate +=translateVector;
}

void SimpleObject3D::scale(const float &s)
{
  m_scale *= s;
}

void SimpleObject3D::setGlobalTransform(const QMatrix4x4 &g)
{
  m_globalTransform = g;
}
