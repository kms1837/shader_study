#version 410

layout (location = 0) in vec3 pos;
layout (location = 3) in vec2 uv;

out vec2 fragUV;

void main() {
  gl_Position = vec4(pos, 1.0);
  fragUV = vec2(uv.x, 1.0 - uv.y); // 수직으로 텍스처 뒤집음
}

// uv를 프래그먼트 셰이더로 전달