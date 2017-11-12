#include "ofApp.h"

static const int NUMBER_OF_PARTICLES = 100;
static const int PARTICLE_SPREADING = 200;

//--------------------------------------------------------------
void ofApp::setup(){




    // create a few line segments
    lines.push_back({ofPoint(0, 0 ,0), ofPoint(10, 50, 0), 20});
    lines.push_back({ofPoint(10,50,0), ofPoint(30, 120, 0), 8});
    lines.push_back({ofPoint(10,50,0), ofPoint(20, 70, 40), 5});

    ofEasyCam cam;

    // Set the camera's initial position.
    cam.setDistance(50);

    // fill mesh
    for(auto line : lines) {
        lineMesh.addVertex(line.start);
        lineMesh.addVertex(line.end);
    }
    lineMesh.setMode(OF_PRIMITIVE_LINE_STRIP);

    // setup Particle System
    particleSystem.parameters.friction = 0.05;
    particleSystem.parameters.startVelocity = 0.0;

    // add forcefields
    particleSystem.addForce(new particle::LineForce(lines[0]));
    particleSystem.addForce(new particle::LineForce(lines[1]));
    particleSystem.addForce(new particle::LineForce(lines[2]));

    // create particles
    const ofPoint emitterPos = {-PARTICLE_SPREADING/4,0,-PARTICLE_SPREADING/4};
    for (int i=0; i < NUMBER_OF_PARTICLES; i++) {
        auto particle = new particle::MeshParticle(particle::randomPointInCircle(PARTICLE_SPREADING) + emitterPos, &particleSystem.parameters);
        particleSystem.addParticle(particle);
    }




}

//--------------------------------------------------------------
void ofApp::update(){

    // get delta t
    float dt = ofClamp( ofGetElapsedTimeMillis() - ofGetLastFrameTime(), 0, 0.02 );

    particleSystem.update(dt*10);

}

//--------------------------------------------------------------
void ofApp::draw(){

    ofBackground(ofColor::whiteSmoke);

    cam.begin();
    ofEnableDepthTest();

    ofSetColor(ofColor::black);
    lineMesh.draw();
    
    particleSystem.draw();

    ofDisableDepthTest();


    ofDrawAxis(30.0);
    cam.end();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

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
