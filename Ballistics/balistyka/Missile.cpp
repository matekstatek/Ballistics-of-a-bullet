//
//  Missile.cpp
//  balistyka
//
//  Created by Matek on 10.01.2018.
//  Copyright © 2018 Matek. All rights reserved.
//

#include "Missile.hpp"
#include "File.hpp"
#include <math.h>
#include <iostream>

#define g 9.81
#define PI 3.1415926f
#define tInc 0.01
#define RHO 1.225f

File file;

void Missile::data(){ // 910 55 4.7 200 0.07 6 30 0
    std::cout << "Predkosc poczatkowa [m/s]: ";
    std::cin >> Vm;
    
    std::cout << "Kat nachylenia od pionu: ";
    std::cin >> Alpha;
    
    std::cout << "Dlugosc lufy [m]: ";
    std::cin >> L;
    
    std::cout << "Liczba obrotow na minute: ";
    std::cin >> spin;
    
    std::cout << "Promien pocisku [m]: ";
    std::cin >> radius;
    
    std::cout << "Masa pocisku [kg]: ";
    std::cin >> m;
    
    std::cout << "Predkosc wiatru [m/s]: ";
    std::cin >> Vw;
    
    std::cout << "Kierunek wiatru: ";
    std::cin >> GammaW;
}

void Missile::doSimulation(){
    
    double cosX;
    double cosY;
    double cosZ;
    double xe, ze;
    double b, Lx, Ly, Lz;
    
    double sx1, vx1;
    double sy1, vy1;
    double sz1, vz1;
    
    file.oss.str("");
    file.oss.clear();
    
    omega = 2*PI*spin/60;           //obrót [rad/s]
    
    V1.i = Vm * cos(Alpha * PI/180)/100;    //składowa x Vp
    V1.j = Vm * sin(Alpha * PI/180)/100;    //składowa y Vp
    
    for(; (s2.j >= 0); Time += tInc){
        double C = PI * RHO * RHO * pow(radius, 3) * omega;
        double t;
        
        t = Time;
        
        /* obliczenia do uwzględnienia efektu magnusa   */
        V2.i = 1.0f/(1.0f-(t/m)*(t/m)*C*C) * (V1.i + C * V1.j * (t/m) - C * g * (t*t)/m);
        V2.j = V1.j + (t/m)*C*V2.i - g*t;
        
        /*          obliczenia rzutu                    */
        b = L * cos((90-Alpha) *3.14/180);
        Lx = b * cos(Gamma * 3.14/180);
        Ly = L * cos(Alpha * 3.14/180);
        Lz = b * sin(Gamma * 3.14/180);
        
        cosX = Lx/L;
        cosY = Ly/L;
        cosZ = Lz/L;
        
        xe = L * cos((90-Alpha) *3.14/180) * cos(Gamma * 3.14/180);
        ze = L * cos((90-Alpha) *3.14/180) * sin(Gamma * 3.14/180);
        
        sx1 = xe;
        vx1 = Vm * cosX;
        sy1 = Yb + L + cos(Alpha * 3.14/180);
        vy1 = Vm * cosY;
        sz1 = ze;
        vz1 = Vm * cosZ;
        
        /*      punkt określający położenie pocisku
                uwzględniając ruch oraz wiatr           */
        s.i = ((m/Cd) * exp(-(Cd * Time)/m) * ((-Cw * Vw) * cos(GammaW* 3.14/180)/Cd - vx1) -
                (Cw * Vw * cos(GammaW * 3.14/180)* Time)/Cd) -
                ((m/Cd)*((-Cw*Vw*cos(GammaW*3.14/180))/Cd-vx1)) + sx1;
        
        s.j = sy1 + (-(vy1 + (m * g)/Cd) * (m/Cd) * exp(-(Cd * Time)/m) -
                (m*g*Time)/Cd )+((m/Cd)*(vy1+(m*g)/Cd));
        
        s.k = ((m/Cd) * exp (-(Cd * Time)/m) * ((-Cw * Vw * sin (GammaW* 3.14/180))/Cd - vz1) -
                (Cw * Vw * sin(GammaW * 3.14/180) * Time) / Cd ) -
                ((m/Cd) * ((-Cw * Vw * sin(GammaW * 3.14/180))/Cd - vz1) ) + sz1;
        
        /*          poprawka o efekt magnusa            */
        s2.i = s.i + V1.i * t + (1.0f/2.0f) * (C/m * V2.j) * (t*t);
        s2.j = s.j + V1.j * t + (1.0f/2.0f) * ( ((C*V2.i) - m*g)/m) * (t*t);
        
        /*          zapis do pliku                      */
        file.oss <<  s2.i << "\t" << s2.j << "\t" << s.k << std::endl;
    }
    file.saveToFile(file.oss.str());
}
