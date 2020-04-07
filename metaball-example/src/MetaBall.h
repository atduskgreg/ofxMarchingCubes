#pragma once

#include "ofMain.h"

#include "ofxMarchingCubes.h"

class MetaBall: public glm::vec3{
public:
	glm::vec3 accel, vel;
	float size;
	MetaBall(){
		size = ofRandom(5, 10);
	}
	
	void init(const glm::vec3& _pos){
		x = _pos.x;
		y = _pos.y;
	}
	
	void goTo(const glm::vec3& target, float k = 0.1f, float damp = 0.9f){
		accel = (target - *this)*k;
		vel += accel;
		vel *= damp;
		*this += vel;
	}
	
	void update(const glm::vec3& _force, float damp = 0.9f){
		vel += _force;
		vel *= damp;
		*this += vel;
	}
};

