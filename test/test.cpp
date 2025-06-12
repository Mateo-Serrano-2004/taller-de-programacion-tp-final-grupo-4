#include <iostream>
#include <chrono>
#include <thread>
#include <cassert>

#include "../server/game/game.h"
#include "../common/DTO/game_state_dto.h"
#include "../common/queue.h"
#include "../common/slot_id.h"
#include "../common/weapon_id.h"
/*
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
    std::cout << "Esperando a que finalice la fase de compra (10s)..." << std::endl;
    std::this_thread::sleep_for(milliseconds(10000));   

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
            if(tick_count < 3 || tick_count > 620){
                std::cout << "[DTO: " << tick_count << "] Player " << static_cast<int>(player.player_id)
                      << " ARMA EQUIPADA ID: " << static_cast<int>(arma_actual)
                      << ", LOADED AMMO: " << loaded_ammo
                      << (esta_disparando ? " DISPARANDO EL ARMA" : " SIN DISPARO") << std::endl;
            }
        
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

void test_player_can_kill_other_and_earn_money() {
    std::cout << "[TEST] - Un jugador mata a otro de dos disparos. Verificamos salud, muerte, dinero y fin de ronda." << std::endl;
    using namespace std::chrono;

    ClientQueue client_queue1;
    ClientQueue client_queue2;
    Game game("test_party", "test_map");

    uint8_t player1_id = game.add_player("Player1", client_queue1);
    uint8_t player2_id = game.add_player("Player2", client_queue2);

    std::cout << "⏳ Esperando 10 segundos a que termine el tiempo de compra..." << std::endl;
    std::this_thread::sleep_for(milliseconds(10000));

    // Disparo 1
    game.get_queue().push({player1_id, UseWeaponEvent()});
    std::this_thread::sleep_for(milliseconds(32));
    game.get_queue().push({player1_id, StopUsingWeaponEvent()});
    std::this_thread::sleep_for(milliseconds(32));

    // Disparo 2
    game.get_queue().push({player1_id, UseWeaponEvent()});
    std::this_thread::sleep_for(milliseconds(32));
    game.get_queue().push({player1_id, StopUsingWeaponEvent()});
    std::this_thread::sleep_for(milliseconds(32));

    game.stop();

    int tick_count = 0;
    DTO::GameStateDTO dto;
    uint8_t last_health = 100;
    uint16_t initial_money = 0;
    bool player2_dead = false;
    bool player1_fired = false;
    bool money_earned_logged = false;
    bool death_logged = false;
    bool round_ended_detected = false;

    while (client_queue1.try_pop(dto)) {
        if (tick_count < 600) {
            tick_count++;
            continue;
        }

        std::cout << "\n[DTO TICK " << tick_count << "] ------------------------" << std::endl;
        std::cout << (dto.ended ? "🔴 RONDA TERMINADA: SÍ" : "🟢 RONDA TERMINADA: NO") << std::endl;

        if (dto.ended) {
            round_ended_detected = true;
        }

        for (const auto& player : dto.players) {
            std::cout << "Player ID: " << static_cast<int>(player.player_id)
                      << " | Nombre: " << player.name
                      << " | Arma ID: " << static_cast<int>(player.weapon_dto.weapon_id)
                      << " | Munición: " << static_cast<int>(player.weapon_dto.loaded_ammo)
                      << " | Disparando: " << (player.shooting ? "Sí" : "No")
                      << " | Dinero: $" << player.money
                      << " | Salud: " << static_cast<int>(player.health)
                      << std::endl;

            if (player.player_id == player1_id) {
                if (!player1_fired && player.shooting) {
                    player1_fired = true;
                    initial_money = player.money;
                }

                if (player2_dead && !money_earned_logged && player.money > initial_money) {
                    std::cout << "💰 PLAYER 1 GANÓ DINERO POR MATAR A PLAYER 2" << std::endl;
                    assert(player.money > initial_money && "El jugador 1 debería haber recibido dinero por la muerte.");
                    money_earned_logged = true;
                }
            }

            if (player.player_id == player2_id) {
                if (player.health < last_health) {
                    std::cout << "💥 PLAYER 2 RECIBIÓ DAÑO - Salud: " << static_cast<int>(last_health)
                              << " → " << static_cast<int>(player.health) << std::endl;
                    assert(player.health < last_health && "Player 2 debe recibir daño tras el disparo");
                }
            
                if (player.health == 0 && !death_logged) {
                    player2_dead = true;
                    std::cout << "☠️ PLAYER 2 MURIÓ" << std::endl;
                    death_logged = true;
            
                    // Inmediatamente chequeamos si Player 1 ganó dinero ya en este tick
                    for (const auto& p : dto.players) {
                        if (p.player_id == player1_id && p.money > initial_money && !money_earned_logged) {
                            std::cout << "💰 PLAYER 1 GANÓ DINERO POR MATAR A PLAYER 2" << std::endl;
                            assert(p.money > initial_money && "El jugador 1 debería haber recibido dinero por la muerte.");
                            money_earned_logged = true;
                        }
                    }
                }
            
                last_health = player.health;
            }
            
        }

        tick_count++;
    }

    assert(round_ended_detected && "La ronda debería haber terminado tras la muerte de Player 2");
    std::cout << "\n✅ Test de muerte y recompensa completado correctamente" << std::endl;
}*/

