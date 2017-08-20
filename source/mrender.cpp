#include "mrender.h"
#include "ui_mrender.h"

mRender::mRender(QWidget *parent) : QMainWindow(parent), ui(new Ui::mRender) {
    // // qDebug() << "in mRender::mRender";
    ui->setupUi(this);

    // replace placeholder OpenGLWidget with RenderGLWidget
    replacePlaceholderWidget();

    // create maps
    createShapeMap();
    createColorMap();

    /*for (std::map<QString, Color>::iterator it = colorMap.begin(); it != colorMap.end(); ++it) {
        // qDebug() << "Color:" << it->first;
        // qDebug() << "RGB:" << it->second.get_color(false);
    }*/

    color = new Color();
    shape = new Shape();
    renderer = new Renderer(renderWidget, *shape, *color);

    updateShape();
    updateColor();
	toggleCustomColors(ui->customColorRadioButton->isChecked());
}

mRender::~mRender() {
    // // qDebug() << "in mRender::~mRender";
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


void mRender::replacePlaceholderWidget() {
    // // qDebug() << "in mRender::replacePlaceholderWidget";
    QRect geo = ui->placeholderWidget->geometry();
    delete ui->placeholderWidget;
    renderWidget = new RenderGLWidget(this);
    ui->verticalLayout->insertWidget(0, renderWidget);
    renderWidget->setGeometry(geo);
}


void mRender::createShapeMap() {
    // // qDebug() << "in mRender::createShapeMap";
    // create a bunch of points that will be used
    // top left
	QVector3D tl = QVector3D(-0.8, 0.8, 0);
	// top mid-left
	QVector3D tml = QVector3D(-0.4, 0.8, 0);
	// top mid
	QVector3D tm = QVector3D(0, 0.8, 0);
	// top mid-right
	QVector3D tmr = QVector3D(0.4, 0.8, 0);
	// top right
	QVector3D tr = QVector3D(0.8, 0.8, 0);
	// upper left
	QVector3D ul = QVector3D(-0.8, 0.4, 0);
	// upper mid-left
	QVector3D uml = QVector3D(-0.4, 0.4, 0);
	// upper mid
	QVector3D um = QVector3D(0, 0.4, 0);
	// upper mid-right
	QVector3D umr = QVector3D(0.4, 0.4, 0);
	// upper right
	QVector3D ur = QVector3D(0.8, 0.4, 0);
    // middle left
    QVector3D ml = QVector3D(-0.8, 0, 0);
    // middle mid-left
    QVector3D mml = QVector3D(-0.4, 0, 0);
    // middle mid
    QVector3D mm = QVector3D(0, 0, 0);
    // middle mid-right
    QVector3D mmr = QVector3D(0.4, 0, 0);
    // middle right
    QVector3D mr = QVector3D(0.8, 0, 0);
	// lower left
	QVector3D ll = QVector3D(-0.8, -0.4, 0);
	// lower mid-left
	QVector3D lml = QVector3D(-0.4, -0.4, 0);
	// lower mid
	QVector3D lm = QVector3D(0, -0.4, 0);
	// lower mid-right
	QVector3D lmr = QVector3D(0.4, -0.4, 0);
	// lower right
	QVector3D lr = QVector3D(0.8, -0.4, 0);
	// bottom left
	QVector3D bl = QVector3D(-0.8, -0.8, 0);
	// bottom mid-left
	QVector3D bml = QVector3D(-0.4, -0.8, 0);
	// bottom mid
	QVector3D bm = QVector3D(0, -0.8, 0);
	// bottom mid-right
	QVector3D bmr = QVector3D(0.4, -0.8, 0);
	// bottom right
	QVector3D br = QVector3D(0.8, -0.8, 0);

    // create point vectors for shapes
    std::vector<QVector3D> square, rect, penta, tri, trap, hexa, septa, octa;
    square.push_back(tl); square.push_back(bl); square.push_back(br); square.push_back(tr);
    rect.push_back(tml); rect.push_back(bml); rect.push_back(bmr); rect.push_back(tmr);
    penta.push_back(tm); penta.push_back(ml); penta.push_back(bml); penta.push_back(bmr); penta.push_back(mr);
    tri.push_back(tm); tri.push_back(bml); tri.push_back(bmr);
    trap.push_back(tml); trap.push_back(bl); trap.push_back(br); trap.push_back(tmr);
	hexa.push_back(tml); hexa.push_back(tmr); hexa.push_back(mr); hexa.push_back(bmr); hexa.push_back(bml); hexa.push_back(ml);
	septa.push_back(tm); septa.push_back(umr); septa.push_back(lr); septa.push_back(bmr); septa.push_back(bml); septa.push_back(ll); septa.push_back(uml);
	octa.push_back(tml); octa.push_back(tmr); octa.push_back(ur); octa.push_back(lr); octa.push_back(bmr); octa.push_back(bml); octa.push_back(ll); octa.push_back(ul);

    shapeMap[QString("Square")] = Shape(square);
    shapeMap[QString("Rectangle")] = Shape(rect);
    shapeMap[QString("Pentagon")] = Shape(penta);
    shapeMap[QString("Triangle")] = Shape(tri);
	shapeMap[QString("Trapezoid")] = Shape(trap);
	shapeMap[QString("Hexagon")] = Shape(hexa);
	shapeMap[QString("Septagon")] = Shape(septa);
	shapeMap[QString("Octagon")] = Shape(octa);
}


void mRender::createColorMap() {
    // // qDebug() << "in mRender::createColorMap";
    colorMap[QString("Red")] = Color(QVector3D(255, 0, 0));
	colorMap[QString("Orange")] = Color(QVector3D(255, 165, 0));
    colorMap[QString("Yellow")] = Color(QVector3D(255, 255, 0));
    colorMap[QString("Green")] = Color(QVector3D(0, 255, 0));
	colorMap[QString("Cyan")] = Color(QVector3D(0, 255, 255));
    colorMap[QString("Blue")] = Color(QVector3D(0, 0, 255));
	colorMap[QString("Magenta")] = Color(QVector3D(255, 0, 255));
	colorMap[QString("White")] = Color(QVector3D(255, 255, 255));
}


void mRender::closeEvent(QCloseEvent * qce) {
    // // qDebug() << "in mRender::closeEvent";
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
    // qDebug() << "in mRender::render";
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
        // qDebug() << "Tried to render with no renderer";
    }
}


