#include <iostream>
#include <chrono>
#include <thread>
#include <cassert>

#include "../server/game/game.h"
#include "../common/DTO/game_state_dto.h"
#include "../common/DTO/dto_variant.h"
#include "../common/DTO/drop_weapon_dto.h"
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
    std::cout << "[TEST] - 2 rondas con tiempos 1,5 s warmup, 10 segundos compra y 60 de jugar. En la primera muere el unico ct por disparos y en la segunda gana por tiempo ct" << std::endl;
    using namespace std::chrono;

    ClientQueue client_queue1;
    ClientQueue client_queue2;
    Game game("test_party", "test_map");

    uint8_t player1_id = 1;
    uint8_t player2_id = 2; 

    game.add_player("Player2", client_queue2, player2_id, Model::TeamID::TT, Model::RoleID::T1);
    game.add_player("Player1", client_queue1, player1_id, Model::TeamID::CT, Model::RoleID::CT1);
    

    std::cout << "ESPERANDO WARMUP Y TIEMPO DE COMPRA DE LA RONDA 1:" << std::endl;
    std::this_thread::sleep_for(seconds(12));
    game.get_queue().push({player2_id, UseWeaponEvent()});
    std::this_thread::sleep_for(milliseconds(32));
    game.get_queue().push({player2_id, StopUsingWeaponEvent()});
    std::this_thread::sleep_for(milliseconds(32));
    game.get_queue().push({player2_id, UseWeaponEvent()});
    std::this_thread::sleep_for(milliseconds(32));
    game.get_queue().push({player2_id, StopUsingWeaponEvent()});
    std::this_thread::sleep_for(milliseconds(32));
    game.get_queue().push({player2_id, UseWeaponEvent()});
    std::this_thread::sleep_for(milliseconds(32));
    game.get_queue().push({player2_id, StopUsingWeaponEvent()});
    std::this_thread::sleep_for(milliseconds(32));
    game.get_queue().push({player2_id, UseWeaponEvent()});
    std::this_thread::sleep_for(milliseconds(32));
    game.get_queue().push({player2_id, StopUsingWeaponEvent()});
    std::this_thread::sleep_for(milliseconds(32));
    game.get_queue().push({player2_id, UseWeaponEvent()});
    std::this_thread::sleep_for(milliseconds(32));
    game.get_queue().push({player2_id, StopUsingWeaponEvent()});
    std::cout << "DEBERÍA HABER MUERTO EL CT" << std::endl;
    std::cout << "ESPERANDO 1 MINUTOS Y 11 SEGUNDOS A QUE TERMINE LA APRTIDA" << std::endl;
    std::this_thread::sleep_for(seconds(71));
    game.stop();

    DTO::GameStateDTO last_printed_dto;
    DTO::GameStateDTO final_dto;
    bool printed_first = false;


    DTO::DTOVariant current_dto_variant;
    while (client_queue1.try_pop(current_dto_variant)) {
        if (!std::holds_alternative<DTO::GameStateDTO>(current_dto_variant)) {
            continue;
        }

        const auto& current_dto = std::get<DTO::GameStateDTO>(current_dto_variant);

        bool should_print = false;

        // Detectar cambios en estado de ronda
        if (!printed_first) {
            should_print = true;
        } else if (
            current_dto.round.ended != last_printed_dto.round.ended ||
            current_dto.round.state != last_printed_dto.round.state
        ) {
            should_print = true;
        } else {
            // ✅ Detectar cambio en vida de al menos un jugador
            for (const auto& current_player : current_dto.players) {
                auto it = std::find_if(
                    last_printed_dto.players.begin(),
                    last_printed_dto.players.end(),
                    [&](const DTO::PlayerDTO& p) { return p.player_id == current_player.player_id; });

                if (it != last_printed_dto.players.end() && it->health != current_player.health) {
                    should_print = true;
                    break;
                }
            }
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

        final_dto = current_dto; 
    }

    // Mostrar explícitamente el DTO final
    std::cout << "\n✅ [ÚLTIMO DTO RECIBIDO] ------------------------" << std::endl;
    std::cout << "📍 Estado de la ronda: " << to_string(final_dto.round.state) << std::endl;
    std::cout << "🎮 Estado del juego: " << (final_dto.game_state == GameState::Finished ? "Finalizado" : "Otro") << std::endl;
    std::cout << "🏆 Ganador de la partida: "
              << (final_dto.winner == Model::TeamID::CT ? "CT" :
                 (final_dto.winner == Model::TeamID::TT ? "TT" : "Ninguno")) << std::endl;
    std::cout << "🔢 Rondas ganadas - CT: " << static_cast<int>(final_dto.ct_rounds_won)
              << " | TT: " << static_cast<int>(final_dto.tt_rounds_won) << std::endl;

    // Asserts con el DTO más reciente
    assert(final_dto.round.state == RoundState::Ended && "La ronda final no terminó correctamente");
    assert(final_dto.game_state == GameState::Finished && "El estado del juego no es 'Finished'");
    assert(final_dto.winner == Model::TeamID::NONE && "Debería ser empate");
    assert(final_dto.ct_rounds_won == 1 && "CT debería haber ganado 1 ronda");
    assert(final_dto.tt_rounds_won == 1 && "TT debería haber ganado 1 ronda");

    bool found_player1 = false, found_player2 = false;
    for (const auto& player : final_dto.players) {
        if (player.player_id == player1_id) {
            assert(player.money == 2000 && "El jugador 1 (CT) debería tener $2000");
            found_player1 = true;
        } else if (player.player_id == player2_id) {
            assert(player.money == 2800 && "El jugador 2 (TT) debería tener $2800");
            found_player2 = true;
        }
    }

    assert(found_player1 && "No se encontró al jugador 1 en el DTO final");
    assert(found_player2 && "No se encontró al jugador 2 en el DTO final");
}

