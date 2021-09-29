# 투명도와 깊이

2D게임 에서는 모든 것을 쿼드(사각형) 위에 그린다.

alphaTest.frag

```glsl
#version 410

uniform sampler2D charTex;
in vec2 fragUV;

out vec4 outCol;

void main() {
  outCol = texture(charTex, fragUV);
  if (outCol.a < 1.0) discard; // GLSL문법 에서 독특한 위치 현재 프레그먼트 쉐이더를 종료함(프래그 먼트 처리를 하지않고 폐기함, 정확히는 현재 파이프 라인에서 폐기함)
}
```

알파나 깊이에 관련된 많은 계산이 `프래그먼트 처리 단계`에서 이루어짐.

이 쉐이더 코드는 `알파 테스팅` 기법이라는데 알파의 컷오프 기준(cutoff threshold)을 정의하고 프래그먼트 알파가 컷오프 기준보다 크면 정상 렌더링 작으면 폐기함.

폐기하면 해당 픽셀이 출력되지 않는건데 예를들면 케릭터를 출력하면 뒤에 이상하게 흰 배경이 있는데 이 픽셀을 폐기하면 이 흰배경이 사라진다.

```cpp
void ofApp::draw() {
	alpthaTestShader.begin();

	alpthaTestShader.setUniformTexture("tex", charImg, 0);
	charQuad.draw();

	alpthaTestShader.setUniformTexture("tex", backgroundImg, 0);
	backgroundQuad.draw();

	alpthaTestShader.end();
}
```

텍스처 입힌 매쉬 2개를 그리면 하나가 안보임 깊이 문제인데 GPU는 별도 명령없이 깊이 버퍼를 만들지 않음 그래서 해결을 위해 `깊이 버퍼(depth buffer)`가 필요함.

깊이 버퍼 처리는 `프래그 먼트 처리 단계`에서 이루어짐.

```cpp
ofEnableDepthTest();
```

오픈 프레임 워크에서는 이거 한줄이면 생성함.

## 알파 블렌딩

---

```glsl
void main() {
  outCol = texture(tex, fragUV);
  outCol.a = min(outCol.a, 0.8); // min, max함수를 제공함
}
```
discard말고 알파값을 조절해 프래그먼트 처리 단계에서 처리하도록 할 수도 있음.

위 코드는 `알파 블렌딩`으로 알파 블렌딩은 `프래그먼트 처리 단계`에서 이루어 진다.

만일 여러개의 이미지가 처리되면 여러개의 프래그먼트가 생성되는데 프래그먼트 처리 단계에서 이 프래그먼트를 합쳐서 최종적으로 화면에 그릴 픽셀을 만든다.

즉 반투명 이미지가 있다면 배경과 프래그먼트가 합쳐저서 반투명하게 비치는듯한 픽셀을 볼 수 있는것.

어떻게 색을 섞을 지는 블렌딩 공식(blend equation)이 결정함

</br>

GPU 블렌딩 공식

```glsl
vec4 finalColor = src * src.a + (1.0 - src.a) * dst;
```
src와 dst는 블렌딩할 두 프래그먼트의 색상 값 이름

dst는 백 버퍼에 이미 저장된 값을 가리킴

프래그먼트 처리 단계까지 마친 렌더링 결과들을 `백 버퍼(back buffer)`에 저장하고 특정 프레임의 렌더링이 모두 끝나면 이 백 버퍼를 화면에 보여줌.

</br>

가산 블렌딩
```glsl
vec4 finalColor = src + dst;
```
두 프래그먼트를 더함

ofApp.cpp
```cpp
ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ALPHA);
ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ADD);
```
오픈프레임웍스는 기본적으로 알파 블렌딩을 사용하는데 위 코드로 다른 블렌딩을 사용할 수 있다.

* 기타
  * 블렌딩은 비용이 큰 작업이라 필요할 떄만 활성화 하는것도 좋음.
  * 대부분의 게임에서 반투명한 매쉬는 깊이 정보 저장에서 제외함(프래그먼트 처리가 건너뛸수도 있기때문, 반투명한데 사각형으로 공간이 잘린듯하게 처리됨)
  * 일부 게임엔진에서는 `깊이 쓰기(depth writing)`와 `깊이 테스팅`을 구분하는데 이렇게 함으로 깊이 버퍼를 이용해 특정 매쉬가 다른 매쉬에 가려지게 만들면서 깊이 정보는 새로 쓰지 않게 만들 수 있다(반투명 메쉬가 반투명 메쉬에 숨는 등의 연출 가능)

## 스프라이트 시트

---

UV좌표와 오프셋(offset)제어로 애니메이션 재생.

spritesheet.vert
```glsl
#version 410

layout (location = 0) in vec3 pos;
layout (location = 3) in vec2 uv;

uniform vec2 size;
uniform vec2 offset;

out vec2 fragUV;

void main() {
  gl_Position = vec4(pos, 1.0);
  fragUV = vec2(uv.x, 1.0-uv.y) * size + (offset * size);
}
```

ofApp.cpp
```
static float frame = 0.0f;
frame = (frame > 10) ? 0.0f : frame += 0.2;
glm::vec2 spriteSize = glm::vec2(0.28f, 0.19);
glm::vec2 spriteFrame = glm::vec2((int)frame % 3, (int)frame / 3);
```