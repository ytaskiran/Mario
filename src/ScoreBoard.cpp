#include "ScoreBoard.h"

ScoreBoard::ScoreBoard()
{
	;
}

void ScoreBoard::setScore(int score)
{
	this->score = score;
}

void ScoreBoard::setLives(int lives)
{
	this->lives = lives;
}

int ScoreBoard::getLives(void)
{
	return lives;
}
