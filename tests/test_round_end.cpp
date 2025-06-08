#include <iostream>
#include <chrono>
#include <thread>
#include <cassert>

#include "../server/game/game.h"
#include "../common/DTO/game_state_dto.h"
#include "../common/queue.h"
#include "common/weapon_type.h"

//ojo que revisa si termino PARTIDA, pero hasta ahora en código informa si temino ronda en el dto de game
void test_round_end() {
    using namespace std::chrono;

    ClientQueue client_queue;
    Game game("test_party", "test_map");

    uint8_t player_id = game.add_player("TestPlayer", client_queue);
    std::cout << "[TEST - ROUND END] Testeo que despues de 3 segundos haya terminado la partida (handcodeado en código)" << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(3)); // esto si la ronda es de 3 segundos

    bool ended_received = false;
    int i = 0;
    int no_termiando = 0;
    DTO::GameStateDTO dto;
    while (client_queue.try_pop(dto) && !ended_received) {
        if(i < 1){
            assert(!dto.ended);
        }
        i++;
        if (dto.ended) {
            ended_received = true;
        }else{
            no_termiando++;
        }
        std::cout << "[TEST - ROUND END] DTO: "<< i << " TIEMPO EN SEGUNDOS: "<< dto.time_left << std::endl;
    }
    std::cout << "[TEST - ROUND END] CANTIDAD DE DTOs DONDE NO HABIA TERMIANADO: "<< no_termiando << std::endl;
    std::cout << "[TEST - ROUND END] TERMINÓ RONDA LLEGÓ EN EL DTO NÚMERO: "<< i << std::endl;
    std::cout << "----------------------------------------------------------------------------------------------------" << std::endl;
    assert(ended_received);
}
// ojo que el 9 esta hardcodeado porque algo en el (10,0) y el (0,10).
void test_player_moves_forward_until_9_then_stops() {
    std::cout << "[TEST - MOVES FWD UNTIL 9] Testeo que si se choca con algo en (10,0) y (0,10) frenen ambos" << std::endl;
    using namespace std::chrono;

    ClientQueue client_queue;
    ClientQueue client_queue2;
    Game game("test_party", "test_map");

    uint8_t player_id = game.add_player("Mover", client_queue);     // mover en X
    uint8_t player_id2 = game.add_player("Mover2", client_queue2);  // mover en Y

    game.get_queue().push({player_id, MovementEvent(1, 0)});
    game.get_queue().push({player_id2, MovementEvent(0, 1)});

    std::this_thread::sleep_for(std::chrono::milliseconds(300));
    game.stop();

    float last_x = -1;
    float last_y = -1;
    bool reached_9_x = false;
    bool reached_9_y = false;
    int count = 0;

    DTO::GameStateDTO dto;
    while (client_queue.try_pop(dto)) {
        for (const auto& player : dto.players) {
            std::cout << "[TEST - MOVES FWD UNTIL 9] "<< "DTO: " << count << " - Player " << static_cast<int>(player.player_id)
                      << " posición_x = " << player.position_x
                      << ", posición_y = " << player.position_y << std::endl;

            if (player.player_id == player_id) {
                float x = player.position_x;
                if (!reached_9_x) {
                    if (last_x >= 0) {
                        assert(x >= last_x);
                    }
                    if (x >= 9.0f) {
                        reached_9_x = true;
                    }
                } else {
                    assert(x == 9.0f);
                }
                last_x = x;
            }

            if (player.player_id == player_id2) {
                float y = player.position_y;
                if (!reached_9_y) {
                    if (last_y >= 0) {
                        assert(y >= last_y);
                    }
                    if (y >= 9.0f) {
                        reached_9_y = true;
                    }
                } else {
                    assert(y == 9.0f);
                }
                last_y = y;
            }
        }
        count++;
    }

    std::cout << "[TEST - MOVES FWD UNTIL 9] FRAMES PROCESADOS: " << count << std::endl;
    std::cout << "----------------------------------------------------------------------------------------------------" << std::endl;
    assert(reached_9_x);
    assert(reached_9_y);
}

void test_player_moves_correctly_with_two_different_commands(){
    using namespace std::chrono;

    ClientQueue client_queue;

    Game game("test_party", "test_map");

    uint8_t player_id = game.add_player("Mover", client_queue);     // mover en X

    game.get_queue().push({player_id, MovementEvent(1, 0)});
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    game.get_queue().push({player_id, MovementEvent(-1, 0)});

    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    game.stop();

    float last_x = -1;
    float last_y = -1;
    int count = 0;

    DTO::GameStateDTO dto;
    while (client_queue.try_pop(dto)) {
        for (const auto& player : dto.players) {
            std::cout << "[DTO: " << count << "] Player " << static_cast<int>(player.player_id)
                      << " posición_x = " << player.position_x
                      << ", posición_y = " << player.position_y << std::endl;
        }
        count++;
    }

    std::cout << "Frames procesados: " << count << std::endl;
    assert(false && "NO ESTA TESTIANDO NADA TODAVÍA"); //no esta testeando nada todavía
}

