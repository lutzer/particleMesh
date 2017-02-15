//
//  treeparticles.cpp
//  particleMesh
//
//  Created by Lutz on 12/02/17.
//
//

#include "treeparticles.hpp"

#include <math.h>

static const float PARTICLE_DISTANCE = 4.0;

using namespace particle;

void LineForce::updateParticle(Particle *particle) {
    ofVec3f acc = shortestVectorToLine(particle->pos, line.start, line.end);
    float dist = acc.length() - line.radius;

    if (dist < 0) {
        particle->vel *= -1.0;
    } else {
        acc *= dist;
        particle->acc += acc;
    }
}

void MeshParticle::addNeighbours(vector<Particle*> &particles) {
    for (auto particle : particles)
        addNeighbour(particle);
}

void MeshParticle::addNeighbour(Particle *particle) {
        neighbours.push_back(particle);
}

void MeshParticle::update() {
    Particle::update();

    //calculate repeling/attraction forces between neighbour particles
    for (auto neighbour : neighbours) {
        float x = this->pos.distance(neighbour->pos) - PARTICLE_DISTANCE;

        if (x < 0)
            this->acc += (neighbour->pos - this->pos).getNormalized() * abs(x) * x;
        else
            this->acc += (neighbour->pos - this->pos).getNormalized() * x * 0.5;


        //x = min(x, -PARTICLE_DISTANCE*2);

        //this->acc += (neighbour->pos - this->pos).getNormalized() * x * 0.5;
    }
}

void MeshParticle::draw() {
    Particle::draw();

    for (auto neighbour : neighbours) {
        ofDrawLine(this->pos,neighbour->pos);
    }
}



/// returns the vector with minimum length between point and a line between p1, and p2
ofPoint particle::shortestVectorToLine(const ofPoint &point, const ofPoint &lineStart, const ofPoint &lineEnd) {
    float length = lineStart.distance(lineEnd);

    // special case, where both line points are the same
    if (length == 0)
        return - point + lineStart;

    // reduce equation to two points
    ofPoint pt = point - lineStart;
    ofPoint line = lineEnd - lineStart;

    // calculate the distance from the linestart, where the pt hits the line with an orthoganol angle
    float s = pt.dot(line) / length;

    s = ofWrap(s, 0.0, length);

    return -pt + (line * s / length);
}
