# 오픈프레임웍스 세팅, 맛보기

맛보기?

1장은 메쉬, 벡터, 렌더링 파이프라인, 셰이더 등 이론적인 내용을 다뤄서 개인적으로만 보고 기록으로는 안남김

## openFrameworks 설정
---
https://openframeworks.cc/ko/download/

visual studio (2017)된 부분 다운로드 후 압축 풀어두고 vs2017 extension에 openFrameworks 플러그인을 설치하니 간단하게 설정 가능했다.

</br>

main.cpp

```cpp
ofGLWindowSettings glSettings;
glSettings.setSize(1024, 768);
glSettings.windowMode = OF_WINDOW;
glSettings.setGLVersion(4, 1);
ofCreateWindow(glSettings);
```
설정 후 <code>main.cpp</code>를 수정하면 OpenGL을 사용할 수 있다.

</br>

## 셰이더 맛보기
---
OpenGL이므로 GLSL(OpenGL Shading Language)을 사용하는것 같음

</br>

* 버텍스(정점) 셰이더

first.vert

```glsl
#version 410
// glsl 버전

in vec3 position; // 렌더링 파이프라인에서 전 단계로 부터 전달 받을 정보를 받을 변수
 
void main() {
  gl_Position = vec4(position, 1.0); // 위치 정보 저장
}
```
정점을 처리하는 셰이더

버텍스 셰이더는 NDC(Normalized Device Coordinates, 정규화 장치 좌표계)를 기준으로 위치 정보를 출력함

스크린 픽셀 좌표계와 NDC의 Y축 방향은 서로 반대

NDC에서 (0, 0)은 중앙

메쉬는 스크린 픽셀 좌표계보다 NDC를 사용하는것이 일반적이라 함

</br>

* 프래그먼트 셰이더

first.frag
```glsl
#version 410
out vec4 outColor; // 렌더링 파이프라인 에서 다음 단계로 부터 전달할 정보

void main() {
  outColor = vec4(1.0, 0.0, 0.0, 1.0); // R, G, B, A
}
```
각 픽셀이 어떻게 처리될 것인지 처리하는 셰이더

</br>

* 셰이더 바인딩

app.cpp
```cpp
ofShader shader;
shader.load("first.vert", "first.frag");

shader.begin(); // 바인딩 시작
triangle.draw(); // 메쉬 출력
shader.end(); // 바인딩 중지
```
메쉬에 셰이더 적용

</br>

* 정보를 여러개 받기
```glsl
#version 410
layout ( location = 0 ) in vec3 pos; // 0번째에 저장된 정보를 가져옴
layout ( location = 1 ) in vec4 color; // 1번째에 저장된 정보를 가져옴

out vec4 fragCol;

void main() {
  gl_Position = vec3(pos, 1.0);
  fragCol = color; // 1번째에 저장된 정보를 다음 단계로 넘김
}
```

* 유니폼 변수
```glsl
#version 410

uniform vec4 fragCol;
out vec4 outColor;

void main() {
  outColor = fragCol;
}
```

app.cpp
```cpp
shader.begin(); // 바인딩 시작
shader.setUniform4f("fragCol", glm::vec4(0, 1, 1, 1));
triangle.draw(); // 메쉬 출력
shader.end(); // 바인딩 중지
```
버텍스 데이터를 매 프레임마다 변경하는것은 꽤나 느린 작업이므로 C++코드에서 파이프 라인으로 데이터를 보낸다.