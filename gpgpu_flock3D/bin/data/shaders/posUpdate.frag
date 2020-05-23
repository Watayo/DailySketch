#version 150
precision mediump float;

uniform sampler2DRect posData;
uniform sampler2DRect velData;

uniform vec2 resolution;
uniform vec3 screen;

uniform float separationDistance; // 20 -> 0.01?
uniform float alignmentDistance; // 40 -> 0.02?
uniform float cohesionDistance; //
uniform float speed;
uniform float force;

uniform vec2 mouse;

in vec2 vTexCoord;

out vec4 vFragColor0;
out vec4 vFragColor1;


// vector utils
vec3 limit(vec3 v,float m){
    float lengthSquared=v.x*v.x+v.y*v.y+v.z*v.z;
    if(lengthSquared>m*m&&lengthSquared>0.){
        float ls=sqrt(lengthSquared);
        float ratio=m/ls;
        v*=ratio;
    }
    return v;
}

// Separation
// Method checks for nearby boids and steers away
vec3 separate(vec3 p,vec3 v){
    float width=resolution.x;
    float height=resolution.y;

    vec3 steer=vec3(0.);
    float count=0.;

    // For every boid in the system, check if it's too close
    for(int x=0;x<width;x++){
        for(int y=0;y<height;y++){
            vec2 uv=vec2(x,y);

            vec3 pos=texture(posData,uv).xyz;

            float d=distance(p,pos);

            // If the distance is greater than 0 and less than an arbitrary amount (0 when you are yourself)
            if((d>0.)&&(d<separationDistance)){
                // Calculate vector pointing away from neighbor
                vec3 diff=p;
                diff-=pos;
                diff=normalize(diff);
                // diff/=d; // Weight by distance
                steer+=diff;
                count+=1.;// Keep track of how many
            }
        }
    }
    // Average -- divide by how many
    if(count>0.){
        steer/=count;
    }
    if(length(steer)>0.){
        // Implement Reynolds: Steering = Desired - Velocity
        steer=normalize(steer);
        steer*=(speed);
        steer -= v;
        steer=limit(steer,force);
        return steer;
    } else {
        return vec3(0.);
    }
}

// Alignment
// For every nearby boid in the system, calculate the average velocity
vec3 align(vec3 p,vec3 v){
    float width=resolution.x;
    float height=resolution.y;

    vec3 sum=vec3(0.);
    float count=0.;
    for(int x=0;x<width;x++){
        for(int y=0;y<height;y++){
            vec2 uv=vec2(x,y);
            vec3 pos=texture(posData,uv).xyz;
            vec3 otherVel=texture(velData,uv).xyz;

            float d=distance(p,pos);

            if((d>0)&&(d<alignmentDistance)){
                sum.x+=otherVel.x;
                sum.y+=otherVel.y;
                sum.z+=otherVel.z;
                count=count+1.;
            }
        }
    }
    if(count>0.){
        sum/=(count);
        //sum=normalize(sum);
        sum*=(speed);
        //sum *= 10000.0;
        vec3 steer=sum-v;
        steer=limit(steer,force);
        return steer;
    }else{
        return vec3(0.);
    }
}

vec3 seek(vec3 p,vec3 vel,vec3 target){
    vec3 desired=target;// A vector pointing from the location to the target
    desired-=p;

    // Normalize desired and scale to maximum speed
    desired=normalize(desired);
    desired*=(speed);

    // Steering = Desired minus Velocity
    vec3 steer=desired;
    steer-=vel;
    steer=limit(steer,force);// Limit to maximum steering force
    return steer;
}

vec3 seekForce(vec3 p,vec3 vel,vec3 target){
    vec3 desired=target;// A vector pointing from the location to the target
    desired-=p;

    // Normalize desired and scale to maximum speed
    desired=normalize(desired);

    // Steering = Desired minus Velocity
    vec3 steer=desired;
    steer-=vel;
    return steer;
}

// Cohesion
// For the average location (i.e. center) of all nearby boids, calculate steering vector towards that location
vec3 cohesion(vec3 p,vec3 vel){
    float width=resolution.x;
    float height=resolution.y;

    vec3 sum=vec3(0.);
    float count=0.;
    for(int x=0;x<width;x++){
        for(int y=0;y<height;y++){
            vec2 uv=vec2(x,y);

            vec3 pos=texture(posData,uv).xyz;
            vec3 otherVel=texture(velData,uv).xyz;

            float d=distance(p,pos);

            if((d>0.)&&(d<cohesionDistance)){
                sum+=pos;
                count=count+1.;
            }
        }
    }
    if(count>0.){
        sum/=count;
        return seek(p,vel,sum);// Steer towards the location
    }else{
        return vec3(0., 0., 0.);
    }
}

vec3 applyForce(vec3 vel,vec3 force){
    // We could add mass here if we want A = F / M
    return vel+force;
}

vec3 flock(vec3 p,vec3 v){
    vec3 sep=separate(p,v);// Separation
    vec3 ali=align(p,v);// Alignment
    vec3 coh=cohesion(p,v);// Cohesion
    // Arbitrarily weight these forces
    // sep*=0.02;
    // ali*=0.02;
    // coh*=0.02;
    // sep*=1.5;
    // ali*=1.0;
    // coh*=1.0;
    // Add the force vectors to acceleration
    v=applyForce(v,sep);
    v=applyForce(v,ali);
    v=applyForce(v,coh);
    return v;
}


void main(void) {

    vec3 pos=texture(posData, vTexCoord).xyz;// ... for gettinh the position data
    vec3 vel=texture(velData, vTexCoord).xyz;// and the velocity

    // Calculates what´s going to be the next position without updating it.
    // Just to see if it collide with the borders of the FBO texture
    //
    vel=flock(pos,vel);
    vel=limit(vel, speed);
    // vec2 nextPos = pos + vel;
    // vel = checkEdges(nextPos, vel);
    pos += vel;
    if (pos.x > 1.0) {
        pos.x = 0.;
    }
    if (pos.x < 0){
        pos.x= 1.;
    }
    if (pos.y > 1.){
        pos.y= 0.;
    }
    if (pos.y < 0.){
        pos.y= 1.;
    }
    if (pos.z > 1.) {
        pos.z = 0;
    }
    if (pos.z < 0.) {
        pos.z = 1.;
    }


    vFragColor0=vec4(pos,1.);
    vFragColor1=vec4(vel,1.);
}
