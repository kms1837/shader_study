#pragma once

#include "ofMain.h"

struct CameraData {
	glm::vec3 position;
	float fov;
};

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
	CameraData cam;
	ofMesh torusMesh;
	ofShader uvShader;

private:
	void createQuad(ofMesh& mesh, const float w, const float h, glm::vec3 pos);
	glm::mat4 createMatrix(glm::vec3 trans, const float rot, glm::vec3 scale);
	glm::mat4 createViewMatrix(CameraData cam);
};
