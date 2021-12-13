# 3D프로젝트 설정

3D프로젝트 설정하는 챕터라 별 내용은 없음

```cpp
torusMesh.load("torus.ply");
// 모델은 이제 버텍스와 인덱스 버퍼를 따로 지정안하고 파일로 불러옴(복잡해서)
// 오픈 프레임 워크는 기본적으로 .ply 매쉬 포맷을 지원한다고함

mat4 mvp = proj * view * model;
uvShader.setUniformMatrix4f("mvp", mvp);
// 투영, 뷰, 모델 행렬을 따로 전달하던것을 이제 처리해서 보내줌
```

```glsl
#version 410

layout (location = 0) in vec3 pos;
layout (location = 3) in vec2 uv;

uniform mat4 mvp; // 투영, 뷰, 모델 행렬을 따로받던것을 이제 미리 처리한후 받음

out vec2 fragUV;

void main() {
  gl_Position = mvp * vec4(pos, 1.0);
  fragUV = uv;
}
```

3D게임은 `원근 투영(perspective projection)`을 사용한다.

3D의 카메라 프러스텀은 근평면, 원평면에 의해 `잘린 피라미드` 모양이다.

카메라와 멀리 있을수록 오브젝트는 작게 보인다.

```cpp
mat4 perspective(fov, aspect, zNear, zFar)
// fov - 시야각, 시야각이 클수록 더 많은 영역을 화면에 그린다.
// aspect - 화면비
```

```cpp
float aspect = 1024.0f / 768.0f;
cam.position = vec3(0, 0, 1);
cam.fov = radians(90.0f);
// 일반적으로 90도 전후의 값을 시야각으로 사용한다고함.
mat4 proj = perspective(cam.fov, aspect, 0.01f, 10.0f);
```

## 기타

UV좌표를 색상으로 출력하는것은 디버깅 기법.