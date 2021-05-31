//#include <iostream>
#include <string>
#include <algorithm>
#include <bitset>
#include <vector>
#include "board.h"


const bool board::check_move(const  uint8_t move, const bool player) const
{
	//Para el yonki del futuro:
	//esta funcion no funciona bien, tienes que crear una lista nueva y mirar esa.
	// no es buena idea penandolo, pero no funciona no



	const uint8_t n = sn - 1; //fichas adyacentes necesarias
	const uint8_t x = move % sx;
	const uint8_t y = move / sx;
	auto _state = state[player];
	_state[move] = 1;

	//comprobacion diagonal \
	// i = num pasos en diagonal
	uint8_t count = 0;
	for (int i = -std::min({ x, y, n }); i < std::min({ (uint8_t)(sx - x), (uint8_t)(sy - y), sn }); ++i)
	{
		//std::cout << (y * sx + x + (sx + 1) * i) << std::endl;
		if (_state[y * sx + x + (sx + 1) * i]) {
			++count; 
			if (count == sn) { return true; }
		}

		else { count = 0; }
	}

	//comprobacion diagonal /
	// i = num pasos en diagonal
	count = 0;
	for (int i = -std::min({ y,(uint8_t)(sx - x - 1), n }); i < std::min({ (uint8_t)(sy - y), (uint8_t)(x + 1), sn }); ++i)
	{
		//std::cout << (y * sx + x + (sx - 1) * i) << std::endl;
		if (_state[y * sx + x + (sx - 1) * i]) {
			++count;
			if (count == sn) { return true; }
		}

		else { count = 0; }
	}

	//comprobacion horizontal
	count = 0;
	for (uint8_t i = std::max({ x - n, 0 }); i < std::min({ (uint8_t)(x + sn), sx }); ++i)
	{
		//std::cout << (unsigned int)(y * sx + i) << std::endl;
		if (_state[y * sx + i]) {
			++count;
			if (count == sn) { return true; }
		}

		else { count = 0; }
	}

	//comprobacion vertical
	if (y < sy - n)
	{
		count = 0;
		for (uint8_t i = 1; i < sn; ++i)
		{
			//std::cout << (unsigned int)(i * sx + move) << std::endl;
			if (_state[i * sx + move] == false) { return false; }
		}
		return true;
	}

	return false;
}

const std::vector<uint8_t> board::get_moves() const
{
	std::vector<uint8_t> possible_moves{}; // si no hay posicion, coloca un valor negativo

	for (int i = sx - 1; i > -1; --i)
	{
		for (int ii = sy - 1; ii > -1; --ii)
		{
			const uint8_t position = ii * sx + i;
			//std::cout << (int)i << " " << int(ii) << " " << (int)state[0][position] << " " << (int)state[1][position] << std::endl;
			if (!(state[0][position] | state[1][position]))
			{
				possible_moves.push_back(position);
				break;
			}
		}
	}

	if (possible_moves.size() == 0) { std::cout << "No more moves left\n"; exit(EXIT_SUCCESS); };

	return std::move(possible_moves);
}

const std::array<std::bitset<size>, players> from_num(const std::pair<uint64_t, uint64_t> nums)
{
	return { *(std::bitset<size>*) & nums.first, *(std::bitset<size>*) & nums.second };
}

const std::pair<uint64_t, uint64_t> board::to_num() const
{
	//even tho the states are std::bitset<42>, they are stored as 8 bytes
	return { *(uint64_t*)&state[0] , *(uint64_t*)&state[1] }; //evil bit hacking
}

std::ostream& operator <<(std::ostream& out, const board board)
{
	for (int i = 0; i < sy; ++i) {
		for (int ii = 0; ii < sx; ++ii) {
			const uint8_t position = i * sx + ii;
			if (board.state[0][position]) {
				out << 1 << ",";
			}
			else if (board.state[1][position]) {
				out << 2 << ",";
			}
			else
				out << " ,";
		}
		out << "\n";
	}
	out << std::flush;
	return out;
}

void board::make_move(const uint8_t move, const uint8_t player)
{
	//auto temp = state[player];
	//temp[move] = 1;
	//state[player] = temp;

	if (!(state[0][move] | state[1][move])) {
		state[player][move] = 1;
		return;
	}

	else {
		std::cout << "invalid move" << std::endl;
		exit(EXIT_FAILURE);
	}

}
