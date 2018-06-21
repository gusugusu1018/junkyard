using UnityEngine;
using System.Collections;
using Unicessing;

public class forest : UGraphics {
    public int randSeed1 = 7;
    public int randSeed2 = 10;
    public int randSeed3 = 10;

    float treeAngle;
    float startLen;

    protected override void Setup()
    {
        stroke(255);
        //treeAngle = radians(24.0f);
        treeAngle = radians(30.0f);
        startLen = 8.0f;
    }

    protected override void Draw()
    {
        Vector3 pos1 = new Vector3(0.0f,0.0f,0.0f);
        tree(pos1,randSeed1);
        Vector3 pos2 = new Vector3(10.0f,0.0f,30.0f);
        tree(pos2,randSeed2);
        Vector3 pos3 = new Vector3(-10.0f,0.0f,25.0f);
        tree(pos3,randSeed3);
        Vector3 pos4 = new Vector3(8.0f,0.0f,2.0f);
        tree(pos1,randSeed1);
        Vector3 pos5 = new Vector3(3.0f,0.0f,5.0f);
        tree(pos2,randSeed2);
        Vector3 pos6 = new Vector3(-3.0f,0.0f,14.0f);
        tree(pos3,randSeed3);
    }
    private void tree(Vector3 p,int _rs){
        randomSeed(_rs);
        pushMatrix();    // Save the current state of transformation (i.e. where are we now)
        translate(p);
        rotateZ(radians(random(10.0f)));
        rotateY(radians(random(360.0f)));
        line(0, 0, 0, startLen);
        translate(0,startLen);
        treeGrow(startLen);
        popMatrix();     // Whenever we get back here, we "pop" in order to restore the previous matrix state
    }
    
    private void treeGrow(float h) {
        // Each branch will be 2/3rds the size of the previous one
        h *= 0.66f;
        // All recursive functions must have an exit condition!!!!
        // Here, ours is when the length of the branch is 2 pixels or less
        if (h > 0.2)
        {
            float temp1 = h;
            temp1 *= random(0.75f,1.45f);
            pushMatrix();    // Save the current state of transformation (i.e. where are we now)
            //rotate(treeAngle+radians(random(-20.0f,20.0f)));   // Rotate by theta
            rotateZ(treeAngle+radians(random(-20.0f,20.0f)));   // Rotate by theta
            rotateY(radians(random(-90.0f,90.0f)));
            //rotate(0.0f,radians(random(-90.0f,90.0f)),treeAngle+radians(random(-20.0f,20.0f)));   // Rotate by theta
            line(0, 0, 0, temp1);  // Draw the branch
            translate(0, temp1); // Move to the end of the branch
            treeGrow(temp1);       // Ok, now call myself to draw two new branches!!
            popMatrix();     // Whenever we get back here, we "pop" in order to restore the previous matrix state

            float temp2 = h;
            temp2 *= random(0.75f,1.45f);
            // Repeat the same thing, only branch off to the "left" this time!
            pushMatrix();
            //rotate(-treeAngle+radians(random(-20.0f,20.0f)));
            rotateZ(-treeAngle+radians(random(-20.0f,20.0f)));
            rotateY(radians(random(-90.0f,90.0f)));
            //rotate(0.0f,radians(random(-90.0f,90.0f)),-treeAngle+radians(random(-20.0f,20.0f)));
            line(0, 0, 0, temp2);
            translate(0, temp2);
            treeGrow(temp2);
            popMatrix();
        }
    }
}
