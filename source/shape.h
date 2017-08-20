#ifndef SHAPE_H
#define SHAPE_H

#include <QDebug>
#include <QVector3D>
#include <vector>


class Shape : public QObject {
    Q_OBJECT

    std::vector<QVector3D> points;

private:

public:
    Shape();
    Shape(std::vector<QVector3D> ps);
    Shape(const Shape & rhs);
    Shape & operator=(const Shape & rhs);
    ~Shape();
    bool set_points(std::vector<QVector3D> ps);
    std::vector<QVector3D> get_points() const;

protected:

public slots:

};

#endif // SHAPE_H
