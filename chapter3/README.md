# 텍스처

버텍스 색상으로 한땀 한땀 찍는건 힘들기에

이를 대신해 이미지 파일 즉 `텍스처(Texture)`를 활용

* 텍스처 매핑(texture mapping): 3D 메쉬에 텍스처를 입힘

  텍스처 좌표(texture coordinates) 나 UV 좌표(UV coordinates)필요

* 텍스처 샘플링(texture sampling): 텍스처에서 특정 좌표의 색상 값을 찾는 과정

## 텍스처 사용

ofApp.cpp
```cpp
ofImage img;
img.load("fileName.png");
```
오픈프레임웍스에서 파일load 기능이 제공되서 간단히 처리됨

ofApp.cpp

```cpp
shader.begin();
shader.setUniformTexture("tex", img, 0);
// 유니폼 변수 이름, 객체, 텍스처 위치(여러개의 텍스처를 사용할 수 있으므로) 설정
quad.draw();
shader.end();
```

texture.frag

```glsl
#version 410

uniform sampler2D tex;
// sampler2D는 glsl에서 제공하는 샘플러

in vec2 fragUV;
out vec4 outCol;

void main() {
  outCol = texture(tex, fragUV);
// texture(샘플러, UV좌표) - glsl 내장 함수;
}
```

texture.vert

```glsl
void main() {
  gl_Position = vec4(pos, 1.0);
  fragUV = vec2(uv.x, 1.0 - uv.y);
}
```
실행시 텍스처가 뒤집혀 보이는데 `1.0 - uv.y` 해주는것으로 문제 해결

이유는 이미지 텍스처는 상단부터 시작하는데 OpenGL은 하단부터 시작한다고 가정한다.


## 텍스처 스크롤

ofApp.cpp

```cpp
void ofApp::setup() {
  ...
  img.getTexture().setTextureWrap(GL_REPEAT, GL_REPEAT);
  ...
}

void ofApp::draw() {
  ...
  shader.setUniform1f("time", ofGetElapsedTimef());
  ...
}

// 가로, 세로를 REPEAT모드로 설정(반복), 설정 안하면 UV좌표 변경시 잡고 늘리는 듯한 느낌이 난다.
```

scrolling_uv.vert

```glsl
#version 410

layout (location = 0) in vec3 pos;
layout (location = 3) in vec2 uv;

uniform float time;
out vec2 fragUV;

void main() {
  gl_Position = vec4(pos, 1.0);
  fragUV = vec2(uv.x, 1.0 - uv.y) + vec2(1.0, 0.0) * time;
}
```
시간에 따라 스크롤됨


## 텍스처 조정

```glsl
vec4 tex = texture(tex, fragUV);
tex.r = 1.0f;
tex.g = 2.0f;
tex.b = 2.0f;
tex.a = 1.0f;
outCol = tex
```

텍스처의 rgba를 설정할 수 있다.

일부 GPU에서는 나누기가 곱하기보다 약간 느린 경우가 있을 수 있음.

GPU 연산 중 곱한 다음 더한다(Multiply, then Add)를 의미하는 `MAD연산`이 있는데 두 연산을 한번의 GPU 명령으로 처리할 수 있게 해준다.

그러므로 `곱하기를 먼저하고 더하면` 최적화에 도움이 된다고 한다.

## 텍스처 혼합

glsl에서는 `mix()` 다른곳에서는 `lerp()`로 불리기도 한다.

이 함수는 세번째 인자로 두 값을 어떤 비율로 섞을지 결정하는데 0이면 첫번째 100% 두번째 0%반영, 1이면 첫번째 0% 두번쨰 100% 반영됨.
mix.vert

```glsl
#version 410

layout (location = 0) in vec3 pos; 
layout (location = 3) in vec2 uv;

out vec2 fragUV;

void main()
{
	gl_Position = vec4(pos, 1.0);
	fragUV = vec2(uv.x, 1.0-uv.y);
}
```

mix.frag

```glsl
uniform sampler2D tex1;
uniform sampler2D tex2;

in vec2 fragUV;
out vec4 outCol;

void main() {
  vec4 loadTex1 = texture(tex1, fragUV);
  vec4 loadTex2 = texture(tex2, fragUV);
  outCol = mix(loadTex1, loadTex2, 0.5);
  // 세번째 인자가 0.5이면 50%, 50% 혼합
}
```

```cpp
outCol = mix(loadTex2, loadTex1, loadTex2.r);
```

책에서는 마지막에 두번째 텍스처의 알파(R)채널 기반으로 혼합한 코드로 변경한 후 챕터2 종료됨.