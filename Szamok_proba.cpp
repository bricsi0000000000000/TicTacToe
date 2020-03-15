#include "pch.h"
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <wincon.h>
#include <cstdlib>

using namespace std;

int const szelesseg = 13;
int const magassag = 13;

int lepesek_szama;
int ossz_lepes = 9; //A döntetlent ez alapján nézem
int melyik_jatekos = 1;
int kezdo_jatekos = 1;
int gep_utolso_lepes;
int gep_varakozas_ido = 200;
int gep_gep_varakozas_ido = 800;

int jatekos_egy_lepes_szam = 0;
int jatekos_ketto_lepes_szam = 0;

enum nehezsegi_szintek { konnyu = 1, kozepes = 2, nehez = 3, expert = 4 };
nehezsegi_szintek nehezsegi_szint = nehezsegi_szintek::konnyu;

enum jatekmodok { JATEKOS_JATEKOS = 1, JATEKOS_GEP = 2, GEP_GEP = 3 };
jatekmodok jatekmod = jatekmodok::JATEKOS_JATEKOS;

#pragma region Pontszamok
int jatekos_egy_pontszam = 0;
int jatekos_ketto_pontszam = 0;

int haromlepeses_gyozelem = 100;
int negylepeses_gyozelem = 50;
#pragma endregion

//Jatekosok karaktere
char JATEKOS_EGY = 'X';
char JATEKOS_KETTO = 'O';

char tabla[szelesseg][magassag];
char kis_tabla[3][3];

bool jatek_vege = false;
bool kilepes_txt_egyszer = true;
bool gep_lepes_eloszor = true;
bool jatek_eleje = true;

#pragma region fuggvenyek
void TablaRajzol();
void TablaInit();
void KisTablaInit();
void TablaSzerkeszt(int szam);
bool TablaCheck(int szam);
int LepesBekerese();
void Cim();
void Vizsgal();
void Dontetlen();
void JatekVege();
void UjJatek();
void GepLepes();
void GepLepesRandom();
void GepLepesMelle();
void KisTablaTarol(int mezo_nev);
void Menu();
void Beallitasok();
void BeallitasokUI();
void Kilepes();
void KarakterekValtoztatasa();
void JatekMehet();
#pragma endregion

#pragma region szinek
int border_szin = 8;
int cim_szin = 14;
int alap_szin = 15;
int jatekos_ketto_szin = 13;
int jatekos_egy_szin = 11;
int szamok_szin = 7;
int jatek_vege_szin = 12;
int beallitasok_szin = 10;
int kilepes_szin = 8;
int jatekmod_allapota_szin = 3;
int gep_elleni_szin = 14;
int ember_elleni_szin = 7;
//nehezsegi szintek
int konnyu_szin = 2;
int kozepes_szin = 9;
int nehez_szin = 6;
int expert_szin = 4;
#pragma endregion

HANDLE szinezes = GetStdHandle(STD_OUTPUT_HANDLE);

int main()
{
	Menu();
}

void JatekMehet() {
	jatekos_egy_lepes_szam = 0;
	jatekos_ketto_lepes_szam = 0;
	jatekos_egy_pontszam = 0;
	jatekos_ketto_pontszam = 0;
	melyik_jatekos = kezdo_jatekos;
	jatek_vege = false;
	gep_lepes_eloszor = true;
	jatek_eleje = true;
	lepesek_szama = 0;
	KisTablaInit();
	TablaInit();
	TablaRajzol();
}

void Menu() {
	system("cls");

	SetConsoleTextAttribute(szinezes, border_szin);
	cout << "\t" << char(201);
	for (int i = 0; i < 33; i++)
	{
		cout << char(205);
	}
	cout << char(187);

	cout << endl << "\t" << char(186);

	SetConsoleTextAttribute(szinezes, cim_szin);
	cout << "\t\tMENU";

	SetConsoleTextAttribute(szinezes, border_szin);
	cout << "\t\t  " << char(186) << endl;

	cout << "\t" << char(186) << "\t\t\t\t  " << char(186);
	cout << endl << "\t" << char(186);

	SetConsoleTextAttribute(szinezes, jatekos_egy_szin);
	cout << "\tJATEK INDITASA 'i'";

	SetConsoleTextAttribute(szinezes, border_szin);
	cout << "\t  " << char(186);

	cout << endl << "\t" << char(186);

	SetConsoleTextAttribute(szinezes, beallitasok_szin);
	cout << "\tBEALLITASOK 'b'";

	SetConsoleTextAttribute(szinezes, border_szin);
	cout << "\t\t  " << char(186) << endl;

	SetConsoleTextAttribute(szinezes, border_szin);
	cout << "\t" << char(186);

	SetConsoleTextAttribute(szinezes, kilepes_szin);
	cout << "\tKILEPES 'k'";

	SetConsoleTextAttribute(szinezes, border_szin);
	cout << "\t\t  " << char(186) << endl;

	SetConsoleTextAttribute(szinezes, border_szin);
	cout << "\t" << char(200);

	SetConsoleTextAttribute(szinezes, border_szin);
	for (int i = 0; i < 33; i++)
	{
		cout << char(205);
	}
	cout << char(188);

	SetConsoleTextAttribute(szinezes, alap_szin);
	cout << endl << "\t\tMelyiket szeretned? ";

	char bekert_karakter;
	cin >> bekert_karakter;

	if (bekert_karakter == 'b') {
		BeallitasokUI();
	}
	else if (bekert_karakter == 'k') {
		Kilepes();
	}
	else if (bekert_karakter == 'i') {
		JatekMehet();
	}
}

void Kilepes() {
	exit(0);
}

