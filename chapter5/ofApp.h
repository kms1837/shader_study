#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

private:
	ofMesh charQuad;
	ofMesh backgroundQuad;
	ofMesh cloudQuad;
	ofMesh sunQuad;

	ofImage charImg;
	ofImage backgroundImg;
	ofImage cloudImg;
	ofImage sunImg;

	ofShader alphaTestShader;
	ofShader cloudShader;
	ofShader spritesheetShader;

	bool walkRight;
	glm::vec3 charPos;

private:
	void createQuad(ofMesh& mesh, const float w, const float h, glm::vec3 pos);
	glm::mat4 ofApp::createMatrix(glm::vec3 trans, const float rot, glm::vec3 scale);
};
