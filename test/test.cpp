#include <iostream>
#include <chrono>
#include <thread>
#include <cassert>

#include "../server/game/game.h"
#include "../common/DTO/game_state_dto.h"
#include "../common/queue.h"
#include "../common/slot_id.h"
#include "../common/weapon_id.h"

void test_player_can_shoot_not_automatic_weapon() {
    std::cout << "[TEST] - Arranca con GLOCK y dispara" << std::endl;
    using namespace std::chrono;

    ClientQueue client_queue1;
    Game game("test_party", "test_map");

    uint8_t player_id = game.add_player("Player1", client_queue1);

    std::this_thread::sleep_for(milliseconds(80));

    game.get_queue().push({player_id, UseWeaponEvent()});

    std::this_thread::sleep_for(milliseconds(80));

    game.stop();

    int tick_count = 0;
    bool hubo_ticks_sin_disparo_antes = false;
    bool se_detecto_disparo = false;
    bool hubo_ticks_sin_disparo_despues = false;
    bool ya_ocurrio_disparo = false;
    int last_loaded_ammo = 99999;
    DTO::GameStateDTO dto;
    while (client_queue1.try_pop(dto)) {
        for (const auto& player : dto.players) {
            if (player.player_id != player_id) continue;

            Model::WeaponID arma_actual = static_cast<Model::WeaponID>(player.weapon_dto.weapon_id);
            bool esta_disparando = player.shooting;
            int loaded_ammo = static_cast<int>(player.weapon_dto.loaded_ammo);
            std::cout << "[DTO: " << tick_count << "] Player " << static_cast<int>(player.player_id)
                      << " ARMA EQUIPADA ID: " << static_cast<int>(arma_actual)
                      << ", LOADED AMMO: " << loaded_ammo
                      << (esta_disparando ? " DISPARANDO EL ARMA" : " SIN DISPARO") << std::endl;
            assert(loaded_ammo <= last_loaded_ammo);
            last_loaded_ammo = loaded_ammo;
            if (!esta_disparando && !se_detecto_disparo)
                hubo_ticks_sin_disparo_antes = true;

            if (esta_disparando) {
                assert(!se_detecto_disparo && "El jugador no debería disparar más de una vez (arma no automática)");
                se_detecto_disparo = true;
                ya_ocurrio_disparo = true;
            } else if (ya_ocurrio_disparo) {
                hubo_ticks_sin_disparo_despues = true;
            }
        }
        tick_count++;
    }

    // Validaciones finales
    assert(hubo_ticks_sin_disparo_antes && "Debe haber al menos un tick sin disparo antes del disparo");
    assert(se_detecto_disparo && "Debe haber exactamente un tick con disparo");
    assert(hubo_ticks_sin_disparo_despues && "Debe haber al menos un tick sin disparo después del único disparo");

    std::cout << "----------------------------------------------------------------------------------------------------------------" << std::endl;
}

