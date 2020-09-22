//
//  pointLight.h
//  deferredRenderingSample
//
//  Created by ryo.w on 2020/09/22.
//

#pragma once
#include "ofMain.h"

class PointLight : public ofNode {
public:
    PointLight() :
    intensity(1.0f)
    {
        sphere.set(10, 10);
        ambient = ofVec3f(0.0, 0.0, 0.0);
        diffuse = ofVec3f(0.0, 0.0, 0.0);
        specular = ofVec3f(0.0, 0.0, 0.0);
        attenuation = ofVec3f(0.0, 0.0);
    }
    
    void setAmbient(float r, float g, float b)
    {
        ambient = ofVec3f(r, g, b);
    }
    
    
    void setDiffuse(float r, float g, float b, float a=1.0f)
    {
        diffuse = ofVec3f(r, g, b);
    }
    
    
    void setSpecular(float r, float g, float b, float a=1.0f)
    {
        specular = ofVec3f(r, g, b);
    }
    
    
    void setAttenuation(float constant, float linear, float exponential)
    {
        attenuation = ofVec3f(constant, linear, exponential);
    }
    
    
    ofVec3f getAmbient() const
    {
        return ambient;
    }
    
    
    ofVec3f getDiffuse() const
    {
        return diffuse;
    }
    
    
    ofVec3f getSpecular() const
    {
        return specular;
    }
    
    
    ofVec3f getAttenuation() const
    {
        return attenuation;
    }
    
    ofVec3f getVectorPos() const {
        ofVec3f pos = this->getPosition();
        return pos;
    }
    
    
    void draw()
    {
        ofVec3f color = this->getSpecular() * 255;
        color.x = (int)color.x;
        color.y = (int)color.y;
        color.z = (int)color.z;
        ofPushStyle();
        ofSetColor(color.x, color.y, color.z, 1.0);
        sphere.setRadius(0.5);
        sphere.draw();
        ofPopStyle();
    }
    
private:
    
    ofVec3f ambient;
    ofVec3f diffuse;
    ofVec3f specular;
    ofVec3f attenuation;
    
    float intensity;
    ofSpherePrimitive sphere;
    
    ofVec3f orbitAxis;
};
 /* pointLight_h */
