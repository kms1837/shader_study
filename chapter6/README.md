# 카메라 좌표
게임 카메라는 `뷰 행렬(view matrix)`이라는 것을 생성 일종의 변환행렬로 카메라 시점에서 `오브젝트 배치`를 위한 `위치, 회전, 크기 정보`를 담고있다.

\* 뷰행렬은 버텍스 셰이더에서 카메라 위치와 방향에 따라 위치 조정할때 사용함

게임 카메라의 변환 행렬은 자신의 변환 연산의 역(inverse)을 저장, 뷰행렬은 카메라 제외 나머지 모든 것을 움직이기 때문이다.

(실제 카메라를 찍을때 카메라를 오른쪽으로 움직이면 모든것들이 왼쪽으로 이동하는것처럼 보이는것을 생각)

</br>

spritesheet.vert

```glsl
uniform mat4 view;
uniform mat4 model;

gl_Position = view * model * vec4(pos, 1.0); // view가 추가 되었음
```

app.cpp

```cpp
glm::mat4 ofApp::createViewMatrix(CameraData cam) {
	// 뷰 행렬 생성
	return glm::inverse(createMatrix(cam.position, cam.rotation, glm::vec3(1, 1, 1)));
}
// 뷰행렬은 자신 행렬의 inverse를 저장하므로
```

NDC는 화면 크기와 무관하게 -1부터 1까지 좌표를 사용해서 다양한 해상도 지원은 무리

</br>

현재 위치를 다른공간의 위치로 바꿀때 `매핑(mapping)` 한다고 한다.

ex) 현재 위치를 월드 공간에서 뷰 공간으로 `매핑`했다.

매핑할 때는 `변환행렬`을 사용한다.

게임에서는 `오브젝트 공간(object space)`, `월드 공간(world space)`, `뷰 공간(view space)`을 사용하며 NDC는 클립 공간(clip space)추가로 사용함.

</br>

`클립 공간(clip space)`: NDC의 -1, 1범위 밖에 있는 버텍스를 GPU가 잘라버림(clip), 버텍스를 클립 공간으로 보내기 위해 `투영 행렬(projection matrix)`을 사용함.

`투영(projection)`: 기하학에서 투영은 3D인 대상을 2D평면에 시각화 하는 방법을 가리킨다.

</br>

spritesheet.vert

```glsl
uniform mat4 view; // 뷰행렬
uniform mat4 proj; // 투영행렬
uniform mat4 model; // 오브젝트

gl_Position = proj * view * model * vec4(pos, 1.0); // proj가 추가 되었음
```

버텍스 쉐이더 에서 투영행렬 사용하는 방법, 단순히 곱하는 것으로 사용함

### 정리

1. 같은 좌표 공간에 있는 두 오브젝트, 버텍스 사이에서만 위치, 회전, 크기를 비교할 수 있음
2. 버텍스에 특정 행렬을 곱해 다른 좌표 공간으로 갈 수 있음
3. 역행렬을 곱하면 원래 공간으로 되돌아 갈 수 있음

## 카메라 프러스텀(frustum)과 투영

투영 행렬은 이동, 회전, 크기로 구성되지 않고 `프러스텀`에 대한 정보를 이용해 만든다.

`프러스텀(frustum)`: 카메라가 볼 수 있는 삼차원 영역, 카메라가 볼 수 있는 가장 가까운 거리 근평면(near clip plane)과 먼 거리 원평면(far clip plane) 사이의 영역으로 이뤄진다.

카메라 프러스텀은 `직각 프리즘`과 `잘려진 피라미드` 두 형태를 갖는다.

직각 프리즘은 직교 투영(orthographic projection)방식으로 씬을 렌더링한다. 직교 투영은 `원근` 효과가 없다.

```cpp
mat4 ortho(float left, float right, float bottom, float top, float zNear, float zFar);
// NDC에서 직교 투영 만들기
```

```cpp
proj = ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.0f, 10.f);
// -1, 1기준

proj = ortho(-1.33f, 1.33f, -1.0f, 1.0f, 0.0f, 10.f);
// 1024 x 768기준 (1024/768 = 1.33)
```
