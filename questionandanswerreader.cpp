#include <fstream>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <algorithm>
#include <stdio.h>
#include <vector>
#include <utility>  
#include <cstring>
#include <chrono>
#include <ctime>
#include "questionandanswerreader.h"
#include <list>
using namespace std;
inline pair<vector<string>, int> getFileData(string fileName) {
	string questions;
	int lineNumber = 0;

	ifstream questionStream(fileName);
	string lineText;
	list<string> lines;
	if (questionStream.is_open()) {
		while (getline(questionStream, lineText)) {
			lines.push_back(lineText);
			lineNumber++;
		}

		questionStream.close();
	}
	
	vector<string> vectorLines(lines.begin(), lines.end());
	return pair<vector<string>, int>(vectorLines, lineNumber);
}
inline vector<int> getRandomNumbers(int size) {
	list<int> availableNumbers; //tablica na wyniki.

	for (int i = 0; i < size; i++)
	{
		availableNumbers.push_back(i);
	}

	vector<int> availableNumbers2(availableNumbers.begin(), availableNumbers.end());
	srand(time(NULL));
	random_shuffle(availableNumbers2.begin(), availableNumbers2.end());

	return availableNumbers2;
}

int main()
{
	float wynik = 0.0;
	string answer;
	float suma = 0.0;
	string questions;
	string repeat;
	string userAnswer = "";
	setlocale(LC_CTYPE, "Polish");
	//"Z jakiego pliku chcesz otworzyć pytania"
	questions = "questions.txt";
	pair<vector<string>, int> questionData = getFileData(questions);
	//"Z jakiego pliku chcesz otworzyć odpowiedzi"
	answer = "answers.txt";
	pair<vector<string>, int> answerData = getFileData(answer);

	int questionSize = (questionData.second);
	int forLoopInc = 0;
	int randomNumber2 = 0;
	int countRepeat = 0;
	std::vector<int> question_numbers;
	for (int i = 0; i < questionSize; i++) {
		question_numbers.push_back(i);
	}

	do {
		repeat = "";

		randomNumber2 = 0;
		countRepeat++;

		vector<int> availableNumbers2 = getRandomNumbers(question_numbers.size());

		int maxValue = question_numbers.size(); //maksymalna liczba losowania

		randomNumber2 = 0;
		suma = 0;
		wynik = 0;
		auto start = chrono::steady_clock::now();

		forLoopInc = 0;
		for (int i = 0; i < questionSize; i++) {
			forLoopInc++;

			randomNumber2 = availableNumbers2[i];

			cout << "\nPytanie " << forLoopInc << ": " << questionData.first[question_numbers[randomNumber2]];
			cout << "\nOdpowiedź: \n";
			cin >> userAnswer;
			transform(userAnswer.begin(), userAnswer.end(), userAnswer.begin(), ::tolower);
			transform(answerData.first[question_numbers[randomNumber2]].begin(),
				answerData.first[question_numbers[randomNumber2]].end(), answerData.first[question_numbers[randomNumber2]].begin(), ::tolower);
			if (userAnswer == answerData.first[question_numbers[randomNumber2]]) {
				cout << "\nDobra odpowiedz!\n";
				wynik++;
			}
			else {
				cout << "\nZła odpowiedz!\n";
			}
		}
		auto end = chrono::steady_clock::now();
		suma = (wynik * 100) / questionSize;
		cout << "\nUzyskałeś: " << suma << "%." << "Test rozwiązałeś w: " << chrono::duration_cast<chrono::seconds>(end - start).count() << " sekund.";
		cout << "\nCzy chcesz powtorzyć test? (T/N)\n";
		cin >> repeat;
		transform(repeat.begin(), repeat.end(), repeat.begin(), ::tolower);

	} while (repeat == "t");
	cout << "\nPowtorzyłes test " << countRepeat << " raz/razy";
	return 0;
}
