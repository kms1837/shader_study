#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	quad.addVertex(glm::vec3(-1, -1, 0));
	quad.addVertex(glm::vec3(-1, 1, 0));
	quad.addVertex(glm::vec3(1, 1, 0));
	quad.addVertex(glm::vec3(1, -1, 0));

	quad.addColor(ofDefaultColorType(1, 0, 0, 1)); // »¡°£»ö
	quad.addColor(ofDefaultColorType(0, 1, 0, 1)); // ³ì»ö
	quad.addColor(ofDefaultColorType(0, 0, 1, 1)); // ÆÄ¶û»ö
	quad.addColor(ofDefaultColorType(1, 1, 1, 1)); // Èò»ö

	// UV ÁÂÇ¥ Ãß°¡
	quad.addTexCoord(glm::vec2(0, 0));
	quad.addTexCoord(glm::vec2(0, 1));
	quad.addTexCoord(glm::vec2(1, 1));
	quad.addTexCoord(glm::vec2(1, 0));

	ofIndexType indices[6] = { 0, 1, 2, 2, 3, 0 };
	quad.addIndices(indices, 6); // ÀÎµ¦½º ¹öÆÛ ÁöÁ¤

	ofDisableArbTex();
	// ½ºÅ©·Ñ
	//img.load("parrot.png");
	//img.getTexture().setTextureWrap(GL_REPEAT, GL_REPEAT);
	//shader.load("scrolling_uv.vert", "texture.frag");

	img1.load("parrot.png");
	img2.load("checker.jpg");
	
	shader.load("mix.vert", "mix.frag");
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {
	shader.begin();
	
	// ½ºÅ©·Ñ
	//shader.setUniformTexture("parrotTex", img, 0);
	//shader.setUniform1f("time", ofGetElapsedTimef());

	shader.setUniformTexture("tex1", img1, 0);
	shader.setUniformTexture("tex2", img2, 1);

	quad.draw();
	shader.end();
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

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
