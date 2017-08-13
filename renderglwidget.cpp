#include "RenderGLWidget.h"

RenderGLWidget::RenderGLWidget(QWidget *parent) : QOpenGLWidget(parent), shaders(NULL), contextSetup(false) {
    // // qDebug() << "in RenderGLWidget constructor";
	vertices.data = NULL;
	vertices.size = 0;
	points.data = NULL;
	points.size = 0;
	color.data = NULL;
	color.size = 0;
	verticesSetup = false;
}

RenderGLWidget::~RenderGLWidget() {
    // // qDebug() << "in RenderGLWidget destructor";
    destroyGL();
    if (shaders) {
        delete shaders;
        shaders = NULL;
    }
}

void RenderGLWidget::destroyGL() {
    // // qDebug() << "in RenderGLWidget::destroyGL";
    if (vao.isCreated()) {
        vao.destroy();
    }
    if (buffer.isCreated()) {
        buffer.destroy();
    }
}

void RenderGLWidget::print_vertices() const {
    // qDebug() << "{";
    for (size_t i = 0; i < points.size; ++i ) {
        qDebug() << points.data[i] << ", ";

    }
    // qDebug() << "}";
}

void RenderGLWidget::reinitGL() {
    // qDebug() << "in RenderGLWidget::reinitGL";
    destroyGL();
    initializeGL();
}

void RenderGLWidget::setVertices(std::vector<float> verts) {
    // qDebug() << "in RenderGLWidget::setVertices";
    // qDebug() << "data @: " << vertices.data;
    // qDebug() << "verts size: " << verts.size();
	/*
    if (vertices.data) {
        delete[] vertices.data;
    }
    vertices.data = new float[verts.size()];
    memcpy(vertices.data, verts.data(), sizeof(float) * verts.size());
    vertices.size = verts.size() / 6;
	*/

	// reset points and color
	if (points.data) {
		delete[] points.data;
	}
	if (color.data) {
		delete[] color.data;
	}

	// set points
	points.size = verts.size() / 2;		// because only have the elements are for point values (other half for color)
	points.data = new float[points.size];
	for (size_t i = 0; i < points.size; ++i) {
		points.data[i] = verts[i + 3 * (i / 3)];	// want every other group of 3 elements
	}

	// set color
	color.size = 3;		// always 3 cause R, G, B
	color.data = new float[color.size];
	for (size_t i = 0; i < color.size; ++i) {
		color.data[i] = verts[i + 3];		// just need first three color elements
	}

	verticesSetup = true;

}

void RenderGLWidget::initializeGL() {
    // qDebug() << "in RenderGLWidget::initializeGL";

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
            // qDebug() << "Error while trying to link shader programs.";
        }
        // qDebug() << "Shaders successfully created.";
        shaders->bind();
    }
    else {
        // qDebug() << "Not trying to create shaders.";
    }

    // create vertex buffer
    buffer.create();
    buffer.bind();
    buffer.setUsagePattern(QOpenGLBuffer::StaticDraw);
    if (!vertices.size) {
        buffer.allocate(vertices.data, vertices.size * sizeof(float));
        // qDebug() << "Successfully allocated space for vertex buffer";
    }
    else {
        // qDebug() << "Not allocating space for vertex buffer.";
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
    // qDebug() << "in RenderGLWidget::resizeGL";
    QOpenGLWidget::resizeGL(w, h);
}

void RenderGLWidget::paintGL() {
    qDebug() << "in RenderGLWidget::paintGL";

    /*  --- HAD TROUBLE USING QT VBO & VAO'S SO NOT USING THIS FOR NOW... ---

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (!shaders) {
        // qDebug() << "Error while trying to render because of no shader programs.";
        return;
    }
    shaders->bind();
    vao.bind();
    // print_vertices();
    QPainter p(this);
    p.beginNativePainting();
    glViewport(0, 0, this->width(),this->height());
    // qDebug() << vertices.size;
    glDrawArrays(GL_LINE_LOOP, 0, vertices.size);
    p.endNativePainting();
    vao.release();
    shaders->release();
    */

	if (!verticesSetup) {
		return;
	}

	print_vertices();

    QPainter painter(this);

    // erase everything
    painter.beginNativePainting();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // define triangle
    GLfloat shape[] = {-1, -1, 0,
                       1, -1, 0,
                       0, 1, 0};

    // draw shape
    glViewport(0, 0, width(), height());

    glDisable(GL_DEPTH_TEST);

    GLuint id;
    glGenVertexArrays(1, &id);
    glBindVertexArray(id);

    GLuint vbuff;
    glGenBuffers(1, &vbuff);
    glBindBuffer(GL_ARRAY_BUFFER, vbuff);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * points.size, points.data, GL_STATIC_DRAW);

	glColor3f(color.data[0], color.data[1], color.data[2]);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glDrawArrays(GL_LINES, 0, points.size);

    glDisableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

    painter.endNativePainting();
}


void RenderGLWidget::mousePressEvent(QMouseEvent * qme) {
    qDebug() << qme->pos().x();
    qDebug() << qme->pos().y();
}
