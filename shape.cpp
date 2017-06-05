#include "shape.h"

Shape::Shape() {
    qDebug() << "in Shape::Shape";
}

Shape::Shape(std::vector<point_t> ps) : points(ps) {
    qDebug() << "in Shape::Shape";
}

Shape::~Shape() {
    qDebug() << "in Shape::~Shape";
}

bool Shape::set_points(std::vector<point_t> ps) {
    qDebug() << "in Shape::set_points";
    if (!points.empty()) {
        points.clear();
        points = ps;
    }

    return true;
}

std::vector<point_t> Shape::get_points() const {
    qDebug() << "in Shape::get_points";
    return points;
}
