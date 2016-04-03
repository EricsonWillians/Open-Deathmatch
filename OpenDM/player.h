#pragma once
#ifndef PLAYER_H
#define PLAYER_H

class Player {
private:
	const char* name;
	int x;
	int y;
public:
	Player(const char* name, int x, int y);
	~Player() {};
}

#endif