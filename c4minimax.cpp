#include <array>
#include <iostream>
#include <thread>
#include <vector>
#include <shared_mutex>
#include "board.h"
#include "c4minimax.h"
#include "Random.h"
#include "stopwatch.h"
#include <algorithm>

//static std::map<std::pair<uint64_t, uint64_t>, uint8_t> computed_boards;

static uint64_t count;

std::shared_mutex lock;


constexpr std::array<bool, 2> next_player {1, 0}; 

uint8_t c4_minimax(const board& prev_board, const bool first_player)
{
	const auto moves = prev_board.get_moves();
	std::vector<std::thread*> threads{};
	uint8_t i = 0;
	std::vector<std::pair<uint8_t, uint8_t>> main_w_and_m(moves.size());

	for (auto move : moves) {
		threads.push_back(new std::thread(minimax_interface, prev_board, first_player, move, 1, i++, std::ref(main_w_and_m)));
	}

	for (std::thread* t : threads) {
		t->join();
	}

	for (std::thread* t : threads) {
		delete t;
	}

	std::cout << " minimax calls aprox: " << count << "\n" << " Unique boards stored: " << computed_boards.size() << "\n";

	computed_boards.clear();
	count = 0;
	//print(main_w_and_m);

	std::sort(main_w_and_m.begin(), main_w_and_m.end());
	if (first_player) { return(main_w_and_m.back().second); }
	else { return(main_w_and_m.front().second); }

}

void minimax_interface(const board& board, const bool player, const uint8_t move, const uint8_t depth, const uint8_t i,
	std::vector<std::pair<uint8_t, uint8_t>>& main_w_and_m)
{
	main_w_and_m[i] = { minimax(board, player, move, depth) , move };
}

uint8_t insert_and_return(const std::pair<uint64_t,uint64_t> num_cur_board, const uint8_t weight)
{
	std::unique_lock<std::shared_mutex> write_lock(lock);
	computed_boards.insert({ num_cur_board, weight });
	return weight;
}

uint8_t minimax(const board& prev_board, const bool player, const uint8_t move, const uint8_t depth)
{
	++count;
	const board current_board(prev_board, move, player);
	const auto num_cur_board = current_board.to_num();

	{
		std::shared_lock < std::shared_mutex > read_lock(lock);

		auto it = computed_boards.find(num_cur_board);

		if (it != computed_boards.end())
		{
			return  it->second;
		}
	}

	if (current_board.check_move(move, player))
	{
		return insert_and_return(num_cur_board, player*255);
	}
	
	else if (depth == sdepth)
	{
		return insert_and_return(num_cur_board, Random::randint(1, 254));
	}

	else
	{
		const auto next_moves = current_board.get_moves();
		std::vector<uint8_t> weights(next_moves.size());
		uint8_t i = 0;
		for (auto branch_move : next_moves) {
			weights[i++] = minimax(current_board, next_player[player], branch_move, depth+1);
		}

		if (player) //player 1, player max, returns min because next player chooses
		{
			return insert_and_return(num_cur_board, *std::min_element(weights.begin(), weights.end()));
		}

		else //player 0, player min, returns max because next player chooses
		{
			return insert_and_return(num_cur_board, *std::max_element(weights.begin(), weights.end()));
		}
	}
}


void ai_play_ai()
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

	board game_state(arr);

	Random::init();

	std::array<bool, 2> next_player{ 1,0 };
	bool player = 0;

	while (1)
	{
		stopwatch s;

		uint8_t move = c4_minimax(game_state, player);
		game_state.make_move(move, player);
		std::cout << game_state << std::endl;

		if (game_state.check_move(move, player)) { std::cout << "player " << player +1  << " wins.\n"; break; }

		player = next_player[player];
	}
}

void i_play_ai(const bool ai_first)
{
	stopwatch global;

	std::array<uint8_t, 42> arr{
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
	};

	board game_state(arr);

	Random::init();

	std::array<bool, 2> next_player{ 1,0 };
	bool player = ai_first;

	while (1)
	{
		int move;

		if(player)
		{
			stopwatch s;
			move = c4_minimax(game_state, 1);
		}

		else	 
		{
			const auto moves = game_state.get_moves();
			std::cout << "Choose a move: ";

			for (int i = moves.size() - 1; i > -1; --i)
			{
				std::cout << (unsigned int)moves[i] << ", ";
			}
			
			std::cout<<std::endl;

			std::cout << "Move: ";
			std::cin >> move;

			while (std::find(moves.begin(), moves.end(), move) == moves.end())
			{
				std::cout << "Invalid move: "<<move<<"\n";
				std::cout << "Try another move: ";
				std::cin >> move;
			}
		}

		game_state.make_move((uint8_t)move, player);
		std::cout << game_state << std::endl;
		if (game_state.check_move(move, player)) { std::cout << "player " << player + 1 << " wins.\n"; break; }

		player = next_player[player];

	}

}


//bool operator<(const computed_board& first, const computed_board& second)
//{
//	auto first_first = first.first.first;
//	auto second_first = second.first.first;
//	if (first_first != second_first)
//		return first_first < second_first;
//
//	return first.first.second < second.first.second;
//}


//single thread ~

//uint8_t c4_minimax(const board& prev_board, const bool first_player)
//{
//	const auto moves = prev_board.get_moves();
//	std::vector<std::pair<uint8_t, uint8_t>> main_w_and_m(moves.size());
//	Random::init();
//
//	uint8_t i = 0;
//	for (auto move : moves)
//	{
//		uint8_t weight = minimax(prev_board, first_player, move, 0);
//		//if (weight == first_player * 255) { return move; }
//		main_w_and_m[i++] = { weight , move };
//	}
//
//	std::cout << " minimax calls aprox: " << count << "\n";
//
//	std::sort(main_w_and_m.begin(), main_w_and_m.end());
//	if (first_player) { return(main_w_and_m.back().second); }
//	else { return(main_w_and_m.front().second); }
//}