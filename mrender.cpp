#include "mrender.h"
#include "ui_mrender.h"

mRender::mRender(QWidget *parent) : QMainWindow(parent), ui(new Ui::mRender) {
    qDebug() << "in mRender::mRender";
    ui->setupUi(this);

    // create maps
    createShapeMap();
    createColorMap();

    color = new color_t;
    shape = new Shape();
    renderer = new Renderer(*shape, *color, ui->renderWidget);

    updateShape();
    updateColor();
}

mRender::~mRender() {
    qDebug() << "in mRender::~mRender";
    delete ui;
    if (color) {
        delete color;
        color = NULL;
    }
    if (shape) {
        delete shape;
        shape = NULL;
    }
    if (renderer) {
        delete renderer;
        renderer = NULL;
    }
}


void mRender::createShapeMap() {
    qDebug() << "in mRender::createShapeMap";
    // create a bunch of points that will be used
    // top left
    point_t tl = {-1, 1, 0};
    // top mid-left
    point_t tml = {-0.5, 1, 0};
    // top mid
    point_t tm = {0, 1, 0};
    // top mid-right
    point_t tmr = {0.5, 1, 0};
    // top right
    point_t tr = {1, 1, 0};
    // middle left
    point_t ml = {-1, 0, 0};
    // middle mid-left
    point_t mml = {-0.5, 0, 0};
    // middle mid
    point_t mm = {0, 0, 0};
    // middle mid-right
    point_t mmr = {0.5, 0, 0};
    // middle right
    point_t mr = {1, 0, 0};
    // bottom left
    point_t bl = {-1, -1, 0};
    // bottom mid-left
    point_t bml = {-0.5, -1, 0};
    // bottom mid
    point_t bm = {0, -1, 0};
    // bottom mid-right
    point_t bmr = {0.5, -1, 0};
    // bottom right
    point_t br = {1, -1, 0};

    // create point vectors for shapes
    std::vector<point_t> square, rect, penta, tri, trap;
    square.push_back(tl); square.push_back(bl); square.push_back(br); square.push_back(tr);
    rect.push_back(tml); rect.push_back(bml); rect.push_back(bmr); rect.push_back(tmr);
    penta.push_back(tm); penta.push_back(ml); penta.push_back(bml); penta.push_back(bmr); penta.push_back(mr);
    tri.push_back(tm); tri.push_back(bml); tri.push_back(bmr);
    trap.push_back(tml); trap.push_back(bl); trap.push_back(br); trap.push_back(tmr);

    shapeMap[QString("Square")] = Shape(square);
    shapeMap[QString("Rectangle")] = Shape(rect);
    shapeMap[QString("Pentagon")] = Shape(penta);
    shapeMap[QString("Triangle")] = Shape(tri);
    shapeMap[QString("Trapezoid")] = Shape(trap);
}


void mRender::createColorMap() {
    qDebug() << "in mRender::createColorMap";
    colorMap[QString("Red")] = {255, 0, 0};
    colorMap[QString("Yellow")] = {255, 255, 0};
    colorMap[QString("Green")] = {0, 255, 0};
    colorMap[QString("Blue")] = {0, 0, 255};
    colorMap[QString("White")] = {255, 255, 255};
}


void mRender::closeEvent(QCloseEvent * qce) {
    qDebug() << "in mRender::closeEvent";
    if (color) {
        delete color;
        color = NULL;
    }
    if (shape) {
        delete shape;
        shape = NULL;
    }
    if (renderer) {
        delete renderer;
        renderer = NULL;
    }
}


void mRender::render() {
    qDebug() << "in mRender::render";
    if (renderer) {
        if (!renderer->render()) {
            QMessageBox * msg = new QMessageBox(this);
            msg->setWindowTitle("ERROR");
            msg->setText("Error:");
            msg->setInformativeText("Render failed!");
            msg->addButton(QMessageBox::Ok);
            msg->exec();
        }
    }
    else {
        qDebug() << "Tried to render with no renderer";
    }
}


void mRender::updateShape() {
    qDebug() << "in mRender::updateShape";
    QString shapeString;
    if (ui->squareRadioButton->isChecked()) {
        shapeString = "Square";
    }
    else if (ui->rectangleRadioButton->isChecked()) {
        shapeString = "Rectangle";
    }
    else if (ui->pentagonRadioButton->isChecked()) {
        shapeString = "Pentagon";
    }
    else if (ui->triangleRadioButton->isChecked()) {
        shapeString = "Triangle";
    }
    else if (ui->trapRadioButton->isChecked()) {
        shapeString = "Trapezoid";
    }
    *shape = shapeMap[shapeString];
    qDebug() << "new Shape: " << shapeString;
}


void mRender::updateColor() {
    qDebug() << "in mRender::updateColor";
    QString colorString;
    if (ui->redRadioButton->isChecked()) {
        colorString = "Red";
    }
    else if (ui->yellowRadioButton->isChecked()) {
        colorString = "Yellow";
    }
    else if (ui->greenRadioButton->isChecked()) {
        colorString = "Green";
    }
    else if (ui->blueRadioButton->isChecked()) {
        colorString = "Blue";
    }
    else if (ui->whiteRadioButton->isChecked()) {
        colorString = "White";
    }
    *color = colorMap[colorString];
    qDebug() << "new Color: " << colorString;
}
