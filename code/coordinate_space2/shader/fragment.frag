#version 330 core
// precision lowp float;
// out vec4 FragColor;
in vec3 oColor;
in vec2 oTexCoords;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float alpha;

void main () {
  // gl_FragColor = texture(sampler, oTexCoords);
  // gl_FragColor = texture2D(texture1, oTexCoords) * vec4(oColor, 1.0);
  // gl_FragColor = mix(texture(texture1, oTexCoords), texture(texture2, vec2(1.0 - oTexCoords.s, oTexCoords.t)), 0.2);
  gl_FragColor = mix(texture(texture1, oTexCoords), texture(texture2, oTexCoords), alpha) * vec4(oColor, 1.0);
}
