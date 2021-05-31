#pragma once
#include <iostream>
#include <map>
#include "board.h"
#include "parallel_hashmap/phmap.h"

static constexpr uint8_t np_sdepth = 9; //calls to minimax  <= sx + sx**2 + .... + sx**sdepth (creo)
//phmap::parallel_flat_hash_map

static phmap::parallel_flat_hash_map<std::pair<uint64_t, uint64_t>, uint8_t> np_computed_boards;

uint8_t np_c4_minimax(const board& prev_board, const bool first_player);

uint8_t np_minimax(const board&, const bool min_or_max, const uint8_t move, const uint8_t depth);

void np_ai_play_ai();