void BeallitasokUI() {
	system("cls");

	SetConsoleTextAttribute(szinezes, border_szin);
	cout << "\t" << char(201);
	for (int i = 0; i < 63; i++)
	{
		cout << char(205);
	}
	cout << char(187) << endl;

	cout << "\t" << char(186);

	SetConsoleTextAttribute(szinezes, beallitasok_szin);
	cout << "\t\t\tBEALLITASOK";

	SetConsoleTextAttribute(szinezes, border_szin);
	cout << "\t\t\t\t" << char(186) << endl;

	cout << "\t" << char(186);
	for (int i = 0; i < 63; i++)
	{
		cout << " ";
	}
	cout << char(186) << endl;

	cout << "\t" << char(186);

	//KI MILYEN KARAKTERREL
	SetConsoleTextAttribute(szinezes, jatekmod_allapota_szin);
	cout << "\tKARAKTEREK VALTOZTATASA 'k'";

	SetConsoleTextAttribute(szinezes, border_szin);
	cout << "\t\t\t\t" << char(186) << endl;

	cout << "\t" << char(186);

	//JATEKMOD VALT
	SetConsoleTextAttribute(szinezes, jatekmod_allapota_szin);
	cout << "\tJatekmod allapota: ";

	switch (jatekmod)
	{
	case JATEKOS_JATEKOS:
		SetConsoleTextAttribute(szinezes, ember_elleni_szin);
		cout << "JATEKOS - JATEKOS";
		SetConsoleTextAttribute(szinezes, jatekmod_allapota_szin);
		cout << " |VALTOZTAT 'j'";

		SetConsoleTextAttribute(szinezes, border_szin);
		cout << "\t" << char(186) << endl;
		break;
	case JATEKOS_GEP:
		SetConsoleTextAttribute(szinezes, gep_elleni_szin);
		cout << "JATEKOS - GEP";
		SetConsoleTextAttribute(szinezes, jatekmod_allapota_szin);
		cout << " |VALTOZTAT 'j'";

		SetConsoleTextAttribute(szinezes, border_szin);
		cout << "\t\t" << char(186) << endl;
		break;
	case GEP_GEP:
		SetConsoleTextAttribute(szinezes, gep_elleni_szin);
		cout << "GEP - GEP";
		SetConsoleTextAttribute(szinezes, jatekmod_allapota_szin);
		cout << " |VALTOZTAT 'j'";

		SetConsoleTextAttribute(szinezes, border_szin);
		cout << "\t\t" << char(186) << endl;
		break;
	}



	cout << "\t" << char(186);

	//NEHEZSEGI SZINT
	if (jatekmod == 2 || jatekmod == 3) {
		SetConsoleTextAttribute(szinezes, jatekmod_allapota_szin);
		cout << "\tNehezsegi szint: ";

		switch (nehezsegi_szint)
		{
		case konnyu:
			SetConsoleTextAttribute(szinezes, konnyu_szin);
			cout << "KONNYU";
			break;
		case kozepes:
			SetConsoleTextAttribute(szinezes, kozepes_szin);
			cout << "KOZEPES";
			break;
		case nehez:
			SetConsoleTextAttribute(szinezes, nehez_szin);
			cout << "NEHEZ";
			break;
		case expert:
			SetConsoleTextAttribute(szinezes, expert_szin);
			cout << "EXPERT";
			break;
		}

		SetConsoleTextAttribute(szinezes, jatekmod_allapota_szin);
		cout << " |VALTOZTAT 'n'";

		SetConsoleTextAttribute(szinezes, border_szin);
		cout << "\t\t\t" << char(186) << endl;

		cout << "\t" << char(186);
	}

	//KI KEZDJEN
	SetConsoleTextAttribute(szinezes, jatekmod_allapota_szin);
	cout << "\tJelenlegi kezdo jatekos: ";

	if (jatekmod == 1) {
		if (kezdo_jatekos == 1) {
			SetConsoleTextAttribute(szinezes, jatekos_egy_szin);
			cout << "JATEKOS EGY";
		}
		else if (kezdo_jatekos == 2) {
			SetConsoleTextAttribute(szinezes, jatekos_ketto_szin);
			cout << "JATEKOS KETTO";
		}
	}
	else if (jatekmod == 2) {
		if (kezdo_jatekos == 1) {
			SetConsoleTextAttribute(szinezes, jatekos_egy_szin);
			cout << "JATEKOS EGY";
		}
		else if (kezdo_jatekos == 2) {
			SetConsoleTextAttribute(szinezes, jatekos_ketto_szin);
			cout << "GEP";
		}
	}
	else if (jatekmod == 3) {
		if (kezdo_jatekos == 1) {
			SetConsoleTextAttribute(szinezes, jatekos_egy_szin);
			cout << "GEP 1";
		}
		else if (kezdo_jatekos == 2) {
			SetConsoleTextAttribute(szinezes, jatekos_ketto_szin);
			cout << "GEP 2";
		}
	}

	SetConsoleTextAttribute(szinezes, jatekmod_allapota_szin);
	cout << " |VALTOZTAT 'v'";

	SetConsoleTextAttribute(szinezes, border_szin);
	if (jatekmod == 2) {
		if (kezdo_jatekos == 1) {
			cout << "\t" << char(186) << endl;
		}
		else {
			cout << "\t\t" << char(186) << endl;
		}
	}
	else if (jatekmod == 3) {
		cout << "\t\t" << char(186) << endl;
	}
	else {
		cout << "\t" << char(186) << endl;
	}


	cout << "\t" << char(186);
	for (int i = 0; i < 63; i++)
	{
		cout << " ";
	}
	cout << char(186) << endl;

	cout << "\t" << char(186);

	SetConsoleTextAttribute(szinezes, border_szin);
	cout << "\tMENU 'm'";

	SetConsoleTextAttribute(szinezes, border_szin);
	cout << "\t\t\t\t\t\t" << char(186) << endl;

	cout << "\t" << char(200);

	for (int i = 0; i < 63; i++)
	{
		cout << char(205);
	}
	cout << char(188);


	SetConsoleTextAttribute(szinezes, alap_szin);
	cout << endl << "\t\tMelyiket szeretned? ";

	Beallitasok();
}

void Beallitasok() {

	char bekert_karakter;
	cin >> bekert_karakter;

	if (bekert_karakter == 'j') {
		if (jatekmod == jatekmodok::JATEKOS_JATEKOS) {
			jatekmod = jatekmodok::JATEKOS_GEP;
		}
		else if (jatekmod == jatekmodok::JATEKOS_GEP) {
			jatekmod = jatekmodok::GEP_GEP;
		}
		else if (jatekmod == jatekmodok::GEP_GEP) {
			jatekmod = jatekmodok::JATEKOS_JATEKOS;
		}
		BeallitasokUI();
	}
	else if (bekert_karakter == 'k') {
		KarakterekValtoztatasa();
	}
	else if (bekert_karakter == 'v') {
		if (kezdo_jatekos == 1) {
			kezdo_jatekos = 2;
		}
		else if (kezdo_jatekos == 2) {
			kezdo_jatekos = 1;
		}
		BeallitasokUI();
	}
	else if (bekert_karakter == 'n') {
		if (nehezsegi_szint == nehezsegi_szintek::konnyu) {
			nehezsegi_szint = nehezsegi_szintek::kozepes;
		}
		else if (nehezsegi_szint == nehezsegi_szintek::kozepes) {
			nehezsegi_szint = nehezsegi_szintek::nehez;
		}
		else if (nehezsegi_szint == nehezsegi_szintek::nehez) {
			nehezsegi_szint = nehezsegi_szintek::expert;
		}
		else if (nehezsegi_szint == nehezsegi_szintek::expert) {
			nehezsegi_szint = nehezsegi_szintek::konnyu;
		}
		BeallitasokUI();
	}
	else if (bekert_karakter == 'i') {
		JatekMehet();
	}
	else {
		Menu();
	}
}

