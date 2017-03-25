/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Enemigo.h
 * Author: juli
 *
 * Created on 24 de marzo de 2017, 23:34
 */

#ifndef ENEMIGO_H
#define ENEMIGO_H
#include <SFML/Graphics.hpp>

#include "Disparo.h"

class Enemigo{
public:
    Enemigo(sf::Vector2f size){
        enemigo.setSize(size);
        enemigo.setFillColor(sf::Color::Red);
    }
    void setPos(sf::Vector2f nuevaPos){
        enemigo.setPosition(nuevaPos);
    }
    void checkColision(Disparo disparo){
        if(disparo.getDerecha() > enemigo.getPosition().x && 
                disparo.getArriba() < enemigo.getPosition().y + enemigo.getSize().y
                && disparo.getAbajo() > enemigo.getPosition().y){
            
            enemigo.setPosition(sf::Vector2f(4234432,4234432));
            
        }
    }
    void draw(sf::RenderWindow &window){
        window.draw(enemigo);
    }

private:
    sf::RectangleShape enemigo;
            
};


#endif /* ENEMIGO_H */

