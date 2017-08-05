/*
attribute highp vec4 qt_Vertex;
attribute highp vec4 qt_MultiTexCoord0;
uniform highp mat4 qt_ModelViewProjectionMatrix;
varying highp vec4 qt_TexCoord0;

void main(void) {
    gl_Position = qt_ModelViewProjectionMatrix * qt_Vertex;
    qt_TexCoord0 = qt_MultiTexCoord0;
}

^all the above code was provided in default Qt template (MOSS)
*/

#version 330
// inputs
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;
// output
out vec4 vColor;

void main() {
  gl_Position = vec4(position, 1.0);
  vColor = vec4(color, 1.0);
}