void KarakterekValtoztatasa() {
	system("cls");

	SetConsoleTextAttribute(szinezes, border_szin);
	cout << "\t" << char(201);
	for (int i = 0; i < 50; i++)
	{
		cout << char(205);
	}
	cout << char(187) << endl;

	cout << "\t" << char(186);

	SetConsoleTextAttribute(szinezes, jatekos_egy_szin);
	cout << "\tJATEKOS 1 jelenlegi karaktere: " << JATEKOS_EGY;

	SetConsoleTextAttribute(szinezes, border_szin);
	cout << "\t   " << char(186) << endl;

	cout << "\t" << char(186);

	SetConsoleTextAttribute(szinezes, jatekos_ketto_szin);
	cout << "\tJATEKOS 2 jelenlegi karaktere: " << JATEKOS_KETTO;

	SetConsoleTextAttribute(szinezes, border_szin);
	cout << "\t   " << char(186) << endl;

	cout << "\t" << char(186);

	for (int i = 0; i < 50; i++)
	{
		cout << " ";
	}
	cout << char(186);

	cout << endl;

	cout << "\t" << char(186);

	SetConsoleTextAttribute(szinezes, border_szin);
	cout << "\tMENU 'm' BEALLITASOK 'b'";

	SetConsoleTextAttribute(szinezes, border_szin);
	cout << "\t\t   " << char(186) << endl;

	cout << "\t" << char(200);
	for (int i = 0; i < 50; i++)
	{
		cout << char(205);
	}
	cout << char(188) << endl;

	//JATEKOS 1
	SetConsoleTextAttribute(szinezes, jatekos_egy_szin);
	char bekert_karakter;
	do {
		cout << "\t\tJATEKOS 1 uj karaktere: ";
		cin >> bekert_karakter;

	} while ((int)bekert_karakter >= 48 && (int)bekert_karakter <= 57);

	if (bekert_karakter == 'b') {
		BeallitasokUI();
	}
	else if (bekert_karakter == 'm') {
		Menu();
	}
	else {
		JATEKOS_EGY = bekert_karakter;
	}

	//JATEKOS 2
	bekert_karakter = ' ';
	SetConsoleTextAttribute(szinezes, jatekos_ketto_szin);
	do {
		cout << "\t\tJATEKOS 2 uj karaktere: ";
		cin >> bekert_karakter;

	} while ((int)bekert_karakter >= 48 && (int)bekert_karakter <= 57);

	if (bekert_karakter == 'b') {
		BeallitasokUI();
	}
	else if (bekert_karakter == 'm') {
		Menu();
	}
	else {
		JATEKOS_KETTO = bekert_karakter;
	}

	BeallitasokUI();
}

void UjJatek() {
	SetConsoleTextAttribute(szinezes, border_szin);
	cout << endl << "\tSzeretned ujrakezdeni? (i/n): ";
	char bekert_karakter;
	cin >> bekert_karakter;
	if (bekert_karakter == 'i') {
		jatekos_egy_lepes_szam = 0;
		jatekos_ketto_lepes_szam = 0;
		jatek_vege = false;
		gep_lepes_eloszor = true;
		jatek_eleje = true;
		lepesek_szama = 0;
		melyik_jatekos = kezdo_jatekos;
		KisTablaInit();
		TablaInit();
		TablaRajzol();
	}
	else if (bekert_karakter == 'b') {
		BeallitasokUI();
	}
	else if (bekert_karakter == 'r') {
		JatekMehet();
	}
	else {
		Menu();
	}
}

void Vizsgal() {
	int mind = 0;
#pragma region ELSO JATEKOS
	//vizszintesen
	for (int sor = 0; sor < szelesseg; sor++)
	{
		for (int oszlop = 0; oszlop < szelesseg; oszlop++)
		{
			if (sor == 2 || sor == 6 || sor == 10)
				if (tabla[sor][oszlop] == JATEKOS_EGY) {
					mind++;
					if (mind == 3) {
						JatekVege();
						return;

					}
				}
		}
		mind = 0;
	}
	//fuggoleges
	for (int sor = 0; sor < szelesseg; sor++)
	{
		for (int oszlop = 0; oszlop < szelesseg; oszlop++)
		{
			if (oszlop == 2 || oszlop == 6 || oszlop == 10)
				if (tabla[oszlop][sor] == JATEKOS_EGY) {
					mind++;
					if (mind == 3) {
						JatekVege();
					}
				}
		}
		mind = 0;
	}
	//atlo: bal_felul -> jobb_alul
	for (int sor = 0; sor < szelesseg; sor++)
	{
		for (int oszlop = 0; oszlop < szelesseg; oszlop++)
		{
			if (sor == oszlop)
				if (tabla[sor][oszlop] == JATEKOS_EGY) {
					mind++;
					if (mind == 9) {
						JatekVege();
					}
				}
		}
	}
	mind = 0;
	//atlo: bal_alul -> jobb_felul
	for (int sor = 0; sor < szelesseg; sor++)
	{
		for (int oszlop = 0; oszlop < szelesseg; oszlop++)
		{
			if (szelesseg - 1 - sor == oszlop)
				if (tabla[sor][oszlop] == JATEKOS_EGY) {
					mind++;
					if (mind == 9) {
						JatekVege();
					}
				}
		}
	}
	mind = 0;
#pragma endregion

#pragma region MASODIK JATEKOS
	//vizszintesen
	for (int sor = 0; sor < szelesseg; sor++)
	{
		for (int oszlop = 0; oszlop < szelesseg; oszlop++)
		{
			if (sor == 2 || sor == 6 || sor == 10)
				if (tabla[sor][oszlop] == JATEKOS_KETTO) {
					mind++;
					if (mind == 6) {
						JatekVege();
						return;

					}
				}
		}
		mind = 0;
	}
	mind = 0;
	//fuggoleges
	for (int sor = 0; sor < szelesseg; sor++)
	{
		for (int oszlop = 0; oszlop < szelesseg; oszlop++)
		{
			if (oszlop == 1 || oszlop == 5 || oszlop == 9)
				if (tabla[oszlop][sor] == JATEKOS_KETTO) {
					mind++;
					if (mind == 3) {
						JatekVege();
					}
				}
		}
		mind = 0;
	}
	//atlo: bal_felul -> jobb_alul
	for (int sor = 0; sor < szelesseg; sor++)
	{
		for (int oszlop = 0; oszlop < szelesseg; oszlop++)
		{
			if (oszlop + 1 == sor)
				if (tabla[sor][oszlop] == JATEKOS_KETTO) {
					mind++;
					if (mind == 6) {
						JatekVege();
					}
				}
		}
	}
	mind = 0;
	//atlo: bal_alul -> jobb_felul
	for (int sor = 0; sor < szelesseg; sor++)
	{
		for (int oszlop = 0; oszlop < szelesseg; oszlop++)
		{
			if (szelesseg - 1 - sor == oszlop)
				if (tabla[sor][oszlop] == ' ') {
					mind++;
					if (mind == 9) {
						JatekVege();
					}
				}
		}
	}
	mind = 0;
#pragma endregion

	if (lepesek_szama == ossz_lepes)
		Dontetlen();
}

