#version 330
// out vec4 FragColor;
in vec3 o_color;

void main () {
  // FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
  gl_FragColor = vec4(o_color, 1.0f);
}
