using UnityEngine;
using System.Collections;
using Unicessing;

public class tree3d : UGraphics {
    public int randSeed = 10;
    float treeAngle;
    float startLen;
    protected override void Setup()
    {
        stroke(255);
        treeAngle = radians(30.0f);
        startLen = 8.0f;
    }
    protected override void Draw()
    {
        Vector3 pos1 = new Vector3(0.0f,0.0f,0.0f);
        tree(pos1,randSeed);
    }
    private void tree(Vector3 p,int _rs){
        randomSeed(_rs);
        pushMatrix();
        translate(p);
        rotateZ(radians(random(10.0f)));
        rotateY(radians(random(360.0f)));
        line(0, 0, 0, startLen);
        translate(0,startLen);
        treeGrow(startLen);
        popMatrix();
    }
    private void treeGrow(float h) {
        h *= 0.66f;
        if (h > 0.15)
        {
            float temp1 = h;
            temp1 *= random(0.75f,1.45f);
            pushMatrix();
            rotateZ(treeAngle+radians(random(-20.0f,20.0f)));
            rotateY(radians(random(-90.0f,90.0f)));
            line(0, 0, 0, temp1);
            translate(0, temp1);
            treeGrow(temp1);
            popMatrix();
            float temp2 = h;
            temp2 *= random(0.75f,1.45f);
            pushMatrix();
            rotateZ(-treeAngle+radians(random(-20.0f,20.0f)));
            rotateY(radians(random(-90.0f,90.0f)));
            line(0, 0, 0, temp2);
            translate(0, temp2);
            treeGrow(temp2);
            popMatrix();
        }
    }
}
