/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Disparo.h
 * Author: juli
 *
 * Created on 24 de marzo de 2017, 23:14
 */

#ifndef DISPARO_H
#define DISPARO_H
#include <SFML/Graphics.hpp>

class Disparo{
public:
    Disparo(sf::Vector2f size){
        disparo.setSize(size);
        disparo.setFillColor(sf:: Color::Blue);
    }
    void cadenciaDisparo(int speed){
        disparo.move(speed,0);
    }

    int getDerecha(){
        return disparo.getPosition().x + disparo.getSize().x;
    }

    int getIzquierda(){
        return disparo.getPosition().x;
    }
    int getArriba(){
        return disparo.getPosition().y;
    }
    int getAbajo(){
        return disparo.getPosition().y + disparo.getSize().y;
    }

    void draw(sf::RenderWindow &window){
        window.draw(disparo);
    }
    
    void setPos(sf::Vector2f(newPos)){
        disparo.setPosition(newPos);
    }
        
    private:
        sf::RectangleShape disparo;
        
};


#endif /* DISPARO_H */

