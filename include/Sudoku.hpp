#ifndef SUDOKU_HPP
#define SUDOKU_HPP

#include <vector>
#include <set>

class Sudoku
{
public:
	enum Level
	{
		Easy = 32,
		Medium = 27,
		Hard = 22
	};

	Sudoku(Level level);
	bool isValid(int column, int row, int number) const;
	int get(int column, int row) const;
	bool set(int column, int row, int number);
	bool isSolved();
	void getInvalidPositions(std::vector <int> &invalidPositions) const;
	const std::vector <int> & getCluePositions() const;

private:
	int generateNumberAt(int column, int row);
	void getPossibleNumbers(int column, int row, std::vector <int> &possibleNumbers) const;

	int sudoku [81];
	std::vector <int> cluePositions;
};

void removeNumberFromVector(std::vector <int> &vector, int number);
bool isInVector(const std::vector <int> &vector, int number);

#endif // SUDOKU_HPP
