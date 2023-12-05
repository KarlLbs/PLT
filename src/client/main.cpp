#include <iostream>
#include <cstring>

// Les lignes suivantes ne servent qu'à vérifier que la compilation avec SFML fonctionne
#include <SFML/Graphics.hpp>
#include <state.h>
#include "render.h"

using namespace std;
using namespace state;

void test();
GameState generateSampleState();


int main(int argc, char *argv[]) {

    if (argc >= 2) {
        if (std::strcmp(argv[1], "hello") == 0) {
           std::cout << "hello my dear" << std::endl;
        } 

        else if (std::strcmp(argv[1], "state") == 0) {
           std::cout << "lancement des tests" << std::endl;
           test();
           std::cout << "everything is fine" << std::endl;
        } 

        else if (std::strcmp(argv[1], "render") == 0) {
           
             sf::RenderWindow window(sf::VideoMode(1600, 900), "Citadelles");
            window.setVerticalSyncEnabled(true);

            GameState gamestate=generateSampleState();
            gamestate.setCurrentCharacter(Architect);
            render::Scene sceneA(render::SceneId::PlayerA, &gamestate);
            


             while (window.isOpen()) {
                sf::Event event;
                while (window.pollEvent(event)) {
                    sceneA.handleEvent(event);
               

                    if (event.type == sf::Event::Closed) {
                        window.close();
                    }
                }
            window.clear();

            sceneA.draw(window);
            window.display();
    }
}

        
        else if (std::strcmp(argv[1], "engine") == 0) {
           
        }

        else {
        // error if no argument
        std::cout << "Wrong command. the correct command is  ../bin/client hello" << std::endl;
        }
        return 0;
    }
    return 1;
}

void test(){
    Card card {"card1", CardType::Military, 2};
    Player player {"player1", PlayerId::PlayerA};
    GameState gameState {std::vector<Player>{player}};
}

GameState generateSampleState() {
    Player playerA {"player1", PlayerId::PlayerA};
    Player playerB {"player2", PlayerId::PlayerB};
    Player playerC {"player3", PlayerId::PlayerC};
    Player playerD {"player4", PlayerId::PlayerD};

    Card card1{"1",Commercial,2};
    Card card2{"2",Commercial,2};
    Card card3{"25",Commercial,2};


    playerA.setCharacter(Warlord);
    playerB.setCharacter(Bishop);
    playerC.setCharacter(Merchant);
    playerD.setCharacter(King);

    playerA.setBoardOfPlayer(std::vector<Card>{card1});
    playerB.setBoardOfPlayer(std::vector<Card>{card2, card3});
    playerC.setBoardOfPlayer(std::vector<Card>{card2,card1});
    playerD.setBoardOfPlayer(std::vector<Card>{card1,card2});
    
    playerA.setHand(std::vector<Card>{card2});

    GameState gameState {std::vector<Player>{playerA,playerB,playerC,playerD}};
    return gameState;
}