void Dontetlen() {
	system("cls");

	jatek_vege = true;

	TablaRajzol();

	SetConsoleTextAttribute(szinezes, jatek_vege_szin);

	cout << endl << endl << "\tJATEK VEGE" << endl;

	SetConsoleTextAttribute(szinezes, cim_szin);
	cout << "\tDONTENTLEN";
	SetConsoleTextAttribute(szinezes, alap_szin);

	UjJatek();
}

void JatekVege() {
	system("cls");

	jatek_vege = true;

	if (melyik_jatekos == 1) {
		if (jatekos_egy_lepes_szam == 3) {
			jatekos_egy_pontszam += haromlepeses_gyozelem;
		}
		else if (jatekos_egy_lepes_szam == 4) {
			jatekos_egy_pontszam += negylepeses_gyozelem;
		}
	}
	if (melyik_jatekos == 2) {
		if (jatekos_ketto_lepes_szam == 3) {
			jatekos_ketto_pontszam += haromlepeses_gyozelem;
		}
		else if (jatekos_ketto_lepes_szam == 4) {
			jatekos_ketto_pontszam += negylepeses_gyozelem;
		}
	}

	TablaRajzol();

	SetConsoleTextAttribute(szinezes, jatek_vege_szin);

	cout << endl << endl << "\tJATEK VEGE" << endl;

	SetConsoleTextAttribute(szinezes, alap_szin);
	cout << "\tNYERTES: ";

	if (melyik_jatekos == 1) {
		SetConsoleTextAttribute(szinezes, jatekos_egy_szin);
		cout << "ELSO JATEKOS" << endl;
	}
	else {
		SetConsoleTextAttribute(szinezes, jatekos_ketto_szin);
		cout << "MASODIK JATEKOS" << endl;
	}

	SetConsoleTextAttribute(szinezes, cim_szin);
	cout << "\tNYEREMENY: +";
	if (melyik_jatekos == 1) {
		if (jatekos_egy_lepes_szam == 3) {
			cout << haromlepeses_gyozelem;
		}
		else if (jatekos_egy_lepes_szam == 4) {
			cout << negylepeses_gyozelem;
		}
	}
	if (melyik_jatekos == 2) {
		if (jatekos_ketto_lepes_szam == 3) {
			cout << haromlepeses_gyozelem;
		}
		else if (jatekos_ketto_lepes_szam == 4) {
			cout << negylepeses_gyozelem;
		}
	}

	cout << " PONT" << endl;

	SetConsoleTextAttribute(szinezes, alap_szin);

	UjJatek();
}

void Cim() {
	cout << endl;

	SetConsoleTextAttribute(szinezes, border_szin);

	cout << endl << "\t" << char(201);
	for (int i = 0; i < 27; i++)
	{
		cout << char(205);
	}
	//jobb felso sarok
	cout << char(187) << endl;
	cout << "\t" << char(186);


	SetConsoleTextAttribute(szinezes, beallitasok_szin);
	//felul balra kanyar
	cout << char(201);
	for (int i = 0; i < 6; i++)
	{
		cout << char(205);
	}

	//cim bal oldala
	cout << char(187);

	//cim
	SetConsoleTextAttribute(szinezes, cim_szin);
	cout << "TIC TAC TOE";

	//cim jobb oldala
	SetConsoleTextAttribute(szinezes, beallitasok_szin);
	//felul jobbra kanyar
	cout << char(201);
	for (int i = 0; i < 6; i++)
	{
		cout << char(205);
	}
	cout << char(187);

	SetConsoleTextAttribute(szinezes, border_szin);
	cout << char(186) << endl;
	cout << "\t" << char(186);

	//bal oldalt egy alahuzas fuggoleges vonal
	SetConsoleTextAttribute(szinezes, beallitasok_szin);
	cout << char(186) << "\t";

	SetConsoleTextAttribute(szinezes, beallitasok_szin);
	//bal also sarok
	cout << char(200);
	for (int i = 0; i < 11; i++)
	{
		//alahuzas
		cout << char(205);
	}
	//jobb also sarok
	cout << char(188);

	//jobb oldalt egy alahuzas fuggoleges vonal
	SetConsoleTextAttribute(szinezes, beallitasok_szin);
	cout << "\t   " << char(186);

	SetConsoleTextAttribute(szinezes, border_szin);
	cout << char(186);

	SetConsoleTextAttribute(szinezes, border_szin);
	cout << endl;
}

void KisTablaTarol(int mezo_szam) {
	for (int sor = 0; sor < 3; sor++)
	{
		for (int oszlop = 0; oszlop < 3; oszlop++)
		{
			if (kis_tabla[sor][oszlop] == mezo_szam + '0') {
				kis_tabla[sor][oszlop] = JATEKOS_KETTO;
			}
		}
	}
}

