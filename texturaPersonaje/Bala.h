/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Bala.h
 * Author: juli
 *
 * Created on 25 de marzo de 2017, 11:47
 */

#ifndef BALA_H
#define BALA_H
#include <SFML/Graphics.hpp>

class Bala:public sf::Drawable {
public:
    Bala(int x,int y);
    Bala(const Bala& orig);
    virtual ~Bala();
    
    void disparar();
    void colisionar();
    void setPosicion();
    void actualiza();
    int getX();
    int getY();
        
private:
    int posx;
    int posy;
    int velx;
    int vely;
    float velocidad = 3.0;
    sf::Texture textura;
    sf::Sprite sprite;
    
    virtual void draw(sf::RenderTarget& sf::RenderStates states)const;
};

#endif /* BALA_H */