void test_finaliza_por_muerte_ct() {
    std::cout << "[TEST] - PARTIDA A 1 RONDA - termina cuando muere el CT, TT gana 1-0 y tiene $3300" << std::endl;

    using namespace std::chrono;

    ClientQueue client_queue1;
    ClientQueue client_queue2;
    Game game("test_party", "test_map");

    uint8_t ct_id = 1;
    uint8_t tt_id = 2;

    game.add_player("CT", client_queue1, ct_id, Model::TeamID::CT, Model::RoleID::CT1);
    game.add_player("TT", client_queue2, tt_id, Model::TeamID::TT, Model::RoleID::T1);

    std::this_thread::sleep_for(seconds(12));  // Warmup + buy

    // TT dispara varias veces
    for (int i = 0; i < 4; ++i) {
        game.get_queue().push({tt_id, UseWeaponEvent()});
        std::this_thread::sleep_for(milliseconds(32));
        game.get_queue().push({tt_id, StopUsingWeaponEvent()});
        std::this_thread::sleep_for(milliseconds(32));
    }

    // Esperar a que llegue el DTO con ronda terminada
    std::this_thread::sleep_for(seconds(2));
    game.stop();

    DTO::DTOVariant dto;
    DTO::GameStateDTO final_dto;
    while (client_queue1.try_pop(dto)) {
        if (std::holds_alternative<DTO::GameStateDTO>(dto)) {
            final_dto = std::get<DTO::GameStateDTO>(dto);
        }
    }

    // Chequeos
    assert(final_dto.round.state == RoundState::Ended);
    assert(final_dto.game_state == GameState::Finished);
    assert(final_dto.winner == Model::TeamID::TT);
    assert(final_dto.tt_rounds_won == 1);
    assert(final_dto.ct_rounds_won == 0);

    bool tt_money_ok = false;
    for (const auto& p : final_dto.players) {
        if (p.player_id == tt_id && p.money == 3300) {
            tt_money_ok = true;
        }
    }

    assert(tt_money_ok && "El TT debería tener $3300 tras ganar la ronda");
    std::cout << "✅ Test finaliza_por_muerte_ct pasó correctamente\n";
}

void test_rotacion_y_disparo() {
    std::cout << "[TEST] - PARTIDA 1 RONDA. PLAYER 2 APUNTA 135 GRADOS Y MATA A 1. p2=(100,100) y p1=(130,40)" << std::endl;

    using namespace std::chrono;

    ClientQueue client_queue1;
    ClientQueue client_queue2;
    Game game("test_party", "test_map");

    uint8_t ct_id = 1;
    uint8_t tt_id = 2;

    game.add_player("CT", client_queue1, ct_id, Model::TeamID::CT, Model::RoleID::CT1);
    game.add_player("TT", client_queue2, tt_id, Model::TeamID::TT, Model::RoleID::T1);

    std::this_thread::sleep_for(seconds(12));  // Warmup + buy

    // 🌀 Rotar a 135 grados antes de disparar
    game.get_queue().push({tt_id, RotationEvent(135)});
    std::this_thread::sleep_for(milliseconds(32));

    // TT dispara varias veces
    for (int i = 0; i < 4; ++i) {
        game.get_queue().push({tt_id, UseWeaponEvent()});
        std::this_thread::sleep_for(milliseconds(32));
        game.get_queue().push({tt_id, StopUsingWeaponEvent()});
        std::this_thread::sleep_for(milliseconds(32));
    }

    // Esperar DTO final
    std::this_thread::sleep_for(seconds(2));
    game.stop();

    DTO::DTOVariant dto;
    DTO::GameStateDTO final_dto;
    while (client_queue1.try_pop(dto)) {
        if (std::holds_alternative<DTO::GameStateDTO>(dto)) {
            final_dto = std::get<DTO::GameStateDTO>(dto);
        }
    }

    assert(final_dto.round.state == RoundState::Ended);
    assert(final_dto.game_state == GameState::Finished);
    assert(final_dto.winner == Model::TeamID::TT);
    assert(final_dto.tt_rounds_won == 1);
    assert(final_dto.ct_rounds_won == 0);

    bool tt_money_ok = false;
    for (const auto& p : final_dto.players) {
        if (p.player_id == tt_id && p.money == 3300) {
            tt_money_ok = true;
        }
    }

    assert(tt_money_ok && "El TT debería tener $3300 tras ganar la ronda");
    std::cout << "✅ Test rotacion_y_disparo pasó correctamente\n";
}

void test_rotacion_y_disparo_2() {
    std::cout << "[TEST] - PARTIDA 1 RONDA. PLAYER 2 APUNTA 90 GRADOS Y MATA A 1. p2=(100,100) y p1=(300,100)" << std::endl;

    using namespace std::chrono;

    ClientQueue client_queue1;
    ClientQueue client_queue2;
    Game game("test_party", "test_map");

    uint8_t ct_id = 1;
    uint8_t tt_id = 2;

    game.add_player("CT", client_queue1, ct_id, Model::TeamID::CT, Model::RoleID::CT1);
    game.add_player("TT", client_queue2, tt_id, Model::TeamID::TT, Model::RoleID::T1);

    std::this_thread::sleep_for(seconds(12));  // Warmup + buy

    // 🌀 Rotar a 90 grados antes de disparar
    game.get_queue().push({tt_id, RotationEvent(90)});
    std::this_thread::sleep_for(milliseconds(32));

    // TT dispara varias veces
    for (int i = 0; i < 5; ++i) {
        game.get_queue().push({tt_id, UseWeaponEvent()});
        std::this_thread::sleep_for(milliseconds(32));
        game.get_queue().push({tt_id, StopUsingWeaponEvent()});
        std::this_thread::sleep_for(milliseconds(32));
    }

    // Esperar DTO final
    std::this_thread::sleep_for(seconds(2));
    game.stop();

    DTO::DTOVariant dto;
    DTO::GameStateDTO final_dto;
    while (client_queue1.try_pop(dto)) {
        if (std::holds_alternative<DTO::GameStateDTO>(dto)) {
            final_dto = std::get<DTO::GameStateDTO>(dto);
        }
    }

    assert(final_dto.round.state == RoundState::Ended);
    assert(final_dto.game_state == GameState::Finished);
    assert(final_dto.winner == Model::TeamID::TT);
    assert(final_dto.tt_rounds_won == 1);
    assert(final_dto.ct_rounds_won == 0);

    bool tt_money_ok = false;
    for (const auto& p : final_dto.players) {
        if (p.player_id == tt_id && p.money == 3300) {
            tt_money_ok = true;
        }
    }

    assert(tt_money_ok && "El TT debería tener $3300 tras ganar la ronda");
    std::cout << "✅ Test rotacion_y_disparo pasó correctamente\n";
}