void GepLepesMelle() {

	int sor;
	int oszlop;

	sor = (gep_utolso_lepes - 1) / 3;
	oszlop = (gep_utolso_lepes - 1) % 3;

	
	//FENT KOZEP
	if ((sor - 1 >= 0 && oszlop >= 0) && (kis_tabla[sor - 1][oszlop] != JATEKOS_EGY && kis_tabla[sor - 1][oszlop] != JATEKOS_KETTO)) {
		gep_utolso_lepes = kis_tabla[sor - 1][oszlop] - '0';

		KisTablaTarol(gep_utolso_lepes);
		TablaSzerkeszt(gep_utolso_lepes);
	}

	//JOBB KOZEP
	else if ((sor >= 0 && oszlop + 1 < 3) && (kis_tabla[sor][oszlop + 1] != JATEKOS_EGY && kis_tabla[sor][oszlop + 1] != JATEKOS_KETTO)) {
		gep_utolso_lepes = kis_tabla[sor][oszlop + 1] - '0';

		KisTablaTarol(gep_utolso_lepes);
		TablaSzerkeszt(gep_utolso_lepes);
	}

	//LENT KOZEP
	else if ((sor + 1 < 3 && oszlop < 3) && (kis_tabla[sor + 1][oszlop] != JATEKOS_EGY && kis_tabla[sor + 1][oszlop] != JATEKOS_KETTO)) {
		gep_utolso_lepes = kis_tabla[sor + 1][oszlop] - '0';

		KisTablaTarol(gep_utolso_lepes);
		TablaSzerkeszt(gep_utolso_lepes);
	}

	//BAL KOZEP
	else if ((sor >= 0 && oszlop - 1 >= 0) && (kis_tabla[sor][oszlop - 1] != JATEKOS_EGY && kis_tabla[sor][oszlop - 1] != JATEKOS_KETTO)) {
		gep_utolso_lepes = kis_tabla[sor][oszlop - 1] - '0';

		KisTablaTarol(gep_utolso_lepes);
		TablaSzerkeszt(gep_utolso_lepes);
	}

	//JOBB FELUL
	else if ((sor - 1 >= 0 && oszlop + 1 < 3) && (kis_tabla[sor - 1][oszlop + 1] != JATEKOS_EGY && kis_tabla[sor - 1][oszlop + 1] != JATEKOS_KETTO)) {
		gep_utolso_lepes = kis_tabla[sor - 1][oszlop + 1] - '0';

		KisTablaTarol(gep_utolso_lepes);
		TablaSzerkeszt(gep_utolso_lepes);
	}

	//JOBB ALUL
	else if ((sor + 1 < 3 && oszlop + 1 < 3) && (kis_tabla[sor + 1][oszlop + 1] != JATEKOS_EGY && kis_tabla[sor + 1][oszlop + 1] != JATEKOS_KETTO)) {
		gep_utolso_lepes = kis_tabla[sor + 1][oszlop + 1] - '0';

		KisTablaTarol(gep_utolso_lepes);
		TablaSzerkeszt(gep_utolso_lepes);
	}

	//BAL ALUL
	else if ((sor + 1 < 3 && oszlop - 1 >= 0) && (kis_tabla[sor + 1][oszlop - 1] != JATEKOS_EGY && kis_tabla[sor + 1][oszlop - 1] != JATEKOS_KETTO)) {
		gep_utolso_lepes = kis_tabla[sor + 1][oszlop - 1] - '0';

		KisTablaTarol(gep_utolso_lepes);
		TablaSzerkeszt(gep_utolso_lepes);
	}
	
	//BAL FELUL
	else if ((sor - 1 >= 0 && oszlop - 1 >= 0) && (kis_tabla[sor - 1][oszlop - 1] != JATEKOS_EGY && kis_tabla[sor - 1][oszlop - 1] != JATEKOS_KETTO)) {
		gep_utolso_lepes = kis_tabla[sor - 1][oszlop - 1] - '0';

		KisTablaTarol(gep_utolso_lepes);
		TablaSzerkeszt(gep_utolso_lepes);
	}
	else {
		GepLepesRandom();
	}
}

void GepLepesRandom() {
	int r;
	do {
		r = rand() % 9 + 1;
	} while (!TablaCheck(r));
	gep_utolso_lepes = r;

	KisTablaTarol(r);

	TablaSzerkeszt(r);
}

