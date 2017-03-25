/*!
 * \file    main.cpp
 * \brief   Sprite del personaje y animacion
 * \author  juli
 */

// SFML libraries
#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdio.h>

using namespace std;

// Sprite speed (high values = high speed)
#define SPRITE_SPEED  1

int main()
{

    float velocidad = 5;
    int contadorPasos = 2;
    // ::: VENTANA PRINCIPAL :::
    sf::RenderWindow window(sf::VideoMode(720, 540), "Hito 1: animacion personaje");
 
    // ::: Creamos y cargamos las texturas :::
    sf::Texture texture;
    if (!texture.loadFromFile("resources/isaacAzul.png"))
    {
        std::cerr << "Error while loading texture" << std::endl;
        return -1;
    }
    
    sf::Sprite personaje(texture);
    personaje.setPosition(window.getSize().x/2,window.getSize().y/2);
    personaje.setTextureRect(sf::IntRect(0,0,32,32));
   
 
      
    // ::: INICIO LOOP :::
    while (window.isOpen())
    {
        // Proceso de eventos
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Cerrar ventana
            if (event.type == sf::Event::Closed) 
                window.close();

            // Si pulsamos una tecla
            if (event.type == sf::Event::KeyPressed)
            {
                switch (event.key.code)
                {
                // Para cerrar la ventana con ESC
                case  sf::Keyboard::Escape : window.close(); break;

                // Teclas  up, down, left and right keys
                case sf::Keyboard::W : // ARRIBA     
                    personaje.move(0,-velocidad);
                    personaje.setTextureRect(sf::IntRect(32*4,0,32,32));
                    
                    break;
                    
                case sf::Keyboard::S:// ABAJO
                    personaje.move(0,velocidad);
                    personaje.setTextureRect(sf::IntRect(32*1,0,32,32));
                    
                    break;
                    
                case sf::Keyboard::A: // IZDA   
                   personaje.move(-velocidad,0);
                   personaje.setTextureRect(sf::IntRect(32*2,0,32,32));
                   personaje.setScale(-1,1);
                    
                    break;
                            
                case sf::Keyboard::D: // DERECHA
                    personaje.move(velocidad,0);
                    personaje.setTextureRect(sf::IntRect(contadorPasos*32,0,32,32));
                    contadorPasos++;
                    if(contadorPasos == 4){
                        contadorPasos = 2;
                    }
                    break;
                    
                default : break;
                }
                
            }

            // Si no pulsamos ninguan tecla
            if (event.type == sf::Event::KeyReleased)
            {
                                
                

              
            }
        }



        
        
        // Limpiamos la ventana y aplicamos un color de fondo 
        window.clear( sf::Color(127,127,127));
       
        
        
        window.draw(personaje);
 

        // Actualizar mostrar por pantalla
        window.display();
    }
    return 0;
}
