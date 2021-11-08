#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(255);
	ofSetLineWidth(2);
	ofEnableDepthTest();

	auto ico_sphere = ofIcoSpherePrimitive(300, 3);
	this->triangle_list.insert(this->triangle_list.end(), ico_sphere.getMesh().getUniqueFaces().begin(), ico_sphere.getMesh().getUniqueFaces().end());

	this->frame.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
}

//--------------------------------------------------------------
void ofApp::update() {

	this->mesh.clear();
	this->frame.clear();

	int radius = 300;
	for (int i = 0; i < this->triangle_list.size(); i++) {

		glm::vec3 avg = (this->triangle_list[i].getVertex(0) + this->triangle_list[i].getVertex(1) + this->triangle_list[i].getVertex(2)) / 3;
		auto noise_value = ofNoise(avg.y * 0.005 + ofGetFrameNum() * 0.02, avg.x * 0.0025, avg.z * 0.0025);

		if (noise_value < 0.45) { noise_value = 0; }
		else if (noise_value > 0.55) { noise_value = 1; }
		else { noise_value = ofMap(noise_value, 0.45, 0.55, 0, 1); }

		vector<glm::vec3> vertices;

		vertices.push_back(glm::normalize(this->triangle_list[i].getVertex(0)) * (radius + 5) - avg);
		vertices.push_back(glm::normalize(this->triangle_list[i].getVertex(1)) * (radius + 5) - avg);
		vertices.push_back(glm::normalize(this->triangle_list[i].getVertex(2)) * (radius + 5) - avg);

		vertices.push_back(glm::normalize(this->triangle_list[i].getVertex(0)) * (radius - 5) - avg);
		vertices.push_back(glm::normalize(this->triangle_list[i].getVertex(1)) * (radius - 5) - avg);
		vertices.push_back(glm::normalize(this->triangle_list[i].getVertex(2)) * (radius - 5) - avg);

		for (auto& vertex : vertices) {

			vertex *= noise_value;
			vertex += avg;
		}

		this->mesh.addVertices(vertices);
		this->frame.addVertices(vertices);

		this->mesh.addColor(ofColor(255));
		this->mesh.addColor(ofColor(255));
		this->mesh.addColor(ofColor(255));

		this->mesh.addColor(ofColor(0));
		this->mesh.addColor(ofColor(0));
		this->mesh.addColor(ofColor(0));

		this->frame.addColor(ofColor(0));
		this->frame.addColor(ofColor(0));
		this->frame.addColor(ofColor(0));

		this->frame.addColor(ofColor(255));
		this->frame.addColor(ofColor(255));
		this->frame.addColor(ofColor(255));

		this->mesh.addTriangle(this->mesh.getNumVertices() - 1, this->mesh.getNumVertices() - 2, this->mesh.getNumVertices() - 3);
		this->mesh.addTriangle(this->mesh.getNumVertices() - 4, this->mesh.getNumVertices() - 5, this->mesh.getNumVertices() - 6);

		this->mesh.addTriangle(this->mesh.getNumVertices() - 1, this->mesh.getNumVertices() - 2, this->mesh.getNumVertices() - 5);
		this->mesh.addTriangle(this->mesh.getNumVertices() - 1, this->mesh.getNumVertices() - 5, this->mesh.getNumVertices() - 4);

		this->mesh.addTriangle(this->mesh.getNumVertices() - 1, this->mesh.getNumVertices() - 3, this->mesh.getNumVertices() - 6);
		this->mesh.addTriangle(this->mesh.getNumVertices() - 1, this->mesh.getNumVertices() - 6, this->mesh.getNumVertices() - 4);

		this->mesh.addTriangle(this->mesh.getNumVertices() - 2, this->mesh.getNumVertices() - 3, this->mesh.getNumVertices() - 6);
		this->mesh.addTriangle(this->mesh.getNumVertices() - 2, this->mesh.getNumVertices() - 6, this->mesh.getNumVertices() - 5);

		this->frame.addIndex(this->frame.getNumVertices() - 1); this->frame.addIndex(this->frame.getNumVertices() - 2);
		this->frame.addIndex(this->frame.getNumVertices() - 2); this->frame.addIndex(this->frame.getNumVertices() - 3);
		this->frame.addIndex(this->frame.getNumVertices() - 1); this->frame.addIndex(this->frame.getNumVertices() - 3);

		this->frame.addIndex(this->frame.getNumVertices() - 4); this->frame.addIndex(this->frame.getNumVertices() - 5);
		this->frame.addIndex(this->frame.getNumVertices() - 5); this->frame.addIndex(this->frame.getNumVertices() - 6);
		this->frame.addIndex(this->frame.getNumVertices() - 4); this->frame.addIndex(this->frame.getNumVertices() - 6);

		this->frame.addIndex(this->frame.getNumVertices() - 1); this->frame.addIndex(this->frame.getNumVertices() - 4);
		this->frame.addIndex(this->frame.getNumVertices() - 2); this->frame.addIndex(this->frame.getNumVertices() - 5);
		this->frame.addIndex(this->frame.getNumVertices() - 3); this->frame.addIndex(this->frame.getNumVertices() - 6);
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateY(ofGetFrameNum() * 0.6666666666666);

	ofSetColor(239);
	this->mesh.drawFaces();

	ofSetColor(39);
	this->frame.drawWireframe();

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}