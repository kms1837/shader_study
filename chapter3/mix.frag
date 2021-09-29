#version 410

uniform sampler2D tex1;
uniform sampler2D tex2;

in vec2 fragUV;
out vec4 outCol;

void main() {
  vec4 loadTex1 = texture(tex1, fragUV);
  vec4 loadTex2 = texture(tex2, fragUV);
  outCol = mix(loadTex2, loadTex1, loadTex2.r);
}