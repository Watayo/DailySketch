#version 150
precision mediump float;

uniform sampler2DRect posData;
uniform sampler2DRect velData;

uniform vec2 resolution;

uniform float separationDistance; // 20 -> 0.01?
uniform float alignmentDistance; // 40 -> 0.02?
uniform float cohesionDistance; //

//uniform float maxspeed;
//uniform float maxforce;
uniform vec2 mouse;
uniform float time;

in vec2 vTexCoord;

out vec4 vFragColor0;
out vec4 vFragColor1;

const float SPEED = 0.1;
const float FORCE = 0.1;

// vector utils
vec2 limit(vec2 v,float m){
    float lengthSquared=v.x*v.x+v.y*v.y;
    if(lengthSquared>m*m&&lengthSquared>0.){
        float ls=sqrt(lengthSquared);
        float ratio=m/ls;
        v*=ratio;
    }
    return v;
}

// Separation
// Method checks for nearby boids and steers away
vec2 separate(vec2 p,vec2 v){
    float width=resolution.x;
    float height=resolution.y;

    vec2 steer=vec2(0.,0.);
    float count=0.;

    // For every boid in the system, check if it's too close
    for(int x=0;x<width;x++){
        for(int y=0;y<height;y++){
            vec2 uv=vec2(x,y);
            // vec2 uv=vec2(x+.5,y+.5);
            // vec2 uv = vec2(x + 0.5,y + 0.5)/resolution.xy;
            vec2 pos=texture(posData, uv).xy;

            float d=distance(p,pos);

            // If the distance is greater than 0 and less than an arbitrary amount (0 when you are yourself)
            if((d>0.)&&(d<separationDistance)){
                // Calculate vector pointing away from neighbor
                vec2 diff=p;
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

    // As long as the vector is greater than 0
    if(length(steer)>0.){
        // Implement Reynolds: Steering = Desired - Velocity
        steer=normalize(steer);
        steer*=(SPEED);
        // steer/=v;
        steer=limit(steer,FORCE);
    }
    return steer;
}

// Alignment
// For every nearby boid in the system, calculate the average velocity
vec2 align(vec2 p,vec2 v){
    float width=resolution.x;
    float height=resolution.y;

    vec2 sum=vec2(0.,0.);
    float count=0.;
    for(int x=0;x<width;x++){
        for(int y=0;y<height;y++){
            vec2 uv=vec2(x,y);
            // vec2 uv=vec2(x+.5,y+.5);
            // vec2 uv=vec2(x+.5,y+.5)/resolution.xy;
            vec2 pos=texture(posData,uv).xy;
            vec2 otherVel=texture(velData, uv).xy;

            float d=distance(p,pos);

            if((d>0)&&(d<alignmentDistance)){
                sum.x+=otherVel.x;
                sum.y+=otherVel.y;
                count=count+1.;
            }
        }
    }
    if(count>0.){
        sum/=(count);
        // sum=normalize(sum);
        sum*=(SPEED);
        sum *= 10000.0;
        vec2 steer=sum-v;
        steer=limit(steer,FORCE);
        return steer;
    }else{
        return vec2(0.,0.);
    }
}

vec2 seek(vec2 p,vec2 vel,vec2 target){
    vec2 desired=target;// A vector pointing from the location to the target
    desired-=p;

    // Normalize desired and scale to maximum speed
    desired=normalize(desired);
    desired*=(SPEED);

    // Steering = Desired minus Velocity
    vec2 steer=desired;
    steer-=vel;
    steer=limit(steer,FORCE);// Limit to maximum steering force
    return steer;
}

vec2 seekForce(vec2 p,vec2 vel,vec2 target){
    vec2 desired=target;// A vector pointing from the location to the target
    desired-=p;

    // Normalize desired and scale to maximum speed
    desired=normalize(desired);

    // Steering = Desired minus Velocity
    vec2 steer=desired;
    steer-=vel;
    return steer;
}

// Cohesion
// For the average location (i.e. center) of all nearby boids, calculate steering vector towards that location
vec2 cohesion(vec2 p,vec2 vel){
    float width=resolution.x;
    float height=resolution.y;

    vec2 sum=vec2(0.,0.);
    float count=0.;
    for(int x=0;x<width;x++){
        for(int y=0;y<height;y++){
            vec2 uv=vec2(x,y);
            // vec2 uv=vec2(x+.5,y+.5);
            // vec2 uv=vec2(x+.5,y+.5)/resolution.xy;
            vec2 pos=texture(posData,uv).xy;
            vec2 otherVel=texture(velData,uv).xy;

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
        return vec2(0.,0.);
    }
}

vec2 applyForce(vec2 vel,vec2 force){
    // We could add mass here if we want A = F / M
    return vel+force;
}

vec2 flock(vec2 p,vec2 v){
    vec2 sep=separate(p,v);// Separation
    vec2 ali=align(p,v);// Alignment
    vec2 coh=cohesion(p,v);// Cohesion
    // Arbitrarily weight these forces
    sep*=0.02;
    ali*=0.02;
    coh*=0.02;

    // Add the force vectors to acceleration
    v=applyForce(v,sep);
    v=applyForce(v,ali);
    v=applyForce(v,coh);
    return v;
}


vec2 checkEdges(vec2 p,vec2 v){
    if(p.x<0.||p.x>1.){
        v.x*=-1;
    }
    if(p.y<0.||p.y>1.){
        v.y*=-1;
    }
    return v;
}
void main(void) {

    vec2 pos=texture(posData, vTexCoord).xy;// ... for gettinh the position data
    vec2 vel=texture(velData, vTexCoord).xy;// and the velocity

    // Calculates what´s going to be the next position without updating it.
    // Just to see if it collide with the borders of the FBO texture
    //
    vel=flock(pos,vel);
    // vec2 nextPos = pos + vel;
    // vel = checkEdges(nextPos, vel);
    pos += vel;
    if (pos.x > 1.0) {
        pos.x = 0.;
    }
    if (pos.x<0.){
        pos.x=1.;
    }
    if (pos.y>1.){
        pos.y=0.;
    }
    if (pos.y<0.){
        pos.y=1.;
    }

    vFragColor0=vec4(pos,1.,1.);
    vFragColor1=vec4(vel,1.,1.);
}
