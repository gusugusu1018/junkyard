using UnityEngine;
using System.Collections;
using Unicessing;

public class lorenz : UGraphics {
    public Transform Sphere;
    Vector3 pos;
    Vector3 vel;
    float dt = 0.01f;
    float sigma = 10.0f;
    float beta = 8.0f/3.0f;
    float rohm = 28.0f;
    protected override void Setup()
    {
        pos = new Vector3(0.1f,0,0);
    }

    protected override void Draw()
    {
        vel.x = sigma * (pos.y - pos.x);
        vel.y = pos.x * (rohm - pos.z) - pos.y;
        vel.z = pos.x * pos.y - beta * pos.z;
        vel *= dt;
        pos += vel;
        Sphere.position = pos;
    }
}
