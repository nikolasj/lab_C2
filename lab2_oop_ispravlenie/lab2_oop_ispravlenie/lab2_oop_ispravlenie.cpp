#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <map>
#include <vector>

using namespace std;
class SuppBase
{
public:
	virtual int Get() = 0;
};
class SuppFile :public SuppBase
{
	FILE *fp;
public:
	SuppFile(char* filename)
	{
		fopen_s(&fp, filename, "r");
	}
	~SuppFile()
	{
		fclose(fp);
	}
	int Get()
	{
		int chislo = 0;
			while (fscanf_s(fp, "%i", &chislo))
			{			
				cout << chislo << endl;
				return chislo;
			}
		return -1;
	}
};
class SuppKbrd :public SuppBase
{
public:
	int Get()
	{
		int chislo = 0;
		cin >> chislo;
		return chislo;
	}

};
class Freq
{
protected:
	map<int, int> massiv;
	int n;
public:
	//friend ostream& operator << (ostream& out, Freq& a);
	void Calc(SuppBase* p)
	{
		int i = 0;
		int number;
		number = p->Get();
		do
		{
			if (number > 0)
			{
				massiv[number]++;
				i++;
			}
		} while (number > 0);
		n = i;		
	}
	map<int, int> GetArrayFreq()
	{
		return massiv;
	}
	int GetN()
	{
		return n;
	}
};
class Diap :public Freq
{
	int sum, min, max;
public:
	Diap()
	{
		sum = 0;
		min = 0;
		max = 0;
	}
	//friend ostream& operator << (ostream& out, Diap& a);
	void Calc(SuppBase*p)
	{
		Freq* t;
		int i = 0;
		int number;
		number = p->Get();
		min = number;
		max = number;
		while (number > 0)
		{
			sum +=number;
			if (number < min) min = number;
			if (number > max) max = number;
			number = p->Get();
			i++;
		}
	}
	int GetSum()
	{
		return sum;
	}
	int GetMin()
	{
		return min;
	}
	int GetMax()
	{
		return max;
	}
	//friend ostream& operator << (ostream& out, Freq& a);
};
ostream& operator << (ostream& out, Diap* a)//через friend-функцию сделать
{
	out << "Max=" << a->GetMax() << endl << "Min=" << a->GetMin() << endl << "Sum=" << a->GetSum() << endl;
	return out;
}
ostream& operator << (ostream& out, Freq* a)//через friend-функцию сделать
{
	map<int, int> array = a->GetArrayFreq();
	std::map<int, int>::iterator it = array.begin();
	for (it = array.begin(); it != array.end(); it++)
		out << (*it).first << " " << (*it).second << endl;
	return out;
}
int main()
{
	setlocale(LC_ALL, "rus");
	char l; int vvod; 
	SuppBase *p;
	SuppKbrd a;// если файл, то нужно чтобы вводил пользователь файл, так как будет конструктор же
	cout << "Введите 2 для ввода чисел с клавиатуры или 1 для чтения чисел из файла " << endl;
	cin >> vvod;
	if (vvod != 1)
		p = &a;
	else
	{
		SuppFile b("file.txt");
		p = &b;
	}
	Freq *freq = new Freq();
	cout << "Обрабатываем массив" << endl;
	freq->Calc(p);
	cout << freq << endl;
	if (vvod != 1)
	{
		cout << "Обрабатываем массив 2" << endl;
		Diap* diap = new Diap();
		diap->Calc(p);
		cout << diap << endl;
	}
	else
	{
		SuppFile c("file.txt");
		p = &c;
		cout << "Обрабатываем массив 2" << endl;
		Diap* diap = new Diap();
		diap->Calc(p);
		cout << diap << endl;
	}
	cin >> l;
	return 0;
}
//}
//using namespace std;
//class SuppBase
//{
//public:
//	virtual int Get() = 0;
//	//virtual void Close() = 0;
//};
//class SuppFile :public SuppBase
//{
//	FILE *fp;
//public:
//	SuppFile(char* filename)
//	{
//		fopen_s(&fp, filename, "r");
//	}//конструктор, здесь нужнооткрывать файл, проверки здесь делать
//	~SuppFile()
//	{
//		fclose(fp);
//	}
//	int Get()//диструктор, нужно закрывать файл
//	{
//		int chislo = 0;
//		//если открытие файла прошло корректно, то
//
//		while (fscanf_s(fp, "%i", &chislo))
//		{
//			//cout << chislo << endl;
//			return chislo;
//		}
//
//		return -1;
//	}
//	/*void Close()
//	{
//	fclose(fp);
//	}*/
//
//};
//class SuppKbrd :public SuppBase
//{
//public:
//	int Get()
//	{
//		int chislo = 0;
//		cin >> chislo;
//		return chislo;
//	}
//	/*void Close()
//	{
//
//	}*/
//};
//class Freq
//{
//protected:
//	map<int, int> massiv;
//	int n;
//public:
//	//friend ostream& operator << (ostream& out, Freq& a);
//	void Calc(SuppBase* p)// в цикле Get пока не отрицательное, но лучше конец церез Ctrl+Z
//	{
//		int i = 0;
//		int number;
//		do
//		{
//			number = p->Get();
//			if (number > 0)
//			{
//				massiv[number]++;
//				i++;
//			}
//		} while (number > 0);
//		n = i;
//		//p->Close();		
//	}
//	map<int, int> GetArrayFreq()
//	{
//		return massiv;
//	}
//	int GetN()
//	{
//		return n;
//	}
//};
//class Diap :public Freq
//{
//	int sum, min, max;
//public:
//	Diap()
//	{
//		sum = 0;
//		min = 0;
//		max = 0;
//	}
//	//friend ostream& operator << (ostream& out, Diap& a);
//	void Calc(SuppBase*p)
//	{
//		/* if (p->GetN() == 0)
//		cout « "Error";
//		else
//		{*/
//		Freq* t;
//
//		int i = 0;
//		int number;
//		number = p->Get();
//		min = number;
//		max = number;
//
//		while (number > 0)
//		{
//			sum += number;
//			if (number < min) min = number;
//			if (number > max) max = number;
//			number = p->Get();
//			i++;
//		}
//		//p->Close();
//	}
//	int GetSum()
//	{
//		return sum;
//	}
//	int GetMin()
//	{
//		return min;
//	}
//	int GetMax()
//	{
//		return max;
//	}
//	//friend ostream& operator << (ostream& out, Freq& a);
//};
//ostream& operator << (ostream& out, Diap* a)//через friend-функцию сделать
//{
//	out << "Max=" << a->GetMax() << endl << "Min=" << a->GetMin() << endl << "Sum=" << a->GetSum() << endl;
//	return out;
//}
//ostream& operator << (ostream& out, Freq* a)//через friend-функцию сделать
//{
//	map<int, int> array = a->GetArrayFreq();
//	std::map<int, int>::iterator it = array.begin();
//	for (it = array.begin(); it != array.end(); it++)
//		out << (*it).first << " " << (*it).second << endl;
//	return out;
//}
//int main()
//{
//	setlocale(LC_ALL, "rus");
//	char l; int vvod; string name2;
//	SuppBase *p;
//	SuppKbrd a;// если файл, то нужно чтобы вводил пользователь файл, так как будет конструктор же
//	cout << "Введите 2 для ввода чисел с клавиатуры или 1 для чтения чисел из файла " << endl;
//	cin >> vvod;
//	if (vvod != 1)
//		p = &a;
//	else
//	{
//		cout << "Введите имя файла" << endl;
//		cin >> name2;
//		char* name = new char[name2.length() + 1];
//		strcpy(name, name2.c_str());
//		SuppFile b(name);
//		p = &b;
//	}
//	Freq *freq = new Freq();
//	cout << "Обрабатываем массив" << endl;
//	freq->Calc(p);
//	cout << freq << endl;
//	if (vvod != 1)
//	{
//		cout << "Обрабатываем массив 2" << endl;
//		Diap* diap = new Diap();
//		diap->Calc(p);
//		cout << diap << endl;
//	}
//	else
//	{
//		SuppFile c("file.txt");
//		p = &c;
//		cout << "Обрабатываем массив 2" << endl;
//		Diap* diap = new Diap();
//		diap->Calc(p);
//		cout << diap << endl;
//	}
//	cin >> l;
//	return 0;
//}

