#include "color.h"

Color::Color() {}

Color::Color(size_t r, size_t g, size_t b) : red(r), green(g), blue(b) {
    validateColors(true);
}

Color::Color(QVector3D c) : red((size_t)c.x()), green((size_t)c.y()), blue((size_t)c.z()) {
    validateColors(true);
}

Color::Color(const Color &rhs) {
    red = rhs.red;
    redNorm = rhs.redNorm;
    green = rhs.green;
    greenNorm = rhs.greenNorm;
    blue = rhs.blue;
    blueNorm = rhs.blueNorm;
}

Color & Color::operator=(const Color & rhs) {
    if (this == &rhs) {
        return *this;
    }
    red = rhs.red;
    redNorm = rhs.redNorm;
    green = rhs.green;
    greenNorm = rhs.greenNorm;
    blue = rhs.blue;
    blueNorm = rhs.blueNorm;

    return *this;
}

Color::~Color() {}

void Color::validateColors(bool normalized) {
    if (!normalized) {
        if (red < 0) {
            red = 0;
        }
        if (red > 255) {
            red = 255;
        }
        if (green < 0) {
            green = 0;
        }
        if (green > 255) {
            green = 255;
        }
        if (blue < 0) {
            blue = 0;
        }
        if (blue > 255) {
            blue = 255;
        }
    }
    else {
        if (redNorm < 0.0f) {
            redNorm = 0.0f;
        }
        if (redNorm > 1.0f) {
            redNorm = 1.0f;
        }
        if (greenNorm < 0.0f) {
            greenNorm = 0.0f;
        }
        if (greenNorm > 1.0f) {
            greenNorm = 1.0f;
        }
        if (blueNorm < 0.0f) {
            blueNorm = 0.0f;
        }
        if (blueNorm > 1.0f) {
            blueNorm = 1.0f;
        }
    }
}

void Color::normalize() {
    redNorm = (float)red / 255.0f;
    greenNorm = (float)green / 255.0f;
    blueNorm = (float)blue / 255.0f;
    validateColors(true);
}

QVector3D Color::get_color(bool normalized) {
    if (!normalized) {
        return QVector3D(red, green, blue);
    }
    else {
        normalize();    // in case this was not already called elsewhere (MOSS)
        return QVector3D(redNorm, greenNorm, blueNorm);
    }
}
