#include <iostream>
#include <cstring>
#include <utility>

// Les lignes suivantes ne servent qu'à vérifier que la compilation avec SFML fonctionne
#include "render.h"
#include "engine.h"
#include "client.h"

using namespace std;
using namespace state;
using namespace engine;

void test();

void generateSampleState(const std::shared_ptr<state::GameState>& gameStateSample);

void startRender(std::shared_ptr<state::GameState> state, bool& notifier);

int main(int argc, char *argv[]) {
    if (argc >= 2) {
        if (std::strcmp(argv[1], "hello") == 0) {
            std::cout << "hello my dear" << std::endl;
        } else if (std::strcmp(argv[1], "state") == 0) {
            std::cout << "everything is fine" << std::endl;
        } else if (std::strcmp(argv[1], "render") == 0) {
            std::shared_ptr<state::GameState> gameState= std::make_shared<GameState>("Simon", "Karl", "Nordine", "Guillaume");
            generateSampleState(gameState);
            bool notif;
            startRender(gameState, notif);
        } else if (std::strcmp(argv[1], "engine") == 0) {
            std::shared_ptr<state::GameState> gameState= std::make_shared<GameState>("Simon", "Karl", "Nordine", "Guillaume");
            generateSampleState(gameState);
        } else if (std::strcmp(argv[1], "network") == 0) {
            if (argc < 4) {
                std::cout << "Invalid argument for target network, expected /client network ${host} ${port}" << endl;
            }
            ApiManager::initNetwork(argv[2], argv[3]);
            string myName = argc > 4 ? argv[4] : "Me";
            ApiManager::sendMessage("POST", "/player", myName);
            string registerString = ApiManager::readAnswer();
            auto pos = registerString.find('/');
            if (pos == string::npos) {
                cout << "error joining the game : " << registerString << endl;
                return -1;
            }
            auto id = static_cast<PlayerId>(registerString.at(pos + 1) - '0');
            bool notifier = false;
            ActiveGame game = ActiveGame(id, myName, notifier);
            auto gameState = game.getGame();
            Engine::getInstance().startThread();
            startRender(gameState, notifier);
        } else {
            // error if no argument
            std::cout << "Wrong command. the correct command is  ../bin/client X" << std::endl;
        }
        return 0;
    }
    return 1;
}

void generateSampleState(const shared_ptr<GameState>& gameStateSample) {

    Card card1{"1", CardType::COMMERCIAL, 2};
    Card card2{"2", CardType::COMMERCIAL, 2};
    Card card3{"25", CardType::COMMERCIAL, 2};

    Player playerA = gameStateSample->getPlayer(PlayerId::PLAYER_A);
    Player playerB = gameStateSample->getPlayer(PlayerId::PLAYER_B);
    Player playerC = gameStateSample->getPlayer(PlayerId::PLAYER_C);
    Player playerD = gameStateSample->getPlayer(PlayerId::PLAYER_D);

    playerA.setCharacter(CharacterType::KING);
    playerA.setCapacityAvailability(true);
    playerB.setCharacter(CharacterType::WARLORD);
    playerC.setCharacter(CharacterType::BISHOP);
    playerD.setCharacter(CharacterType::ASSASSIN);

    std::vector<Card> playerABoard{card1};
    std::vector<Card> playerBBoard{card2};
    std::vector<Card> playerCBoard{card2, card1, card3};
    std::vector<Card> playerDBoard{card1, card2};

    playerA.setBoardOfPlayer(playerABoard);
    playerB.setBoardOfPlayer(playerBBoard);
    playerC.setBoardOfPlayer(playerCBoard);
    playerD.setBoardOfPlayer(playerDBoard);

    gameStateSample->updatePlayer(playerA);
    gameStateSample->updatePlayer(playerB);
    gameStateSample->updatePlayer(playerC);
    gameStateSample->updatePlayer(playerD);

    gameStateSample->setCurrentCharacter(KING);
    gameStateSample->setGamePhase(CALL_CHARACTER);
    gameStateSample->setSubPhase(Default);
    gameStateSample->setPlaying(PLAYER_A);
    gameStateSample->setCrownOwner(PLAYER_B);
}

void startRender(std::shared_ptr<state::GameState> state, bool& notifier) {
    render::Scene scene(render::SceneId::PlayerA, std::move(state), notifier);
    sf::RenderWindow window(sf::VideoMode(1600, 900), "Citadelles");
    window.setVerticalSyncEnabled(true);
    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            scene.handleEvent(event);
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        window.clear();

        scene.draw(window);
        window.display();
    }
}