void GepLepes() {
	if (jatekmod == jatekmodok::GEP_GEP) {
		Sleep(gep_gep_varakozas_ido);
		if (melyik_jatekos == 1) {
			jatekos_egy_lepes_szam++;
		}
		else {
			jatekos_ketto_lepes_szam++;
		}
	}
	else {
		Sleep(gep_varakozas_ido);
		jatekos_ketto_lepes_szam++;
	}


	if (nehezsegi_szint == 1) {
		GepLepesRandom();
	}
	else if (nehezsegi_szint >= 2) {
		//ELSO LEPES
		if (gep_lepes_eloszor) {
			gep_lepes_eloszor = false;

			if (nehezsegi_szint == 2) {
				GepLepesRandom();
			}
			else if (nehezsegi_szint == 3) {
				GepLepesMelle();
			}
			else if (nehezsegi_szint == 4) {
				//SAROKRA LEP
				int r;
				do {
					do {
						r = rand() % 9 + 1;
					} while (r == 2 || r == 6 || r == 8 || r == 4 || r == 5);
				} while (!TablaCheck(r));

				if (r == 1)
				{
					//BAL FELSO
					if (kis_tabla[0][0] != JATEKOS_EGY) {
						gep_utolso_lepes = kis_tabla[0][0] - '0';
						KisTablaTarol(gep_utolso_lepes);
						TablaSzerkeszt(gep_utolso_lepes);
					}
				}
				else if (r == 3) {
					//JOBB FELSO
					if (kis_tabla[0][2] != JATEKOS_EGY) {
						gep_utolso_lepes = kis_tabla[0][2] - '0';
						KisTablaTarol(gep_utolso_lepes);
						TablaSzerkeszt(gep_utolso_lepes);
					}
				}
				else if (r == 9) {
					//JOBB ALSO
					if (kis_tabla[2][2] != JATEKOS_EGY) {
						gep_utolso_lepes = kis_tabla[2][2] - '0';
						KisTablaTarol(gep_utolso_lepes);
						TablaSzerkeszt(gep_utolso_lepes);
					}
				}
				else if (r == 7) {
					//BAL ALSO
					if (kis_tabla[2][0] != JATEKOS_EGY) {
						gep_utolso_lepes = kis_tabla[2][0] - '0';
						KisTablaTarol(gep_utolso_lepes);
						TablaSzerkeszt(gep_utolso_lepes);
					}
				}
			}
		}
		//TOBBI LEPES
		else {
			int ketto_x = 0;
			int melyik_sor = -1;
			int melyik_oszlop = -1;
			int mezo_szam = 0;

			bool vizszintes = false;
			bool fuggoleges = false;
			bool atlo1 = false;
			bool atlo2 = false;
			bool tudott_rakni = false;

#pragma region HA A GEP NYERNE
			//VIZSZINTES
			for (int sor = 0; sor < 3; sor++)
			{
				for (int oszlop = 0; oszlop < 3; oszlop++)
				{
					if (kis_tabla[sor][oszlop] == JATEKOS_KETTO) {
						ketto_x++;
					}
					if (ketto_x == 2) {
						vizszintes = true;
						melyik_sor = sor;
					}
				}
				if (vizszintes)
					break;
				ketto_x = 0;
			}

			if (melyik_sor >= 0) {
				for (int oszlop = 0; oszlop < 3; oszlop++)
				{
					if (kis_tabla[melyik_sor][oszlop] != JATEKOS_KETTO) {
						mezo_szam = kis_tabla[melyik_sor][oszlop] - '0';
					}
				}

				if (TablaCheck(mezo_szam)) {
					tudott_rakni = true;

					gep_utolso_lepes = mezo_szam;

					KisTablaTarol(mezo_szam);

					TablaSzerkeszt(mezo_szam);
					return;
				}
			}

			//FUGGOLEGES
			ketto_x = 0;
			for (int oszlop = 0; oszlop < 3; oszlop++)
			{
				for (int sor = 0; sor < 3; sor++)
				{
					if (kis_tabla[sor][oszlop] == JATEKOS_KETTO) {
						ketto_x++;
					}
					if (ketto_x == 2) {
						fuggoleges = true;
						melyik_oszlop = oszlop;
					}
				}
				if (fuggoleges)
					break;
				ketto_x = 0;
			}

			if (melyik_oszlop >= 0) {
				for (int sor = 0; sor < 3; sor++)
				{
					if (kis_tabla[sor][melyik_oszlop] != JATEKOS_KETTO) {
						mezo_szam = kis_tabla[sor][melyik_oszlop] - '0';
					}
				}

				if (TablaCheck(mezo_szam)) {
					tudott_rakni = true;

					gep_utolso_lepes = mezo_szam;

					KisTablaTarol(mezo_szam);

					TablaSzerkeszt(mezo_szam);
					return;
				}
			}

			//ATLO BALFELUL -> JOBB ALUL
			ketto_x = 0;
			for (int sor = 0; sor < 3; sor++)
			{
				for (int oszlop = 0; oszlop < 3; oszlop++)
				{
					if (sor == oszlop) {
						if (kis_tabla[sor][oszlop] == JATEKOS_KETTO) {
							ketto_x++;
						}
						if (ketto_x == 2) {
							atlo1 = true;
							//ha megvan a 2, akkor mégegyszer végigmegy
							for (int sor = 0; sor < 3; sor++)
							{
								for (int oszlop = 0; oszlop < 3; oszlop++)
								{
									if (sor == oszlop) {
										if (kis_tabla[sor][oszlop] != JATEKOS_KETTO) {
											mezo_szam = kis_tabla[sor][oszlop] - '0';
										}

										if (TablaCheck(mezo_szam)) {
											tudott_rakni = true;

											gep_utolso_lepes = mezo_szam;

											KisTablaTarol(mezo_szam);

											TablaSzerkeszt(mezo_szam);
											return;
										}
									}
								}
							}
						}
					}
				}
			}
			//ATLO BALALUL -> JOBB FELUL
			ketto_x = 0;
			for (int sor = 0; sor < 3; sor++)
			{
				for (int oszlop = 0; oszlop < 3; oszlop++)
				{
					if (3 - 1 - sor == oszlop) {
						if (kis_tabla[sor][oszlop] == JATEKOS_KETTO) {
							ketto_x++;
						}
						if (ketto_x == 2) {
							//ha megvan a 2, akkor mégegyszer végigmegy
							for (int sor = 0; sor < 3; sor++)
							{
								for (int oszlop = 0; oszlop < 3; oszlop++)
								{
									if (3 - 1 - sor == oszlop) {
										if (kis_tabla[sor][oszlop] != JATEKOS_KETTO) {
											mezo_szam = kis_tabla[sor][oszlop] - '0';
										}

										if (TablaCheck(mezo_szam)) {
											tudott_rakni = true;

											gep_utolso_lepes = mezo_szam;

											KisTablaTarol(mezo_szam);

											TablaSzerkeszt(mezo_szam);
											return;
										}
									}
								}
							}
						}
					}
				}
			}
			ketto_x = 0;
#pragma endregion

#pragma region HA AZ EGYES JATEKOS NYERNE
			if (nehezsegi_szint >= 3) {
				//VIZSZINTES
				for (int sor = 0; sor < 3; sor++)
				{
					for (int oszlop = 0; oszlop < 3; oszlop++)
					{
						if (kis_tabla[sor][oszlop] == JATEKOS_EGY) {
							ketto_x++;
						}
						if (ketto_x == 2) {
							vizszintes = true;
							melyik_sor = sor;
						}
					}
					if (vizszintes)
						break;
					ketto_x = 0;
				}

				if (melyik_sor >= 0) {
					for (int oszlop = 0; oszlop < 3; oszlop++)
					{
						if (kis_tabla[melyik_sor][oszlop] != JATEKOS_EGY) {
							mezo_szam = kis_tabla[melyik_sor][oszlop] - '0';
						}
					}

					if (TablaCheck(mezo_szam)) {
						tudott_rakni = true;

						gep_utolso_lepes = mezo_szam;

						KisTablaTarol(mezo_szam);

						TablaSzerkeszt(mezo_szam);
						return;
					}
				}

				//FUGGOLEGES
				ketto_x = 0;
				for (int oszlop = 0; oszlop < 3; oszlop++)
				{
					for (int sor = 0; sor < 3; sor++)
					{
						if (kis_tabla[sor][oszlop] == JATEKOS_EGY) {
							ketto_x++;
						}
						if (ketto_x == 2) {
							fuggoleges = true;
							melyik_oszlop = oszlop;
						}
					}
					if (fuggoleges)
						break;
					ketto_x = 0;
				}

				if (melyik_oszlop >= 0) {
					for (int sor = 0; sor < 3; sor++)
					{
						if (kis_tabla[sor][melyik_oszlop] != JATEKOS_EGY) {
							mezo_szam = kis_tabla[sor][melyik_oszlop] - '0';
						}
					}

					if (TablaCheck(mezo_szam)) {
						tudott_rakni = true;

						gep_utolso_lepes = mezo_szam;

						KisTablaTarol(mezo_szam);

						TablaSzerkeszt(mezo_szam);
						return;
					}
				}

				//ATLO BALFELUL -> JOBB ALUL
				ketto_x = 0;
				for (int sor = 0; sor < 3; sor++)
				{
					for (int oszlop = 0; oszlop < 3; oszlop++)
					{
						if (sor == oszlop) {
							if (kis_tabla[sor][oszlop] == JATEKOS_EGY) {
								ketto_x++;
							}
							if (ketto_x == 2) {
								atlo1 = true;
								//ha megvan a 2, akkor mégegyszer végigmegy
								for (int sor = 0; sor < 3; sor++)
								{
									for (int oszlop = 0; oszlop < 3; oszlop++)
									{
										if (sor == oszlop) {
											if (kis_tabla[sor][oszlop] != JATEKOS_EGY) {
												mezo_szam = kis_tabla[sor][oszlop] - '0';
											}

											if (TablaCheck(mezo_szam)) {
												tudott_rakni = true;

												gep_utolso_lepes = mezo_szam;

												KisTablaTarol(mezo_szam);

												TablaSzerkeszt(mezo_szam);
												return;
											}
										}
									}
								}
							}
						}
					}
				}

				//ATLO BALALUL -> JOBB FELUL
				ketto_x = 0;
				for (int sor = 0; sor < 3; sor++)
				{
					for (int oszlop = 0; oszlop < 3; oszlop++)
					{
						if (3 - 1 - sor == oszlop) {
							if (kis_tabla[sor][oszlop] == JATEKOS_EGY) {
								ketto_x++;
							}
							if (ketto_x == 2) {
								//ha megvan a 2, akkor mégegyszer végigmegy
								for (int sor = 0; sor < 3; sor++)
								{
									for (int oszlop = 0; oszlop < 3; oszlop++)
									{
										if (3 - 1 - sor == oszlop) {
											if (kis_tabla[sor][oszlop] != JATEKOS_EGY) {
												mezo_szam = kis_tabla[sor][oszlop] - '0';
											}

											if (TablaCheck(mezo_szam)) {
												tudott_rakni = true;

												gep_utolso_lepes = mezo_szam;

												KisTablaTarol(mezo_szam);

												TablaSzerkeszt(mezo_szam);
												return;
											}
										}
									}
								}
							}
						}
					}
				}
				ketto_x = 0;
			}
#pragma endregion

			if (!tudott_rakni) {
				if (nehezsegi_szint == 4) {
					GepLepesMelle();
				}
				else if (nehezsegi_szint <= 3) {
					GepLepesRandom();
				}
			}
		}

	}
}

