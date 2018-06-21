using UnityEngine;
using System.Collections;
using System.Collections.Generic;
using Unicessing;

public class Boid : UGraphics{
    public Vector3 location;
    public Vector3 velocity;
    Vector3 acceleration;
    float maxforce;
    float maxspeed;
    float sepWeight;
    float aliWeight;
    float cohWeight;
    public Boid(float x, float y, float z){
        acceleration = new Vector3(0, 0, 0);
        float angle1 = random(PI);
        float angle2 = random(TWO_PI);
        velocity = new Vector3(sin(angle1) * cos(angle2), sin(angle1) * sin(angle2), cos(angle1));
        location = new Vector3(x, y, z);
    }
    void boidConfig(float sepW,float aliW,float cohW,float maxF,float maxS){
        sepWeight = sepW;
        aliWeight = aliW;
        cohWeight = cohW;
        maxforce = maxF;
        maxspeed = maxS;
    }
    public void run(List<Boid> boids,float _sep,float _ali,float _coh,float _for,float _spe){
        boidConfig(_sep,_ali,_coh,_for,_spe);
        flock(boids);
        update();
        borders();
    }   
    void applyForce(Vector3 force){
        acceleration+=force;
    }    
    void flock(List<Boid> boids){
        Vector3 sep = separate(boids);
        Vector3 ali = align(boids);
        Vector3 coh = cohesion(boids);
        sep=sep*sepWeight;
        ali=ali*aliWeight;
        coh=coh*cohWeight;
        applyForce(sep);
        applyForce(ali);
        applyForce(coh);
    }    
    void update(){
        velocity+=acceleration;
        velocity.x=constrain(velocity.x,-maxspeed,maxspeed);
        velocity.y=constrain(velocity.y,-maxspeed,maxspeed);
        velocity.z=constrain(velocity.z,-maxspeed,maxspeed);
        location+=velocity;
        acceleration=Vector3.zero;
    }        
    Vector3 seek(Vector3 target){
        Vector3 desired = target - location;
        desired.Normalize();
        desired*=maxspeed;
        Vector3 steer = desired - velocity;
        steer.x=constrain(steer.x,-maxforce,maxforce);
        steer.y=constrain(steer.y,-maxforce,maxforce);
        steer.z=constrain(steer.z,-maxforce,maxforce);
        return steer;
    }   
    void borders(){
        width = 100.0f;
        height = 100.0f;
        if(location.x > width / 2) location.x = -width / 2;
        if(location.y > height / 2) location.y = -height / 2;
        if(location.z > height / 2) location.z = -height / 2;
        if(location.x < -width / 2) location.x = width / 2;
        if(location.y < -height / 2) location.y = height / 2;
        if(location.z < -height / 2) location.z = height / 2;
    }    
    Vector3 separate(List<Boid> boids){
        float desiredseparation = 25.0f;
        Vector3 steer = Vector3.zero;
        int count = 0;
        foreach(Boid other in boids){
            float d = Vector3.Distance(location,other.location);
            if((d > 0) && (d < desiredseparation)){
                Vector3 diff = location - other.location;
                diff.Normalize();
                diff/=d;
                steer+=diff;
                count++;
            }
        }
        if(count > 0) steer/=(float)count;
        if(steer.magnitude > 0){
            steer.Normalize();
            steer*=maxspeed;
            steer-=velocity;
            steer.x=constrain(steer.x,-maxforce,maxforce);
            steer.y=constrain(steer.y,-maxforce,maxforce);
            steer.z=constrain(steer.z,-maxforce,maxforce);
        }
        return steer;
    }
    Vector3 align(List<Boid> boids){
        float neighbordist = 50;
        Vector3 sum = Vector3.zero;
        int count = 0;
        foreach(Boid other in boids){
            float d = Vector3.Distance(location, other.location);
            if((d > 0) && (d < neighbordist)){
                sum+=other.velocity;
                count++;
            }
        }
        if(count > 0){
            sum/=(float)count;
            sum.Normalize();
            sum*=maxspeed;
            Vector3 steer = sum - velocity;
            steer.x=constrain(steer.x,-maxforce,maxforce);
            steer.y=constrain(steer.y,-maxforce,maxforce);
            steer.z=constrain(steer.z,-maxforce,maxforce);
            return steer;
        } else {
            return Vector3.zero;
        }
    }
    Vector3 cohesion(List<Boid> boids){
        float neighbordist = 50;
        Vector3 sum = Vector3.zero;
        int count = 0;
        foreach (Boid other in boids) {
            float d = Vector3.Distance(location, other.location);
            if((d > 0) && (d < neighbordist)){
                sum+=other.location;
                count++;
            }
        }
        if(count > 0){
            sum/=count;
            return seek(sum);
        } else{
            return Vector3.zero;
        }
    }
}
