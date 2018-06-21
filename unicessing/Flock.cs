using UnityEngine;
using System.Collections;
using System.Collections.Generic;
using Unicessing;

public class Flock : UGraphics {
    float sepWeight = 0.7f;
    float aliWeight = 1.0f;
    float cohWeight = 1.0f;
    float maxforce = 0.05f;
    float maxspeed = 0.5f;
    List<Boid> boids;
    int boidNums=300;
    GameObject agentPrefab;
    List<GameObject> agentObjs = new List<GameObject>();
    protected override void Setup()
    {
        boids = new List<Boid>();
        for(int i = 0; i < boidNums; i++){
            boids.Add(new Boid(random(10.0f),random(10.0f),random(10.0f)));
        }
        agentPrefab = loadPrefab("Unicessing/Prefabs/Cube");
        for (int i = 0; i < boidNums; i++)
        {
            agentObjs.Add( createObj(agentPrefab) );
        }

    }
    protected override void Draw()
    {
        float t = modulo(frameSec * 1.0f, 20.0f);
        if (t < 2) cohWeight = 0.0f;
        else if (t < 10) cohWeight = 1.0f;
        else if (t < 15) cohWeight = 0.0f;
        else if (t < 18)cohWeight = 2.0f;
        else cohWeight = 1.2f;
        fill(color(128, 255, 128));
        int i =0;
        foreach (Boid boid in boids) {
            boid.run(boids,sepWeight,aliWeight,cohWeight,maxforce,maxspeed);
            pushMatrix();
            translate(boid.location.x, boid.location.y, boid.location.z);
            rotateZ(atan2(boid.velocity.y, boid.velocity.x) + HALF_PI);
            rotateY(atan2(boid.velocity.x, boid.velocity.z) + HALF_PI);
            float r = 0.1f;
            draw(agentObjs[i],Vector3.zero,Vector3.one*0.01f);
            popMatrix();
            i++;
        }
    }
}
