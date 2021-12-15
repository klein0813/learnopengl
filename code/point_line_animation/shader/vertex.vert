#version 330
in vec2 apos;
layout (location = 1) in float alpha;
uniform vec3 u_fromColor;
uniform vec3 u_toColor;
uniform float u_time;
out vec4 o_color;

void main () {
  gl_Position = vec4(apos, 0.0, 1.0);
  if (abs(gl_Position.x) > 0.9999 && abs(gl_Position.y) > 0.9999) {
    vec3 color = (u_fromColor - u_toColor + 1.0) * u_time + u_toColor;
    o_color = vec4(color / 255.0, 1.0);
  } else if (alpha == 1.0) {
    o_color = vec4(1.0, 1.0, 1.0, 3.0);
  } else {
    o_color = vec4(1.0, 1.0, 1.0, alpha);
  }
}
