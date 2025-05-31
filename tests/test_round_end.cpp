#include <iostream>
#include <chrono>
#include <thread>
#include <cassert>

#include "../server/game/game.h"
#include "../common/DTO/game_state_dto.h"
#include "../common/queue.h"

void test_round_end() {
    using namespace std::chrono;

    ClientQueue client_queue;
    Game game("test_party", "test_map");

    uint8_t player_id = game.add_player("TestPlayer", client_queue);

    std::this_thread::sleep_for(std::chrono::seconds(3)); // esto si la ronda es de 3 segundos

    bool ended_received = false;
    int i = 0;
    DTO::GameStateDTO dto;
    while (client_queue.try_pop(dto)) {
        if(i < 1){
            assert(!dto.ended);
        }
        i++;
        if (dto.ended) {
            ended_received = true;
            break;
        }
    }
    std::cout << "ITERACIONES: " << i << std::endl;
    assert(ended_received);
}

int main() {
    test_round_end();
    std::cout << "Pasaron los test" << std::endl;
    return 0;
}
