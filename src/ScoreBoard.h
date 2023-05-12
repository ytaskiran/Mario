#pragma once

#include <string>

class ScoreBoard
{
public:
	ScoreBoard();
	void setScore(int score); //Sets the score 
	void setLives(int lives); //Sets the remaining lives 
	int getLives(void); //Gets the remaining lives
private:
	std::string score; //Current score 
	int lives; //Remaining life count for Mario 
};