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
#include "Bala.h"

#include <stdio.h>
#include <iostream>



Bala::Bala(int x,int y,int velx, int vely) {
    posx = x;
    posy = y; 
    this->velx=velx;
    this->vely=vely;
    destruirBala = false;
    clock.restart();
    
    if(!textura.loadFromFile("resources/bala.png")){
        std::cerr << "Error while loading texture ISAAC" << std::endl;
        return;
    };
    
    sprite = sf::Sprite(textura);
    sprite.setTextureRect(sf::IntRect(16, 16, 32, 32));
    sprite.setScale(0.5,0.5);
}

Bala::~Bala() {}

void Bala::setPosicion(int x, int y){       }
void Bala::colisionar(){       }

void Bala::actualiza(){
    posx+=velx;
    posy+=vely;
    
        
    if(clock.getElapsedTime().asSeconds()< 3){
        sprite.setPosition(posx,posy);
    }
    else
        destruirBala = true;
        
    
}
int Bala::getX(){
    return posx;
}

int Bala::getY(){
    return posy;
}
void Bala::draw(sf::RenderTarget& target, sf::RenderStates states)const{
    target.draw(sprite,states); 
}