#include "../server/game/round.h"
#include <cassert>
#include <iostream>

std::string round_state_to_string(RoundState state) {
    switch (state) {
        case RoundState::Warmup: return "Warmup";
        case RoundState::Buying: return "Buying";
        case RoundState::Active: return "Active";
        case RoundState::Ended: return "Ended";
        default: return "Desconocido";
    }
}

std::string team_to_string(Model::TeamID team) {
    switch (team) {
        case Model::TeamID::CT: return "CT";
        case Model::TeamID::TT: return "TT";
        case Model::TeamID::NONE: return "NONE";
        default: return "Desconocido";
    }
}

void expect_dto(const Round& round, RoundState expected_state, bool expected_ended,
                uint16_t expected_time_left, Model::TeamID expected_winner,
                bool expected_bomb_planted, bool expected_bomb_defused,
                const Physics::Vector2D& expected_position) {
    DTO::RoundDTO dto = round.to_dto(60);
    bool paso = true;

    if (dto.state != expected_state) {
        std::cout << "[Estado]      Obtenido: " << round_state_to_string(dto.state)
                  << " | Esperado: " << round_state_to_string(expected_state) << "\n";
        paso = false;
    }
    if (dto.ended != expected_ended) {
        std::cout << "[Terminada]   Obtenido: " << std::boolalpha << dto.ended
                  << " | Esperado: " << expected_ended << "\n";
        paso = false;
    }
    if (dto.time_left != expected_time_left) {
        std::cout << "[Tiempo]      Obtenido: " << dto.time_left
                  << " | Esperado: " << expected_time_left << "\n";
        paso = false;
    }
    if (dto.winner != expected_winner) {
        std::cout << "[Ganador]     Obtenido: " << team_to_string(dto.winner)
                  << " | Esperado: " << team_to_string(expected_winner) << "\n";
        paso = false;
    }
    if (dto.bomb_planted != expected_bomb_planted) {
        std::cout << "[Bomba]       Obtenido: " << dto.bomb_planted
                  << " | Esperado: " << expected_bomb_planted << "\n";
        paso = false;
    }
    if (dto.bomb_defused != expected_bomb_defused) {
        std::cout << "[Defused]     Obtenido: " << dto.bomb_defused
                  << " | Esperado: " << expected_bomb_defused << "\n";
        paso = false;
    }
    if (dto.bomb_position != expected_position) {
        std::cout << "[Posición]    Obtenido: (" << dto.bomb_position.get_x() << ", " << dto.bomb_position.get_y()
                  << ") | Esperado: (" << expected_position.get_x() << ", " << expected_position.get_y() << ")\n";
        paso = false;
    }

    assert(paso && "❌ DTO no coincide con lo esperado");
}

void test_warmup_round() {
    std::cout << "TESTEANDO: test_warmup_round\n";
    Round round = Round::create_warmup_round();
    expect_dto(round, RoundState::Warmup, false, 1, Model::TeamID::NONE, false, false, Physics::Vector2D(0, 0));

    round.update(30);
    expect_dto(round, RoundState::Warmup, false, 1, Model::TeamID::NONE, false, false, Physics::Vector2D(0, 0));

    round.update(60);
    expect_dto(round, RoundState::Ended, true, 0, Model::TeamID::NONE, false, false, Physics::Vector2D(0, 0));
    std::cout << "✔ test_warmup_round OK\n";
}

void test_ct_killed_gives_win_to_tt() {
    std::cout << "TESTEANDO: test_ct_killed_gives_win_to_tt\n";
    Round round(1, 1);
    round.notify_on_one_player_less(Model::TeamID::CT);
    expect_dto(round, RoundState::Ended, true, 0, Model::TeamID::TT, false, false, Physics::Vector2D(0, 0));
    std::cout << "✔ test_ct_killed_gives_win_to_tt OK\n";
}

void test_tt_killed_no_bomb_gives_win_to_ct() {
    std::cout << "TESTEANDO: test_tt_killed_no_bomb_gives_win_to_ct\n";
    Round round(1, 1);
    round.notify_on_one_player_less(Model::TeamID::TT);
    expect_dto(round, RoundState::Ended, true, 0, Model::TeamID::CT, false, false, Physics::Vector2D(0, 0));
    std::cout << "✔ test_tt_killed_no_bomb_gives_win_to_ct OK\n";
}

void test_bomb_planted_tt_dies_then_explodes() {
    std::cout << "TESTEANDO: test_bomb_planted_tt_dies_then_explodes\n";
    Round round(1, 1);
    round.update(600);  // pasa de buying a active
    assert(round.is_active());

    round.notify_bomb_planted(Physics::Vector2D(10, 10));
    expect_dto(round, RoundState::Active, false, 10, Model::TeamID::NONE, true, false, Physics::Vector2D(10, 10));

    round.update(120);  // pasan 2s
    round.notify_on_one_player_less(Model::TeamID::TT);
    expect_dto(round, RoundState::Active, false, 8, Model::TeamID::NONE, true, false, Physics::Vector2D(10, 10));

    round.update(480);
    expect_dto(round, RoundState::Ended, true, 0, Model::TeamID::TT, true, false, Physics::Vector2D(10, 10));
    std::cout << "✔ test_bomb_planted_tt_dies_then_explodes OK\n";
}

void test_bomb_planted_and_defused_ct_wins() {
    std::cout << "TESTEANDO: test_bomb_planted_and_defused_ct_wins\n";
    Round round(1, 1);
    round.update(600);  // pasa a active
    round.notify_bomb_planted(Physics::Vector2D(5, 5));
    round.update(300);
    round.notify_bomb_is_being_defused(1);
    round.update(300);
    expect_dto(round, RoundState::Ended, true, 0, Model::TeamID::CT, true, true, Physics::Vector2D(5, 5));
    std::cout << "✔ test_bomb_planted_and_defused_ct_wins OK\n";
}