//#include <iostream>
//#include <fstream>
//#include <iomanip>
//#include <stdlib.h>
//#include <stdio.h>
//#include <string>
//#include <map>
//#include <vector>
//
//using namespace std;
//class SuppBase
//{
//public:
//	virtual int Get() = 0;
//	//virtual void Close() = 0;
//};
//class SuppFile :public SuppBase
//{
//	FILE *fp;
//public:
//	SuppFile(char* filename)
//	{
//		fopen_s(&fp, filename, "r");
//	}//конструктор, здесь нужнооткрывать файл, проверки здесь делать
//	~SuppFile()
//	{
//		fclose(fp);
//	}
//	int Get()//диструктор, нужно закрывать файл
//	{
//		int chislo = 0;
//		//если открытие файла прошло корректно, то
//
//		while (fscanf_s(fp, "%i", &chislo))
//		{
//			//cout << chislo << endl;
//			return chislo;
//		}
//
//		return -1;
//	}
//	/*void Close()
//	{
//	fclose(fp);
//	}*/
//
//};
//class SuppKbrd :public SuppBase
//{
//public:
//	int Get()
//	{
//		int chislo = 0;
//		cin >> chislo;
//		return chislo;
//	}
//	/*void Close()
//	{
//
//	}*/
//};
//class Freq
//{
//protected:
//	map<int, int> massiv;
//	int n;
//public:
//	//friend ostream& operator << (ostream& out, Freq& a);
//	void Calc(SuppBase* p)// в цикле Get пока не отрицательное, но лучше конец церез Ctrl+Z
//	{
//		int i = 0;
//		int number;
//		do
//		{
//			number = p->Get();
//			if (number > 0)
//			{
//				massiv[number]++;
//				i++;
//			}
//		} while (number > 0);
//		n = i;
//		//p->Close();		
//	}
//	map<int, int> GetArrayFreq()
//	{
//		return massiv;
//	}
//	int GetN()
//	{
//		return n;
//	}
//};
//class Diap :public Freq
//{
//	int sum, min, max;
//public:
//	Diap()
//	{
//		sum = 0;
//		min = 0;
//		max = 0;
//	}
//	//friend ostream& operator << (ostream& out, Diap& a);
//	void Calc(SuppBase*p)
//	{
//		/* if (p->GetN() == 0)
//		cout « "Error";
//		else
//		{*/
//		Freq* t;
//
//		int i = 0;
//		int number;
//		number = p->Get();
//		min = number;
//		max = number;
//
//		while (number > 0)
//		{
//			sum += number;
//			if (number < min) min = number;
//			if (number > max) max = number;
//			number = p->Get();
//			i++;
//		}
//		//p->Close();
//	}
//	int GetSum()
//	{
//		return sum;
//	}
//	int GetMin()
//	{
//		return min;
//	}
//	int GetMax()
//	{
//		return max;
//	}
//	//friend ostream& operator << (ostream& out, Freq& a);
//};
//ostream& operator << (ostream& out, Diap* a)//через friend-функцию сделать
//{
//	out << "Max=" << a->GetMax() << endl << "Min=" << a->GetMin() << endl << "Sum=" << a->GetSum() << endl;
//	return out;
//}
//ostream& operator << (ostream& out, Freq* a)//через friend-функцию сделать
//{
//	map<int, int> array = a->GetArrayFreq();
//	std::map<int, int>::iterator it = array.begin();
//	for (it = array.begin(); it != array.end(); it++)
//		out << (*it).first << " " << (*it).second << endl;
//	return out;
//}
//int main()
//{
//	setlocale(LC_ALL, "rus");
//	char l; int vvod; string name2;
//	SuppBase *p;
//	SuppKbrd a;// если файл, то нужно чтобы вводил пользователь файл, так как будет конструктор же
//	cout << "Введите 2 для ввода чисел с клавиатуры или 1 для чтения чисел из файла " << endl;
//	cin >> vvod;
//	if (vvod != 1)
//		p = &a;
//	else
//	{
//		cout << "Введите имя файла" << endl;
//		cin >> name2;
//		char* name = new char[name2.length() + 1];
//		strcpy(name, name2.c_str());
//		SuppFile b(name);
//		p = &b;
//	}
//	Freq *freq = new Freq();
//	cout << "Обрабатываем массив" << endl;
//	freq->Calc(p);
//	cout << freq << endl;
//	if (vvod != 1)
//	{
//		cout << "Обрабатываем массив 2" << endl;
//		Diap* diap = new Diap();
//		diap->Calc(p);
//		cout << diap << endl;
//	}
//	else
//	{
//		SuppFile c("file.txt");
//		p = &c;
//		cout << "Обрабатываем массив 2" << endl;
//		Diap* diap = new Diap();
//		diap->Calc(p);
//		cout << diap << endl;
//	}
//	cin >> l;
//	return 0;
//}