void test_rotacion_y_disparo_m3() {
    std::cout << "[TEST] - PARTIDA 1 RONDA. (con M3) PLAYER 2 APUNTA 90 GRADOS Y MATA A 1. p2=(100,100) y p1=(140,100)" << std::endl;

    using namespace std::chrono;

    ClientQueue client_queue1;
    ClientQueue client_queue2;
    Game game("test_party", "test_map");

    uint8_t ct_id = 1;
    uint8_t tt_id = 2;

    game.add_player("CT", client_queue1, ct_id, Model::TeamID::CT, Model::RoleID::CT1);
    game.add_player("TT", client_queue2, tt_id, Model::TeamID::TT, Model::RoleID::T1);

    std::this_thread::sleep_for(seconds(2));  // Warmup

    game.get_queue().push({tt_id, BuyEvent(Model::WeaponID::M3)});

    std::this_thread::sleep_for(seconds(10));

    // 🌀 Rotar a 90 grados antes de disparar
    game.get_queue().push({tt_id, RotationEvent(90)});
    std::this_thread::sleep_for(milliseconds(32));

    // TT dispara varias veces
    for (int i = 0; i < 1; ++i) {
        game.get_queue().push({tt_id, UseWeaponEvent()});
        std::this_thread::sleep_for(milliseconds(32));
        game.get_queue().push({tt_id, StopUsingWeaponEvent()});
        std::this_thread::sleep_for(milliseconds(32));
    }

    // Esperar DTO final
    std::this_thread::sleep_for(seconds(2));
    game.stop();

    DTO::DTOVariant dto;
    DTO::GameStateDTO final_dto;
    while (client_queue1.try_pop(dto)) {
        if (std::holds_alternative<DTO::GameStateDTO>(dto)) {
            final_dto = std::get<DTO::GameStateDTO>(dto);
        }
    }

    assert(final_dto.round.state == RoundState::Ended);
    assert(final_dto.game_state == GameState::Finished);
    assert(final_dto.winner == Model::TeamID::TT);
    assert(final_dto.tt_rounds_won == 1);
    assert(final_dto.ct_rounds_won == 0);

    bool tt_money_ok = false;
    for (const auto& p : final_dto.players) {
        if (p.player_id == tt_id && p.money == 2700) {
            std::cout << "dinero del tt: " << p.money << std::endl;
            tt_money_ok = true;
        }
    }

    assert(tt_money_ok && "El TT debería tener $2700 tras ganar la ronda");
    std::cout << "✅ Test rotacion_y_disparo_M3 pasó correctamente\n";
}

void test_disparo_con_reload() {
    std::cout << "[TEST] - PARTIDA 1 RONDA. PLAYER 2 DISPARA 2 VECES, RECARGA, Y DISPARA 2 VECES MÁS\n";

    using namespace std::chrono;

    ClientQueue client_queue1;
    ClientQueue client_queue2;
    Game game("test_party", "test_map");

    uint8_t ct_id = 1;
    uint8_t tt_id = 2;

    game.add_player("CT", client_queue1, ct_id, Model::TeamID::CT, Model::RoleID::CT1);
    game.add_player("TT", client_queue2, tt_id, Model::TeamID::TT, Model::RoleID::T1);

    std::this_thread::sleep_for(seconds(12));  // Warmup + buy

    // 🌀 Rotar a 90 grados
    game.get_queue().push({tt_id, RotationEvent(90)});
    std::this_thread::sleep_for(milliseconds(32));

    // 🔫 Disparar 2 veces
    for (int i = 0; i < 2; ++i) {
        game.get_queue().push({tt_id, UseWeaponEvent()});
        std::this_thread::sleep_for(milliseconds(32));
        game.get_queue().push({tt_id, StopUsingWeaponEvent()});
        std::this_thread::sleep_for(milliseconds(32));
    }

    // 🔁 Recargar arma
    game.get_queue().push({tt_id, ReloadWeaponEvent()});
    std::this_thread::sleep_for(seconds(2));
    game.get_queue().push({tt_id, StopReloadingEvent()});
    std::this_thread::sleep_for(milliseconds(32));

    // 🔫 Disparar otras 2 veces
    for (int i = 0; i < 2; ++i) {
        game.get_queue().push({tt_id, UseWeaponEvent()});
        std::this_thread::sleep_for(milliseconds(32));
        game.get_queue().push({tt_id, StopUsingWeaponEvent()});
        std::this_thread::sleep_for(milliseconds(32));
    }

    std::this_thread::sleep_for(seconds(2));
    game.stop();

    DTO::DTOVariant dto;
    DTO::GameStateDTO final_dto;
    DTO::GameStateDTO last_dto;
    bool first = true;

    std::unordered_map<uint8_t, bool> was_reloading;

    while (client_queue1.try_pop(dto)) {
        if (!std::holds_alternative<DTO::GameStateDTO>(dto)) continue;
        const auto& g_dto = std::get<DTO::GameStateDTO>(dto);
        final_dto = g_dto;

        for (const auto& p : g_dto.players) {
            uint8_t pid = p.player_id;

            // 🔄 Mostrar solo si reloading cambia de false a true
            bool prev_reloading = was_reloading[pid];
            if (p.reloading && !prev_reloading) {
                std::cout << "\n♻️ [RECARGANDO] ------------------------" << std::endl;
                std::cout << "👤 Player " << static_cast<int>(p.player_id)
                          << " está recargando su arma." << std::endl;
            }
            was_reloading[pid] = p.reloading;

            // 💥 Mostrar si cambia loaded_ammo (usando p.weapon.loaded_ammo)
            if (!first) {
                auto it = std::find_if(last_dto.players.begin(), last_dto.players.end(),
                                       [&](const DTO::PlayerDTO& old_p) {
                                           return old_p.player_id == p.player_id;
                                       });

                if (it != last_dto.players.end() &&
                    it->weapon_dto.loaded_ammo != p.weapon_dto.loaded_ammo) {
                    std::cout << "\n🔫 [AMMO CAMBIADO] ------------------------" << std::endl;
                    std::cout << "👤 Player " << static_cast<int>(p.player_id)
                              << " | Munición cargada: " << static_cast<int>(p.weapon_dto.loaded_ammo)
                              << " (antes: " << static_cast<int>(it->weapon_dto.loaded_ammo) << ")\n";
                }
            }
        }

        last_dto = g_dto;
        first = false;
    }

    // Asserts
    assert(final_dto.round.state == RoundState::Ended);
    assert(final_dto.game_state == GameState::Finished);
    assert(final_dto.winner == Model::TeamID::TT);
    assert(final_dto.tt_rounds_won == 1);
    assert(final_dto.ct_rounds_won == 0);

    bool tt_money_ok = false;
    for (const auto& p : final_dto.players) {
        if (p.player_id == tt_id && p.money == 3300) {
            tt_money_ok = true;
        }
    }

    assert(tt_money_ok && "El TT debería tener $3300 tras ganar la ronda");
    std::cout << "✅ Test disparo_con_reload pasó correctamente\n";
}

