/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Bala.cpp
 * Author: juli
 * 
 * Created on 25 de marzo de 2017, 11:47
 */

#include <stdio.h>
#include "Bala.h"


Bala::Bala(int x,int y) {
    posx = x;
    posy = y; 
    if(!textura.loadFromFile("resources/bala.png")){
        std::cerr << "Error while loading texture ISAAC" << std::endl;
        return -1;
    };
    
    sprite.setTextureRect(textura);
    sprite.setTextureRect(sf::IntRect(16, 16, 32, 32));
    
    

}

Bala::~Bala() {
}

void Bala::setPosicion(int x, int y){
         
}

void Bala::actualiza(){
    posx+=velx;
    posy+=vely;
}
int Bala::getX(){
    return posx;
}

int Bala::getY(){
    return posy;
}
virtual void Bala::draw(sf::RenderTarget& sf::RenderStates states)const{
    target.draw(*sprite,states);
    
}