#include <iostream>
#include <string>
#include <iomanip>
#include <Windows.h>
#include <fstream>

using namespace std;

enum Specialnist { Kn, In, Me, PhI, Tn };
enum Kurs { I = 1, II, III, IV, V, VI };
string specialnistStr[]{ "����'����� �����", "�����������" ,  "���������� �� ��������" , "Գ���� �� �����������" , "������� ��������" };

struct Student
{
	string prizv;
	Kurs kurs;
	Specialnist specialnist;
	int physichs;
	int Math;
	union
	{
		int programming;
		int chusel_methods;
		int pedagog;
	};
};

void StudentInfo(Student& student);
void CreateBIN(const Student& student, char* filename);
void PrintBIN(char* filename);
void PrizvAndMarks(char* filename);

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	
	char fname[100];
	cout << "������ ����� �����: "; cin >> fname;

	int c;
	cout << "Enter number of students: "; cin >> c;

	// ���������� ����� ��� ��������
	Student student;
	for (int i = 0; i < c; i++) {
		StudentInfo(student);

		// ����� ����� ��� �������� � ������� ����
		CreateBIN(student, fname);
	}
	PrintBIN(fname);
	PrizvAndMarks(fname);
	
	return 0;

}

void StudentInfo(Student& student)
{
	int specialnist, kurs;

	cin.get();
	cin.sync();

	cout << "�������: ";
	getline(cin, student.prizv);

	cout << "���� (1-6): ";
	cin >> kurs;
	student.kurs = (Kurs)kurs;
	cin.ignore();

	cout << "������ � ������: ";
	cin >> student.physichs;

	cout << "������ � ����������: ";
	cin >> student.Math;

	cout << "������������ (0 - ����'����� �����, 1 - �����������, 2 - ���������� �� ��������, 3 - Գ���� �� �����������, 4 - ������� ��������): ";
	cin >> specialnist;
	student.specialnist = (Specialnist)specialnist;

	switch (student.specialnist)
	{
	case Kn:
		cout << "������ � �������������: ";
		cin >> student.programming;
		break;
	case In:
		cout << "������ � ��������� ������: ";
		cin >> student.chusel_methods;
		break;
	case Me:
	case PhI:
	case Tn:
		cout << "������ � ���������: ";
		cin >> student.pedagog;
		break;
	}
	cout << endl;
}

void CreateBIN(const Student& student, char* filename)
{
	ofstream out(filename, ios::app | ios::binary);

	out.write((char*)&student, sizeof(student));

	out.close();

}

void PrintBIN(char* filename)
{
	ifstream fin(filename, ios::in | ios::binary);

	if (!fin) {
		cout << "������� ������� �����!" << endl;
		return;
	}

	cout << "==========================================================================================================================="<< endl;
	cout << "| � | �������    | ���� |      ������������      | Գ���� | ���������� |  �������������  | ������� ������ | ��������� |"<< endl;
	cout << "---------------------------------------------------------------------------------------------------------------------------"<< endl;


	Student student;
	int i = 1;
	while (fin.read((char*)&student, sizeof(student)))
	{
		cout << "| " << setw(1) << right << i  << " ";
		cout << "| " << setw(12) << left << student.prizv
			<< "| " << setw(4) << right << student.kurs << " "
			<< "| " << setw(24) << left << specialnistStr[student.specialnist]
			<< "| " << setw(7) << right << student.physichs
			<< "| " << setw(11) << right << student.Math;

		switch (student.specialnist)
		{
		case Kn:
			cout << "| " << setw(15) << student.programming << right << " | " << setw(18) << " | " << setw(12) << " |" << endl;
			break;
		case In:
			cout << "| " << setw(18) << " | " << setw(15) << student.chusel_methods << right << " | " << setw(12) << " |" << endl;
			break;
		case Me:
		case PhI:
		case Tn:
			cout << "| " << setw(18) << " | " << setw(18) << " | " << setw(10) << student.pedagog << right << " |" << endl;
			break;
		}

		i++;
	}
	cout << "===========================================================================================================================" << endl;
	cout << endl;

	fin.close();
	return;
}

void PrizvAndMarks(char* filename)
{
	ifstream fin(filename, ios::in | ios::binary);
	Student student;

	if (!fin) {
		cout << "������� ������� �����!" << endl;
		return;
	}

	int math = 0, ph = 0, programming = 0, chusel_methods = 0, pedagog = 0;

	cout << "������� ��������, �� �������� � � ������ � � ���������� ������ �5� ��� �4� :" << endl;

	while (fin.read((char*)&student, sizeof(student))) 
	{
		if ((student.physichs == 5 || student.physichs == 4) && (student.Math == 5 || student.Math == 4)) 
		{
			cout << student.prizv << endl;
		}
		if (student.Math == 3)
		{
			math++;
		}
		if (student.physichs == 3)
		{
			ph++;
		}
		if (student.specialnist == Kn && student.programming == 3)
		{
			programming++;
		}
		if (student.specialnist == In && student.chusel_methods == 3)
		{
			chusel_methods++;
		}
		if ((student.specialnist == Me || student.specialnist == PhI || student.specialnist == Tn) && student.pedagog == 3)
		{
			pedagog++;
		}
	}
	fin.close();

	cout << endl;
	cout << "������ \"���������\" � ����������: " << math << endl;
	cout << "������ \"���������\" � ������: " << ph << endl;
	cout << "������ \"���������\" � �������������: " << programming << endl;
	cout << "������ \"���������\" � ��������� ������: " << chusel_methods << endl;
	cout << "������ \"���������\" � ���������: " << pedagog << endl;
}
