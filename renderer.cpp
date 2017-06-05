#include "renderer.h"

Renderer::Renderer(Shape & s, color_t & c) : shape(s), color(c) {
    qDebug() << "in Renderer::Renderer";
    contextSetup = false;
}

Renderer::Renderer(Shape & s, color_t & c, QOpenGLWidget * oglw) : shape(s), color(c), space(oglw) {
    qDebug() << "in Renderer::Renderer";
    /*
    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    format.setMajorVersion(4);
    format.setMinorVersion(5);
    format.setSamples(4);
    format.setProfile(QSurfaceFormat::CoreProfile);

    // Create an OpenGL context
    context.setFormat(format);
    context.create();

    // Make the context current on this window
    // context.makeCurrent(space);

    // Obtain a functions object and resolve all entry points
    // m_funcs is declared as: QOpenGLFunctions_4_5_Core* m_funcs
    if (!context.versionFunctions()) {
        qDebug() << "Could not obtain OpenGL versions object";
        contextSetup = false;
        return;
    }
    initializeOpenGLFunctions();
    contextSetup = true;
    */
}

Renderer::~Renderer() {
    qDebug() << "in Renderer::~Renderer";
}

bool Renderer::render() {
    qDebug() << "in Renderer::render";
    /*
    QPainter painter(space);
    qDebug() << "created painter";
    painter.beginNativePainting();
    qDebug() << "beginning painting";

    // set up vertex array objects
    // vertices
    GLuint vertexArrayID, colorArrayID;
    glGenVertexArrays(1, &vertexArrayID);
    glBindVertexArray(vertexArrayID);
    qDebug() << "VAO setup 1 complete";
    // colors
    glGenVertexArrays(1, &colorArrayID);
    glBindVertexArray(colorArrayID);
    qDebug() << "VAO setup 2 complete";

    // set vertices
    const GLfloat vertices[] = {-1, -1, 0,
                                0, 1, 0,
                                1, -1, 0};
    // set colors
    const GLfloat colors[] = {1, 0, 0,
                              1, 0, 0,
                              1, 0, 0};
    qDebug() << "setup of vertices and colors complete";

    // set up buffers
    // vertex
    GLuint vertexBufferID, colorBufferID;
    glGenBuffers(1, &vertexBufferID);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices),
                 vertices, GL_STATIC_DRAW);
    // color
    glGenBuffers(1, &colorBufferID);
    glBindBuffer(GL_ARRAY_BUFFER, colorBufferID);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors),
                 colors, GL_STATIC_DRAW);
    qDebug() << "buffer setup complete";

    // draw colored vertices
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
    glVertexAttribPointer(0,
                          3,
                          GL_FLOAT,
                          GL_FALSE,
                          0,
                          NULL);
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, colorBufferID);
    glVertexAttribPointer(0,
                          3,
                          GL_FLOAT,
                          GL_FALSE,
                          0,
                          NULL);
    qDebug() << "buffer binding complete";

    glDrawArrays(GL_TRIANGLES, 0, 3);
    qDebug() << "drawing";

    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(0);

    painter.endNativePainting();
    qDebug() << "ending painting";
    */

    // set vertices
    const float vertices[] = {-1, -1, 0,
                              0, 1, 0,
                              1, -1, 0};
    // set colors
    const float colors[] = {1, 0, 0,
                            1, 0, 0,
                            1, 0, 0};

    // QOpenGLShaderProgram shader(space);
    QPainter p(space);
    p.beginNativePainting();

    QOpenGLVertexArrayObject vao(space);
    vao.create();
    vao.bind();
    QOpenGLBuffer pointBuffer(QOpenGLBuffer::VertexBuffer), colorBuffer(QOpenGLBuffer::VertexBuffer);
    pointBuffer.create();
    pointBuffer.setUsagePattern(QOpenGLBuffer::StreamDraw);
    pointBuffer.bind();
    pointBuffer.allocate(vertices, sizeof(float) * 3 * 3);
    colorBuffer.create();
    colorBuffer.setUsagePattern(QOpenGLBuffer::StreamDraw);
    colorBuffer.bind();
    colorBuffer.allocate(colors, sizeof(float) * 3 * 3);

    // glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    vao.bind();
    glDrawArrays(GL_TRIANGLES, 0, 3);
    p.endNativePainting();

    return true;
}

bool Renderer::setSpace(QOpenGLWidget * oglw) {
    qDebug() << "in Renderer::setSpace";
    space = oglw;
    return true;
}