void test_players_have_default_guns() {
    using namespace std::chrono;

    ClientQueue client_queue1;
    ClientQueue client_queue2;

    Game game("test_party", "test_map");

    uint8_t player_id1 = game.add_player("Player1", client_queue1);
    uint8_t player_id2 = game.add_player("Player2", client_queue2);

    std::this_thread::sleep_for(milliseconds(80));
    game.stop();

    int count = 0;

    DTO::GameStateDTO dto;
    while (client_queue1.try_pop(dto)) {
        for (const auto& player : dto.players) {
            std::cout << "[DTO: " << count << "] Player " << static_cast<int>(player.player_id)
                      << " ARMA EQUIPADA ID: " << static_cast<int>(player.weapon.id)
                      << ", LOADED AMMO: " << static_cast<int>(player.weapon.loaded_ammo)
                      << std::endl;

            assert(player.weapon.id == static_cast<uint8_t>(WeaponID::KNIFE));
        }
        count++;
    }
}

void test_player_switch_weapon() {
    std::cout << "[TEST] - Arranca con KNIFE (como default) e intenta cambiar a la SECONDARY" << std::endl;
    using namespace std::chrono;

    ClientQueue client_queue1;

    Game game("test_party", "test_map");

    uint8_t player_id = game.add_player("Player1", client_queue1);

    std::this_thread::sleep_for(milliseconds(80));

    game.get_queue().push({player_id, SwitchWeaponEvent(WeaponType::SECONDARY)});

    std::this_thread::sleep_for(milliseconds(80));
    game.stop();

    int count = 0;
    bool weapon_was_switched = false;
    DTO::GameStateDTO dto;
    bool knife_detected = false;
    bool glock_detected = false;

    while (client_queue1.try_pop(dto)) {
        for (const auto& player : dto.players) {
            if (player.player_id != player_id) continue;

            WeaponID current_weapon = static_cast<WeaponID>(player.weapon.id);

            std::cout << "[DTO: " << count << "] Player " << static_cast<int>(player.player_id)
                    << " ARMA EQUIPADA ID: " << static_cast<int>(current_weapon)
                    << ", LOADED AMMO: " << static_cast<int>(player.weapon.loaded_ammo)
                    << std::endl;

            if (!glock_detected) {
                if (current_weapon == WeaponID::KNIFE) {
                    knife_detected = true;
                } else if (current_weapon == WeaponID::GLOCK) {
                    assert(knife_detected);
                    glock_detected = true;
                } else {
                    assert(false && "Arma inesperada antes del cambio a Glock");
                }
            } else {
                assert(current_weapon == WeaponID::GLOCK);
            }
        }
        count++;
    }

    assert(knife_detected && "Nunca se recibió el arma KNIFE");
    assert(glock_detected && "Nunca se cambió a GLOCK");
    std::cout << "----------------------------------------------------------------------------------------------------------------" << std::endl;
}

void test_player_cannot_switch_to_unowned_primary_weapon(){
    std::cout << "[TEST] El jugador comienza con KNIFE y trata de cambiar al arma PRIMARY (que no tiene) — debería mantenerse con el KNIFE" << std::endl;

    using namespace std::chrono;

    ClientQueue client_queue1;

    Game game("test_party", "test_map");

    uint8_t player_id = game.add_player("Player1", client_queue1);

    std::this_thread::sleep_for(milliseconds(80));

    game.get_queue().push({player_id, SwitchWeaponEvent(WeaponType::PRIMARY)});

    std::this_thread::sleep_for(milliseconds(80));
    game.stop();

    int count = 0;

    DTO::GameStateDTO dto;
    while (client_queue1.try_pop(dto)) {
        for (const auto& player : dto.players) {
            std::cout << "[DTO: " << count << "] Player " << static_cast<int>(player.player_id)
                      << " ARMA EQUIPADA ID: " << static_cast<int>(player.weapon.id)
                      << ", LOADED AMMO: " << static_cast<int>(player.weapon.loaded_ammo)
                      << std::endl;

            assert(player.weapon.id == static_cast<uint8_t>(WeaponID::KNIFE));
        }
        count++;
    }
    std::cout << "----------------------------------------------------------------------------------------------------------------" << std::endl;
}

