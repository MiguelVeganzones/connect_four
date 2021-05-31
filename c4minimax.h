#pragma once
#include <thread>
#include <iostream>
#include <map>
#include "board.h"
#include <vector>
#include "parallel_hashmap/phmap.h"

static constexpr uint8_t sdepth = 12; //calls to minimax  <= sx + sx**2 + .... + sx**sdepth (creo)
//phmap::parallel_flat_hash_map

static phmap::parallel_flat_hash_map<std::pair<uint64_t, uint64_t>, uint8_t> computed_boards;

uint8_t c4_minimax(const board& prev_board, const bool first_player);

uint8_t minimax(const board&, const bool min_or_max, const uint8_t move, const uint8_t depth);

void minimax_interface(const board& board, bool player, const uint8_t move, const uint8_t depth, const uint8_t i,
	std::vector<std::pair<uint8_t, uint8_t>>& main_m_and_w);

void ai_play_ai();

void i_play_ai(const bool ai_first = false); //ai_first = 0 for i, 1 for ai

//bool operator<(const computed_board& first, const computed_board& second);