#include <iostream>
#include <chrono>
#include <thread>
#include <cassert>

#include "../server/game/game.h"
#include "../common/DTO/game_state_dto.h"
#include "../common/queue.h"
#include "../common/slot_id.h"
#include "../common/weapon_id.h"

const char* to_string(RoundState state) {
    switch (state) {
        case RoundState::Warmup: return "Warmup";
        case RoundState::Buying: return "Buying";
        case RoundState::Active: return "Active";
        case RoundState::Ended:  return "Ended";
        default: return "Unknown";
    }
}

void test_cambio_ronda() {
    std::cout << "[TEST] - Cambio de ronda" << std::endl;
    using namespace std::chrono;

    ClientQueue client_queue1;
    ClientQueue client_queue2;
    Game game("test_party", "test_map");

    uint8_t player1_id = game.add_player("Player1", client_queue1, Model::TeamID::CT, Model::RoleID::CT1);
    uint8_t player2_id = game.add_player("Player2", client_queue2, Model::TeamID::TT, Model::RoleID::T1);

    std::this_thread::sleep_for(seconds(7));
    game.get_queue().push({player2_id, UseWeaponEvent()});
    std::this_thread::sleep_for(milliseconds(32));
    game.get_queue().push({player2_id, StopUsingWeaponEvent()});
    std::this_thread::sleep_for(milliseconds(32));
    game.get_queue().push({player2_id, UseWeaponEvent()});
    std::this_thread::sleep_for(milliseconds(32));
    game.get_queue().push({player2_id, StopUsingWeaponEvent()});
    std::this_thread::sleep_for(seconds(53));
    game.stop();

    DTO::GameStateDTO last_printed_dto;
    bool printed_first = false;

    DTO::GameStateDTO current_dto;
    while (client_queue1.try_pop(current_dto)) {
        bool should_print = false;

        if (!printed_first) {
            should_print = true;
        } else if (
            current_dto.round.ended != last_printed_dto.round.ended ||
            current_dto.round.state != last_printed_dto.round.state
        ) {
            should_print = true;
        }

        if (should_print) {
            std::cout << "\n[DTO CAMBIADO] ------------------------" << std::endl;

            // RONDA
            std::cout << (current_dto.round.state == RoundState::Warmup ? "❌ RONDA WARMUP" : "✅ RONDA QUE CUENTA") << " | ";
            std::cout << (current_dto.round.ended ? "🔴 RONDA TERMINADA" : "🟢 RONDA EN CURSO") << " | ";
            std::cout << "⏳ Tiempo restante: " << static_cast<int>(current_dto.round.time_left) << "s" << std::endl;
            std::cout << "📍 Estado de la ronda: " << to_string(current_dto.round.state) << std::endl;

            // GAME
            std::cout << "🎮 Estado del juego: ";
            switch (current_dto.game_state) {
                case GameState::WaitingStart: std::cout << "Esperando inicio"; break;
                case GameState::Playing:      std::cout << "Jugando"; break;
                case GameState::Finished:     std::cout << "Finalizado"; break;
            }
            std::cout << std::endl;

            std::cout << "🏆 Ganador de la partida: ";
            switch (current_dto.winner) {
                case Model::TeamID::CT:   std::cout << "CT"; break;
                case Model::TeamID::TT:   std::cout << "TT"; break;
                case Model::TeamID::NONE: std::cout << "Ninguno"; break;
            }
            std::cout << std::endl;

            std::cout << "🔢 Rondas ganadas - CT: " << static_cast<int>(current_dto.ct_rounds_won)
                      << " | TT: " << static_cast<int>(current_dto.tt_rounds_won) << std::endl;

            // PLAYERS
            for (const auto& player : current_dto.players) {
                std::cout << "Player ID: " << static_cast<int>(player.player_id)
                          << " | Nombre: " << player.name
                          << " | Arma ID: " << static_cast<int>(player.weapon_dto.weapon_id)
                          << " | Munición: " << static_cast<int>(player.weapon_dto.loaded_ammo)
                          << " | Disparando: " << (player.shooting ? "Sí" : "No")
                          << " | Dinero: $" << player.money
                          << " | Salud: " << static_cast<int>(player.health)
                          << " | Pos: (" << player.position_x << ", " << player.position_y << ")"
                          << std::endl;
            }

            last_printed_dto = current_dto;
            printed_first = true;
        }
    }
}

int main() {
    //test_player_can_shoot_not_automatic_weapon();
    //test_player_shoots_only_once_after_two_triggers();
    //test_player_shoots_twice_with_release_in_between();
    //test_player_buy_m3_and_switch_auto();
    //test_player_buy_ak47_and_hold_fire();
    //test_player_can_kill_other_and_earn_money();
    test_cambio_ronda();
    std::cout << "Pasaron los test" << std::endl;
    return 0;
}