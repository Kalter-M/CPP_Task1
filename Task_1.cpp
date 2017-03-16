//11B ��������� ���� ���������� 
//11. ��������� ��� ����� �� �������� ������������� �� �����. 
//B) ������������ ������� (std::deque)

#include "stdafx.h"
#include <string>
#include <iostream>
#include <fstream>
#include <deque>        // ���������� ������������ ���� �����
#include <iterator>     // ��������� ����������
#include <vector>
#include <algorithm>
#include <functional>
#include "Task_1.h"

//������
//������� ��������������
template <typename T>
struct TransformNumber
	: public std::binary_function<double, T, T>
{
	double operator()(int input, int max)
	{
		return (double)input / (double)max * 2;
	}
};

//�������� ����� ����� �� ������������
bool CorrectFileName(std::string s)
{
	int i = 0;
	int j;
	char cor[] = "\\/:?*<>|";
	int len = s.length();
	while (i < len)
	{
		j = 0;
		while (j < 9)
		{
			if (s[i] != cor[j])
				j++;
			else
				return false;
		}
		i++;
	}
	return true;
}

//����� ������������� ����� � ����
int MaxNumber(std::deque<int> dec)
{
	if (dec.size() == 0) throw std::string("��� ������!");
	int max = dec[0];
	
	for (std::deque<int>::iterator it = dec.begin(); it != dec.end(); it++)
	{
		if (*it > max) max = *it;
	}
	if (max == 0) throw std::string("������� �� ���� ����������");
	return max;
}

//������� ��������������
//float TransformNumber(int input, int max)
//{
//	return input / max * 2;
//}

//��������� ����� �� ���������
int RandomNumber(int diapason)
{
	return -diapason + (rand() % (2 * diapason + 1));
}

//���������� ����� ������
bool FillTextFileCycle(std::string FileName,int amount, int diapason)
{
	if (!CorrectFileName(FileName))
	{
		std::cout << "������������ ��� �����(������������� �������� / \\ : * ? \" < > | ���������)" << std::endl;
		return false;

	}

	std::ofstream file(FileName);

	if (!file.is_open())
	{
		std::cout << "���������� ������� ����" << std::endl;
		return false;
	}
		
	for (int i = 0; i < amount; i++)
	{
		file << RandomNumber(diapason) << " ";
	}

	file.close();
	return true;
}

//���������� ����� std::generate
bool FillTextFileGenerate(std::string FileName, int amount, int diapason)
{
	if (!CorrectFileName(FileName))
	{
		std::cout << "������������ ��� �����(������������� �������� / \\ : * ? \" < > | ���������)" << std::endl;
		return false;

	}

	std::ofstream file(FileName);

	if (!file.is_open())
	{
		std::cout << "���������� ������� ����" << std::endl;
		return false;
	}

	std::vector<int> v(amount);

	std::generate(v.begin(), v.end(), [diapason]() -> int {return -diapason + (rand() % (2 * diapason + 1));});

	for (int elem : v)
	{
		file << elem << " ";
	}
	file.close();
	return true;
}

std::deque<int> ReadFromFile(std::string FileName)
{
	std::deque<int> dec;
	if (!CorrectFileName(FileName))
	{
		std::cout << "������������ ��� �����(������������� �������� / \\ : * ? \" < > | ���������)" << std::endl;
		return dec;

	}

	std::ifstream file(FileName);

	if (!file.is_open())
	{
		std::cout << "���������� ������� ����" << std::endl;
		return dec;
	}

	int buffer;

	while (file >> buffer)
		dec.push_back(buffer);

	file.close();

	return dec;
}

std::deque<double> Modify(std::deque<int> inputDec)
{
	int max;
	std::deque<double> outputDec;
	try
	{
		max = MaxNumber(inputDec);

		for (int elem : inputDec)
		{
			outputDec.push_back(TransformNumber<int>()(elem, max));
		}
	}
	catch (std::string err)
	{
		std::cout << err << std::endl;
	}

	return outputDec;
}

std::deque<double> Modify(std::deque<int>::iterator begin, std::deque<int>::iterator end)
{
	int max = *begin;

	for (std::deque<int>::iterator it = begin; it != end ; it++)
	{
		if (*it > max) max = *it;
	}

	std::deque<double> outputDec;

	for (std::deque<int>::iterator it = begin; it != end; it++)
	{
		outputDec.push_back(TransformNumber<int>()(*it, max));
	}
	return outputDec;
}

