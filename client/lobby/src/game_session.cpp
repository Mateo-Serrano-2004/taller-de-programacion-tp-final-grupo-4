#include "game_session.h"

void GameSession::setUsername(const QString& username) {
    this->username = username;
}

void GameSession::setMapName(const QString& map) {
    this->mapName = map;
}

void GameSession::setGameName(const QString& name) {
    this->gameName = name;
    this->joining = false;
}

void GameSession::setJoinedGame(const QString& game) {
    this->joinedGame = game;
    this->joining = true;
}

QString GameSession::getUsername() const { return username; }
QString GameSession::getMapName() const { return mapName; }
QString GameSession::getGameName() const { return gameName; }
QString GameSession::getJoinedGame() const { return joinedGame; }
bool GameSession::isJoining() const { return joining; }
