#include <iostream>
#include <list>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>
#include <cctype>
using namespace std;
class Karta
{

public:
	string rodzaj;
	string temp;
	Karta()
	{

	}
	~Karta()
	{
	}
	Karta(string rodzaj) {
		this->rodzaj = rodzaj;
	}
	void display()
	{
		cout << "\n Karta: " << rodzaj;
	}
	void checkForPin(int pin)
	{
		if (pin < 0 || pin > 9999)
		{
			cout << "\nPin jest niepoprawny.\n";
			exit(1);
		}
	}
	auto getValue(string kar) const
	{

		if (kar == this->rodzaj)
			return  0;
		else
			return 1;
	}

};

inline vector<Karta*> addCards(vector<Karta*> karty, string karta)
{
	transform(karta.begin(), karta.end(), karta.begin(), [](unsigned char c) { return std::tolower(c); });
	karty.push_back(new Karta(karta));
	return karty;
}

void checkCards(vector<Karta*> tempList, string* card)
{
	string cardRzut = "";
	cardRzut = *card;
	transform(cardRzut.begin(), cardRzut.end(), cardRzut.begin(), [](unsigned char c) { return std::tolower(c); });
	if (std::find_if(tempList.begin(), tempList.end(), [&cardRzut](Karta* my) { return my->getValue(cardRzut) == 0; }) != tempList.end())
	{
		cout << "\nKarta znaleziona.\n";
	}
	else
	{
		cout << "\nKarta nie istnieje.\n";
		exit(1);
	}

}

void showCards(vector<Karta*> tempList)
{
	for (auto i : tempList)
	{
		i->display();
	}
}

int main(int argc, char** argv) {
	string odp = "";
	string karta;
	string* choosenCard;
	Karta* pinPtr = new Karta;
	string choosenCardE = "";
	string repeatPay;
	double kwota = 0;
	double suma = 0;
	choosenCard = &choosenCardE;
	int repeat;
	int pin;
	vector<Karta*> karty{};
	do {

		kwota = 0;
		suma = 0;
		repeat = 0;
		pin = 0;
		cout << "\nPodaj liczbe akceptowalnych kart\n";
		cin >> repeat;
		for (int i = 0; i < repeat; i++) {
			cout << "\nPrzed instalacja bankomatu, podaj akceptowalne karty:\n";
			cin >> karta;
			karty = addCards(karty, karta);
		}

		cout << "\nBANKOMAT QUAGMIRE ATM\n";
		cout << "\nKARTY AKCEPTOWANE PRZEZ BANKOMAT:\n";
		showCards(karty);
		cout << "\nWloz karte: \n";
		cin >> *choosenCard;

		checkCards(karty, choosenCard);
		cout << "\nWprowadz pin: \n";
		cin >> pin;
		pinPtr->checkForPin(pin);

		do {
			cout << "\nWyplac kwote: \n";
			cin >> kwota;

			if (kwota <= 0)
			{
				cout << "\nNieprawidlowa kwota.\n";
				break;
			}
			suma += ceil(kwota * 100.0) / 100.0;
			cout << "\nCzy chcesz wyplacic ponownie? (T/N)\n";
			cin >> repeatPay;
			transform(repeatPay.begin(), repeatPay.end(), repeatPay.begin(), [](unsigned char c) { return std::tolower(c); });
		} while (repeatPay == "t");
		cout << "\nWyplaciles: " << suma << " zl.\n";

		cout << "\nCzy chcesz skorzystac z bankomatu ponownie? (T/N)\n";
		cin >> odp;
		transform(odp.begin(), odp.end(), odp.begin(), [](unsigned char c) { return std::tolower(c); });
	} while (odp == "t");
	return 0;
}