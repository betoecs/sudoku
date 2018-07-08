#include "Sudoku.hpp"
#include <stdlib.h>
#define COLUMNS 9
#define ROWS 9

/////////////////////////////////////
Sudoku::Sudoku(Level level)
{
	std::vector <int> prevIndices;
	for (int i = 0; i < 81; i++)
		sudoku [i] = 0;

	for (int row = 0; row < ROWS; row++)
	{
		prevIndices.clear();

		for (int column = 0; column < COLUMNS; column++)
		{
			if (! sudoku [row * COLUMNS + column])
			{
				int generatedNumber = generateNumberAt(column, row);

				if (! generatedNumber)
				{
					// Try to use a number in the same row
					for (int i = 0; i < COLUMNS; i++)
					{
						int index = row * COLUMNS + i;
						if (! isInVector(prevIndices, index))
						{
							int possibleNumber = sudoku [index];
							sudoku [index] = 0;

							if (isValid(column, row, possibleNumber))
							{
								sudoku [row * COLUMNS + column] = possibleNumber;
								prevIndices.push_back(index);
								column = i - 1;
								break;
							}
							else
							{
								sudoku [index] = possibleNumber;
							}
						}
					}
				}
				else
				{
					sudoku [row * COLUMNS + column] = generatedNumber;
				}
			}
		}
	}

	for (int i = 0; i < level;)
	{
		int randomPosition = rand() % 81;

		if (! isInVector(cluePositions, randomPosition))
		{
			cluePositions.push_back(randomPosition);
			i++;
		}
	}

	for (int i = 0; i < 81; i++)
		if (! isInVector(cluePositions, i))
			sudoku [i] = 0;
}

/////////////////////////////////////
bool Sudoku::isValid(int column, int row, int number) const
{
	if (! number)
		return false;

	// Look in row and column
	for (int i = 0; i < COLUMNS; i++)
		if (sudoku [row * COLUMNS + i] == number || sudoku [i * COLUMNS + column] == number)
			return false;

	// Look in area
	int firstAreaColumn = column / 3 * 3;
	int firstAreaRow = row / 3 * 3;
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			if (sudoku [(firstAreaRow + i) * COLUMNS + firstAreaColumn + j] == number)
				return false;

	return true;
}

/////////////////////////////////////
int Sudoku::get(int column, int row) const
{
	return sudoku [row * COLUMNS + column];
}

/////////////////////////////////////
bool Sudoku::set(int column, int row, int number)
{
	int index = row * COLUMNS + column;

	if (isInVector(cluePositions, index))
		return false;

	sudoku [index] = number;
	return true;
}

/////////////////////////////////////
bool Sudoku::isSolved()
{
	for (int row = 0; row < ROWS; row++)
	{
		for (int column = 0; column < COLUMNS; column++)
		{
			int position = row * COLUMNS + column;
			int number = sudoku [position];

			if (! number)
				return false;

			sudoku [position] = 0;
			if (! isValid(column, row, number))
			{
				sudoku [position] = number;
				return false;
			}

			sudoku [position] = number;
		}
	}

	return true;
}

/////////////////////////////////////
void Sudoku::getInvalidPositions(std::vector <int> &invalidPositions) const
{
	// Look repited numbers in columns and rows
	for (int i = 0; i < 9; i++)
	{
		std::vector <int> repitedNumbersInColumn;
		std::vector <int> repitedNumbersInRow;
		for (int j = 0; j < 9; j++)
		{
			int number = sudoku [i * COLUMNS + j];
			if (number)
			{
				bool repitedInColumn = false;
				bool repitedInRow = false;

				if (! isInVector(repitedNumbersInColumn, number))
				{
					for (int k = j + 1; k < COLUMNS; k++)
					{
						int position = i * COLUMNS + k;
						if (sudoku [position] == number)
						{
							if (! isInVector(cluePositions, position))
								invalidPositions.push_back(position);

							repitedInColumn = true;
						}
					}
				}

				if (! isInVector(repitedNumbersInRow, number))
				{
					for (int k = i + 1; k < ROWS; k++)
					{
						int position = k * COLUMNS + j;
						if (sudoku [position] == number)
						{
							if (! isInVector(cluePositions, position))
								invalidPositions.push_back(position);

							repitedInRow = true;
						}
					}
				}

				if (repitedInColumn || repitedInRow)
				{
					int position = i * COLUMNS + j;
					if (! isInVector(cluePositions, position))
						invalidPositions.push_back(position);

					if (repitedInColumn) repitedNumbersInColumn.push_back(number);
					if (repitedInRow) repitedNumbersInRow.push_back(number);
				}
			}
		}
	}

	// Look repited numbers in area
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			std::vector <int> repitedNumbersInArea;
			int firstAreaColumn = j * 3;
			int firstAreaRow = i * 3;

			for (int k = 0; k < 3; k++)
			{
				for (int l = 0; l < 3; l++)
				{
					int number = sudoku [(firstAreaRow + k) * COLUMNS + (firstAreaColumn + l)];

					if (number && ! isInVector(repitedNumbersInArea, number))
					{
						bool repited = false;
						for (int m = 0; m < 3; m++)
						{
							for (int n = 0; n < 3; n++)
							{
								int position = (firstAreaRow + m) * COLUMNS + (firstAreaColumn + n);
								if (position != (firstAreaRow + k) * COLUMNS + (firstAreaColumn + l) && number == sudoku [position])
								{
									if (! isInVector(cluePositions, position))
										invalidPositions.push_back(position);

									repited = true;
								}
							}
						}

						if (repited)
						{
							int position = (firstAreaRow + k) * COLUMNS + (firstAreaColumn + l);
							if (! isInVector(cluePositions, position))
								invalidPositions.push_back(position);

							repitedNumbersInArea.push_back(number);
						}
					}
				}
			}
		}
	}
}

/////////////////////////////////////
const std::vector <int> & Sudoku::getCluePositions() const
{
	return cluePositions;
}

/////////////////////////////////////
int Sudoku::generateNumberAt(int column, int row)
{
	std::vector <int> possibleNumbers;
	getPossibleNumbers(column, row, possibleNumbers);

	// No possible numbers
	if (! possibleNumbers.size())
		return 0;

	return possibleNumbers [rand() % possibleNumbers.size()];
}

/////////////////////////////////////
void Sudoku::getPossibleNumbers(int column, int row, std::vector <int> &possibleNumbers) const
{
	possibleNumbers.clear();
	for (int i = 1; i <= 9; i++)
		possibleNumbers.push_back(i);

	for (int i = 0; i < 9; i++)
	{
		removeNumberFromVector(possibleNumbers, sudoku [row * COLUMNS + i]);
		removeNumberFromVector(possibleNumbers, sudoku [i * COLUMNS + column]);
	}

	int firstAreaColumn = (column / 3) * 3;
	int firstAreaRow = (row / 3) * 3;
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			removeNumberFromVector(possibleNumbers, sudoku [(firstAreaRow + i) * COLUMNS + firstAreaColumn + j]);
}

/////////////////////////////////////
void removeNumberFromVector(std::vector <int> &vector, int number)
{
	for (auto it = vector.begin(); it != vector.end(); ++it)
	{
		if (*it == number)
		{
			vector.erase(it);
			return;
		}
	}
}

/////////////////////////////////////
bool isInVector(const std::vector <int> &vector, int number)
{
	for (auto x : vector)
		if (x == number)
			return true;

	return false;
}