void test_bomba_y_estado_round() {
    std::cout << "[TEST] - Simulación de bomba plantada y estados de ronda" << std::endl;
    using namespace std::chrono;

    ClientQueue client_queue1;
    ClientQueue client_queue2;
    Game game("test_party", "test_map");

    uint8_t player1_id = 1;
    uint8_t player2_id = 2; 
    game.add_player("Player1", client_queue1, player1_id, Model::TeamID::CT, Model::RoleID::CT1);
    game.add_player("Player2", client_queue2, player2_id, Model::TeamID::TT, Model::RoleID::T1);

    // Salir de warmup (por ej. 11s)
    std::this_thread::sleep_for(seconds(11));

    // Cambiar a bomba
    game.get_queue().push({player2_id, SwitchWeaponEvent(Model::SlotID::BOMB_SLOT)});

    std::this_thread::sleep_for(seconds(10));

    game.get_queue().push({player2_id, UseWeaponEvent()});
    std::this_thread::sleep_for(seconds(4));
    game.get_queue().push({player2_id, StopUsingWeaponEvent()});

    std::this_thread::sleep_for(seconds(8));
    
    // Finaliza el juego
    game.stop();

    bool printed_bomb_planted = false;
    bool printed_ended = false;

    DTO::DTOVariant current_dto_variant;
    while (client_queue1.try_pop(current_dto_variant)) {
        if (!std::holds_alternative<DTO::GameStateDTO>(current_dto_variant)) continue;
        const auto& dto = std::get<DTO::GameStateDTO>(current_dto_variant);
        const auto& round = dto.round;

        if (round.state == RoundState::Warmup || round.state == RoundState::Buying) continue;

        if (!printed_bomb_planted && round.state == RoundState::Active && round.bomb_planted) {
            std::cout << "\n🧨 Bomba plantada en ronda activa:" << std::endl;
            std::cout << "📍 Posición de bomba: (" << round.bomb_position.get_x()
                      << ", " << round.bomb_position.get_y() << ")" << std::endl;
            std::cout << "⏳ Tiempo restante: " << static_cast<int>(round.time_left) << "s" << std::endl;
            printed_bomb_planted = true;
            continue;
        }

        if (!printed_ended && round.state == RoundState::Ended) {
            std::cout << "\n✅ RONDA TERMINADA:" << std::endl;
            std::cout << "📍 Estado final: Ended" << std::endl;
            std::cout << "🏆 Ganador: ";
            switch (round.winner) {
                case Model::TeamID::CT:   std::cout << "CT"; break;
                case Model::TeamID::TT:   std::cout << "TT"; break;
                case Model::TeamID::NONE: std::cout << "Ninguno"; break;
            }
            std::cout << std::endl;

            std::cout << "⏳ Tiempo restante: " << static_cast<int>(round.time_left) << "s" << std::endl;
            std::cout << "🧨 Bomba plantada: " << (round.bomb_planted ? "Sí" : "No") << std::endl;
            std::cout << "💣 Bomba defuseada: " << (round.bomb_defused ? "Sí" : "No") << std::endl;
            std::cout << "📍 Posición bomba: (" << round.bomb_position.get_x()
                      << ", " << round.bomb_position.get_y() << ")" << std::endl;

            printed_ended = true;
            break;  // ya no mostramos más nada
        }
    }
}

DTO::GameStateDTO print_dtos(ClientQueue& client_queue, uint8_t player1_id, uint8_t player2_id) {
    DTO::GameStateDTO last_dto;
    DTO::GameStateDTO final_dto;
    bool first = true;

    uint8_t last_defusing_progress = 0;  // 👉 Se guarda el valor anterior mostrado

    DTO::DTOVariant variant;
    while (client_queue.try_pop(variant)) {
        if (!std::holds_alternative<DTO::GameStateDTO>(variant)) continue;
        const auto& dto = std::get<DTO::GameStateDTO>(variant);

        bool round_changed = first;
        if (!first) {
            round_changed |= dto.round.ended != last_dto.round.ended;
            round_changed |= dto.round.state != last_dto.round.state;
            round_changed |= dto.round.bomb_planted != last_dto.round.bomb_planted;
        }

        if (round_changed) {
            std::cout << "\n[DTO CAMBIADO - ESTADO DE RONDA] ------------------------" << std::endl;
            std::cout << (dto.round.state == RoundState::Warmup ? "❌ WARMUP" : "✅ RONDA NORMAL") << " | ";
            std::cout << (dto.round.ended ? "🔴 RONDA TERMINADA" : "🟢 RONDA EN CURSO") << " | ";
            std::cout << "⏳ Tiempo restante: " << static_cast<int>(dto.round.time_left) << "s" << std::endl;
            std::cout << "📍 Estado de la ronda: " << to_string(dto.round.state) << std::endl;
            std::cout << (dto.round.bomb_planted ? "💣 BOMBA PLANTADA" : "🧯 SIN BOMBA") << std::endl;
            std::cout << "🏆 Rondas ganadas - CT: " << static_cast<int>(dto.ct_rounds_won)
                      << " | TT: " << static_cast<int>(dto.tt_rounds_won) << std::endl;
        }

        // ✅ Solo mostramos el progreso si cambió desde el último mostrado
        if (dto.round.defusing_progress > 0 &&
            dto.round.defusing_progress != last_defusing_progress) {
            std::cout << "\n⏳ [DEFUSE EN PROGRESO] ------------------------" << std::endl;
            std::cout << "🔧 Progreso de desactivación: "
                      << static_cast<int>(dto.round.defusing_progress) << "%" << std::endl;

            last_defusing_progress = dto.round.defusing_progress;  // actualizamos
        }

        for (const auto& p : dto.players) {
            auto it = std::find_if(last_dto.players.begin(), last_dto.players.end(),
                                   [&](const DTO::PlayerDTO& x) { return x.player_id == p.player_id; });

            bool changed_defuse = (it == last_dto.players.end() || it->defusing_bomb != p.defusing_bomb);

            if (changed_defuse) {
                std::cout << "\n🧷 [DEFUSE STATUS CAMBIADO] ------------------------" << std::endl;
                std::cout << "👤 Player " << (int)p.player_id
                          << " | defusing_bomb: " << (p.defusing_bomb ? "✅ SÍ" : "❌ NO") << std::endl;
            }
        }

        last_dto = dto;
        final_dto = dto;
        first = false;
    }

    std::cout << "\n✅ [ÚLTIMO DTO RECIBIDO] ------------------------" << std::endl;
    std::cout << "📍 Estado final de ronda: " << to_string(final_dto.round.state) << std::endl;
    std::cout << "🎮 Estado del juego: " << (final_dto.game_state == GameState::Finished ? "Finalizado" : "En curso") << std::endl;
    std::cout << "🏆 Ganador del juego: "
              << (final_dto.winner == Model::TeamID::CT ? "CT" :
                 final_dto.winner == Model::TeamID::TT ? "TT" : "Ninguno") << std::endl;
    std::cout << "🔢 Rondas ganadas - CT: " << (int)final_dto.ct_rounds_won
              << " | TT: " << (int)final_dto.tt_rounds_won << std::endl;

    return final_dto;
}

