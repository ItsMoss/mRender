#ifndef COLOR_H
#define COLOR_H

#include <cstdlib>
#include <QObject>
#include <QVector3D>

class Color : public QObject {
	Q_OBJECT

	size_t rgb[3];			// rgb content from 0-255
	float rgbnorm[3];		// normalized rgb content

private:
    void validateColors(bool normalized);   // makes sure all private member color values are in valid ranges

public:
    Color();                                    // default constructor
    Color(size_t r, size_t g, size_t b);        // constructor
    Color(QVector3D c);                         // constructor
    Color(const Color & rhs);                   // copy constructor
    Color & operator=(const Color & rhs);       // assignment operator
    ~Color();                                   // destructor
    void normalize();                           // normalizes red, green, blue private variables and sets *Norm
    QVector3D get_color_vec(bool normalized);   // gets (normalized) color information
	float * get_color(bool normalized);			// gets (normalized) color information

protected:

public slots:

};

#endif // COLOR_H
