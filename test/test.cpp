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

void test_player_buy_m3_and_switch_auto() {
    std::cout << "[TEST] - Arranca con GLOCK, compra M3 ($650 y tiene $800) y se cambia automáticamente" << std::endl;
    using namespace std::chrono;

    ClientQueue client_queue1;
    Game game("test_party", "test_map");

    uint8_t player_id = game.add_player("Player1", client_queue1);

    std::this_thread::sleep_for(milliseconds(100));  

    game.get_queue().push({player_id, BuyEvent(Model::WeaponID::M3)});  

    std::this_thread::sleep_for(milliseconds(100));

    game.stop();

    int tick_count = 0;
    bool glock_detected = false;
    bool m3_detected = false;

    DTO::GameStateDTO dto;
    while (client_queue1.try_pop(dto)) {
        for (const auto& player : dto.players) {
            if (player.player_id != player_id) continue;

            Model::WeaponID arma_actual = static_cast<Model::WeaponID>(player.weapon_dto.weapon_id);
            int loaded_ammo = static_cast<int>(player.weapon_dto.loaded_ammo);

            std::cout << "[DTO: " << tick_count << "] Player " << static_cast<int>(player.player_id)
                      << " ARMA EQUIPADA ID: " << static_cast<int>(arma_actual)
                      << ", LOADED AMMO: " << loaded_ammo << std::endl;

            if (!m3_detected) {
                if (arma_actual == Model::WeaponID::GLOCK) {
                    glock_detected = true;
                } else if (arma_actual == Model::WeaponID::M3) {
                    assert(glock_detected && "Debe haber pasado por GLOCK antes de cambiar a M3");
                    m3_detected = true;
                } else {
                    assert(false && "Arma inesperada antes del cambio a M3");
                }
            } else {
                assert(arma_actual == Model::WeaponID::M3 && "Después del cambio solo debería tener M3 equipada");
            }
        }
        tick_count++;
    }

    assert(glock_detected && "Nunca se detectó el arma GLOCK equipada");
    assert(m3_detected && "Nunca se cambió a M3");
    std::cout << "----------------------------------------------------------------------------------------------------------------" << std::endl;
}

void test_player_buy_ak47_and_hold_fire() {
    std::cout << "[TEST] - AK47 dispara varias veces pero nunca en ticks consecutivos (respeta cooldown)" << std::endl;
    using namespace std::chrono;

    ClientQueue client_queue1;
    Game game("test_party", "test_map");

    uint8_t player_id = game.add_player("Player1", client_queue1);
    std::this_thread::sleep_for(milliseconds(32));

    game.get_queue().push({player_id, BuyEvent(Model::WeaponID::AK47)});
    std::this_thread::sleep_for(milliseconds(80));  

    game.get_queue().push({player_id, UseWeaponEvent()});
    std::this_thread::sleep_for(milliseconds(300));  

    game.get_queue().push({player_id, StopUsingWeaponEvent()});
    std::this_thread::sleep_for(milliseconds(50));
    
    game.stop();

    int tick_count = 0;
    bool arma_era_ak = false;
    bool ya_tenia_ak = false;
    int last_loaded_ammo = -1;

    int cantidad_disparos = 0;
    bool disparando_anterior = false;

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

            if (arma_actual == Model::WeaponID::AK47) {
                if (!ya_tenia_ak) {
                    ya_tenia_ak = true;
                    last_loaded_ammo = loaded_ammo;
                }

                assert(loaded_ammo <= last_loaded_ammo && "La munición no debería aumentar después de tener el AK47");
                last_loaded_ammo = loaded_ammo;

                if (esta_disparando) {
                    cantidad_disparos++;
                    assert(!disparando_anterior && "No debe haber dos DTOs consecutivos disparando con AK47");
                    disparando_anterior = true;
                } else {
                    disparando_anterior = false;
                }
            }
        }
        tick_count++;
    }

    // Validaciones finales
    assert(ya_tenia_ak && "El jugador nunca cambió a AK47");
    assert(cantidad_disparos >= 2 && "Debe haber al menos dos disparos (no consecutivos)");

    std::cout << "----------------------------------------------------------------------------------------------------------------" << std::endl;
}

int main() {
    test_player_can_shoot_not_automatic_weapon();
    test_player_shoots_only_once_after_two_triggers();
    test_player_shoots_twice_with_release_in_between();
    //test_player_buy_m3_and_switch_auto();
    test_player_buy_ak47_and_hold_fire();
    std::cout << "Pasaron los test" << std::endl;
    return 0;
}