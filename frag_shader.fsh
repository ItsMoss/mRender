/*
uniform sampler2D qt_Texture0;
varying highp vec4 qt_TexCoord0;

void main(void) {
    gl_FragColor = texture2D(qt_Texture0, qt_TexCoord0.st);
}

^all the above code was provided in Qt default template (MOSS)
*/

#version 330
// input
in vec4 vColor;
// output
out vec4 fColor;

void main() {
   fColor = vColor;
}