int LepesBekerese() {
	lepesek_szama++;
	bool mehet_tovabb = false;
	char bekert_karakter;
	int szam;

	SetConsoleTextAttribute(szinezes, alap_szin);

	cout << endl << endl << "\t" << melyik_jatekos << ". jatekos kovetkezik!" << endl;

	if (melyik_jatekos == 1) {
		SetConsoleTextAttribute(szinezes, jatekos_egy_szin);
		cout << "\t" << "Karaktere: " << JATEKOS_EGY << endl;
		if (jatekmod == 3) {
			GepLepes();
			return NULL;
		}
	}
	if (melyik_jatekos == 2) {
		SetConsoleTextAttribute(szinezes, jatekos_ketto_szin);
		cout << "\t" << "Karaktere: " << JATEKOS_KETTO << endl;
		if (jatekmod == 2 || jatekmod == 3) {
			GepLepes();
			return NULL;
		}
	}

	SetConsoleTextAttribute(szinezes, alap_szin);

	do {
		cout << "\t" << "Melyik mezore szeretnel lepni? ";
		cin >> bekert_karakter;

		if (bekert_karakter == 'm') {
			Menu();
		}
		else if (bekert_karakter == 'b') {
			BeallitasokUI();
		}
		else if (bekert_karakter == 'r') {
			JatekMehet();
		}
		else if (bekert_karakter == 'k') {
			Kilepes();
		}
		else {
			szam = bekert_karakter - '0';
			if (TablaCheck(szam)) {
				if (melyik_jatekos == 1) {
					jatekos_egy_lepes_szam++;
				}
				else if (melyik_jatekos == 2) {
					jatekos_ketto_lepes_szam++;
				}

				mehet_tovabb = true;
			}
		}
	} while (!mehet_tovabb);

	return szam;
}

bool TablaCheck(int szam) {
	if (szam <= 0 || szam > 9)
		return false;
	for (int sor = 0; sor < magassag; sor++)
	{
		for (int oszlop = 0; oszlop < szelesseg; oszlop++)
		{
			if (tabla[sor][oszlop] == szam + '0') {
				return true;
			}
		}
	}
	return false;
}

void KisTablaInit() {
	int index = 1;
	for (int sor = 0; sor < 3; sor++)
	{
		for (int oszlop = 0; oszlop < 3; oszlop++)
		{
			kis_tabla[sor][oszlop] = index + '0';
			index++;
		}
	}
}

void TablaInit() {
	for (int sor = 0; sor < magassag; sor++)
	{
		for (int oszlop = 0; oszlop < szelesseg; oszlop++)
		{
			//SRAKOK
			if (oszlop == 12 && sor == 12) {
				tabla[sor][oszlop] = (char)217;
			}
			else if (oszlop == 0 && sor == 12) {
				tabla[sor][oszlop] = (char)192;
			}
			else if (oszlop == 12 && sor == 0) {
				tabla[sor][oszlop] = (char)191;
			}
			else if (oszlop == 0 && sor == 0) {
				tabla[sor][oszlop] = (char)218;
			}

			//SZELEK KOZEPE
			//bal
			else if (oszlop == 0 && sor == 4) {
				tabla[sor][oszlop] = (char)195;
			}
			else if (oszlop == 0 && sor == 8) {
				tabla[sor][oszlop] = (char)195;
			}
			//teteje
			else if (oszlop == 4 && sor == 0) {
				tabla[sor][oszlop] = (char)194;
			}
			else if (oszlop == 8 && sor == 0) {
				tabla[sor][oszlop] = (char)194;
			}
			//lent
			else if (oszlop == 4 && sor == 12) {
				tabla[sor][oszlop] = (char)193;
			}
			else if (oszlop == 8 && sor == 12) {
				tabla[sor][oszlop] = (char)193;
			}
			//jobb
			else if (oszlop == 12 && sor == 4) {
				tabla[sor][oszlop] = (char)180;
			}
			else if (oszlop == 12 && sor == 8) {
				tabla[sor][oszlop] = (char)180;
			}

			else if (oszlop == 4 && sor == 4) {
				tabla[sor][oszlop] = (char)197;
			}
			else if (oszlop == 4 && sor == 8) {
				tabla[sor][oszlop] = (char)197;
			}
			else if (oszlop == 8 && sor == 4) {
				tabla[sor][oszlop] = (char)197;
			}
			else if (oszlop == 8 && sor == 8) {
				tabla[sor][oszlop] = (char)197;
			}

			else if (sor % 4 == 0)
				tabla[sor][oszlop] = (char)196;
			else if (oszlop % 4 == 0) {
				tabla[sor][oszlop] = (char)179;
			}



			else if (oszlop == 2 && sor == 2) {
				tabla[sor][oszlop] = '1';
			}
			else if (oszlop == 6 && sor == 2) {
				tabla[sor][oszlop] = '2';
			}
			else if (oszlop == 10 && sor == 2) {
				tabla[sor][oszlop] = '3';
			}

			else if (oszlop == 2 && sor == 6) {
				tabla[sor][oszlop] = '4';
			}
			else if (oszlop == 6 && sor == 6) {
				tabla[sor][oszlop] = '5';
			}
			else if (oszlop == 10 && sor == 6) {
				tabla[sor][oszlop] = '6';
			}

			else if (oszlop == 2 && sor == 10) {
				tabla[sor][oszlop] = '7';
			}
			else if (oszlop == 6 && sor == 10) {
				tabla[sor][oszlop] = '8';
			}
			else if (oszlop == 10 && sor == 10) {
				tabla[sor][oszlop] = '9';
			}

			else {
				tabla[sor][oszlop] = ' ';
			}
		}
	}
}

