#include "ofApp.h"
using namespace glm;

//--------------------------------------------------------------
void ofApp::setup() {
	ofDisableArbTex();
	ofEnableDepthTest();

	torusMesh.load("torus.ply");
	diffuseShader.load("mesh.vert", "diffuse.frag");
	rimlightShader.load("mesh.vert", "rimlight.frag");
	mixLightShader.load("mesh.vert", "diffuse_rim_mix.frag");
}

//--------------------------------------------------------------
void ofApp::update() {
}

//--------------------------------------------------------------
void ofApp::draw() {
	DirectionalLight dirLight;

	cam.position = vec3(0, 0.75f, 1.0f);
	cam.fov = radians(90.0f);

	float cAngle = radians(-45.0f);
	vec3 right = vec3(1, 0, 0);
	mat4 view = inverse(translate(cam.position) * rotate(cAngle, right));
	mat4 model = rotate(radians(90.0f), right) * scale(vec3(0.3, 0.3, 0.3));
	mat3 normalMatrix = (transpose(inverse(mat3(model))));

	float aspect = 1024.0f / 768.0f;
	mat4 proj = perspective(cam.fov, aspect, 0.01f, 10.0f);
	mat4 mvp = proj * view * model;

	dirLight.direction = normalize(vec3(0, -1, 0));
	dirLight.color = vec3(1, 1, 1);
	dirLight.intensity = 1.0f;

	diffuseShader.begin();
	diffuseShader.setUniformMatrix4f("mvp", mvp);
	diffuseShader.setUniform3f("meshCol", glm::vec3(1, 0, 0));
	diffuseShader.setUniform3f("lightDir", getLightDirection(dirLight));
	diffuseShader.setUniform3f("lightCol", getLightColor(dirLight));
	diffuseShader.setUniformMatrix3f("normal", normalMatrix);
	torusMesh.draw();
	diffuseShader.end();


	model = scale(vec3(0.3, 0.3, 0.3)) * rotate(radians(90.0f), right) * translate(vec3(-3.0f, 0, 0));
	normalMatrix = (transpose(inverse(mat3(model))));
	mvp = proj * view * model;

	rimlightShader.begin();
	rimlightShader.setUniformMatrix4f("model", model);
	rimlightShader.setUniformMatrix4f("mvp", mvp);
	rimlightShader.setUniformMatrix3f("normal", normalMatrix);
	rimlightShader.setUniform3f("meshCol", glm::vec3(1, 0, 0));
	rimlightShader.setUniform3f("cameraPos", cam.position);
	torusMesh.draw();
	rimlightShader.end();

	model = scale(vec3(0.3, 0.3, 0.3)) * rotate(radians(90.0f), right) * translate(vec3(3.0f, 0, 0));
	normalMatrix = (transpose(inverse(mat3(model))));
	mvp = proj * view * model;

	mixLightShader.begin();
	mixLightShader.setUniformMatrix4f("model", model);
	mixLightShader.setUniformMatrix4f("mvp", mvp);
	mixLightShader.setUniformMatrix3f("normal", normalMatrix);
	mixLightShader.setUniform3f("lightDir", getLightDirection(dirLight));
	mixLightShader.setUniform3f("lightCol", getLightColor(dirLight));
	mixLightShader.setUniform3f("meshCol", glm::vec3(1, 0, 0));
	mixLightShader.setUniform3f("cameraPos", cam.position);
	torusMesh.draw();
	mixLightShader.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
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

glm::mat4 ofApp::createMatrix(glm::vec3 trans, const float rot, glm::vec3 scale) {
	// ???? ????
	using glm::mat4;
	mat4 translation = glm::translate(trans);
	mat4 rotation = glm::rotate(rot, glm::vec3(0.0, 0.0, 1.0));
	mat4 scaler = glm::scale(scale);

	return translation * rotation * scaler;
}

mat4 ofApp::createViewMatrix(CameraData cam) {
	// ?? ???? ????
	return inverse(createMatrix(cam.position, cam.fov, vec3(1, 1, 1)));
}

vec3 ofApp::getLightDirection(DirectionalLight& l) {
	return glm::normalize(l.direction * -1.0f);
}

vec3 ofApp::getLightColor(DirectionalLight& l) {
	return l.color * l.intensity;
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
