//
//  treeparticles.hpp
//  particleMesh
//
//  Created by Lutz on 12/02/17.
//
//

#ifndef treeparticles_hpp
#define treeparticles_hpp

#include <stdio.h>

#include "particles.hpp"

#include "geometries.hpp"

namespace particle {

    class LineForce : public Force {
    public:

        LineForce(LineSegment line) : line(line) {};

        void updateParticle(Particle *particle) override;
        float getDistance(const ofPoint &pos) override;

        LineSegment line;
    };

    class MeshParticle : public Particle {
    public:

        MeshParticle(const ofPoint &pos, ParticleParameters *params) : Particle(pos,params) {}

        void addNeighbours(vector<Particle*> &particles);
        void addNeighbour(Particle *particle);
        
        void update() override;
        void draw() override;

        vector<Particle*> neighbours;
    };


    ofPoint shortestVectorToLine(const ofPoint &point, const ofPoint &lineStart, const ofPoint &lineEnd);
}


#endif /* treeparticles_hpp */
