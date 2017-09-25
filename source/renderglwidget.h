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
#include "Shape.h"

#define POINT_ATTRIB 0
#define COLOR_ATTRIB 1

typedef std::pair<QVector3D, QVector3D> vertex_t;

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
	Shape * currentShape;

private:
    void destroyGL();
	void set_vertices();
	void print_vertices() const;
	void print_color() const;
	void modify_points_for_square();

public:
    explicit RenderGLWidget(QWidget * parent = 0);
    ~RenderGLWidget();
    void reinitGL();
	void set_shape(Shape * s);
	void set_color(float * rgb);

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    void mousePressEvent(QMouseEvent * qme);

};

#endif // RENDERGLWIDGET_H
