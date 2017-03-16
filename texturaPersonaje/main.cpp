/*!
 * \file    main.cpp
 * \brief   move a sprite with the keyboard (http://www.lucidarme.me/?p=6127)
 * \author  Philippe Lucidarme
 * Sprite del personaje y animacion: JULIAN SANCHEZ GARCIA 
 */

// SFML libraries
#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>

// Sprite speed (high values = high speed)
#define SPRITE_SPEED  1

int main()
{
    // _____________________
    // ::: VENTANA PRINCIPAL :::

    int altoPantalla = 540;
    int anchoPantalla = 900;
    //Creamos una ventana 
    sf::RenderWindow window(sf::VideoMode(anchoPantalla, altoPantalla), "Hito 1: animacion personaje");
    // Enable vertical sync. (vsync)
    window.setVerticalSyncEnabled (true);
    // When a key is pressed, sf::Event::KeyPressed will be true only once
    window.setKeyRepeatEnabled(false);

    // ::: Creamos y cargamos las texturas :::
    sf::Texture texture;
    if (!texture.loadFromFile("resources/isaacAzul.png"))
    {
        std::cerr << "Error while loading texture" << std::endl;
        return -1;
    }
    // Filtro SMOOTH
    // texture.setSmooth(true);

    //Y creo el spritesheet a partir de la imagen anterior
    sf::Sprite cabeza(texture);
    sf::Sprite piernas(texture);
    int tamCabeza = 32;
    int radioCabeza = tamCabeza/2;
    int tamPiernas = 32;
    int radioPiernas = tamPiernas/2; 
    int ajustePierna = 12;
    // para cambiar el tamaño de los sprites
    float escalCab = 1.5;
    float escalPie = 1.5;
    
    //Le pongo el centroide donde corresponde
    cabeza.setOrigin(tamCabeza/2,tamCabeza/2);
    piernas.setOrigin(tamPiernas/2,tamPiernas/2);
    //Cojo el sprite que me interesa por defecto del sheet
    cabeza.setTextureRect(sf::IntRect(0*tamCabeza, 0*tamCabeza, tamCabeza, tamCabeza));
    piernas.setTextureRect(sf::IntRect(0*tamPiernas, 1*tamPiernas, tamPiernas, tamPiernas));
    // Lo dispongo en el centro de la pantalla
    cabeza.setPosition(anchoPantalla/2, altoPantalla/2);
    piernas.setPosition(anchoPantalla/2, altoPantalla/2+radioPiernas);
    // tamaño de los esprites
    cabeza.setScale(escalCab,escalCab);
    piernas.setScale(escalPie,escalPie);

    // Coordenadas para los sprites
    int x=window.getSize().x/2.;
    int y=window.getSize().y/2.;

    // avisadores de tecla pulsada
    bool upFlag=false;
    bool downFlag=false;
    bool leftFlag=false;
    bool rightFlag=false;
    
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
                    upFlag=true; 
                    cabeza.setTextureRect(sf::IntRect(5*tamCabeza, 0*tamCabeza, tamCabeza, tamCabeza));
                    piernas.setTextureRect(sf::IntRect(1*tamPiernas,1*tamPiernas, tamPiernas, tamPiernas));
                    piernas.setScale(-escalPie,escalPie);
                    break;
                    
                case sf::Keyboard::S:// ABAJO
                    downFlag=true;
                    cabeza.setTextureRect(sf::IntRect(1*tamCabeza, 0*tamCabeza, tamCabeza, tamCabeza));     
                    piernas.setTextureRect(sf::IntRect(1*tamPiernas,1*tamPiernas, tamPiernas, tamPiernas));
                    piernas.setScale(escalPie,escalPie);
                    break;
                    
                case sf::Keyboard::A: // IZDA   
                    leftFlag=true; 
                    cabeza.setTextureRect(sf::IntRect(2*tamCabeza, 0*tamCabeza, tamCabeza, tamCabeza));
                    //Reflejo vertical
                    cabeza.setScale(-escalCab,escalCab);
                    piernas.setTextureRect(sf::IntRect(3*tamPiernas,2*tamPiernas, tamPiernas, tamPiernas));
                    piernas.setScale(-escalPie,escalPie);
                    break;
                            
                case sf::Keyboard::D: // DERECHA
                    rightFlag=true; 
                    cabeza.setTextureRect(sf::IntRect(2*tamCabeza, 0*tamCabeza, tamCabeza, tamCabeza));
                    //Escala por defecto
                    cabeza.setScale(escalCab,escalCab);
                    piernas.setTextureRect(sf::IntRect(3*tamPiernas,2*tamPiernas, tamPiernas, tamPiernas));
                    piernas.setScale(escalPie,escalPie);
                    break;
                    
                default : break;
                }
            }

            // Si no pulsamos ninguan tecla
            if (event.type == sf::Event::KeyReleased)
            {
                // solu provisional. Falta controlar cuando son dos teclas pulsadas
                if(upFlag==false || downFlag==false || leftFlag==false || rightFlag==false){
                    
                    cabeza.setTextureRect(sf::IntRect(0*tamCabeza, 0*tamCabeza, tamCabeza, tamCabeza));
                    piernas.setTextureRect(sf::IntRect(0*tamPiernas, 1*tamPiernas, tamPiernas, tamPiernas));
                    //Escala por defecto
                    cabeza.setScale(escalCab,escalCab);             
                }
                
                
                
                switch (event.key.code)
                {
                // Process the up, down, left and right keys
                case sf::Keyboard::W : // ARRIBA     
                    upFlag=false; break;
                case sf::Keyboard::S:  // ABAJO  
                    downFlag=false; break;
                case sf::Keyboard::A:  // IZDA  
                    leftFlag=false; break;
                case sf::Keyboard::D:  // DERECHA
                    rightFlag=false; break;
                default : break;
                
                }
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

        // Limpiamos la ventana y aplicamos un color de fondo 
        window.clear( sf::Color(127,127,127));

        // Fijamos las posiciones de los sprites
        cabeza.setPosition(x,y);
        piernas.setPosition(x,y+(ajustePierna)*escalPie); // valor para ajustar cuerpo a cabeza
        window.draw(piernas);
        window.draw(cabeza);

        // Actualizar mostrar por pantalla
        window.display();
    }
    return 0;
}