void test_tt_plants_and_bomb_explodes() {
    std::cout << "\n[TEST] - TT planta y explota (CT gana la segunda ronda por tiempo)\n";

    ClientQueue q1, q2;
    Game game("test1", "mapa");
    uint8_t ct_id = 1, tt_id = 2;

    game.add_player("CT", q1, ct_id, Model::TeamID::CT, Model::RoleID::CT1);
    game.add_player("TT", q2, tt_id, Model::TeamID::TT, Model::RoleID::T1);

    using namespace std::chrono;

    // Primera ronda
    std::this_thread::sleep_for(seconds(12)); // Warmup + tiempo de compra
    game.get_queue().push({tt_id, SwitchWeaponEvent(Model::SlotID::BOMB_SLOT)});
    std::this_thread::sleep_for(milliseconds(32));
    game.get_queue().push({tt_id, UseWeaponEvent()});
    std::this_thread::sleep_for(seconds(4));
    game.get_queue().push({tt_id, StopUsingWeaponEvent()});
    std::this_thread::sleep_for(seconds(11)); // Esperar explosión

    // Segunda ronda (esperar que se termine sola)
    std::cout << "⌛ Esperando segunda ronda...\n";
    std::this_thread::sleep_for(seconds(70));  // Warmup + compra + active
    game.stop();

    DTO::GameStateDTO final_dto = print_dtos(q1, ct_id, tt_id);

    assert(final_dto.game_state == GameState::Finished);
    assert(final_dto.winner == Model::TeamID::NONE && "Debería ser empate (1-1)");
    assert(final_dto.ct_rounds_won == 1 && "CT debería haber ganado una ronda");
    assert(final_dto.tt_rounds_won == 1 && "TT debería haber ganado una ronda");

    std::cout << "✔ test_tt_plants_and_bomb_explodes OK\n";
}

void test_tt_plants_and_ct_defuses() {
    std::cout << "\n[TEST] - TT planta pero CT defusea (CT gana ambas rondas)\n";

    ClientQueue q1, q2;
    Game game("test2", "mapa");
    uint8_t ct_id = 1, tt_id = 2;

    game.add_player("CT", q1, ct_id, Model::TeamID::CT, Model::RoleID::CT1);
    game.add_player("TT", q2, tt_id, Model::TeamID::TT, Model::RoleID::T1);

    using namespace std::chrono;

    // Primera ronda
    std::this_thread::sleep_for(seconds(12)); // Warmup y compra
    game.get_queue().push({tt_id, SwitchWeaponEvent(Model::SlotID::BOMB_SLOT)});
    std::this_thread::sleep_for(milliseconds(32));
    game.get_queue().push({tt_id, UseWeaponEvent()});
    std::this_thread::sleep_for(seconds(4));
    game.get_queue().push({tt_id, StopUsingWeaponEvent()});

    // Defuseo exitoso
    std::this_thread::sleep_for(seconds(2));
    game.get_queue().push({ct_id, DefuseBombEvent()});
    std::this_thread::sleep_for(seconds(5));
    game.get_queue().push({ct_id, StopDefusingBombEvent()});

    // Segunda ronda (esperar que termine sin eventos)
    std::cout << "⌛ Esperando segunda ronda...\n";
    std::this_thread::sleep_for(seconds(2));

    game.stop();
    DTO::GameStateDTO final_dto = print_dtos(q1, ct_id, tt_id);

    assert(final_dto.game_state == GameState::Finished);
    assert(final_dto.winner == Model::TeamID::CT && "CT debería haber ganado 1-0");
    assert(final_dto.ct_rounds_won == 1);
    assert(final_dto.tt_rounds_won == 0);
    std::cout << "✔ test_tt_plants_and_ct_defuses OK\n";
}