void test_player_shoots_only_once_after_two_triggers() {
    std::cout << "[TEST] - GLOCK no dispara más de una vez aunque se intente dos veces" << std::endl;
    using namespace std::chrono;

    ClientQueue client_queue1;
    Game game("test_party", "test_map");

    uint8_t player_id = game.add_player("Player1", client_queue1);

    std::this_thread::sleep_for(milliseconds(80));
    
    game.get_queue().push({player_id, UseWeaponEvent()});
    std::this_thread::sleep_for(milliseconds(40));

    game.get_queue().push({player_id, UseWeaponEvent()});
    std::this_thread::sleep_for(milliseconds(80));

    game.stop();

    int tick_count = 0;
    bool hubo_ticks_sin_disparo_antes = false;
    bool se_detecto_disparo = false;
    bool hubo_ticks_sin_disparo_despues = false;
    bool ya_ocurrio_disparo = false;
    int last_loaded_ammo = 9999;
    DTO::GameStateDTO dto;
    while (client_queue1.try_pop(dto)) {
        for (const auto& player : dto.players) {
            if (player.player_id != player_id) continue;

            Model::WeaponID arma_actual = static_cast<Model::WeaponID>(player.weapon_dto.weapon_id);
            bool esta_disparando = player.shooting;
            int loaded_ammo = static_cast<int>(player.weapon_dto.loaded_ammo);
            std::cout << "[DTO: " << tick_count << "] Player " << static_cast<int>(player.player_id)
                      << " ARMA EQUIPADA ID: " << static_cast<int>(arma_actual)
                      << ", LOADED AMMO: " << loaded_ammo
                      << (esta_disparando ? " DISPARANDO EL ARMA" : " SIN DISPARO") << std::endl;

            assert(loaded_ammo <= last_loaded_ammo);
            last_loaded_ammo = loaded_ammo;
            if (!esta_disparando && !se_detecto_disparo)
                hubo_ticks_sin_disparo_antes = true;

            if (esta_disparando) {
                assert(!se_detecto_disparo && "El jugador no debería disparar más de una vez (arma no automática)");
                se_detecto_disparo = true;
                ya_ocurrio_disparo = true;
            } else if (ya_ocurrio_disparo) {
                hubo_ticks_sin_disparo_despues = true;
            }
        }
        tick_count++;
    }

    // Validaciones finales
    assert(hubo_ticks_sin_disparo_antes && "Debe haber al menos un tick sin disparo antes del disparo");
    assert(se_detecto_disparo && "Debe haber exactamente un tick con disparo");
    assert(hubo_ticks_sin_disparo_despues && "Debe haber al menos un tick sin disparo después del único disparo");

    std::cout << "----------------------------------------------------------------------------------------------------------------" << std::endl;
}

void test_player_shoots_twice_with_release_in_between() {
    std::cout << "[TEST] - GLOCK dispara dos veces NO consecutivas con release intermedio" << std::endl;
    using namespace std::chrono;

    ClientQueue client_queue1;
    Game game("test_party", "test_map");

    uint8_t player_id = game.add_player("Player1", client_queue1);

    std::this_thread::sleep_for(milliseconds(80));

    game.get_queue().push({player_id, UseWeaponEvent()});
    std::this_thread::sleep_for(milliseconds(40));

    game.get_queue().push({player_id, StopUsingWeaponEvent()});
    std::this_thread::sleep_for(milliseconds(80));

    game.get_queue().push({player_id, UseWeaponEvent()});
    std::this_thread::sleep_for(milliseconds(80));

    game.stop();

    int tick_count = 0;
    int cantidad_ticks_con_disparo = 0;
    std::vector<int> ticks_con_disparo;
    int last_loaded_ammo = 999999;
    DTO::GameStateDTO dto;
    while (client_queue1.try_pop(dto)) {
        for (const auto& player : dto.players) {
            if (player.player_id != player_id) continue;

            Model::WeaponID arma_actual = static_cast<Model::WeaponID>(player.weapon_dto.weapon_id);
            bool esta_disparando = player.shooting;
            int loaded_ammo = static_cast<int>(player.weapon_dto.loaded_ammo);

            std::cout << "[DTO: " << tick_count << "] Player " << static_cast<int>(player.player_id)
                      << " ARMA EQUIPADA ID: " << static_cast<int>(arma_actual)
                      << ", LOADED AMMO: " << loaded_ammo
                      << (esta_disparando ? " DISPARANDO EL ARMA" : " SIN DISPARO") << std::endl;
            assert(loaded_ammo <= last_loaded_ammo);
            last_loaded_ammo = loaded_ammo;
            if (esta_disparando) {
                cantidad_ticks_con_disparo++;
                ticks_con_disparo.push_back(tick_count);
            }
        }
        tick_count++;
    }

    assert(cantidad_ticks_con_disparo == 2 && "Debe haber exactamente dos ticks con disparo");

    // Validar que los disparos no hayan sido en ticks consecutivos
    assert((ticks_con_disparo[1] - ticks_con_disparo[0]) >= 2 && "Los dos disparos no deben ser consecutivos");

    std::cout << "----------------------------------------------------------------------------------------------------------------" << std::endl;
}



int main() {
    test_player_can_shoot_not_automatic_weapon();
    test_player_shoots_only_once_after_two_triggers();
    test_player_shoots_twice_with_release_in_between();
    std::cout << "Pasaron los test" << std::endl;
    return 0;
}
