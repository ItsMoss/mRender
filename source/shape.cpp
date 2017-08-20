#include "shape.h"

Shape::Shape() {
    // // qDebug() << "in Shape::Shape";
}

Shape::Shape(std::vector<QVector3D> ps) : points(ps) {
    // // qDebug() << "in Shape::Shape";
}

Shape::Shape(const Shape &rhs) {
    points = rhs.points;
}

Shape & Shape::operator=(const Shape & rhs) {
    if (this == &rhs) {
        return *this;
    }
    points = rhs.points;
    return *this;
}

Shape::~Shape() {
    // // qDebug() << "in Shape::~Shape";
}

bool Shape::set_points(std::vector<QVector3D> ps) {
    // // qDebug() << "in Shape::set_points";
    if (!points.empty()) {
        points.clear();
        points = ps;
    }

    return true;
}

std::vector<QVector3D> Shape::get_points() const {
    // // qDebug() << "in Shape::get_points";
    return points;
}
