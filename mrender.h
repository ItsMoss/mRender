#ifndef MRENDER_H
#define MRENDER_H

#include <QMainWindow>
#include <QDebug>
#include <QMessageBox>
#include <QString>
#include <map>
#include "renderer.h"

namespace Ui {
class mRender;
}

class mRender : public QMainWindow {
    Q_OBJECT

    Ui::mRender * ui;
    Renderer * renderer;
    Shape * shape;
    Color * color;
    std::map<QString, Shape> shapeMap;
    std::map<QString, Color> colorMap;

private:
    void createShapeMap();
    void createColorMap();

public:
    explicit mRender(QWidget *parent = 0);
    ~mRender();

protected:
    void closeEvent(QCloseEvent * qce);

public slots:
    void render();
    void updateShape();
    void updateColor();
};

#endif // MRENDER_H