///*
//#include <iostream>
//#include <fstream>
//#include <iomanip>
//#include <stdlib.h>
//#include <stdio.h>
//#include <string>
//#include <map>
//#include <vector>
//
//using namespace std;
//class SuppBase
//{
//public:
//virtual int Get() = 0;
//virtual void Close() = 0;
//};
//class SuppFile :public SuppBase
//{
//FILE *fp;
//public:
//SuppFile(char* filename)
//{
//fopen_s(&fp, filename, "r");
//}//конструктор, здесь нужнооткрывать файл, проверки здесь делать
//~SuppFile()
//{
//fclose(fp);
//}
//int Get()//диструктор, нужно закрывать файл
//{
//int chislo = 0;
////если открытие файла прошло корректно, то
//
//while (fscanf_s(fp, "%i", &chislo))
//{
//cout << chislo << endl;
//return chislo;
//}
//
//return -1;
//}
//void Close()
//{
//fclose(fp);
//}
//
//};
//class SuppKbrd :public SuppBase
//{
//public:
//int Get()
//{
//int chislo = 0;
//cin >> chislo;
//return chislo;
//}
//void Close()
//{
//
//}
//};
//class Freq
//{
//protected:
//map<int, int> massiv;
//int n;
//public:
//void Calc(SuppBase* p)// в цикле Get пока не отрицательное, но лучше конец церез Ctrl+Z
//{
//int i = 0;
//int number;
//do
//{
//number = p->Get();
//if (number > 0)
//{
//massiv[number]++;
//i++;
//}
//} while (number > 0);
//n = i;
//p->Close();
//}
//map<int, int> GetArrayFreq()
//{
//return massiv;
//}
//int GetN()
//{
//return n;
//}
//};
//class Diap :public Freq
//{
//int sum, min, max;
//public:
//Diap()
//{
//sum = 0;
//min = 0;
//max = 0;
//}
//void Calc(SuppBase*p)
//{
///* if (p->GetN() == 0)
//cout « "Error";
//else
//{*/
//Freq* t;
//
//int i = 0;
//int number;
//number = p->Get();
//min = number;
//max = number;
//
//while (number > 0)
//{
//	sum += sum + number;
//	if (number < min) min = number;
//	if (number > max) max = number;
//	number = p->Get();
//	i++;
//}
//p->Close();
//	}
//	int GetSum()
//	{
//		return sum;
//	}
//	int GetMin()
//	{
//		return min;
//	}
//	int GetMax()
//	{
//		return max;
//	}
//};
//ostream& operator << (ostream& out, Diap* a)//через friend-функцию сделать
//{
//	out << "Max=" << a->GetMax() << endl << "Min=" << a->GetMin() << endl << "Sum=" << a->GetSum() << endl;
//	return out;
//}
//ostream& operator << (ostream& out, Freq* a)//через friend-функцию сделать
//{
//	map<int, int> array = a->GetArrayFreq();
//	std::map<int, int>::iterator it = array.begin();
//	for (it = array.begin(); it != array.end(); it++)
//		out << (*it).first << " " << (*it).second << endl;
//	return out;
//}
//int main()
//{
//	setlocale(LC_ALL, "rus");
//	char l; int vvod; string name;
//	SuppBase *p;
//	SuppKbrd a;// если файл, то нужно чтобы вводил пользователь файл, так как будет конструктор же
//
//	SuppFile b("file.txt");
//	cout << "Введите 2 для ввода чисел с клавиатуры или 1 для чтения чисел из файла " << endl;
//	cin >> vvod;
//	if (vvod != 1)
//		p = &a;
//	else
//		p = &b;
//
//	Freq *freq = new Freq();
//	cout << "Обрабатываем массив" << endl;
//	freq->Calc(p);
//	cout << freq << endl;
//
//	SuppFile c("file.txt");
//	p = &c;
//	cout << "Обрабатываем массив 2" << endl;
//	Diap* diap = new Diap();
//	diap->Calc(p);
//	cout << diap << endl;
//
//	cin >> l;
//	return 0;
//}
//
//*/