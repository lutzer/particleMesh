//
//  particles.hpp
//  particleMesh
//
//  Created by Lutz on 10/02/17.
//
//

#ifndef particles_hpp
#define particles_hpp

#include <stdio.h>

#include "ofMain.h"

namespace particle {

    class Force;

    struct ParticleParameters {
        float friction = 0.1;
        float startVelocity = 0;
        float maxVelocity = 2.0;
    };

    class Particle {
    public:
        Particle(ParticleParameters *params);
        Particle(const ofPoint &pos, ParticleParameters *params);
        
        void setPosition(const ofPoint &pos);

        void addForces(const vector<Force*> &forces);
        void addForce(Force *force);

        virtual void update();
        virtual void draw();
        void move(float dt);

        ofPoint pos, vel, acc;    // Position, Velocity, Acceleration

        ParticleParameters *params;

        vector<Force*> forces;

        bool fixed; // cannot move anymore
    };

    class Force {
    public:
        virtual void updateParticle(Particle *particle) {
            // change particle
        }
    };

    class ParticleSystem {
    public:

        ~ParticleSystem();

        void addParticle(Particle *particle);
        void emit(ofPoint start);
        void update(float dt);
        void draw();

        void addForce(Force *force);

        vector<Particle*> particles;
        vector<Force*> forces;
        ParticleParameters parameters;
    };


    ofPoint randomPointInCircle(float maxRad);
}


#endif /* particles_hpp */
