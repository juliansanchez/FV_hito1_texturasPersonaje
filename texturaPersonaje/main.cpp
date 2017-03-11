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
    int tamSprite = 32;
    //Le pongo el centroide donde corresponde
    
    cabeza.setOrigin(tamSprite/2,tamSprite/2);
    //Cojo el sprite que me interesa por defecto del sheet
    cabeza.setTextureRect(sf::IntRect(0*tamSprite, 0*tamSprite, tamSprite, tamSprite));

    // Lo dispongo en el centro de la pantalla
    cabeza.setPosition(anchoPantalla/2, altoPantalla/2);

    

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
                            cabeza.setTextureRect(sf::IntRect(0*tamSprite, 0*tamSprite, tamSprite, tamSprite));
                            //Escala por defecto
                            cabeza.setScale(1,1);
                          
                break;
                    
                //Se pulsó una tecla, imprimo su codigo
                case sf::Event::KeyPressed:
                    
                    //Verifico si se pulsa alguna tecla de movimiento
                    switch(event.key.code) {
                        
                        //Mapeo del cursor
                        
                        case sf::Keyboard::Right:
                            cabeza.setTextureRect(sf::IntRect(2*tamSprite, 0*tamSprite, tamSprite, tamSprite));
                            //Escala por defecto
                            cabeza.setScale(1,1);
                            cabeza.move(kVel,0);
                        break;

                        case sf::Keyboard::Left:
                            cabeza.setTextureRect(sf::IntRect(2*tamSprite, 0*tamSprite, tamSprite, tamSprite));
                            //Reflejo vertical
                            cabeza.setScale(-1,1);
                            cabeza.move(-kVel,0); 
                        break;
                        
                        case sf::Keyboard::Up:
                            cabeza.setTextureRect(sf::IntRect(5*tamSprite, 0*tamSprite, tamSprite, tamSprite));
                            cabeza.move(0,-kVel); 
                        break;
                        
                        case sf::Keyboard::Down:
                            cabeza.setTextureRect(sf::IntRect(1*tamSprite, 0*tamSprite, tamSprite, tamSprite));
                            cabeza.move(0,kVel); 
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
        window.draw(cabeza);
        window.display();
    }

    return 0;
}