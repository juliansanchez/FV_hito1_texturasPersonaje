#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>

#define kVel 8
#define Ancho 800
#define Alto 600
#define vy 200
#define vx 200
#define kInc 0.001

void reiniciar (sf::Sprite& c, sf::Sprite& e, sf::CircleShape& p, int& g, float& v1, float&v2, sf::Clock& r){
    c.setPosition(c.getLocalBounds().width, Alto/2);
    e.setPosition(Ancho-e.getLocalBounds().width, Alto/2);
    p.setPosition(Ancho/2, Alto/2);
    g = 0;
    r.restart();
    double s = ((double) rand() / (RAND_MAX)-0.5)*50;
    double s2 = ((double) rand() / (RAND_MAX)-0.5)*50;
    if(((double) rand() / (RAND_MAX)-0.5)<0) //Cacula numeros entre -0.5 y 0.5
        v1 = -vx + s;
    else
        v1 = vx + s;
    if(((double) rand() / (RAND_MAX)-0.5)<0)
        v2 = -vy + s2;
    else
        v2 = vy + s2;
}


int main()
{
    //Creamos una ventana 
    sf::RenderWindow window(sf::VideoMode(Ancho, Alto), "P0. Fundamentos de los Videojuegos. DCCIA");

    //Cargo la imagen donde reside la textura del sprite
    sf::Texture tex;
    if (!tex.loadFromFile("resources/spritebob.png"))
    {
        std::cerr << "Error cargando la imagen spritebob.png";
        exit(0);
    }
    
    sf::Texture tex2;
    if (!tex2.loadFromFile("resources/spritefunguy.png"))
    {
        std::cerr << "Error cargando la imagen spritefunguy.png";
        exit(0);
    }
    
    //Y creo el spritesheet a partir de la imagen anterior
    sf::Sprite cabeza(tex);
    sf::Sprite cabeza2(tex2);
    
    //Le pongo el centroide donde corresponde
    cabeza.setOrigin(27/2,25/2);
    cabeza2.setOrigin(40/2, 40/2);
    
    
    //Cojo el sprite que me interesa por defecto del sheet
    cabeza.setTextureRect(sf::IntRect(18, 17, 27, 25));
    cabeza2.setTextureRect(sf::IntRect(397, 9, 40, 40));
    
    // Lo dispongo en el centro de la pantalla
    
    cabeza.setScale(2.5, 2.5);
    cabeza2.setScale(2, 2);
    
    sf::Clock veloc;
    sf::Time tiem;
    
    //Pelota
    const int radio = 7;
    sf::CircleShape pelota;
    pelota.setRadius(radio);
    pelota.setOutlineThickness(1.5);
    pelota.setOutlineColor(sf::Color::Cyan);
    pelota.setFillColor(sf::Color::White);
    pelota.setOrigin(5, 5); 
    float vely = vy;
    float velx= vx;
    
    bool jugando = false;
    
    //Marcadores
    int vida1 = 3;
    int vida2 = 3;
    int golpes = 0;
    
    sf::Font fuente;
    if (!fuente.loadFromFile("resources/game_over.ttf")){
        std::cerr << "Error cargando la fuente";
        exit(0);
    }
    
    sf::Text contvida;
    contvida.setFont(fuente);
    contvida.setFillColor(sf::Color::White);
    contvida.setCharacterSize(70);
    
    sf::Text contvida2;  
    contvida2.setFont(fuente);
    contvida2.setFillColor(sf::Color::White);
    contvida2.setCharacterSize(70);
    
    sf::Text marcador;  
    marcador.setFont(fuente);
    marcador.setFillColor(sf::Color::White);
    marcador.setCharacterSize(70);
    
    sf::Text ganada;
    ganada.setString("HAS GANADO");
    ganada.setFont(fuente);
    ganada.setFillColor(sf::Color::White);
    ganada.setCharacterSize(120);
    
    sf::Text perdida;
    perdida.setString("HAS PERDIDO");
    perdida.setFont(fuente);
    perdida.setFillColor(sf::Color::White);
    perdida.setCharacterSize(120);
    
    sf::Text esp;
    esp.setString("Pulse espacio para jugar");
    esp.setFont(fuente);
    esp.setFillColor(sf::Color::White);
    esp.setCharacterSize(60);
    
    sf::Text pong;
    pong.setString("PONG");
    pong.setFont(fuente);
    pong.setFillColor(sf::Color::White);
    pong.setCharacterSize(200);
    
    contvida2.setPosition(Ancho-20, 0);
    marcador.setPosition(Ancho/2, 0);
    contvida.setPosition(20, 0);
    
    //Bucle del juego
    while (window.isOpen())
    {
        tiem= veloc.restart();
        switch (jugando){
            case false:
                
                //Final de partida
                if (vida1 == 0 || vida2 == 0){ 
                    if (vida1 == 0)
                        perdida.setPosition(Ancho/2 - 140, Alto/2 -200); 
                    
                    else
                        ganada.setPosition(Ancho/2 - 140, Alto/2 -200);                                                                           
                }               
                //Programacion de pantalla de inicio
                else
                    pong.setPosition(Ancho/2 -100, Alto/2 -250);
                
                esp.setPosition(Ancho/2 -120, Alto/2 - 50); 
                sf::Event event; 
                while (window.pollEvent(event)){
                    if(event.type == sf::Event::Closed 
                            ||(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) 
                        window.close();
                        
                    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space){
                        jugando = true; 
                        vida1 = 3;
                        vida2 = 3;
                        reiniciar (cabeza, cabeza2, pelota, golpes, velx, vely, veloc);
                    }                   
                }
            break;
            
            case true:              
                std::string v = std::to_string(vida1);
                std::string v2 = std::to_string(vida2);
                std::string m = std::to_string(golpes);
                contvida.setString(v); 
                contvida2.setString(v2);
                marcador.setString(m); 

                //Bucle de obtención de eventos
                sf::Event event2;
                while (window.pollEvent(event2))
                {                       
                    switch(event2.type){

                        //Si se recibe el evento de cerrar la ventana la cierro
                        case sf::Event::Closed:
                            window.close();
                        break;

                        case sf::Event::KeyReleased:
                            cabeza.setTextureRect(sf::IntRect(146, 17, 27, 25));
                        break;

                        //Se pulsó una tecla, imprimo su codigo
                        case sf::Event::KeyPressed:

                            //Verifico si se pulsa alguna tecla de movimiento
                            switch(event2.key.code) {

                                case sf::Keyboard::Up:
                                    cabeza.setTextureRect(sf::IntRect(274, 17, 27, 25));
                                    if(cabeza.getPosition().y - cabeza.getGlobalBounds().height/2 > 0)
                                        cabeza.move(0,-kVel);
                                break;

                                case sf::Keyboard::Down:
                                    cabeza.setTextureRect(sf::IntRect(18, 17, 27, 25));
                                    if (cabeza.getPosition().y + cabeza.getGlobalBounds().height/2 < Alto)                                
                                        cabeza.move(0,kVel); 
                                break;

                                //Tecla ESC para salir
                                case sf::Keyboard::Escape:
                                    window.close();
                                break;

                                //Cualquier tecla desconocida se imprime por pantalla su código
                                default:
                                    std::cout << event2.key.code << std::endl;
                                break;        
                                }
                        break;
                        }    
                }

                //Movimiento enemigo y colisiones con pantalla
                if (pelota.getPosition().y + radio > cabeza2.getPosition().y + cabeza2.getGlobalBounds().height/2 
                        && cabeza2.getPosition().y + cabeza2.getGlobalBounds().height/2 < Alto){
                    cabeza2.move(0, kVel);
                }
                else if (pelota.getPosition().y - radio < cabeza2.getPosition().y - cabeza2.getGlobalBounds().height/2 
                        && cabeza2.getPosition().y - cabeza2.getGlobalBounds().height/2 > 0){
                    cabeza2.move(0, -kVel);
                }


                //Movimiento pelota
                if (velx < 0)
                    velx = velx - golpes*kInc;
                else
                    velx = velx + golpes*kInc;
                if (vely<0)
                    vely = vely - golpes*kInc;
                else
                    vely = vely + golpes*kInc;
                pelota.move(velx * tiem.asSeconds(), vely * tiem.asSeconds());

                //Colisiones pelota-entorno
                if (pelota.getPosition().x - radio < 0){
                    vida1--;
                    if (vida1 == 0)
                        jugando = false;
                    else{
                        sf::Time t = sf::seconds(2);
                        sf::sleep(t);
                        reiniciar(cabeza, cabeza2, pelota, golpes, velx, vely, veloc);
                    }

                }
                if (pelota.getPosition().x + radio > Ancho){
                    vida2--;
                    
                    if (vida2 == 0)
                        jugando = false;
                    else{
                        sf::Time t = sf::seconds(2);
                        sf::sleep(t);
                        reiniciar(cabeza, cabeza2, pelota, golpes, velx, vely, veloc);
                    }
                }
                if (pelota.getPosition().y - radio < 0)
                    {
                        vely = -vely;
                        pelota.setPosition(pelota.getPosition().x, radio + 0.1f);
                    }
                if (pelota.getPosition().y + radio > Alto)
                    {
                        vely = -vely;
                        pelota.setPosition(pelota.getPosition().x, Alto - radio - 0.1f);
                    }

                //Colisiones pelota-jugador - Comprobar si esta contenida la pelota en el sprite
                if (pelota.getPosition().x - radio < cabeza.getPosition().x + cabeza.getGlobalBounds().width/2 //Si el centro de la pelota es menor que el borde de la cabeza
                        && pelota.getPosition().x - radio > cabeza.getPosition().x //Si el centro de la pelota es mayor que el centro de la cabeza
                        && pelota.getPosition().y + radio >= cabeza.getPosition().y - cabeza.getGlobalBounds().height/2 //Si la y de la pelota se encuentra por arriba del centro de la cabeza
                        && pelota.getPosition().y - radio <= cabeza.getPosition().y + cabeza.getGlobalBounds().height/2){ //Y el centro de la pelota esta por debajo del borde en Y de la cabeza
                    if (pelota.getPosition().y > cabeza.getPosition().y){
                        velx = -velx;
                    }
                    else{
                        velx = -velx;
                    }
                    pelota.setPosition(cabeza.getPosition().x + radio + cabeza.getGlobalBounds().width/2 + 0.1, pelota.getPosition().y);
                    golpes++;
                }

                //Colisiones pelota-IA
                if (pelota.getPosition().x + radio > cabeza2.getPosition().x - cabeza2.getGlobalBounds().width/2
                        && pelota.getPosition().x + radio < cabeza2.getPosition().x
                        && pelota.getPosition().y + radio >= cabeza2.getPosition().y - cabeza2.getGlobalBounds().height/2
                        && pelota.getPosition().y + radio <= cabeza2.getPosition().y + cabeza2.getGlobalBounds().height/2){
                    if (pelota.getPosition().y > cabeza2.getPosition().y){
                        velx = -velx;
                    }               
                    else{
                        velx = -velx;
                    }             
                    pelota.setPosition(cabeza2.getPosition().x - radio - cabeza2.getGlobalBounds().width/2 - 0.1, pelota.getPosition().y);
                    golpes++;
                }
            break;         
        }

        window.clear();
        if (jugando){
            window.draw(cabeza);
            window.draw(pelota);
            window.draw(cabeza2);
            window.draw(contvida);
            window.draw(contvida2);
            window.draw(marcador);
        }
        else if (!jugando && vida1 == 0){
            window.draw(perdida);
            window.draw (esp); 
        }
        else if (!jugando && vida2 ==0){
            window.draw (ganada);
            window.draw (esp);         
        }
        else{
            window.draw (pong);
            window.draw (esp);
        }

        window.display();
    }
    return 0;
}