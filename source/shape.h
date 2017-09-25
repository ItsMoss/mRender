#ifndef SHAPE_H
#define SHAPE_H

#include <QDebug>
#include <QVector3D>
#include <vector>

enum polygon_t {
	TRIANGLE,
	SQUARE,
	RECTANGLE,
	TRAPEZOID,
	PENTAGON,
	HEXAGON,
	SEPTAGON,
	OCTAGON,
	FREEFORM
};

struct vertices {
	float * data;
	int size;
};
typedef struct vertices vertices_t;

class Shape : public QObject {
	Q_OBJECT

	polygon_t shapeName;
    std::vector<QVector3D> points;

private:

public:
	Shape();
    Shape(polygon_t name);
    Shape(polygon_t name, std::vector<QVector3D> ps);
    Shape(const Shape & rhs);
    Shape & operator=(const Shape & rhs);
    ~Shape();
    bool set_points(std::vector<QVector3D> ps);
    std::vector<QVector3D> get_points() const;
	polygon_t get_name() const;
	std::vector<float> create_vertices() const;

protected:

public slots:

};

#endif // SHAPE_H
