using UnityEngine;
using System.Collections;
using Unicessing;

public class tree : UGraphics {
    float treeAngle;
    float startLen;

    protected override void Setup()
    {
        stroke(255);
        treeAngle = radians(24.0f);
        startLen = 8;
    }

    protected override void Draw()
    {
        line(0, 0, 0, startLen);
        translate(0,startLen);
        randomSeed(0);
        treeGrow(startLen);
    }
    
    private void treeGrow(float h) {
        // Each branch will be 2/3rds the size of the previous one
        h *= 0.66f;
        // All recursive functions must have an exit condition!!!!
        // Here, ours is when the length of the branch is 2 pixels or less
        if (h > 0.15)
        {
            h *= random(0.5f,1.5f);
            pushMatrix();    // Save the current state of transformation (i.e. where are we now)
            rotate(treeAngle+radians(random(-20.0f,20.0f)));   // Rotate by theta
            line(0, 0, 0, h);  // Draw the branch
            translate(0, h); // Move to the end of the branch
            treeGrow(h);       // Ok, now call myself to draw two new branches!!
            popMatrix();     // Whenever we get back here, we "pop" in order to restore the previous matrix state

            // Repeat the same thing, only branch off to the "left" this time!
            h *= random(0.5f,1.5f);
            pushMatrix();
            rotate(-treeAngle+radians(random(-20.0f,20.0f)));
            line(0, 0, 0, h);
            translate(0, h);
            treeGrow(h);
            popMatrix();
        }
    }
}
