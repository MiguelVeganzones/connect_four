#pragma once
#include <iostream>
#include <bitset>
#include <array>
#include <vector>

constexpr uint8_t sx = 7, sy = 6, sn = 4;
constexpr uint8_t size = sx * sy;
constexpr uint8_t players = 2;

struct board
{
	board() {}
	board(std::array<uint8_t, size> arr) 
	{
		for (uint8_t i = 0; i < size; ++i)
		{
			state[0][i] = arr[i] == 1;//must be changed for more than two players
			state[1][i] = arr[i] == 2;//must be changed for more than two players
		}
	}
	board(const board& board, const uint8_t move, const bool player):state{board.state}
	{
		state[player][move] = true;
	}

	std::array<std::bitset<size>, 2> state;

	const std::pair<uint64_t, uint64_t> to_num() const;
	const bool check_move (const uint8_t move, const bool player) const; //player 0 or 1, index for state
	const std::vector<uint8_t> get_moves() const;
	void make_move(const uint8_t move, const uint8_t player);
	friend std::ostream& operator <<(std::ostream& out, const board board);

};

const std::array<std::bitset<size>, players> from_num(const std::pair<uint64_t, uint64_t> nums); 