void mRender::updateShape() {
    // // qDebug() << "in mRender::updateShape";
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
	else if (ui->hexRadioButton->isChecked()) {
		shapeString = "Hexagon";
	}
	else if (ui->septRadioButton->isChecked()) {
		shapeString = "Septagon";
	}
	else if (ui->octaRadioButton->isChecked()) {
		shapeString = "Octagon";
	}
    *shape = shapeMap[shapeString];
    // qDebug() << "new Shape: " << shapeString;
}


void mRender::updateColor() {
    // qDebug() << "in mRender::updateColor";
	if (ui->customColorRadioButton->isChecked()) {
		char numString[4];
		if (QObject::sender() == ui->redHorizontalSlider) {
			ui->RLabel->setText(itoa(ui->redHorizontalSlider->value(), numString, 10));			
		}
		else if (QObject::sender() == ui->greenHorizontalSlider) {
			ui->GLabel->setText(itoa(ui->greenHorizontalSlider->value(), numString, 10));
		}
		else if (QObject::sender() == ui->blueHorizontalSlider) {
			ui->BLabel->setText(itoa(ui->blueHorizontalSlider->value(), numString, 10));
		}
		*color = Color(ui->redHorizontalSlider->value()-1, ui->greenHorizontalSlider->value()-1,
			ui->blueHorizontalSlider->value()-1);
	}
	else {
		QString colorString;
		if (ui->redRadioButton->isChecked()) {
			colorString = "Red";
		}
		else if (ui->orangeRadioButton->isChecked()) {
			colorString = "Orange";
		}
		else if (ui->yellowRadioButton->isChecked()) {
			colorString = "Yellow";
		}
		else if (ui->greenRadioButton->isChecked()) {
			colorString = "Green";
		}
		else if (ui->cyanRadioButton->isChecked()) {
			colorString = "Cyan";
		}
		else if (ui->blueRadioButton->isChecked()) {
			colorString = "Blue";
		}
		else if (ui->magentaRadioButton->isChecked()) {
			colorString = "Magenta";
		}
		else if (ui->whiteRadioButton->isChecked()) {
			colorString = "White";
		}
		*color = colorMap[colorString];
	}
    // qDebug() << "new Color: " << colorString << "(" << colorMap[colorString].get_color(false) << ")";
}


void mRender::toggleCustomColors(bool on) {
	// qDebug() << "in toggleCustomColors";
	ui->redHorizontalSlider->setEnabled(on);
	ui->greenHorizontalSlider->setEnabled(on);
	ui->blueHorizontalSlider->setEnabled(on);
}
