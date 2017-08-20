#ifndef RENDERGLWIDGET_H
#define RENDERGLWIDGET_H

#include <cstddef>
#include <windows.h>
#include <gl/GL.h>
#include <QDebug>
#include <QMouseEvent>
#include <QOpenGLBuffer>
#include <QOpenGLContext>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QOpenGLFunctions_4_0_Core>
#include <QOpenGLShaderProgram>
#include <QPainter>
#include <QSurfaceFormat>
#include <QVector3D>
#include <utility>

#define POINT_ATTRIB 0
#define COLOR_ATTRIB 1

typedef std::pair<QVector3D, QVector3D> vertex_t;

struct vertices {
    float * data;
    int size;
};
typedef struct vertices vertices_t;

class RenderGLWidget : public QOpenGLWidget, protected QOpenGLFunctions_4_0_Core {
    QOpenGLContext context;
    QSurfaceFormat surfFormat;
    QOpenGLBuffer buffer;
    QOpenGLVertexArrayObject vao;
    QOpenGLShaderProgram * shaders;
    vertices_t vertices;
    bool contextSetup;
	bool verticesSetup;
	vertices_t points;
	vertices_t color;

private:
    void destroyGL();
    void print_vertices() const;

public:
    explicit RenderGLWidget(QWidget * parent = 0);
    ~RenderGLWidget();
    void reinitGL();
    void setVertices(std::vector<float> verts);

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    void mousePressEvent(QMouseEvent * qme);

};

#endif // RENDERGLWIDGET_H
