#include <iostream>
#include <chrono>
#include <thread>
#include <cassert>

#include "../server/game/game.h"
#include "../common/DTO/game_state_dto.h"
#include "../common/DTO/dto_variant.h"
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
    game.add_player("Player1", client_queue1, player1_id, Model::TeamID::CT, Model::RoleID::CT1);
    game.add_player("Player2", client_queue2, player2_id, Model::TeamID::TT, Model::RoleID::T1);

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
            assert(player.money == 2500 && "El jugador 1 (CT) debería tener $10500");
            found_player1 = true;
        } else if (player.player_id == player2_id) {
            assert(player.money == 3300 && "El jugador 2 (TT) debería tener $3300");
            found_player2 = true;
        }
    }

    assert(found_player1 && "No se encontró al jugador 1 en el DTO final");
    assert(found_player2 && "No se encontró al jugador 2 en el DTO final");
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



int main() {
    test_cambio_ronda();
    //test_bomba_y_estado_round();
    std::cout << "Pasaron los test" << std::endl;
    return 0;
}