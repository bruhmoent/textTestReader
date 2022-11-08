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
#include <Windows.h>
#include <locale>
#include <codecvt>


using namespace std;

 inline pair<vector<wstring>, int> getFileData(string fileName) {
	string questions;
	int lineNumber = 0;

	wifstream questionStream(fileName);
	wchar_t buffer[1024];
	list<wstring> lines;
	std::locale utf8_locale(std::locale(), new std::codecvt_utf8<wchar_t>);
	questionStream.imbue(utf8_locale);

	if (questionStream.is_open()) {
		while (questionStream.good()) {
			questionStream.getline(buffer, 1024);
			wstring ws(buffer);
			lines.push_back(ws);
			lineNumber++;
		}

		questionStream.close();
	}

	vector<wstring> vectorLines(lines.begin(), lines.end());
	return pair<vector<wstring>, int>(vectorLines, lineNumber);
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
void centerify_output(string str, int num_cols) {

	int padding_left = (num_cols - 3) - (str.size());

	for (int i = 0; i < padding_left; ++i) cout << ' ';
	cout << str;
}
int main()
{
	SetConsoleOutputCP(65001);
	setvbuf(stdout, nullptr, _IOFBF, 1000);

	ios_base::sync_with_stdio(false);
	wcin.imbue(locale("pl_PL.UTF-8"));
	wcout.imbue(locale("pl_PL.UTF-8"));

	std::vector<std::string> lines = {
	   "--------------------------------",
	   "|                              |",
	   "|                              |",
	   "|       Tolopogie sieci        |",
	   "|          Test/Quiz           |",
	   "|                              |",
	   "|                              |",
	   "--------------------------------",
	};

	int num_cols = 80;
	cout << endl;
	for (int i = 0; i < lines.size(); ++i) {
		centerify_output(lines[i], num_cols);
		cout << endl;
	}
	cout << endl;
	float wynik = 0.0;
	string answer;
	float suma = 0.0;
	string questions;
	string repeat;
	wstring userAnswer;
	//cout << "\n\t\t\t\t\t|| QUIZ Z ZAKRESU TOPOLOGII SIECI ||\n";
	//"Z jakiego pliku chcesz otworzyć pytania"
	questions = "questions.txt";
	pair<vector<wstring>, int> questionData = getFileData(questions);
	//"Z jakiego pliku chcesz otworzyć odpowiedzi"
	answer = "answers.txt";
	pair<vector<wstring>, int> answerData = getFileData(answer);

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

			cout << "\nPytanie " << forLoopInc << ": ";
			wcout << questionData.first[question_numbers[randomNumber2]];
			cout << "\nOdpowiedź: \n";
			wcin >> userAnswer;
			transform(userAnswer.begin(), userAnswer.end(), userAnswer.begin(), ::tolower);
			transform(answerData.first[question_numbers[randomNumber2]].begin(),
				answerData.first[question_numbers[randomNumber2]].end(), answerData.first[question_numbers[randomNumber2]].begin(), ::tolower);
			if (userAnswer == answerData.first[question_numbers[randomNumber2]]) {
				cout << "\nDobra odpowiedź!\n";
				wynik++;
			}
			else {
				cout << "\nZła odpowiedz!\n";
			}
		}
		auto end = chrono::steady_clock::now();
		suma = (wynik * 100) / questionSize;
		cout << "\nUzyskałeś: " << suma << "%." << " Test rozwiązałeś w: " << chrono::duration_cast<chrono::seconds>(end - start).count() << " sekund.";
		cout << "\nCzy chcesz powtorzyć test? (T/N)\n";
		cin >> repeat;
		transform(repeat.begin(), repeat.end(), repeat.begin(), ::tolower);

	} while (repeat == "t");
	cout << "\nPowtórzyłeś test " << countRepeat << " raz/razy";
	return 0;
}
