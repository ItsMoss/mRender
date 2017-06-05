#ifndef SHAPE_H
#define SHAPE_H

#include <QDebug>
#include <vector>

struct point {
    float x;
    float y;
    float z;
};
typedef struct point point_t;

class Shape {
private:
    std::vector<point_t> points;

public:
    Shape();
    Shape(std::vector<point_t> ps);
    ~Shape();
    bool set_points(std::vector<point_t> ps);
    std::vector<point_t> get_points() const;
};

#endif // SHAPE_H
