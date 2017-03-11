#include <iostream>
#include <SFML/Graphics.hpp>

#define kVel 5

int main()
{
    int altoPantalla = 540;
    int anchoPantalla = 900;
    
    //Creamos una ventana 
    sf::RenderWindow window(sf::VideoMode(anchoPantalla, altoPantalla), "Hito 1: animacion personaje");

    //Cargo la imagen donde reside la textura del sprite
    sf::Texture tex;
    if (!tex.loadFromFile("resources/isaacAzul.png"))
    {
        std::cerr << "Error cargando la imagen sprites.png";
        exit(0);
    }
    
    //Y creo el spritesheet a partir de la imagen anterior
    sf::Sprite cabeza(tex);
    sf::Sprite piernas(tex);
    int tamCabeza = 32;
    int radioCabeza = tamCabeza/2;
    int tamPiernas = 32;
    int radioPiernas = (tamPiernas/2)-4;
    
    int escalCab = 2;
    int escalPie = 4.5;
    //Le pongo el centroide donde corresponde
    
    cabeza.setOrigin(tamCabeza/2,tamCabeza/2);
    piernas.setOrigin(tamPiernas/2,tamPiernas/2);
    //Cojo el sprite que me interesa por defecto del sheet
    cabeza.setTextureRect(sf::IntRect(0*tamCabeza, 0*tamCabeza, tamCabeza, tamCabeza));
    piernas.setTextureRect(sf::IntRect(0*tamPiernas, 1*tamPiernas, tamPiernas, tamPiernas));
    // Lo dispongo en el centro de la pantalla
    cabeza.setPosition(anchoPantalla/2, altoPantalla/2);
    piernas.setPosition(anchoPantalla/2, altoPantalla/2+radioPiernas);
    
    cabeza.setScale(escalCab,escalCab);
    piernas.setScale(escalPie,escalPie);

    

    //Bucle del juego
    while (window.isOpen())
    {
        //Bucle de obtención de eventos
        sf::Event event;
        while (window.pollEvent(event))
        {
            
            switch(event.type){
                
                //Si se recibe el evento de cerrar la ventana la cierro
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyReleased:
                            cabeza.setTextureRect(sf::IntRect(0*tamCabeza, 0*tamCabeza, tamCabeza, tamCabeza));
                            piernas.setTextureRect(sf::IntRect(0*tamPiernas, 1*tamPiernas, tamPiernas, tamPiernas));
                            //Escala por defecto
                            cabeza.setScale(escalCab,escalCab);
                          
                break;
                    
                //Se pulsó una tecla, imprimo su codigo
                case sf::Event::KeyPressed:
                    
                    //Verifico si se pulsa alguna tecla de movimiento
                    switch(event.key.code) {
                        
                        //Mapeo del cursor
                        
                        case sf::Keyboard::Right:
                            cabeza.setTextureRect(sf::IntRect(2*tamCabeza, 0*tamCabeza, tamCabeza, tamCabeza));
                            //Escala por defecto
                            cabeza.setScale(escalCab,escalCab);
                            cabeza.move(kVel,0);
                            piernas.setTextureRect(sf::IntRect(3*tamPiernas,2*tamPiernas, tamPiernas, tamPiernas));
                            piernas.move(kVel,0);
                            piernas.setScale(escalPie,escalPie);
                        break;

                        case sf::Keyboard::Left:
                            cabeza.setTextureRect(sf::IntRect(2*tamCabeza, 0*tamCabeza, tamCabeza, tamCabeza));
                            //Reflejo vertical
                            cabeza.setScale(-escalCab,escalCab);
                            cabeza.move(-kVel,0); 
                            piernas.setTextureRect(sf::IntRect(3*tamPiernas,2*tamPiernas, tamPiernas, tamPiernas));
                            piernas.setScale(-escalPie,escalPie);
                            piernas.move(-kVel,0);
                            
                            
                            
                        break;
                        
                        case sf::Keyboard::Up:
                            cabeza.setTextureRect(sf::IntRect(5*tamCabeza, 0*tamCabeza, tamCabeza, tamCabeza));
                            cabeza.move(0,-kVel); 
                            
                            piernas.setTextureRect(sf::IntRect(1*tamPiernas,1*tamPiernas, tamPiernas, tamPiernas));
                            piernas.move(0,-kVel);
                            piernas.setScale(-escalPie,escalPie);
                        break;
                        
                        case sf::Keyboard::Down:
                            cabeza.setTextureRect(sf::IntRect(1*tamCabeza, 0*tamCabeza, tamCabeza, tamCabeza));
                            cabeza.move(0,kVel); 
                            piernas.setTextureRect(sf::IntRect(1*tamPiernas,1*tamPiernas, tamPiernas, tamPiernas));
                            piernas.move(0,kVel);
                            piernas.setScale(escalPie,escalPie);
                        break;
                        
                 
                        //Tecla ESC para salir
                        case sf::Keyboard::Escape:
                            window.close();
                        break;
                        
                        //Cualquier tecla desconocida se imprime por pantalla su código
                        default:
                            std::cout << event.key.code << std::endl;
                        break;
                              
                    }

            }
            
        }
        window.clear();
        window.draw(piernas);
        window.draw(cabeza);
        
        window.display();
    }

    return 0;
}