void test_tt_defuse_interrumpido_dos_veces() {
    std::cout << "\n[TEST] - TT gana ambas rondas porque CT interrumpe el defuse dos veces\n";

    ClientQueue q1, q2;
    Game game("test_defuse_fail", "mapita");
    uint8_t ct_id = 1, tt_id = 2;

    game.add_player("CT", q1, ct_id, Model::TeamID::CT, Model::RoleID::CT1);
    game.add_player("TT", q2, tt_id, Model::TeamID::TT, Model::RoleID::T1);

    using namespace std::chrono;

    // ------------------ RONDA 2: TT vuelve a plantar ------------------
    std::this_thread::sleep_for(seconds(12)); // Compra
    game.get_queue().push({tt_id, SwitchWeaponEvent(Model::SlotID::BOMB_SLOT)});
    std::this_thread::sleep_for(milliseconds(32));
    game.get_queue().push({tt_id, UseWeaponEvent()});
    std::this_thread::sleep_for(seconds(4));
    game.get_queue().push({tt_id, StopUsingWeaponEvent()});

    std::this_thread::sleep_for(milliseconds(32));

    game.get_queue().push({ct_id, DefuseBombEvent()});
    std::this_thread::sleep_for(seconds(4)); // Solo 4s
    game.get_queue().push({ct_id, StopDefusingBombEvent()});

    std::this_thread::sleep_for(milliseconds(32));

    game.get_queue().push({ct_id, DefuseBombEvent()});
    std::this_thread::sleep_for(seconds(4)); // Solo 4s
    game.get_queue().push({ct_id, StopDefusingBombEvent()});

    // Esperar a que explote y finalice ronda
    std::this_thread::sleep_for(seconds(4));

    game.stop();
    DTO::GameStateDTO final_dto = print_dtos(q1, ct_id, tt_id);

    // Verificaciones finales
    assert(final_dto.game_state == GameState::Finished);
    assert(final_dto.winner == Model::TeamID::TT && "TT debería haber ganado 1-0");
    assert(final_dto.ct_rounds_won == 0);
    assert(final_dto.tt_rounds_won == 1);
    std::cout << "✔ test_tt_defuse_interrumpido_dos_veces OK\n";
}

void test_movimiento_con_colisiones() {
    std::cout << "[TEST] - Movimiento de jugador 2 para arriba durante 3 segundos y luego stop\n";

    using namespace std::chrono;

    ClientQueue client_queue1;
    ClientQueue client_queue2;
    Game game("test_party", "de_dummy");

    uint8_t player1_id = 1;
    uint8_t player2_id = 2;

    game.add_player("Player2", client_queue2, player2_id, Model::TeamID::TT, Model::RoleID::T1);
    game.add_player("Player1", client_queue1, player1_id, Model::TeamID::CT, Model::RoleID::CT1);

    std::cout << "🕒 Esperando warmup y compra (12 segundos)...\n";
    std::this_thread::sleep_for(seconds(12));

    std::cout << "🚶Jugador 2 empieza a moverse hacia arriba\n";
    game.get_queue().push({player2_id, MovementEvent(0, 1)});

    std::this_thread::sleep_for(seconds(3));

    std::cout << "⛔ Jugador 2 se detiene\n";
    game.get_queue().push({player2_id, StopMovementEvent(false)});

    std::this_thread::sleep_for(seconds(1));

    game.stop();

    DTO::GameStateDTO final_dto;
    DTO::DTOVariant current_dto_variant;

    while (client_queue1.try_pop(current_dto_variant)) {
        if (std::holds_alternative<DTO::GameStateDTO>(current_dto_variant)) {
            final_dto = std::get<DTO::GameStateDTO>(current_dto_variant);
        }
    }

    std::cout << "\n📦 Posiciones finales de los jugadores:\n";
    for (const auto& player : final_dto.players) {
        std::cout << "📍 Player ID: " << static_cast<int>(player.player_id)
                  << " | Posición: (" << player.position_x << ", " << player.position_y << ")\n";
    }

    const auto& player2 = *std::find_if(
        final_dto.players.begin(),
        final_dto.players.end(),
        [&](const DTO::PlayerDTO& p) { return p.player_id == player2_id; });

    assert(player2.position_x == 100 && "El jugador 2 debería tener X = 100");
    assert(player2.position_y == 168 && "El jugador 2 debería tener Y = 168");
}

void test_movimiento_hacia_pared_doble() {
    std::cout << "[TEST] - Dos jugadores se mueven hacia arriba\n";

    using namespace std::chrono;

    ClientQueue client_queue1;
    ClientQueue client_queue2;
    Game game("test_party", "de_dummy");

    uint8_t player1_id = 1;
    uint8_t player2_id = 2;

    game.add_player("Jugador1", client_queue1, player1_id, Model::TeamID::CT, Model::RoleID::CT1);
    game.add_player("Jugador2", client_queue2, player2_id, Model::TeamID::TT, Model::RoleID::T2);

    std::cout << "🕒 Esperando warmup y compra...\n";
    std::this_thread::sleep_for(seconds(12));

    std::cout << "🚶JUgador 1 para abajo, 2 para arriba se tienenq ue chocar ellos\n";
    game.get_queue().push({player1_id, MovementEvent(0, -1)});
    game.get_queue().push({player2_id, MovementEvent(0, 1)});

    std::this_thread::sleep_for(seconds(3));

    std::cout << "🛑 Stop\n";
    game.get_queue().push({player1_id, StopMovementEvent(false)});
    game.get_queue().push({player2_id, StopMovementEvent(false)});

    std::this_thread::sleep_for(seconds(1));
    game.stop();

    // Estado anterior de cada jugador
    DTO::PlayerDTO last_player1;
    DTO::PlayerDTO last_player2;
    bool first1 = true, first2 = true;

    auto mostrar_cambios = [&](ClientQueue& queue, uint8_t player_id, DTO::PlayerDTO& last_known, bool& first) {
        DTO::DTOVariant dto_variant;
        while (queue.try_pop(dto_variant)) {
            if (!std::holds_alternative<DTO::GameStateDTO>(dto_variant)) continue;
            const auto& dto = std::get<DTO::GameStateDTO>(dto_variant);
            for (const auto& p : dto.players) {
                if (p.player_id != player_id) continue;
                if (first || p.position_x != last_known.position_x || p.position_y != last_known.position_y) {
                    std::cout << "📍 Posición jugador " << unsigned(player_id) << ": ("
                              << p.position_x << ", " << p.position_y << ")\n";
                    last_known = p;
                    first = false;
                }
            }
        }
    };

    mostrar_cambios(client_queue1, player1_id, last_player1, first1);
    mostrar_cambios(client_queue2, player2_id, last_player2, first2);
}

