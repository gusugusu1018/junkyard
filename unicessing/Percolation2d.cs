using UnityEngine;
using System.Collections;
using System.Collections.Generic;
using Unicessing;

public class Percolation2d : UGraphics {
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
            int k2 = (int)(random(Length));
            int k3 = (int)(random(Length));
            //k4,k5は速度ベクトル
            int k4 = 0;
            int k5 = 0;
            if(k1 == 1){
                k4 = 3 - (int)(random(5));
                if(k4 == 0) k4 = 1;
                k5 = 3 - (int)(random(5));
                if(k5 == 0) k5 = 1;
            }
            else{
                k4 = 2 - (int)(random(4));
                if(k4 == 0) k4 = 1;
                k5 = 2 - (int)(random(4));
                if(k5 == 0) k5 = 1;
            }
            humans.Add(new Human(k1,k2,k3,k4,k5,Length));
        }

    }

    protected override void Draw()
    {
        //人間を描画
        foreach (Human human in humans) {
            noLights ();
            if (human.condition == 1) fill(200);
            else fill(255,125,125);
            Vector3 pos = new Vector3(human.xpos,human.ypos,0.0f);
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
        static int[,] MAP;
        public int condition; //健康かそれとも病気かのパラメータ
        public int xpos; //x座標
        public int ypos; //y座標
        int xvel; //x方向の速さ
        int yvel; //y方向の速さ
        int Length;
        public Human(int c, int xp, int yp, int xv, int yv,int len) {
            xpos = xp;
            ypos = yp;
            xvel = xv;
            yvel = yv;
            condition = c;
            Length = len;
            MAP = new int[Length,Length];
            for(int i=0; i< Length; i++){
                for(int j=0; j< Length; j++){
                    MAP[i,j] = 0;
                }
            }
        }

        //もし健康ならば青、病気ならば赤を描画

        public void drive () {
            MAP[xpos,ypos] = 0;
            xpos = (xpos + xvel + Length) % Length;
            ypos = (ypos + yvel + Length) % Length;
            MAP[xpos,ypos] = condition;  
        }
        
        //衝突判定を行う部分
        public void coll () {
            for(int i = -2; i < 3; i++){
                for(int j = -2; j < 3; j++){
                    if ((MAP[(xpos+i+Length)%Length,(ypos+j+Length)%Length] > 0) && (i != 0) && (j != 0)){
                        xvel = -xvel;
                        yvel = -yvel;
                        if(MAP[(xpos+i+Length)%Length,(ypos+j+Length)%Length] == 2){
                            condition = 2;
                        }
                    }
                }
            }
        }
    }
}