#include "shape.h"

Shape::Shape() {}

Shape::Shape(polygon_t name) : shapeName(name) {
    // // qDebug() << "in Shape::Shape";
}

Shape::Shape(polygon_t name, std::vector<QVector3D> ps) : shapeName(name), points(ps) {
    // // qDebug() << "in Shape::Shape";
}

Shape::Shape(const Shape &rhs) {
    points = rhs.points;
	shapeName = rhs.shapeName;
}

Shape & Shape::operator=(const Shape & rhs) {
	if (this != &rhs) {
		points = rhs.points;
		shapeName = rhs.shapeName;
	}
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

polygon_t Shape::get_name() const {
	return shapeName;
}

std::vector<float> Shape::create_vertices() const {
	// qDebug() << "in Shape::createVertices";
	std::vector<float> verts;    // return variable

	std::vector<QVector3D> pts = get_points();

	for (std::vector<QVector3D>::const_iterator it = pts.begin(); it != pts.end(); ++it) {
		verts.push_back(it->x());
		verts.push_back(it->y());
		verts.push_back(it->z());
		// if this is the first point do not re-add point yet
		if (it == pts.begin()) {
			continue;
		}
		// because GL_LINES will be used for drawing arrays each point is repeated
		verts.push_back(it->x());
		verts.push_back(it->y());
		verts.push_back(it->z());
	}
	// add first point here
	verts.push_back(verts[0]);
	verts.push_back(verts[1]);
	verts.push_back(verts[2]);

	return verts;
}