void test_muerte_stats() {
    std::cout << "[TEST] - PARTIDA 1 RONDA. PLAYER 2 MATA A 1. p2=(32,32) y p1=(32,96)" << std::endl;

    using namespace std::chrono;

    ClientQueue client_queue1;
    ClientQueue client_queue2;
    Game game("test_party", "de_dummy");

    uint8_t ct_id = 1;
    uint8_t tt_id = 2;

    game.add_player("CT", client_queue1, ct_id, Model::TeamID::CT, Model::RoleID::CT1);
    game.add_player("TT", client_queue2, tt_id, Model::TeamID::TT, Model::RoleID::T1);

    std::this_thread::sleep_for(seconds(11));  // Warmup

    game.get_queue().push({ct_id, BuyEvent(Model::WeaponID::GLOCK)});
    std::this_thread::sleep_for(seconds(11));  // Buy

    game.get_queue().push({ct_id, RotationEvent(0)});
    std::this_thread::sleep_for(milliseconds(32));

    for (int i = 0; i < 4; ++i) {
        game.get_queue().push({ct_id, UseWeaponEvent()});
        std::this_thread::sleep_for(milliseconds(32));
        game.get_queue().push({ct_id, StopUsingWeaponEvent()});
        std::this_thread::sleep_for(milliseconds(32));
    }

    std::this_thread::sleep_for(seconds(2));
    game.stop();

    DTO::DTOVariant dto;
    std::map<uint8_t, std::tuple<uint8_t, uint8_t, uint16_t, uint8_t>> last_stats;
    std::set<uint8_t> printed_players;

    std::vector<std::tuple<uint8_t, uint16_t, uint16_t>> last_drops;
    bool first_drops_printed = false;

    while (client_queue1.try_pop(dto)) {
        if (!std::holds_alternative<DTO::GameStateDTO>(dto)) continue;

        const auto& state = std::get<DTO::GameStateDTO>(dto);

        // Mostrar stats de jugadores (con 💀 si murió)
        for (const auto& p : state.players) {
            auto stats = std::make_tuple(p.kills, p.deaths, p.money, p.health);
            bool first = !printed_players.count(p.player_id);
            bool changed = !first && stats != last_stats[p.player_id];

            if (first || changed) {
                std::string death_icon = (p.health == 0) ? "💀 " : "";
                std::cout << death_icon << "[PLAYER " << (int)p.player_id << "] "
                          << "Kills: " << (int)p.kills << ", "
                          << "Deaths: " << (int)p.deaths << ", "
                          << "Money: " << p.money << ", "
                          << "Health: " << (int)p.health << "\n";

                last_stats[p.player_id] = stats;
                printed_players.insert(p.player_id);
            }
        }

        // Extraer drops actuales en forma simple
        std::vector<std::tuple<uint8_t, uint16_t, uint16_t>> current_drops;
        for (const auto& d : state.round.dropped_weapons) {
            current_drops.emplace_back(d.weapon_id, d.position_x, d.position_y);
        }

        // Mostrar si es el primero no vacío o si cambió respecto al último
        bool changed = current_drops.size() != last_drops.size();

        if (!changed) {
            for (size_t i = 0; i < current_drops.size(); ++i) {
                if (current_drops[i] != last_drops[i]) {
                    changed = true;
                    break;
                }
            }
        }

        if (!current_drops.empty() && (!first_drops_printed || changed)) {
            std::cout << "🟡 Drops recibidos en este GameStateDTO:\n";
            for (const auto& [weapon_id, x, y] : current_drops) {
                std::cout << "  🧨 WeaponID: " << static_cast<int>(weapon_id)
                          << " en (" << x << ", " << y << ")\n";
            }
            last_drops = current_drops;
            first_drops_printed = true;
        }
    }

    std::cout << "✅ Test muerte_stats terminó (sin asserts)\n";
}

void test_drop_weapon_event() {
    std::cout << "[TEST] - Ambos jugadores dropean arma luego de warmup\n";

    using namespace std::chrono;

    ClientQueue client_queue1;
    ClientQueue client_queue2;
    Game game("test_party", "de_dummy");

    uint8_t ct_id = 1;
    uint8_t tt_id = 2;

    game.add_player("CT", client_queue1, ct_id, Model::TeamID::CT, Model::RoleID::CT1);
    game.add_player("TT", client_queue2, tt_id, Model::TeamID::TT, Model::RoleID::T1);

    std::this_thread::sleep_for(seconds(11));  // Warmup

    game.get_queue().push({ct_id, DropWeaponEvent()});
    std::this_thread::sleep_for(milliseconds(32));
    game.get_queue().push({tt_id, DropWeaponEvent()});

    std::this_thread::sleep_for(seconds(1)); 

    game.stop();

    DTO::DTOVariant dto;
    std::vector<std::tuple<uint8_t, uint16_t, uint16_t>> last_drops;
    bool first_dto_checked = false;
    bool printed_drop_dto = false;

    while (client_queue1.try_pop(dto)) {
        if (!std::holds_alternative<DTO::GameStateDTO>(dto)) continue;
        const auto& state = std::get<DTO::GameStateDTO>(dto);

        std::vector<std::tuple<uint8_t, uint16_t, uint16_t>> current_drops;
        for (const auto& d : state.round.dropped_weapons) {
            current_drops.emplace_back(d.weapon_id, d.position_x, d.position_y);
        }

        if (!first_dto_checked) {
            std::cout << "🔍 Primer GameStateDTO tiene drops? "
                      << (current_drops.empty() ? "NO" : "SÍ") << "\n";
            first_dto_checked = true;
        }

        bool changed = current_drops.size() != last_drops.size();
        if (!changed) {
            for (size_t i = 0; i < current_drops.size(); ++i) {
                if (current_drops[i] != last_drops[i]) {
                    changed = true;
                    break;
                }
            }
        }

        if (!current_drops.empty() && changed) {
            std::cout << "🟡 Nuevo GameStateDTO con Drops:\n";
            for (const auto& [weapon_id, x, y] : current_drops) {
                std::cout << "  🧨 WeaponID: " << static_cast<int>(weapon_id)
                          << " en (" << x << ", " << y << ")\n";
            }
            last_drops = current_drops;
            printed_drop_dto = true;
        }
    }

    if (!printed_drop_dto) {
        std::cout << "⚠️  No se detectaron GameStateDTO con drops distintos tras el primero\n";
    }

    std::cout << "✅ Test drop_weapon_event terminado\n";
}

