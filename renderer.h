#ifndef RENDERER_H
#define RENDERER_H

#include <QObject>
#include "RenderGLWidget.h"
#include "Shape.h"
#include "Color.h"

class Renderer : public QObject {
    Q_OBJECT

    RenderGLWidget * renderWidget;  // OpenGL widget to draw on
    Shape & shape;                  // shape to be rendered
    Color & color;                  // color of rendered shape

private:
    std::vector<float> createVertices() const;

protected:

public:
    explicit Renderer(Shape & s, Color & c);                            // constructor
    explicit Renderer(RenderGLWidget * glw, Shape & s, Color & c);      // constructor
    ~Renderer();                                                        // destructor
    bool render();                                                      // performs actual render
    bool setRenderWidget(RenderGLWidget * glw);                         // sets OpenGLWidget to draw on

public slots:

signals:

};

#endif // RENDERER_H
