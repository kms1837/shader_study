#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofDisableArbTex();
	ofEnableDepthTest();

	createQuad(charQuad, 0.1f, 0.2f, glm::vec3(0.f, -0.2f, 0.f));
	charPos = glm::vec3(0.f, -0.2f, 0.f);

	createQuad(backgroundQuad, 1.f, 1.f, glm::vec3(0.f, 0.f, 0.5f));
	createQuad(cloudQuad, 0.25f, 0.15f, glm::vec3(-0.55f, 0.f, 0.f));
	createQuad(sunQuad, 1.f, 1.f, glm::vec3(0.f, 0.f, 0.4f));

	charImg.load("walk_sheet.png");
	backgroundImg.load("forest.png");
	cloudImg.load("cloud.png");
	sunImg.load("sun.png");
	
	alphaTestShader.load("chapter5_passthrough.vert", "alpha_test.frag");
	cloudShader.load("chapter5_passthrough.vert", "cloud.frag");
	spritesheetShader.load("spritesheet.vert", "alpha_test.frag");
}

//--------------------------------------------------------------
void ofApp::update() {
	if (walkRight) {
		float speed = 0.4 * ofGetLastFrameTime();
		// ofGetLastFrameTime: ���� ������ ���� ���� �����ӱ��� ����� �ð�
		charPos += glm::vec3(speed, 0, 0);
	}
}

//--------------------------------------------------------------
void ofApp::draw() {
	static float frame = 0.0f;
	frame = (frame > 10) ? 0.0f : frame += 0.2;
	glm::vec2 spriteSize = glm::vec2(0.28f, 0.19);
	glm::vec2 spriteFrame = glm::vec2((int)frame % 3, (int)frame / 3);

	glm::mat4 identity = glm::mat4(); // 단위행렬(glm mat4의 기본값이 단위행렬임)

	ofDisableBlendMode();
	ofEnableDepthTest();

	{
		spritesheetShader.begin();

		spritesheetShader.setUniform2f("size", spriteSize);
		spritesheetShader.setUniform2f("offset", spriteFrame);
		spritesheetShader.setUniformTexture("tex", charImg, 0);
		spritesheetShader.setUniformMatrix4f("transform", translate(charPos));
		charQuad.draw();

		spritesheetShader.end();
	}

	{
		alphaTestShader.begin();
		alphaTestShader.setUniformTexture("tex", backgroundImg, 0);
		alphaTestShader.setUniformMatrix4f("transform", identity);
		// glm::translate(glm::vec3(0.f, 0.f, 0.5f)
		backgroundQuad.draw();

		alphaTestShader.end();
	}

	ofDisableDepthTest();
	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ALPHA);

	{
		static float rotation = 1.f;
		rotation += 1.0f * ofGetLastFrameTime();

		glm::mat4 translationA = glm::translate(glm::vec3(-0.55, 0.f, 0.f));
		glm::mat4 scaleA = glm::scale(glm::vec3(1.5, 1, 1));
		glm::mat4 transformA = translationA * scaleA;

		glm::mat4 ourRotation = glm::rotate(rotation, glm::vec3(0.f, 0.f, 1.0));
		glm::mat4 newMatrix = translationA * ourRotation * inverse(translationA);
		glm::mat4 finalMatrixA = newMatrix * transformA;
		glm::mat4 transformB = createMatrix(glm::vec3(0.4f, 0.2f, 0.f), 1.0f, glm::vec3(1, 1, 1));

		cloudShader.begin();
		cloudShader.setUniformTexture("tex", cloudImg, 0);

		cloudShader.setUniformMatrix4f("transform", finalMatrixA);
		cloudQuad.draw();

		cloudShader.setUniformMatrix4f("transform", transformB);
		cloudQuad.draw();

		ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ADD);
		cloudShader.setUniformTexture("tex", sunImg, 0);
		cloudShader.setUniformMatrix4f("transform", identity);
		sunQuad.draw();

		cloudShader.end();
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	//glm::vec3 curPos = triangle.getVertex(2);
	//triangle.setVertex(2, curPos + glm::vec3(0, -20, 0));

	if (key == ofKey::OF_KEY_RIGHT || key == ofKey::OF_KEY_LEFT) {
		walkRight = true;
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {
	if (key == ofKey::OF_KEY_RIGHT || key == ofKey::OF_KEY_LEFT) {
		walkRight = false;
	}
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
	
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

void ofApp::createQuad(ofMesh & mesh, const float w, const float h, glm::vec3 pos) {
	float verts[] = {
		-w + pos.x, -h + pos.y, pos.z,
		-w + pos.x, h + pos.y,	pos.z,
		w + pos.x,	h + pos.y,	pos.z,
		w + pos.x,	-h + pos.y, pos.z
	};

	float uvs[] = { 0, 0, 0, 1, 1, 1, 1, 0 };

	for (int i = 0; i < 4; ++i) {
		int idx = i * 3;
		int uvIdx = i * 2;

		mesh.addVertex(glm::vec3(verts[idx], verts[idx + 1], verts[idx + 2]));
		mesh.addTexCoord(glm::vec2(uvs[uvIdx], uvs[uvIdx + 1]));
	}

	ofIndexType indices[6] = { 0, 1, 2, 2, 3, 0 };
	mesh.addIndices(indices, 6);
}

glm::mat4 ofApp::createMatrix(glm::vec3 trans, const float rot, glm::vec3 scale) {
	using glm::mat4;
	mat4 translation = glm::translate(trans);
	mat4 rotation = glm::rotate(rot, glm::vec3(0.0, 0.0, 1.0));
	mat4 scaler = glm::scale(scale);
	return translation * rotation * scaler;
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
