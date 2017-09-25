#include "renderer.h"

Renderer::Renderer(Shape & s, Color & c) : renderWidget(NULL), shape(s), color(c) {
    // // qDebug() << "in Renderer::Renderer";
}

Renderer::Renderer(RenderGLWidget * glw, Shape & s, Color & c) : renderWidget(glw), shape(s), color(c)  {
    // // qDebug() << "in Renderer::Renderer";
}

Renderer::~Renderer() {
    // // qDebug() << "in Renderer::~Renderer";
}

bool Renderer::render() {
    // qDebug() << "in Renderer::render";

    if (!renderWidget) {
        return false;
    }

    // set vertices
	renderWidget->set_shape(&shape);
	renderWidget->set_color(color.get_color(true));

    // reinitialize and update
    renderWidget->reinitGL();
    renderWidget->update();

    return true;
}

bool Renderer::setRenderWidget(RenderGLWidget * glw) {
    // qDebug() << "in Renderer::setSpace";
    renderWidget = glw;
    return true;
}