void test_dropped_weapon_position() {
    std::cout << "[TEST] - Dropeo de arma y verificación de posición\n";

    using namespace std::chrono;

    ClientQueue client_queue;
    Game game("test_party", "de_dummy");

    uint8_t player_id = 1;

    game.add_player("Player", client_queue, player_id, Model::TeamID::CT, Model::RoleID::CT1);

    std::this_thread::sleep_for(seconds(11));  // Warmup

    game.get_queue().push({player_id, DropWeaponEvent()});

    std::this_thread::sleep_for(seconds(1));  // Esperar a que procese el evento

    game.stop();

    DTO::DTOVariant dto;
    while (client_queue.try_pop(dto)) {
        if (!std::holds_alternative<DTO::GameStateDTO>(dto)) continue;
        const auto& state = std::get<DTO::GameStateDTO>(dto);

        if (!state.round.dropped_weapons.empty()) {
            std::cout << "🎯 Se detectó dropped_weapon:\n";
            for (const auto& d : state.round.dropped_weapons) {
                std::cout << "  🧨 WeaponID: " << static_cast<int>(d.weapon_id)
                          << " en posición (" << d.position_x << ", " << d.position_y << ")\n";
            }
            break;  // Solo mostrar el primer DTO válido con drops
        }
    }

    std::cout << "✅ Test dropped_weapon_position terminado\n";
}

void test_drop_and_move_weapon_with_weapon_tracking() {
    std::cout << "[TEST] - Dropea arma, se mueve y se monitorea el arma equipada\n";

    using namespace std::chrono;

    ClientQueue client_queue;
    Game game("test_party", "de_dummy");

    uint8_t player_id = 1;

    game.add_player("Player", client_queue, player_id, Model::TeamID::CT, Model::RoleID::CT1);

    std::this_thread::sleep_for(seconds(11));  // Warmup

    game.get_queue().push({player_id, DropWeaponEvent()});
    std::this_thread::sleep_for(seconds(1));

    game.get_queue().push({player_id, MovementEvent(0, -1)});
    std::this_thread::sleep_for(seconds(3));
    game.get_queue().push({player_id, StopMovementEvent(false)});

    game.stop();

    DTO::DTOVariant dto;
    std::vector<std::tuple<uint8_t, uint16_t, uint16_t>> last_drops;
    std::optional<DTO::PlayerDTO> last_player_dto;
    bool printed_first_player_dto = false;

    while (client_queue.try_pop(dto)) {
        if (!std::holds_alternative<DTO::GameStateDTO>(dto)) continue;
        const auto& state = std::get<DTO::GameStateDTO>(dto);

        // DROPS
        std::vector<std::tuple<uint8_t, uint16_t, uint16_t>> current_drops;
        for (const auto& d : state.round.dropped_weapons) {
            current_drops.emplace_back(d.weapon_id, d.position_x, d.position_y);
        }

        if (current_drops != last_drops && !current_drops.empty()) {
            std::cout << "🟡 DTO con nuevos dropped weapons:\n";
            for (const auto& [weapon_id, x, y] : current_drops) {
                std::cout << "  🧨 WeaponID: " << static_cast<int>(weapon_id)
                          << " en (" << x << ", " << y << ")\n";
            }
            last_drops = current_drops;
        }

        // PLAYER DTO
        for (const auto& p : state.players) {
            if (p.player_id != player_id) continue;

            if (!printed_first_player_dto && state.round.state != RoundState::Warmup) {
                std::cout << "🔹 Primer PlayerDTO con ronda activa:\n";
                std::cout << "  Pos: (" << p.position_x << ", " << p.position_y << ") - ";
                std::cout << "Health: " << static_cast<int>(p.health) << "\n";
                std::cout << "  Weapon: ID = " << static_cast<int>(p.weapon_dto.weapon_id)
                          << " | Ammo: [" << static_cast<int>(p.weapon_dto.loaded_ammo)
                          << "/" << static_cast<int>(p.weapon_dto.total_ammo) << "]\n";
                printed_first_player_dto = true;
            }

            if (!last_player_dto.has_value() ||
                last_player_dto->weapon_dto.weapon_id != p.weapon_dto.weapon_id ||
                last_player_dto->weapon_dto.loaded_ammo != p.weapon_dto.loaded_ammo ||
                last_player_dto->weapon_dto.total_ammo != p.weapon_dto.total_ammo) {
                std::cout << "🟢 Cambio en arma equipada:\n";
                std::cout << "  Pos: (" << p.position_x << ", " << p.position_y << ") - ";
                std::cout << "Weapon ID = " << static_cast<int>(p.weapon_dto.weapon_id)
                          << " | Ammo: [" << static_cast<int>(p.weapon_dto.loaded_ammo)
                          << "/" << static_cast<int>(p.weapon_dto.total_ammo) << "]\n";
            }

            last_player_dto = p;
        }
    }

    if (last_player_dto.has_value()) {
        const auto& p = last_player_dto.value();
        std::cout << "🔻 Último PlayerDTO recibido:\n";
        std::cout << "  Pos: (" << p.position_x << ", " << p.position_y << ") - ";
        std::cout << "Health: " << static_cast<int>(p.health) << "\n";
        std::cout << "  Weapon: ID = " << static_cast<int>(p.weapon_dto.weapon_id)
                  << " | Ammo: [" << static_cast<int>(p.weapon_dto.loaded_ammo)
                  << "/" << static_cast<int>(p.weapon_dto.total_ammo) << "]\n";
    }

    std::cout << "✅ Test test_drop_and_move_weapon_with_weapon_tracking terminado\n";
}


int main() {
    //test_cambio_ronda();
    //test_finaliza_por_muerte_ct();
    //test_rotacion_y_disparo();
    //test_rotacion_y_disparo_2(); este
    //test_rotacion_y_disparo_m3(); este
    //test_disparo_con_reload();
    //test_bomba_y_estado_round();
    //test_tt_plants_and_bomb_explodes();
    //test_tt_plants_and_ct_defuses();
    //test_tt_defuse_interrumpido_dos_veces(); este
    //test_movimiento_con_colisiones();
    //test_movimiento_hacia_pared_doble();
    //test_muerte_stats();
    //test_drop_weapon_event();
    //test_dropped_weapon_position();
    test_drop_and_move_weapon_with_weapon_tracking();
    std::cout << "Pasaron los test" << std::endl;
    return 0;
}