void TablaSzerkeszt(int szam) {
	for (int sor = 0; sor < magassag; sor++)
	{
		for (int oszlop = 0; oszlop < szelesseg; oszlop++)
		{
			if (tabla[sor][oszlop] == szam + '0') {

				//ELSO JATEKOS
				if (melyik_jatekos == 1) {
					tabla[sor - 1][oszlop - 1] = JATEKOS_EGY;
					tabla[sor][oszlop - 1] = ' ';
					tabla[sor + 1][oszlop - 1] = JATEKOS_EGY;

					tabla[sor - 1][oszlop] = ' ';
					tabla[sor][oszlop] = JATEKOS_EGY;
					tabla[sor + 1][oszlop] = ' ';

					tabla[sor - 1][oszlop + 1] = JATEKOS_EGY;
					tabla[sor][oszlop + 1] = ' ';
					tabla[sor + 1][oszlop + 1] = JATEKOS_EGY;
				}

				//MASODIK JATEKOS
				if (melyik_jatekos == 2) {
					tabla[sor - 1][oszlop - 1] = ' ';
					tabla[sor][oszlop - 1] = JATEKOS_KETTO;
					tabla[sor + 1][oszlop - 1] = ' ';

					tabla[sor - 1][oszlop] = JATEKOS_KETTO;
					tabla[sor][oszlop] = ' ';
					tabla[sor + 1][oszlop] = JATEKOS_KETTO;

					tabla[sor - 1][oszlop + 1] = ' ';
					tabla[sor][oszlop + 1] = JATEKOS_KETTO;
					tabla[sor + 1][oszlop + 1] = ' ';
				}
			}
		}
	}
	TablaRajzol();
}

void TablaRajzol() {
	system("cls");

	Cim();

	for (int sor = 0; sor < magassag; sor++)
	{
		cout << "\t" << char(186);

		//bal oldalon egy alahuzas fuggoleges vonal
		SetConsoleTextAttribute(szinezes, beallitasok_szin);
		cout << char(186) << "\t";

		SetConsoleTextAttribute(szinezes, alap_szin);

		for (int oszlop = 0; oszlop < szelesseg; oszlop++)
		{
			if (tabla[sor][oszlop] == JATEKOS_EGY) {
				SetConsoleTextAttribute(szinezes, jatekos_egy_szin);
			}
			if (tabla[sor][oszlop] == JATEKOS_KETTO) {
				SetConsoleTextAttribute(szinezes, jatekos_ketto_szin);
			}
			if (tabla[sor][oszlop] == '1' || tabla[sor][oszlop] == '2' || tabla[sor][oszlop] == '3' || tabla[sor][oszlop] == '4' || tabla[sor][oszlop] == '5' || tabla[sor][oszlop] == '6' || tabla[sor][oszlop] == '7' || tabla[sor][oszlop] == '8' || tabla[sor][oszlop] == '9') {
				SetConsoleTextAttribute(szinezes, szamok_szin);
			}
			cout << tabla[sor][oszlop];

			SetConsoleTextAttribute(szinezes, alap_szin);
		}

#pragma region UI
		//jobb oldalon egy alahuzas fuggoleges vonal
		SetConsoleTextAttribute(szinezes, beallitasok_szin);
		cout << "\t   " << char(186);

		SetConsoleTextAttribute(szinezes, border_szin);
		cout << char(186);

		//PONTSZAMOK KIIRASA
		if (sor == 1) {
			SetConsoleTextAttribute(szinezes, jatekos_egy_szin);
			cout << "\tJATEKOS EGY PONTSZAMA: ";

			SetConsoleTextAttribute(szinezes, cim_szin);
			cout << jatekos_egy_pontszam;
		}
		if (sor == 2) {
			SetConsoleTextAttribute(szinezes, jatekos_ketto_szin);
			cout << "\tJATEKOS KETTO PONTSZAMA: ";

			SetConsoleTextAttribute(szinezes, cim_szin);
			cout << jatekos_ketto_pontszam;
		}

		//LEPESEK KIIRASA
		if (sor == 4) {
			SetConsoleTextAttribute(szinezes, border_szin);
			cout << "\tjatekos egy lepesszama: ";

			SetConsoleTextAttribute(szinezes, jatekos_egy_szin);
			cout << jatekos_egy_lepes_szam;
		}
		if (sor == 5) {
			SetConsoleTextAttribute(szinezes, border_szin);
			cout << "\tjatekos ketto lepesszama: ";

			SetConsoleTextAttribute(szinezes, jatekos_ketto_szin);
			cout << jatekos_ketto_lepes_szam;
		}

		if (sor == 7) {
			//NEHEZSEGI SZINT
			if (jatekmod == 2 || jatekmod == 3) {
				SetConsoleTextAttribute(szinezes, jatekmod_allapota_szin);
				cout << "\tNehezsegi szint: ";
				switch (nehezsegi_szint)
				{
				case konnyu:
					SetConsoleTextAttribute(szinezes, konnyu_szin);
					cout << "KONNYU";
					break;
				case kozepes:
					SetConsoleTextAttribute(szinezes, kozepes_szin);
					cout << "KOZEPES";
					break;
				case nehez:
					SetConsoleTextAttribute(szinezes, nehez_szin);
					cout << "NEHEZ";
					break;
				case expert:
					SetConsoleTextAttribute(szinezes, expert_szin);
					cout << "EXPERT";
					break;
				}
			}

		}

		//MENU
		SetConsoleTextAttribute(szinezes, border_szin);
		if (sor == 9) {
			cout << "\tMenu 'm'";
		}
		if (sor == 10) {
			cout << "\tBeallitasok 'b'";
		}
		if (sor == 11) {
			cout << "\tUjrainditas 'r'";
		}
		if (sor == 12) {
			cout << "\tKilepes 'k'";
		}

		cout << endl;
	}

	cout << "\t" << char(186);

	SetConsoleTextAttribute(szinezes, beallitasok_szin);
	cout << char(200);
	for (int i = 0; i < 25; i++)
	{
		cout << char(205);
	}
	cout << char(188);

	SetConsoleTextAttribute(szinezes, border_szin);
	cout << char(186);
	cout << endl;

	cout << "\t" << char(200);
	for (int i = 0; i < 27; i++)
	{
		cout << char(205);
	}
	cout << char(188);
#pragma endregion

	if (!jatek_vege) {
		Vizsgal();

		if (!jatek_eleje) {
			if (melyik_jatekos == 1) {
				melyik_jatekos = 2;
			}
			else if (melyik_jatekos == 2) {
				melyik_jatekos = 1;
			}
		}
		jatek_eleje = false;

		//UJRA BEKERI A SZAMOT A KOVETKEZO JATEKOSTOL
		int szam = LepesBekerese();
		if (TablaCheck(szam)) {

			if (melyik_jatekos == 1) {
				//kis_tabla[szam - 1] = JATEKOS_EGY;
				for (int sor = 0; sor < 3; sor++)
				{
					for (int oszlop = 0; oszlop < 3; oszlop++)
					{
						if (kis_tabla[sor][oszlop] == szam + '0') {
							kis_tabla[sor][oszlop] = JATEKOS_EGY;
						}
					}
				}
			}

			TablaSzerkeszt(szam);
		}
	}
}
