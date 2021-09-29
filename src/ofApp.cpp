#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofDisableArbTex();
	ofEnableDepthTest();

	createQuad(charQuad, 0.1f, 0.2f, glm::vec3(0.f, -0.2f, 0.f));
	createQuad(backgroundQuad, 1.f, 1.f, glm::vec3(0.f, 0.f, 0.5f));
	createQuad(cloudQuad, 0.25f, 0.15f, glm::vec3(-0.55f, 0.f, 0.f));
	createQuad(sunQuad, 1.f, 1.f, glm::vec3(0.f, 0.f, 0.4f));

	charImg.load("walk_sheet.png");
	backgroundImg.load("forest.png");
	cloudImg.load("cloud.png");
	sunImg.load("sun.png");
	
	alpthaTestShader.load("chapter4_passthrough.vert", "alpha_test.frag");
	cloudShader.load("chapter4_passthrough.vert", "cloud.frag");
	spritesheetShader.load("spritesheet.vert", "alpha_test.frag");
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {
	static float frame = 0.0f;
	frame = (frame > 10) ? 0.0f : frame += 0.2;
	glm::vec2 spriteSize = glm::vec2(0.28f, 0.19);
	glm::vec2 spriteFrame = glm::vec2((int)frame % 3, (int)frame / 3);

	ofDisableBlendMode();
	ofEnableDepthTest();

	{
		spritesheetShader.begin();

		spritesheetShader.setUniform2f("size", spriteSize);
		spritesheetShader.setUniform2f("offset", spriteFrame);
		alpthaTestShader.setUniformTexture("tex", charImg, 0);
		charQuad.draw();

		spritesheetShader.end();
	}

	{
		alpthaTestShader.begin();
		alpthaTestShader.setUniformTexture("tex", backgroundImg, 0);
		backgroundQuad.draw();

		alpthaTestShader.end();
	}

	ofDisableDepthTest();
	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ALPHA);

	{
		cloudShader.begin();

		cloudShader.setUniformTexture("tex", cloudImg, 0);
		cloudQuad.draw();

		ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ADD);
		cloudShader.setUniformTexture("tex", sunImg, 0);
		sunQuad.draw();

		cloudShader.end();
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	//glm::vec3 curPos = triangle.getVertex(2);
	//triangle.setVertex(2, curPos + glm::vec3(0, -20, 0));
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

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

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
