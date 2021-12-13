# 버텍스 셰이더와 이동, 회전, 크기

```cpp
int numVerts = charMesh.getNumVertices();
for (int i = 0; i < numVerts; ++i) {
  charMesh.setVertex(i, charMesh.getVertex(i) + glm::vec3(0.2f, 0.f, 0.f));
}
```
메쉬의 정점(Vertex)을 갱신하는 것으로 이동하는 방법

이 방법은 상대적으로 느린 연산이라 매 프레임마다 이런 연산을 처리하는 것은 피해야함.

move.vert
```glsl
uniform vec3 translation;

gl_Position = vec4(pos + translation, 1.0);
```
버텍스 셰이더에서 Position에서 벡터를 더해 주는것으로 이동이 가능함.

scale.vert
```glsl
uniform vec3 scale;

gl_Position = vec4((pos * scale), 1.0);
```
벡터를 곱하면 메쉬 크기를 바꾼다.

rotate.vert
```glsl
uniform vec3 rotation;

vec3 rotated;
rotated.x = (cos(rotation) * pos.x) - (sin(rotation) * pos.y);
rotated.y = (cos(rotation) * pos.y) + (sin(rotation) * pos.x);

gl_Position = vec4(rotated 1.0);
```
벡터 회전

대부분의 버텍스 셰이더는 `크기`, `회전`, `이동` 순으로 처리한다.

</br>

메쉬의 버텍스가 정의된 좌표계를 메쉬의 `오브젝트 공간(object space)`이라고 한다.

컴퓨터 그래픽에서는 `좌표계(coordinate system)` 대신 `좌표 공간(coordinate space)`이라는 용어를 종종 사용함.

## 변환 행렬(Transformation matrix)

대부분의 게임은 크기, 회전, 이동을 하나의 행렬로 합쳐서 처리한다.

```cpp
mat4 translation = glm::translation(vec3(0.5f, 0.f, 0.f));
mat4 rotation = glm::rotate((float)PI * 0.5f, vec3(0.f, 0.f, 1.f));
mat4 scale = glm::scale(vec3(0.5f, 0.25f, 1.f));
```
오픈 프레임웍스에서는 glm이라는 수학 라이브러리가 있는데 벡터를 행렬로 변환함

```cpp
mat4 transform1 = translation * rotation * scale;
mat4 transform2 = scale * rotation * translation;
```
행렬을 서로 곱하면 행렬을 합칠 수 있다.(순서에 영향이 있으니 주의)

데이터가 행에 따라 배치될 경우 행우선 행렬, 열에 따르면 열우선 행렬이라고 한다.(행렬의 메모리 레이아웃 방식을 지칭하는 그래픽 용어, 레이아웃 간 우열은 없다고한다)

glm은 열우선 행렬 사용한다고 한다.

삼각함수 sin, cos 등은 처리 속도가 느린데 행렬 간 곱셈으로 대체하여 속도향상을 노려볼 수 있다.