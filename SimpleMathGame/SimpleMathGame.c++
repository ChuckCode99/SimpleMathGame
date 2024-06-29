#include <iostream>
#include <chrono>
#include <random>

#define MAX_NUMBER 25
#define MIN_NUMBER -25
#define NUMBER_OF_PROBLEMS 3 //24

enum Operators { PLUS = 0, MINUS, MULTIPLY };

char findOperator(Operators Input)
{
	switch (Input)
	{
	case PLUS:
		return '+';
	case MINUS:
		return '-';
	case MULTIPLY:
		return '*';
	}

	return '&';
}

struct problem
{
	int Operatees[2];
	Operators Operator;

	void display()
	{
		std::cout << Operatees[0] << " " << findOperator(Operator) << " " << Operatees[1] << " =";
	}
}Example;

struct game_result
{
	problem A;
	int Answer;
	int CorrectAnswer;
	static float CorrectAnswers;

	game_result() = default;

	game_result(problem& InputProblem, int& InputAnswer)
	{
		A = InputProblem;
		Answer = InputAnswer;

		switch (A.Operator)
		{
		case PLUS:
		{
			CorrectAnswer = A.Operatees[0] + A.Operatees[1];
			break;
		}
		case MINUS:
		{
			CorrectAnswer = A.Operatees[0] - A.Operatees[1];
			break;
		}
		case MULTIPLY:
		{
			CorrectAnswer = A.Operatees[0] * A.Operatees[1];
			break;
		}
		}

		if (Answer == CorrectAnswer)
			CorrectAnswers += 1;
	}

	void display()
	{
		A.display();
		std::cout << " " << CorrectAnswer << "\tYour answer: " << Answer;
	}

}GameResult[NUMBER_OF_PROBLEMS];

float game_result::CorrectAnswers{};

int main()
{
	std::random_device rd;															// Create a random device
	std::mt19937 RandomEngine(rd()); 												// Seed the random number engine with the random device
	std::uniform_int_distribution<> RandomNumberGenerator(MIN_NUMBER, MAX_NUMBER);	// Define a distribution (uniform distribution in this case) range from MIN_NUMBER to MAX_NUMBER
	std::uniform_int_distribution<> RandomOperatorGenerator(0, 2);

	//This is where the game code starts
	auto start = std::chrono::high_resolution_clock::now();

	for (int i{ 0 }; i < NUMBER_OF_PROBLEMS; i++)
	{
		int Answer;

		Example.Operatees[0] = RandomNumberGenerator(RandomEngine);
		Example.Operatees[1] = RandomNumberGenerator(RandomEngine);
		Example.Operator = static_cast<Operators>(RandomOperatorGenerator(RandomEngine));
		Example.display();

		std::cout << " ";
		std::cin >> Answer;

		GameResult[i] = game_result(Example, Answer);
	}

	auto end = std::chrono::high_resolution_clock::now();


	for (int i{ 0 }; i < NUMBER_OF_PROBLEMS; i++)
	{
		std::cout << "No." << i + 1 << ":  ";
		GameResult[i].display();
		std::cout << std::endl;
	}
	auto duration = std::chrono::duration_cast<std::chrono::seconds>(end - start);

	std::cout << "Operation took " << duration.count() << " seconds and " << game_result::CorrectAnswers / NUMBER_OF_PROBLEMS * 100 << "\% correct." << std::endl;

	return 0;
}