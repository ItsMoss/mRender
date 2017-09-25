#include "color.h"

Color::Color() {}

Color::Color(size_t r, size_t g, size_t b) {
	rgb[0] = r;
	rgb[1] = g;
	rgb[2] = b;
    validateColors(true);
}

Color::Color(QVector3D c) {
	rgb[0] = (size_t)c.x();
	rgb[1] = (size_t)c.y();
	rgb[2] = (size_t)c.z();
    validateColors(true);
}

Color::Color(const Color &rhs) {
	for (size_t i = 0; i < 3; ++i) {
		rgb[i] = rhs.rgb[i];
		rgbnorm[i] = rhs.rgbnorm[i];
	}
}

Color & Color::operator=(const Color & rhs) {
	if (this != &rhs) {
		for (size_t i = 0; i < 3; ++i) {
			rgb[i] = rhs.rgb[i];
			rgbnorm[i] = rhs.rgbnorm[i];
		}
	}

    return *this;
}

Color::~Color() {}

void Color::validateColors(bool normalized) {
    if (normalized) {
		for (size_t i = 0; i < 3; ++i) {
			if (rgbnorm[i] < 0.0f) {
				rgbnorm[i] = 0.0f;
			}
			else if (rgbnorm[i] > 1.0f) {
				rgbnorm[i] = 1.0f;
			}
		}
    }
	for (size_t i = 0; i < 3; ++i) {
		if (rgb[i] < 0) {
			rgb[i] = 0;
		}
		else if (rgb[i] > 255) {
			rgb[i] = 255;
		}
	}

}

void Color::normalize() {
    rgbnorm[0] = (float)rgb[0] / 255.0f;
    rgbnorm[1] = (float)rgb[1] / 255.0f;
    rgbnorm[2] = (float)rgb[2] / 255.0f;
    validateColors(true);
}

float * Color::get_color(bool normalized) {
	if (!normalized) {
		return (float *)rgb;
	}
	else {
		normalize();    // in case this was not already called elsewhere (MOSS)
		return rgbnorm;
	}
}

QVector3D Color::get_color_vec(bool normalized) {
    if (!normalized) {
        return QVector3D(rgb[0], rgb[1], rgb[2]);
    }
    else {
        normalize();    // in case this was not already called elsewhere (MOSS)
        return QVector3D(rgbnorm[0], rgbnorm[1], rgbnorm[2]);
    }
}
