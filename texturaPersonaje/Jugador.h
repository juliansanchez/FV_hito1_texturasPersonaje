/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Jugador.h
 * Author: juli
 *
 * Created on 24 de marzo de 2017, 23:30
 */

#ifndef JUGADOR_H
#define JUGADOR_H
#include <SFML/Graphics.hpp>

class Jugador{
public:
    Jugador(sf::Vector2f size){
        jugador.setScale(size);
        jugador.setFillColor(sf::Color::Green);
    }
    
    void move(sf:: Vector2f dir){
        jugador.move(dir);
    }
    int getX(){
        return jugador.getPosition().x;
    }
    int getY(){
        return jugador.getPosition().y;
    }
    void draw(sf::RenderWindow &window){
        window.draw(jugador);
    }
    
private:
    sf::RectangleShape jugador;
};


#endif /* JUGADOR_H */

