#ifndef RENDERER_H
#define RENDERER_H

#include <QObject>
#include <QOpenGLBuffer>
#include <QOpenGLContext>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLWidget>
#include <QOpenGLFunctions_4_5_Core>
#include <QOpenGLShaderProgram>
#include <QPainter>
#include <QSurfaceFormat>
#include "Shape.h"
#include "Color.h"

class Renderer : public QObject, protected QOpenGLFunctions_4_5_Core {
    Q_OBJECT

private:
    QOpenGLWidget * space;  // OpenGL widget to draw on
    Shape & shape;          // shape to be rendered
    color_t & color;        // color of rendered shape
    QOpenGLContext context; // OpenGL context
    bool contextSetup;      // has OpenGL context been setup

protected:

public:
    explicit Renderer(Shape & s, color_t & c);                          // constructor
    explicit Renderer(Shape & s, color_t & c, QOpenGLWidget * oglw);    // constructor
    ~Renderer();                                                        // destructor
    bool render();                                                      // performs actual render
    bool setSpace(QOpenGLWidget * oglw);                                // sets OpenGLWidget to draw on

public slots:

signals:

};

#endif // RENDERER_H
