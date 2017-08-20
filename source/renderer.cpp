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

std::vector<float> Renderer::createVertices() const {
    // qDebug() << "in Renderer::createVertices";
    std::vector<float> verts;    // return variable

    std::vector<QVector3D> pts = shape.get_points();
    QVector3D col = color.get_color(true);

    for (std::vector<QVector3D>::const_iterator it = pts.begin(); it != pts.end(); ++it) {
        verts.push_back(it->x());
        verts.push_back(it->y());
        verts.push_back(it->z());
        verts.push_back(col.x());
        verts.push_back(col.y());
        verts.push_back(col.z());
        // if this is the first point do not re-add point yet
        if (it == pts.begin()) {
            continue;
        }
        // because GL_LINES will be used for drawing arrays each point is repeated
        verts.push_back(it->x());
        verts.push_back(it->y());
        verts.push_back(it->z());
        verts.push_back(col.x());
        verts.push_back(col.y());
        verts.push_back(col.z());
    }
	// add first point here
	verts.push_back(verts[0]);
	verts.push_back(verts[1]);
	verts.push_back(verts[2]);
	verts.push_back(verts[3]);
	verts.push_back(verts[4]);
	verts.push_back(verts[5]);

    return verts;
}

bool Renderer::render() {
    // qDebug() << "in Renderer::render";

    if (!renderWidget) {
        return false;
    }

    // set vertices
    renderWidget->setVertices(createVertices());

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