void test_player_buy_ak47_and_switch_auto() {
    std::cout << "[TEST] - Arranca con KNIFE (como default) compra AK47 ($800 y tiene $800) y se cambia automáticamente" << std::endl;
    using namespace std::chrono;

    ClientQueue client_queue1;

    Game game("test_party", "test_map");

    uint8_t player_id = game.add_player("Player1", client_queue1);

    std::this_thread::sleep_for(milliseconds(80));

    game.get_queue().push({player_id, BuyEvent(WeaponID::AK47)});

    std::this_thread::sleep_for(milliseconds(80));

    game.stop();

    int count = 0;
    bool weapon_was_switched = false;
    DTO::GameStateDTO dto;
    bool knife_detected = false;
    bool ak_detected = false;

    while (client_queue1.try_pop(dto)) {
        for (const auto& player : dto.players) {
            if (player.player_id != player_id) continue;

            WeaponID current_weapon = static_cast<WeaponID>(player.weapon.id);

            std::cout << "[DTO: " << count << "] Player " << static_cast<int>(player.player_id)
                    << " ARMA EQUIPADA ID: " << static_cast<int>(current_weapon)
                    << ", LOADED AMMO: " << static_cast<int>(player.weapon.loaded_ammo)
                    << std::endl;

            if (!ak_detected) {
                if (current_weapon == WeaponID::KNIFE) {
                    knife_detected = true;
                } else if (current_weapon == WeaponID::AK47) {
                    assert(knife_detected);
                    ak_detected = true;
                } else {
                    assert(false && "Arma inesperada antes del cambio a AK47");
                }
            } else {
                assert(current_weapon == WeaponID::AK47);
            }
        }
        count++;
    }

    assert(knife_detected && "Nunca se recibió el arma KNIFE");
    assert(ak_detected && "Nunca se cambió a AK47");
    std::cout << "----------------------------------------------------------------------------------------------------------------" << std::endl;
}

void test_player_buy_m3_and_switch_auto() {
    std::cout << "[TEST] - Arranca con KNIFE, compra M3 ($650 y tiene $800) y se cambia automáticamente" << std::endl;
    using namespace std::chrono;

    ClientQueue client_queue1;
    Game game("test_party", "test_map");

    uint8_t player_id = game.add_player("Player1", client_queue1);

    std::this_thread::sleep_for(milliseconds(80));

    game.get_queue().push({player_id, BuyEvent(WeaponID::M3)});

    std::this_thread::sleep_for(milliseconds(80));
    game.stop();

    int count = 0;
    bool knife_detected = false;
    bool m3_detected = false;

    DTO::GameStateDTO dto;
    while (client_queue1.try_pop(dto)) {
        for (const auto& player : dto.players) {
            if (player.player_id != player_id) continue;

            WeaponID current_weapon = static_cast<WeaponID>(player.weapon.id);

            std::cout << "[DTO: " << count << "] Player " << static_cast<int>(player.player_id)
                      << " ARMA EQUIPADA ID: " << static_cast<int>(current_weapon)
                      << ", LOADED AMMO: " << static_cast<int>(player.weapon.loaded_ammo)
                      << std::endl;

            if (!m3_detected) {
                if (current_weapon == WeaponID::KNIFE) {
                    knife_detected = true;
                } else if (current_weapon == WeaponID::M3) {
                    assert(knife_detected);
                    m3_detected = true;
                } else {
                    assert(false && "Arma inesperada antes del cambio a M3");
                }
            } else {
                assert(current_weapon == WeaponID::M3);
            }
        }
        count++;
    }

    assert(knife_detected && "Nunca se recibió el arma KNIFE");
    assert(m3_detected && "Nunca se cambió a M3");
    std::cout << "----------------------------------------------------------------------------------------------------------------" << std::endl;
}

void test_player_cannot_buy_awp_due_to_money() {
    std::cout << "[TEST] - Arranca con KNIFE y NO puede comprar AWP (cuesta 1000, tiene 800)" << std::endl;
    using namespace std::chrono;

    ClientQueue client_queue1;
    Game game("test_party", "test_map");

    uint8_t player_id = game.add_player("Player1", client_queue1);  // Tiene 800

    std::this_thread::sleep_for(milliseconds(80));

    game.get_queue().push({player_id, BuyEvent(WeaponID::AWP)});  // AWP cuesta más

    std::this_thread::sleep_for(milliseconds(80));
    game.stop();

    int count = 0;
    bool only_knife_detected = true;

    DTO::GameStateDTO dto;
    while (client_queue1.try_pop(dto)) {
        for (const auto& player : dto.players) {
            if (player.player_id != player_id) continue;

            WeaponID current_weapon = static_cast<WeaponID>(player.weapon.id);

            std::cout << "[DTO: " << count << "] Player " << static_cast<int>(player.player_id)
                      << " ARMA EQUIPADA ID: " << static_cast<int>(current_weapon)
                      << ", LOADED AMMO: " << static_cast<int>(player.weapon.loaded_ammo)
                      << std::endl;

            assert(current_weapon == WeaponID::KNIFE && "El jugador no debería haber cambiado de arma (no tenía suficiente dinero)");
        }
        count++;
    }

    std::cout << "----------------------------------------------------------------------------------------------------------------" << std::endl;
}


int main() {
    //test_round_end();
    //test_player_moves_forward_until_9_then_stops();
    //test_player_moves_correctly_with_two_different_commands();
    //test_players_have_default_guns();
    //test_player_switch_weapon();
    //test_player_cannot_switch_to_unowned_primary_weapon();
    test_player_buy_ak47_and_switch_auto();
    test_player_buy_m3_and_switch_auto();
    test_player_cannot_buy_awp_due_to_money();
    std::cout << "Pasaron los test" << std::endl;
    return 0;
}
