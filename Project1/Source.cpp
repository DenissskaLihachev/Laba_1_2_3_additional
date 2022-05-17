#include <iostream>
#include <Windows.h>
#include <stdio.h>
#include <conio.h>
#include <string>
#include <fstream>

using namespace std;

/*
Обеспечьте всю работу с файлами с помощью перенаправления стандартных потоков
функцией freopen_s().
Программа должна выполнять простую работу с массивом строк. При запуске
пользователю на выбор предоставляется несколько действий:
 Пользователь может добавить новую строку в массив.
 Пользователь может удалить строку из массива по номеру (порядок строк должен остаться тот же).
 Пользователь может вывести массив на экран.
 Пользователь может сохранить массив строк в файле.
 Пользователь может загрузить массив строк из файла.
*/

void main()
{
	setlocale(LC_ALL, "rus");
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);

	string* str = NULL;
	int size = 0;
	while (true)
	{
		std::cout << "1. Добавить"
				<< "\n2. Удалить"
				<< "\n3. Вывести"
				<< "\n4. Сохранить"
				<< "\n5. Загрузить\nВыбор: ";

		int choice;	std::cin >> choice;

		system("cls");
	
		switch (choice)
		{
			case (1):
			{
				std::cout << "Добавить строку\n";

				string inputStr; 

				std::cin.get();
				getline(std::cin, inputStr);	//вводим строку

				size++;	//увеличиваем размер

				if (str == NULL) str = new string[size];	//выделяем память под динамический массив
				else
				{
					string* temp = new string[size];	//выделяем память под динамический массив

					for (int i = 0; i < size - 1; i++)	//запись существующих строк в наш промежуточный массив
					{
						temp[i] = str[i];
					}

					delete[] str;	//освобождаем память

					str = new string[size];	//снова выделяем память

					for (int i = 0; i < size - 1; i++)	//перезаписываем в новый динамический массив
					{
						str[i] = temp[i];
					}

					delete[] temp;	//освободжаем память
				}
				str[size - 1] = inputStr;	//записываем введенную строку в конец
				system("cls");
				break;
			}

			case (2):
			{
				if (size == 0)
				{
					std::cout << "\nНечего удалять... ";
					char p = _getch();
					system("cls");
					break;
				}

				if (size == 1)
				{
					std::cout << "\nУдалёнa последняя строка... ";
					delete[] str;
					size = 0;
					char p = _getch();
					system("cls");
					break;
				}

				std::cout << "Удаление строки\n\nВыберете строку:\n";

				for (int i = 0; i < size; i++)	//выводим все строки для выбора
				{
					std::cout << i + 1 << ": " << str[i] << "\n";
				}

				int inI;
				std::cin >> inI;	//выбираем нужную строку

				inI -= 1;

				system("cls");

				size--;	//уменьшаем размер

				string* temp = new string[size];	//выделяем память под промежуточный массив

				for (int i = 0; i < inI; i++)
				{
					temp[i] = str[i];	//записываем в п.м. элемент, который хотим удалить
				}

				for (int i = inI; i < size; i++)
				{
					temp[i] = str[i + 1];	//записываем нужный элемент в конец массива
				}

				delete[] str;	//освобождаем память

				str = new string[size];	//выделяем память

				for (int i = 0; i < size; i++)	//записываем все эелементы кроме последнего
				{
					str[i] = temp[i];
				}

				delete[] temp;	//освобождаем память

				break;
			}

			case (3):
			{
				if (size == 0)
				{
					std::cout << "Нечего выводить... ";
					char p = _getch();
					system("cls");
					break;
				}
				std::cout << "Вывод\n\n";
				for (int i = 0; i < size; i++)
				{
					std::cout << str[i] << "\n";	//просто выод всего массива
				}
				_getch();
				system("cls");
				break;
			}

			case (4):
			{
				std::cout << endl << "Введите имя файла (.txt): ";
				char fileNameOut[100];
				std::cin >> fileNameOut;	//вводим имя файлы, в который сохраняем

				system("cls");

				if (size == 0)
				{
					std::cout << "\nНечего выводить... ";
					char p = _getch();
					system("cls");
					break;
				}

				FILE* file = nullptr;	//создаем указатель на файл

				freopen_s(&file, fileNameOut, "w", stdout);	//перенаправляем поток для записи

				for (int i = 0; i < size; i++)
				{
					std::cout << str[i] << endl;	//выводим все элементы массива не в консоль, а в сам файл
				}

				freopen_s(&file, "CON", "w", stdout);	//перенаправляем поток обратно в консоль

				std::cout << endl << "\nСохранено... ";
				char p = _getch();
				system("cls");

				break;
			}

			case (5):
			{
				std::cout << endl << "\nВведите имя файла (.txt): ";
				char fileNameIn[100];
				std::cin >> fileNameIn;	//снова вводим имя файла

				std::cout << "\nВведите количество строк: ";
				int s;
				std::cin >> s;	//вводим сколько строк нам нужно загрузить

				FILE* file = NULL;	//указатель на файл

				freopen_s(&file, fileNameIn, "r", stdin);	//перенаправляем поток для чтения

				if (file != NULL)
				{
					std::cout << "Файл откыт\n";
					for (int i = 0; i < s; i++)
					{
						size++;
						if (str == NULL) str = new string[size];	//выделяем память
						else
						{
							string* temp = new string[size];	//выделяем память

							for (int i = 0; i < size - 1; i++)
							{
								temp[i] = str[i];	//записываем нужные нам элементы
							}

							delete[] str;	//освобождаем память

							str = new string[size];

							for (int i = 0; i < size - 1; i++)
							{
								str[i] = temp[i];
							}

							delete[] temp;	//освобождаем память
						}
						getline(std::cin, str[size - 1]);	//записываем элемент из файла
						std::cout << "\nДобавлена строка: " << str[size - 1];
						_getch();
						system("cls");
					}
					std::cout << endl;
					freopen_s(&file, "CON", "r", stdin); //перенаправляем в консоль
				}
				else
				{
					std::cout << "Ошибка открытия!!!";
					freopen_s(&file, "CON", "r", stdin);
					char p = _getch();
					system("cls");
				}
				break;
			}
		}
	}
	_getch();
}
//final
