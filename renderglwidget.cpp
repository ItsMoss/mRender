#include "RenderGLWidget.h"

RenderGLWidget::RenderGLWidget(QWidget *parent) : QOpenGLWidget(parent), shaders(NULL), contextSetup(false) {
    // qDebug() << "in RenderGLWidget constructor";
    vertices.data = NULL;
    vertices.size = 0;
}

RenderGLWidget::~RenderGLWidget() {
    // qDebug() << "in RenderGLWidget destructor";
    destroyGL();
    if (shaders) {
        delete shaders;
        shaders = NULL;
    }
}

void RenderGLWidget::destroyGL() {
    // qDebug() << "in RenderGLWidget::destroyGL";
    if (vao.isCreated()) {
        vao.destroy();
    }
    if (buffer.isCreated()) {
        buffer.destroy();
    }
}

void RenderGLWidget::print_vertices() const {
    qDebug() << "{";
    for (size_t i = 0; i < vertices.size; ++i ) {
        qDebug() << vertices.data[i] << ", ";
    }
    qDebug() << "}";
}

void RenderGLWidget::reinitGL() {
    qDebug() << "in RenderGLWidget::reinitGL";
    destroyGL();
    initializeGL();
}

void RenderGLWidget::setVertices(std::vector<float> verts) {
    qDebug() << "in RenderGLWidget::setVertices";
    qDebug() << "data @: " << vertices.data;
    qDebug() << "verts size: " << verts.size();
    if (vertices.data) {
        delete[] vertices.data;
    }
    vertices.data = new float[verts.size()];
    memcpy(vertices.data, verts.data(), sizeof(float) * verts.size());
    vertices.size = verts.size() / 6;
}

void RenderGLWidget::initializeGL() {
    qDebug() << "in RenderGLWidget::initializeGL";

    // init OpenGL backend
    if (!contextSetup) {
        initializeOpenGLFunctions();

        // set clear color
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    }

    // create shaders
    if (!shaders) {
        shaders = new QOpenGLShaderProgram();
        shaders->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/vertex_shader.vsh");
        shaders->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/frag_shader.fsh");
        if (!shaders->link()) {
            qDebug() << "Error while trying to link shader programs.";
        }
        qDebug() << "Shaders successfully created.";
        shaders->bind();
    }
    else {
        qDebug() << "Not trying to create shaders.";
    }

    // create vertex buffer
    buffer.create();
    buffer.bind();
    buffer.setUsagePattern(QOpenGLBuffer::StaticDraw);
    if (!vertices.size) {
        buffer.allocate(vertices.data, vertices.size * sizeof(float));
        qDebug() << "Successfully allocated space for vertex buffer";
    }
    else {
        qDebug() << "Not allocating space for vertex buffer.";
    }

    // create VAO
    vao.create();
    vao.bind();
    shaders->enableAttributeArray(POINT_ATTRIB);
    shaders->enableAttributeArray(COLOR_ATTRIB);
    shaders->setAttributeBuffer(POINT_ATTRIB, GL_FLOAT, 0, 3, 3 * sizeof(float));
    shaders->setAttributeBuffer(COLOR_ATTRIB, GL_FLOAT, 3, 3, 3 * sizeof(float));

    // unbind (release) everything
    vao.release();
    buffer.release ();
    shaders->release();

    contextSetup = true;
}

void RenderGLWidget::resizeGL(int w, int h) {
    qDebug() << "in RenderGLWidget::resizeGL";
    QOpenGLWidget::resizeGL(w, h);
}

void RenderGLWidget::paintGL() {
    qDebug() << "in RenderGLWidget::paintGL";
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    if (!shaders) {
        qDebug() << "Error while trying to render because of no shader programs.";
        return;
    }
    shaders->bind();
    vao.bind();
    // print_vertices();
    QPainter p(this);
    p.beginNativePainting();
    glViewport(0, 0, this->width(),this->height());
    qDebug() << vertices.size;
    glDrawArrays(GL_LINE_LOOP, 0, vertices.size);
    p.endNativePainting();
    vao.release();
    shaders->release();
}
