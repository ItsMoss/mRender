#ifndef COLOR_H
#define COLOR_H

#include <cstdlib>
#include <QObject>
#include <QVector3D>

class Color : public QObject {
    Q_OBJECT

    size_t red;         // 0 to 255 red content
    size_t green;       // 0 to 255 green content
    size_t blue;        // 0 to 255 blue content
    float redNorm;      // 0 to 1 red content
    float greenNorm;    // 0 to 1 green content
    float blueNorm;     // 0 to 1 blue content

private:
    void validateColors(bool normalized);   // makes sure all private member color values are in valid ranges

public:
    Color();                                    // default constructor
    Color(size_t r, size_t g, size_t b);        // constructor
    Color(QVector3D c);                         // constructor
    ~Color();                                   // destructor
    void normalize();                           // normalizes red, green, blue private variables and sets *Norm
    QVector3D get_color(bool normalized) const; // gets (normalized) color information

protected:

public slots:

};

#endif // COLOR_H
