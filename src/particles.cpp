//
//  particles.cpp
//  particleMesh
//
//  Created by Lutz on 10/02/17.
//
//


#include "particles.hpp"

static const float SIZE = 0.5;
static const float MAX_VELOCITY = 10.0;

using namespace particle;

#pragma mark - Forces

#pragma mark - Particle

Particle::Particle(ParticleParameters *params) {
    Particle({0,0,0},params);
}

Particle::Particle(const ofPoint &pos, ParticleParameters *params) {
    this->params = params;
    this->vel = randomPointInCircle(params->startVelocity);
    this->pos = pos;
}

void Particle::setPosition(const ofPoint &pos) {
    this->pos = pos;
}

void Particle::addForces(const vector<Force*> &forces) {
    this->forces.insert(this->forces.end(),forces.begin(),forces.end());
}
void Particle::addForce(Force *force) {
    this->forces.push_back(force);
}

void Particle::update() {
    this->acc = {0,0,0};
    for (auto force : this->forces) {
        force->updateParticle(this);
    }
    this->forces.clear();
}

void Particle::move(float dt){
        vel += acc * dt;            //Euler method
        vel *= ( 1 - params->friction );  //Friction

        if (vel.length() > params->maxVelocity)
            vel.normalize() *= params->maxVelocity;

        //Update pos
        pos += vel * dt;    //Euler method
}

void Particle::draw(){
        
    //Compute color
    float hue = ofMap( vel.length(), 0, MAX_VELOCITY, 128, 255, true );
    ofColor color = ofColor::red;
    color.setHue(hue);

    ofSetColor(color);
    ofDrawSphere( pos, SIZE );  //Draw particle
}

#pragma mark - ParticleSystem

ParticleSystem::~ParticleSystem() {
    for (auto force : forces)
        delete force;

    for (auto particle : particles)
        delete particle;
}

void ParticleSystem::addParticle(Particle *particle) {
    particles.push_back(particle);
}

void ParticleSystem::emit(ofPoint start) {
    particles.push_back(new Particle(start, &this->parameters));
}

void ParticleSystem::update(float dt) {
    for (auto particle : particles) {
        particle->addForces(forces);
        particle->update();
        particle->move(dt);
    }
}

void ParticleSystem::draw() {
    for (auto &particle : particles) {
        particle->draw();
    }
}

void ParticleSystem::addForce(Force *force) {
    forces.push_back(force);
}

#pragma mark - Particle Helpers

ofPoint particle::randomPointInCircle( float maxRad ) {
    ofPoint pnt;
    float length = ofRandom( 0, maxRad );
    pnt.x = ofRandom(0,1);
    pnt.y = ofRandom(0,1);
    pnt.z = ofRandom(0,1);
    pnt = pnt.getNormalized() * length;
    return pnt;
}
