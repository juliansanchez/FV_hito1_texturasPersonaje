/*!
 * \file    main.cpp
 * \brief   move a sprite with the keyboard (http://www.lucidarme.me/?p=6127)
 * \author  Philippe Lucidarme
 * Sprite del personaje y animacion: JULIAN SANCHEZ GARCIA 
 */

// SFML libraries
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Bala.h"
#include <vector>
// Sprite speed (high values = high speed)
#define SPRITE_SPEED  1
using namespace std;
// control direccion de disparo

enum{
    Arriba = 0,
    Abajo  = 1,
    Izda = 2,
    Decha = 3,
};

int main()
{
    // ::: VENTANA PRINCIPAL :::
    // variable para animar los FRAMES de piernas
    int contadorPasos = 0;
    
    int altoPantalla = 540;
    int anchoPantalla = 900;
    //Creamos una ventana 
    sf::RenderWindow window(sf::VideoMode(anchoPantalla, altoPantalla), "Hito 1: animacion personaje");
    // Enable vertical sync. (vsync)
    window.setVerticalSyncEnabled (true);
    window.setFramerateLimit(60);
    // When a key is pressed, sf::Event::KeyPressed will be true only once
    window.setKeyRepeatEnabled(false);

    // ::: Creamos y cargamos las texturas :::
    sf::Texture texture;
    
    if (!texture.loadFromFile("resources/isaacAzul.png"))
    {
        std::cerr << "Error while loading texture ISAAC" << std::endl;
        return -1;
    }
    
    int x=window.getSize().x/2;
    int y=window.getSize().y/2;
    
    std::vector<Bala*> balas;
    // velocidad de bala
    int velx = 0;
    int vely = 0;
    float rangoDisparo = 1.5;  
    
    int dispara = 0;
    // control direccion de disparo
    int direccionDisparo=Decha;
    
        
    int tamCabeza = 32;
    int radioCabeza = tamCabeza/2;
    int tamPiernas = 32;
    int radioPiernas = tamPiernas/2; 
    int ajustePierna = 12;
    // para cambiar el tamaño de los sprites
    float escalCab = 1;
    float escalPie = 1;
        
    //Y creo el spritesheet a partir de la imagen anterior
    sf:: IntRect rectSpriteCabeza (0*tamCabeza, 0*tamCabeza, tamCabeza, tamCabeza);
    sf:: IntRect rectSpritePiernas (0*tamPiernas, 1*tamPiernas, tamPiernas, tamPiernas);
    
    sf::Sprite cabeza(texture);
    sf::Sprite piernas(texture);
    
    //Le pongo el centroide donde corresponde
    cabeza.setOrigin(tamCabeza/2,tamCabeza/2);
    piernas.setOrigin(tamPiernas/2,tamPiernas/2);
    //Cojo el sprite que me interesa por defecto del sheet
    cabeza.setTextureRect(rectSpriteCabeza);
    piernas.setTextureRect(rectSpritePiernas);
    // Lo dispongo en el centro de la pantalla
    cabeza.setPosition(anchoPantalla/2, altoPantalla/2);
    piernas.setPosition(anchoPantalla/2, altoPantalla/2+radioPiernas);
    // tamaño de los esprites
    cabeza.setScale(escalCab,escalCab);
    piernas.setScale(escalPie,escalPie);

   
    // avisadores de tecla pulsada
    bool upFlag=false;
    bool downFlag=false;
    bool leftFlag=false;
    bool rightFlag=false;
    
    sf::Clock reloj;
    sf::Clock relojSprite;
    reloj.restart();
    relojSprite.restart();

    
    // ::: INICIO LOOP :::
    while (window.isOpen())
    {
        if(dispara !=0 ){
            int velx = 0;
            int vely = 0;
            if (leftFlag) velx = -3;
            else if(rightFlag) velx = 3;
            if (upFlag) vely = -3;
            else if(downFlag) vely = 3;
            switch (direccionDisparo){
                case Arriba:
                    cabeza.setTextureRect(sf::IntRect(5*tamCabeza, 0*tamCabeza, tamCabeza, tamCabeza));
                    if(reloj.getElapsedTime().asSeconds() > 0.3){
                        balas.push_back(new Bala(x,y,velx,-3,rangoDisparo));
                        reloj.restart();
                    }
                break;
                
                case Abajo:
                    cabeza.setTextureRect(sf::IntRect(1*tamCabeza, 0*tamCabeza, tamCabeza, tamCabeza));
                    if(reloj.getElapsedTime().asSeconds() > 0.3){
                        balas.push_back(new Bala(x,y,velx,3,rangoDisparo));
                        reloj.restart();
                    }
                break;
                case Decha:
                    cabeza.setTextureRect(sf::IntRect(2*tamCabeza, 0*tamCabeza, tamCabeza, tamCabeza)); 
                    cabeza.setScale(escalCab,escalCab);
                    if(reloj.getElapsedTime().asSeconds() > 0.3){
                        balas.push_back(new Bala(x,y,3,vely,rangoDisparo));
                        reloj.restart();
                    }
                break;
                case Izda:
                    cabeza.setTextureRect(sf::IntRect(2*tamCabeza, 0*tamCabeza, tamCabeza, tamCabeza));
                    //Reflejo vertical
                    cabeza.setScale(-escalCab,escalCab);
                    if(reloj.getElapsedTime().asSeconds() > 0.3){
                        balas.push_back(new Bala(x,y,-3,vely,rangoDisparo));
                        reloj.restart();
                    }
                break;
            }
        }else{
            if(upFlag == true){
                cabeza.setTextureRect(sf::IntRect(5*tamCabeza, 0*tamCabeza, tamCabeza, tamCabeza));
            }
            else if(downFlag == true){
                cabeza.setTextureRect(sf::IntRect(1*tamCabeza, 0*tamCabeza, tamCabeza, tamCabeza));
            }
            else if(leftFlag==true){
                cabeza.setTextureRect(sf::IntRect(2*tamCabeza, 0*tamCabeza, tamCabeza, tamCabeza));
                //Reflejo vertical
                cabeza.setScale(-escalCab,escalCab);
            }
            else if(rightFlag==true){
                cabeza.setTextureRect(sf::IntRect(2*tamCabeza, 0*tamCabeza, tamCabeza, tamCabeza));
                //Escala por defecto
                cabeza.setScale(escalCab,escalCab);                 
               
            }
            else{
                cabeza.setTextureRect(sf::IntRect(0*tamCabeza, 0*tamCabeza, tamCabeza, tamCabeza)); 
            }
        }
        
        if(relojSprite.getElapsedTime().asSeconds()> .1 && (upFlag==true || downFlag==true || leftFlag==true || rightFlag==true)){
            contadorPasos++;
            if(contadorPasos == 8){
                contadorPasos = 0;
            }
            if(upFlag == true){
                piernas.setTextureRect(sf::IntRect(contadorPasos*tamPiernas,1*tamPiernas, tamPiernas, tamPiernas));
                piernas.setScale(-escalPie,escalPie);
            }
            if(downFlag == true){
                piernas.setTextureRect(sf::IntRect(contadorPasos*tamPiernas,1*tamPiernas, tamPiernas, tamPiernas));
                piernas.setScale(escalPie,escalPie);
            }
            if(leftFlag==true){
                piernas.setTextureRect(sf::IntRect(contadorPasos*tamPiernas,2*tamPiernas, tamPiernas, tamPiernas));
                piernas.setScale(-escalPie,escalPie);
            }
            if(rightFlag==true){
                piernas.setTextureRect(sf::IntRect(contadorPasos*tamPiernas,2*tamPiernas, tamPiernas, tamPiernas));
                piernas.setScale(escalPie,escalPie);
            }

            relojSprite.restart();
        }
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

                // MOV del personaje
                case sf::Keyboard::W : // ARRIBA     
                    upFlag=true; 
                    //cabeza.setTextureRect(sf::IntRect(5*tamCabeza, 0*tamCabeza, tamCabeza, tamCabeza));
                    break;
                    
                case sf::Keyboard::S:// ABAJO
                    downFlag=true;
                    //cabeza.setTextureRect(sf::IntRect(1*tamCabeza, 0*tamCabeza, tamCabeza, tamCabeza));
                    break;
                break;
                
                case sf::Keyboard::A: // IZDA   
                    leftFlag=true; 
                    //cabeza.setTextureRect(sf::IntRect(2*tamCabeza, 0*tamCabeza, tamCabeza, tamCabeza));
                    //Reflejo vertical
                    //cabeza.setScale(-escalCab,escalCab);
                break;
                            
                case sf::Keyboard::D: // DERECHA
                    rightFlag=true; 
                    //cabeza.setTextureRect(sf::IntRect(2*tamCabeza, 0*tamCabeza, tamCabeza, tamCabeza));
                    //Escala por defecto
                    //cabeza.setScale(escalCab,escalCab);                 
                break;
                
                
                /* DISPAROS */
                case sf::Keyboard::Up: // Arriba
                    direccionDisparo=Arriba;
                    dispara++; 
                break;
                case sf::Keyboard::Down: // Abajo  
                    direccionDisparo=Abajo;
                    dispara++;
                 break;
                case sf::Keyboard::Left: // Letf
                    direccionDisparo=Izda;
                    dispara++;
                break;
                case sf::Keyboard::Right: // Arriba              
                    direccionDisparo=Decha;
                    dispara++;
                break;                    
                default : break;
                }
            }
            
            
            
            // Si no pulsamos ninguan tecla
            if (event.type == sf::Event::KeyReleased)
            {
                switch (event.key.code)
                {
                // Process the up, down, left and right keys
                case sf::Keyboard::W : // ARRIBA     
                    upFlag=false;break;                    
                case sf::Keyboard::S:  // ABAJO  
                    downFlag=false; break;
                case sf::Keyboard::A:  // IZDA  
                    leftFlag=false; break;
                case sf::Keyboard::D:  // DERECHA
                    rightFlag=false; break;
               
                // release DISPARO
                case sf::Keyboard::Up : // Up     
                    dispara--; break;                    
                case sf::Keyboard::Down:  // Down  
                    dispara--; break;
                case sf::Keyboard::Left:  // Izda  
                    dispara--; break;
                case sf::Keyboard::Right: // Dech
                    dispara--; break;
                default : break;
                
                }
                
            }
            
            if(upFlag==false && downFlag==false && leftFlag==false && rightFlag==false){
                cabeza.setTextureRect(sf::IntRect(0*tamCabeza, 0*tamCabeza, tamCabeza, tamCabeza));
                piernas.setTextureRect(sf::IntRect(0*tamPiernas, 1*tamPiernas, tamPiernas, tamPiernas));
                //Escala por defecto
                cabeza.setScale(escalCab,escalCab);             
            }
        }
        

        // Actalizamos coordenadas
        if (leftFlag) x-=SPRITE_SPEED;
        if (rightFlag) x+=SPRITE_SPEED;
        if (upFlag) y-=SPRITE_SPEED;
        if (downFlag) y+=SPRITE_SPEED;

        // Controlar colisión con paredes
        if (x<0) 
            x=radioCabeza;
        if (x>(int)window.getSize().x) 
            x=window.getSize().x-radioCabeza;
        if (y<0) 
            y=radioCabeza;
        if (y>(int)window.getSize().y) 
            y=window.getSize().y-radioCabeza;

        // actualizo posicion de la bala
        for(int i = 0 ; i<balas.size(); i++){
            if(balas.at(i)){
                balas.at(i)->actualiza();
                if(balas.at(i)->destruirBala){
                    delete balas.at(i);
                    balas.erase(balas.begin()+i);
                }
                    
            }
        }
        
        // Limpiamos la ventana y aplicamos un color de fondo 
        window.clear( sf::Color(127,127,127));

        // Fijamos las posiciones de los sprites
        cabeza.setPosition(x,y);
        piernas.setPosition(x,y+(ajustePierna)*escalPie); // valor para ajustar cuerpo a cabeza
          
        // pintamos las balas
        for(int i = 0 ; i<balas.size(); i++){
            if(balas.at(i)){
                window.draw(*balas.at(i));
            }
        }
        window.draw(piernas);

        window.draw(cabeza);
    
        // Actualizar mostrar por pantalla
        window.display();
    }
    return 0;
}
