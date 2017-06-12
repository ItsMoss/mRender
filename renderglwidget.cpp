#include "RenderGLWidget.h"

RenderGLWidget::RenderGLWidget(QWidget *parent) : QOpenGLWidget(parent),
                                                  buffer(QOpenGLBuffer(QOpenGLBuffer::VertexBuffer)),
                                                  vao(QOpenGLVertexArrayObject(parent)),
                                                  shaders(NULL) {
    // init OpenGL backend
    initializeOpenGLFunctions();

    // set clear color
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

RenderGLWidget::~RenderGLWidget() {
    destroyGL();
    if (shaders) {
        delete shaders;
        shaders = NULL;
    }
}

void RenderGLWidget::destroyGL() {
    if (vao.isCreated()) {
        vao.destroy();
    }
    if (buffer.isCreated()) {
        buffer.destroy();
    }
}

void RenderGLWidget::reinitGL() {
    destroyGL();
    initializeGL();
}

void RenderGLWidget::setVertices(std::vector<std::pair<QVector3D, QVector3D> > verts) {
    vertices.clear();
    vertices = verts;
}

void RenderGLWidget::initializeGL() {
    // create shaders
    if (!shaders) {
        shaders = new QOpenGLShaderProgram();
        shaders->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shaders/vertex_shader.vsh");
        shaders->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shaders/frag_shader.fsh");
        shaders->link();
        shaders->bind();
    }
    else {
        qDebug() << "Error while trying to create shaders.";
    }

    // create vertex buffer
    buffer.create();
    buffer.bind();
    buffer.setUsagePattern(QOpenGLBuffer::StaticDraw);
    if (!vertices.empty()) {
        buffer.allocate(vertices.data(), vertices.size() * sizeof(std::pair<QVector3D, QVector3D>));
    }
    else {
        qDebug() << "Error while allocating space for vertex buffer.";
    }

    // create VAO
    vao.create();
    vao.bind();
    shaders->enableAttributeArray(POINT_ATTRIB);
    shaders->enableAttributeArray(COLOR_ATTRIB);
    shaders->setAttributeBuffer(POINT_ATTRIB, GL_FLOAT, offsetof(vertex_t, first), vertices.size(),
                                sizeof(vertex_t));
    shaders->setAttributeBuffer(COLOR_ATTRIB, GL_FLOAT, offsetof(vertex_t, second), vertices.size(),
                                sizeof(vertex_t));

    // unbind (release) everything
    vao.release();
    buffer.release ();
    shaders->release();
}

void RenderGLWidget::resizeGL(int w, int h) {
    QOpenGLWidget::resizeGL(w, h);
}

void RenderGLWidget::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT);
    if (!shaders) {
        qDebug() << "Error while trying to render because of no shader programs.";
        return;
    }
    shaders->bind();
    glDrawArrays(GL_LINE_LOOP, 0, vertices.size());
    vao.release();
    shaders->release();
}
