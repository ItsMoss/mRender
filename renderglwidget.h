#ifndef RENDERGLWIDGET_H
#define RENDERGLWIDGET_H

#include <cstddef>
#include <QDebug>
#include <QOpenGLBuffer>
#include <QOpenGLContext>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QVector3D>
#include <utility>

#define POINT_ATTRIB 0
#define COLOR_ATTRIB 1

typedef std::pair<QVector3D, QVector3D> vertex_t;

class RenderGLWidget : public QOpenGLWidget, protected QOpenGLFunctions {
    QOpenGLBuffer buffer;
    QOpenGLVertexArrayObject vao;
    QOpenGLShaderProgram * shaders;
    std::vector<vertex_t> vertices;

private:
    void destroyGL();

public:
    explicit RenderGLWidget(QWidget * parent = 0);
    ~RenderGLWidget();
    void reinitGL();
    void setVertices(std::vector<vertex_t> verts);

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

};

#endif // RENDERGLWIDGET_H
