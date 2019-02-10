//
//  Missile.hpp
//  balistyka
//
//  Created by Matek on 10.01.2018.
//  Copyright © 2018 Matek. All rights reserved.
//

#ifndef Missile_hpp
#define Missile_hpp
#include <stdio.h>

class Missile
{
    typedef struct TVectorTag
    {
        double i;
        double j;
        double k;
    } TVector;
    
    double Vm;          //prędkość początkowa
    double Alpha;       //kąt między osią Y i działem
    double Gamma = 0;   //kąt od osi X do działa (dodatnie wartości przesuwają w stronę Z)
    double L;           //długość działa
    double Yb = 0;      //wysokość umieszczenia podstawy działa
    
    double X;       //
    double Y;       //
    double Z;       //
    
    TVector s;
    TVector V1;
    TVector V2;
    TVector s1;
    TVector s2;
    
    double spin = 200;      //obroty na minute
    double omega;           //obroty w [rad/s]
    double radius = 0.1;          //promień pocisku
    
    double m = 6;       //masa pocisku [kg]
    double Cd = 0.2;        //współczynnik oporu
    double Vw = 10;         //prędkość wiatru [m/s]
    double Cw = 1;        //współczynnik oporu
    double GammaW = 35;     //kierunek wiatru [stopnie]
    
    double Time;            //czas od chwili wylotu pocisku
    
public:
    void doSimulation();
    void data();
};

#endif /* Missile_hpp */
