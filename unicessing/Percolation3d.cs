using UnityEngine;
using System.Collections;
using System.Collections.Generic;
using Unicessing;

public class Percolation3d : UGraphics {
    List<Human> humans;
    const int humanNums = 100;
    const int Length = 500;
    int normal_number = 0;
    int sick_number = 0;
    const int Sick = 98;
    protected override void Setup()
    {
        humans = new List<Human>();
        for(int i = 0; i < humanNums; i++){
            int k1 = (int)(random(100));
            //乱数を生成し、Sick以下ならば健常者、それ以外なら病気
            if(k1 < Sick) k1 = 1;
            else k1 = 2;
            //動きのための初期設定
            //k2,k3は出現座標
            //k4,k5は速度ベクトル
            int k4 = 0;
            int k5 = 0;
            int k6 = 0;
            if(k1 == 1){
                k4 = 2 - (int)(random(4));
                if(k4 == 0) k4 = 1;
                k5 = 2 - (int)(random(4));
                if(k5 == 0) k5 = 1;
                k6 = 2 - (int)(random(4));
                if(k6 == 0) k6 = 1;
            }
            else{
                k4 = 1 - (int)(random(2));
                if(k4 == 0) k4 = 1;
                k5 = 1 - (int)(random(2));
                if(k5 == 0) k5 = 1;
                k6 = 1 - (int)(random(2));
                if(k6 == 0) k6 = 1;
            }
            Vector3 pos = new Vector3((int)(random(Length)),(int)(random(Length)),(int)(random(Length)));
            Vector3 vel = new Vector3(k4,k5,k6);
            humans.Add(new Human(k1,pos,vel,Length));
        }

    }

    protected override void Draw()
    {
        //人間を描画
        foreach (Human human in humans) {
            noLights ();
            if (human.condition == 1) fill(200);
            else fill(255,125,125);
            Vector3 pos = human.pos;
            box(pos,Vector3.one);
        }

        //人間を動かす
        foreach (Human human in humans) {
            human.drive();
        }
        
        //人間同士の衝突判定
        foreach (Human human in humans) {
            human.coll();
        }
        
        //現在の状況をカウント
        normal_number = 0;
        sick_number = 0;
        foreach (Human human in humans) {
            if(human.condition == 1) normal_number++;
            else sick_number++;
        }
    }

    //人間のクラスを定義
    public class Human
    {
        static int[,,] MAP;
        public int condition; //健康かそれとも病気かのパラメータ
        public Vector3 pos;
        public Vector3 vel;
        int Length;
        public Human(int c, Vector3 p, Vector3 v,int len) {
            pos = p;
            vel = v;
            condition = c;
            Length = len;
            MAP = new int[Length,Length,Length];
            for(int i=0; i< Length; i++){
                for(int j=0; j< Length; j++){
                    for(int k=0; k< Length; k++){
                        MAP[i,j,k] = 0;
                    }
                }
            }
        }

        //もし健康ならば青、病気ならば赤を描画
        public void drive () {
            MAP[(int)(pos.x),(int)(pos.y),(int)(pos.z)] = 0;
            pos.x = (pos.x + vel.x + Length)%Length;
            pos.y = (pos.y + vel.y + Length)%Length;
            pos.z = (pos.z + vel.z + Length)%Length;
            MAP[(int)(pos.x),(int)(pos.y),(int)(pos.z)] = condition;
        }
        
        //衝突判定を行う部分
        public void coll () {
            for(int i = -2; i < 3; i++){
                for(int j = -2; j < 3; j++){
                    for(int k = -2; k < 3; k++){
                        int temp = MAP[((int)(pos.x)+i+Length)%Length,((int)(pos.y)+j+Length)%Length,((int)(pos.z)+k+Length)%Length];
                        if ((temp > 0) && (i != 0) && (j != 0) && (k != 0)){
                            vel = -vel;
                            if(temp == 2){
                                condition = 2;
                            }
                        }
                    }
                }
            }
        }
    }
}