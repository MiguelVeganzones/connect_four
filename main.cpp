#pragma once
//#include <array>
//#include "board.h"
//#include "stopwatch.h"
#include "c4minimax.h"
//#include "non_parallel_minimax.h"
//#include "Random.h"

int main()
{

	//stopwatch global;

	//std::ios_base::sync_with_stdio(false);

	//std::array<uint8_t, 42> arr{
	//	0,0,0,0,0,0,0,
	//	0,0,0,0,0,0,0,
	//	0,0,0,0,0,0,0,
	//	0,0,0,0,0,0,0,
	//	0,0,0,0,0,0,0,
	//	0,0,0,0,0,0,0,
	//};

	//board b1(arr);

	//Random::init();

	//std::array<bool, 2> next_player{ 1,0 };
	//bool player = 0;

	//uint8_t move = c4_minimax(b1, player);
	//b1.make_move(move, player);
	//std::cout << b1 << std::endl;


	//while (1)
	//{
	//	stopwatch s;

	//	uint8_t move = c4_minimax(b1, player);
	//	b1.make_move(move, player);
	//	std::cout << b1 << std::endl;

	//	if (b1.check_move(move, player)) { std::cout << "player " << player + 1 << " wins.\n"; break; }

	//	player = next_player[player];

	//	break;
	//}

	//std::cout << "done\n";
	int i = 0;
	while(1)
	{
		i_play_ai(i);
		bool m;
		std::cout << "More: ";
		std::cin >> m;
		if (m != 1) {
			break;
		}
		i = i ? 0 : 1, 0;
	}

	return EXIT_SUCCESS; 
}