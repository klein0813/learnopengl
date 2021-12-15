#version 330
// precision lowp float;
// out vec4 FragColor;
in vec4 o_color;

void main () {
  float alpha = o_color.a;
  if (o_color.a > 2.0) {
    float r = distance(gl_PointCoord, vec2(0.5, 0.5));
    if (r > 0.5) {
      discard;
    }
    alpha = 0.3;
  }
  gl_FragColor = vec4(vec3(o_color), alpha);
}