std::deque<double> ModifyTransform(std::deque<int> inputDec)
{
	int max;
	std::deque<double> outputDec;
	try
	{
		max = MaxNumber(inputDec);

		outputDec.resize(inputDec.size());

		// Transform number, possibly 
		std::transform(inputDec.begin(), inputDec.end(), outputDec.begin(), [max](int num) -> double {return TransformNumber<int>()(num, max);});
	}
	catch (std::string err)
	{
		std::cout << err << std::endl;
	}

	return outputDec;
}


std::deque<double> ModifyForEach(std::deque<int> inputDec)
{
	int max;
	std::deque<double> outputDec;

	try
	{
		max = MaxNumber(inputDec);

		for (std::deque<int>::iterator it = inputDec.begin(); it != inputDec.end(); it++)
		{
			outputDec.push_back((double)*it);
		}

		// TransformNumber
		std::for_each(outputDec.begin(), outputDec.end(), [max](double &num) -> void {num = TransformNumber<double>()(num, max);});
		
	}
	catch (std::string err)
	{
		std::cout << err << std::endl;
	}

	return outputDec;
}

int SumDeque(std::deque<int> inputDec)
{
	int result = 0;

	for (int elem : inputDec)
	{
		result += elem;
	}
	return result;
}

double AverageDeque(std::deque<int> inputDec)
{
	return (double)SumDeque(inputDec) / inputDec.size();
}

//������ ������
template <typename T>
void PrintResult(std::deque<T> inputDec)
{
	for ( T elem : inputDec)
	{
		std::cout << elem << " ";
	}
	std::cout << std::endl;
}

template <typename T>
bool SaveToFile(std::string FileName, std::deque<T> inputDec)
{
	if (!CorrectFileName(FileName))
	{
		std::cout << "������������ ��� �����(������������� �������� / \\ : * ? \" < > | ���������)" << std::endl;
		return false;

	}

	std::ofstream file(FileName);

	if (!file.is_open())
	{
		std::cout << "���������� ������� ����" << std::endl;
		return false;
	}

	PrintResult(inputDec);

	file.close();
	return true;
}

int ShowMenu()
{
	int res = 0;
	while ((res < 1) || (res > 9))
	{
		std::cout << "1) ���������� �����" << std::endl;
		std::cout << "2) �������� �� �����" << std::endl;
		std::cout << "3) �������������� ����������" << std::endl;
		std::cout << "4) �������������� ���������� � �����������" << std::endl;
		std::cout << "5) �������������� std::transform" << std::endl;
		std::cout << "6) �������������� std::for_each" << std::endl;
		std::cout << "7) ����� � ������� ��������������" << std::endl;
		std::cout << "8) ����� ���������� � ����" << std::endl;
		std::cout << "9) �����" << std::endl;
		std::cin >> res;
	}
	return res;
}

int main()
{
	setlocale(LC_ALL, "rus");
	bool exit = false;
	int choice;
	std::deque<int> Deq;

	std::deque<double> OutDeq;
	std::string filename;
	int x, y;

	while (!exit)
	{
		choice = ShowMenu();
		switch (choice)
		{
		case 1:
			std::cout << "������� ��� �����\n";
			std::cin >> filename;
			std::cout << "������� ���������� � ��������\n";
			std::cin >> x >> y;
			FillTextFileCycle(filename, x, y);			
			break;
		case 2:
			std::cout << "������� ��� �����\n";
			std::cin >> filename;
			Deq = ReadFromFile(filename);
			PrintResult(Deq);
			break;
		case 3:
			OutDeq = Modify(Deq);
			PrintResult(OutDeq);
			break;
		case 4:
			OutDeq = Modify(Deq.begin(), Deq.end());
			PrintResult(OutDeq);
			break;
		case 5:
			OutDeq = ModifyTransform(Deq);
			PrintResult(OutDeq);
			break;
		case 6:
			OutDeq = ModifyForEach(Deq);
			PrintResult(OutDeq);
			break;
		case 7:
			PrintResult(Deq);
			std::cout << "�����:" << SumDeque(Deq) << std::endl;
			std::cout << "������� ��������������:" << AverageDeque(Deq) << std::endl;
			break;
		case 8:
			std::cout << "������� ��� �����\n";
			std::cin >> filename;
			SaveToFile(filename, OutDeq);
			break;
		case 9:
			exit = true;
			break;
		}
	}
	return 0;
}