void test_bomb_tick_override() {
    std::cout << "TESTEANDO: test_bomb_tick_override\n";
    Round round(1, 1);
    round.update(600);
    expect_dto(round, RoundState::Active, false, 60, Model::TeamID::NONE, false, false, Physics::Vector2D(0, 0));

    round.notify_bomb_planted(Physics::Vector2D(2, 2));
    expect_dto(round, RoundState::Active, false, 10, Model::TeamID::NONE, true, false, Physics::Vector2D(2, 2));

    std::cout << "✔ test_bomb_tick_override OK\n";
}

void test_bomb_planted_before_timeout_extends_round() {
    std::cout << "TESTEANDO: test_bomb_planted_before_timeout_extends_round\n";
    Round round(1, 1);
    round.update(600);
    round.update(3540);  // queda 1s
    expect_dto(round, RoundState::Active, false, 1, Model::TeamID::NONE, false, false, Physics::Vector2D(0, 0));

    round.notify_bomb_planted(Physics::Vector2D(3, 3));
    expect_dto(round, RoundState::Active, false, 10, Model::TeamID::NONE, true, false, Physics::Vector2D(3, 3));

    std::cout << "✔ test_bomb_planted_before_timeout_extends_round OK\n";
}

void test_not_enough_time_to_defuse_bomb_explodes() {
    std::cout << "TESTEANDO: test_not_enough_time_to_defuse_bomb_explodes\n";
    Round round(1, 1);
    round.update(600); // PASO A WARMUP
    round.notify_bomb_planted(Physics::Vector2D(4, 4));
    round.update(360); // (10s de bomba - 6s que avanzo, no alcanza a defusear bomb aporque encesita 5s)
    assert(round.notify_bomb_is_being_defused(1));
    round.update(300); // aunque avance los 5 segundos
    expect_dto(round, RoundState::Ended, true, 0, Model::TeamID::TT, true, false, Physics::Vector2D(4, 4));

    std::cout << "✔ test_not_enough_time_to_defuse_bomb_explodes OK\n";
}

void test_defusing_is_interrupted_and_bomb_explodes() {
    std::cout << "TESTEANDO: test_defusing_is_interrupted_and_bomb_explodes\n";
    Round round(1, 1);
    round.update(600); // PASO A WARMUP
    round.notify_bomb_planted(Physics::Vector2D(4, 4));
    round.update(120); // (10s de bomba - 2s que avanzo)
    assert(round.notify_bomb_is_being_defused(1));
    round.update(120); // quedas en 6s
    round.notify_bomb_is_not_longer_being_defused();
    round.update(360); // queda en 0, te da el tiempo de defuseo pero no debería porque soltó
    expect_dto(round, RoundState::Ended, true, 0, Model::TeamID::TT, true, false, Physics::Vector2D(4, 4));

    std::cout << "✔ test_defusing_is_interrupted_and_bomb_explodes OK\n";
}

void test_defusing_restarts_and_previous_progress_is_lost() {
    std::cout << "TESTEANDO: test_defusing_restarts_and_previous_progress_is_lost\n";
    Round round(1, 1);
    round.update(600); // PASO A WARMUP
    round.notify_bomb_planted(Physics::Vector2D(4, 4));
    round.update(120); // (10s de bomba - 2s que avanzo)
    assert(round.notify_bomb_is_being_defused(1));
    round.update(240); // quedas en 4s
    round.notify_bomb_is_not_longer_being_defused();
    assert(round.notify_bomb_is_being_defused(1));
    round.update(300); // haces que le alcance el tiempo, pero como solto tenía 4s y no deberia defusear
    expect_dto(round, RoundState::Ended, true, 0, Model::TeamID::TT, true, false, Physics::Vector2D(4, 4));

    std::cout << "✔ test_defusing_restarts_and_previous_progress_is_lost OK\n";
}

void test_bomb_planted_during_invalid_phase_is_ignored() {
    std::cout << "TESTEANDO: test_bomb_planted_during_invalid_phase_is_ignored\n";

    Round warmup = Round::create_warmup_round();
    warmup.notify_bomb_planted(Physics::Vector2D(0, 0));
    expect_dto(warmup, RoundState::Warmup, false, 1, Model::TeamID::NONE, false, false, Physics::Vector2D(0, 0));

    Round buying(1, 1);
    buying.notify_bomb_planted(Physics::Vector2D(0, 0));
    expect_dto(buying, RoundState::Buying, false, 10, Model::TeamID::NONE, false, false, Physics::Vector2D(0, 0));

    std::cout << "✔ test_bomb_planted_during_invalid_phase_is_ignored OK\n";
}

int main() {
    test_warmup_round();
    test_ct_killed_gives_win_to_tt();
    test_tt_killed_no_bomb_gives_win_to_ct();
    test_bomb_planted_tt_dies_then_explodes();
    test_bomb_planted_and_defused_ct_wins();
    test_bomb_tick_override();
    test_bomb_planted_before_timeout_extends_round();
    test_not_enough_time_to_defuse_bomb_explodes();
    test_defusing_is_interrupted_and_bomb_explodes();
    test_defusing_restarts_and_previous_progress_is_lost();
    test_bomb_planted_during_invalid_phase_is_ignored();

    std::cout << "✅ TODOS LOS TEST PASARON CORRECTAMENTE ✅" << std::endl;
    return 0;
}