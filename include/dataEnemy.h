#ifndef DATA_ENEMY_H
#define DATA_ENEMY_H
#include <vector>
#include <map>
#include <string>
#include <stdexcept>
#include "enemy.h"

void initializeEnemyMap(std::map<std::string, std::tuple<int, int, int, int, int, int>>& enemyMap);
Enemy createEnemy(std::map<std::string, std::tuple<int, int, int, int, int, int>>& enemyMap, const std::string& enemyKey, int depth);

#endif
