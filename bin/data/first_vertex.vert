// 버텍스 쉐이더
#version 410
layout ( location = 0 ) in vec3 pos;
//layout ( location = 1 ) in vec4 color;

//out vec4 fragCol;

//in vec3 position;

void main() {
  //gl_Position = vec4(position, 1.0);

  // 스크린 픽셀 좌표를 NDC로 변환
  //float x = (position.x / 1024.0) * 2.0 - 1.0;
  //float y = (position.y / 768.0) * 2.0 - 1.0;
  //gl_Position = vec4(x, y, 0.0, 1.0);

  gl_Position = vec4(pos, 1.0);
  //fragCol = color;
}