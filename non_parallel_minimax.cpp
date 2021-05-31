#include <array>
#include <iostream>
#include <vector>
#include "board.h"
#include "non_parallel_minimax.h"
#include "Random.h"
#include "stopwatch.h"

//static std::map<std::pair<uint64_t, uint64_t>, uint8_t> computed_boards;

static uint64_t np_count;

static constexpr std::array<bool, 2> next_player{ 1, 0 };

void np_print_vector_pair(const std::vector<std::pair<uint8_t, uint8_t>> v)
{
	for (auto elem : v)
	{
		std::cout << " weight: " << (int)elem.first << ", move: " << (int)elem.second << "\n";
	}
}

uint8_t np_c4_minimax(const board& prev_board, const bool first_player)
{
	const auto moves = prev_board.get_moves();
	uint8_t i = 0;
	std::vector<std::pair<uint8_t, uint8_t>> main_w_and_m(moves.size());

	for (auto move : moves)
	{
		const auto weight = np_minimax(prev_board, first_player, move, 1);
		if (weight == first_player * 255) { return move; }
		main_w_and_m[i++] = { weight, move };
	}

	std::cout << " minimax calls aprox: " << np_count << "\n" << " Unique boards stored: " << np_computed_boards.size() << "\n";

	np_computed_boards.clear();
	np_count = 0;

	//print(main_w_and_m);

	std::sort(main_w_and_m.begin(), main_w_and_m.end());
	if (first_player) { return(main_w_and_m.back().second); }
	else { return(main_w_and_m.front().second); }

}

uint8_t np_insert_and_return(const std::pair<uint64_t, uint64_t> num_cur_board, const uint8_t weight)
{
	np_computed_boards.insert({ num_cur_board, weight });
	return weight;
}

uint8_t np_minimax(const board& prev_board, const bool player, const uint8_t move, const uint8_t depth)
{
	++np_count;
	const board current_board(prev_board, move, player);
	const auto num_cur_board = current_board.to_num();
	//std::cout << current_board << std::endl;
	auto it = np_computed_boards.find(num_cur_board);

	if (it != np_computed_boards.end())
	{
		return  it->second;
	}

	else if (current_board.check_move(move, player))
	{
		return np_insert_and_return(num_cur_board, player * 255);
	}

	else if (depth == np_sdepth)
	{
		return np_insert_and_return(num_cur_board, Random::randint(1, 254));
	}

	else
	{
		const auto next_moves = current_board.get_moves();
		std::vector<uint8_t> weights(next_moves.size());
		uint8_t i = 0;
		for (auto branch_move : next_moves) {
			weights[i++] = np_minimax(current_board, next_player[player], branch_move, depth + 1);
		}

		if (player) //player 1, player max
		{
			return np_insert_and_return(num_cur_board, *std::min_element(weights.begin(), weights.end()));
		}

		else //player 0, player min
		{
			return np_insert_and_return(num_cur_board, *std::max_element(weights.begin(), weights.end()));
		}
	}
}

void np_ai_play_ai()
{
	stopwatch global;

	std::ios_base::sync_with_stdio(false);

	std::array<uint8_t, 42> arr{
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
	};

	board b1(arr);

	Random::init();

	std::array<bool, 2> next_player{ 1,0 };
	bool player = 0;

	while (1)
	{
		stopwatch s;

		uint8_t move = np_c4_minimax(b1, player);
		b1.make_move(move, player);
		std::cout << b1 << std::endl;

		if (b1.check_move(move, player)) { std::cout << "player " << player + 1 << " wins.\n"; break; }

		player = next_player[player];
	}

	std::cout << "done\n" << np_sdepth;
}