#include <iomanip>
#include <iostream>
#include <ctime>
#include <chrono> 

using namespace std;

//void showArr(int arr[], int arrSize);//Печать
void SelectionSort(int arr[], int size);//Выбором
void FastSort(int* arr, int size, int& sravn, int& peres);//Быстрая
class Timer
{
private:
	using clock_t = chrono::high_resolution_clock;
	using milliseconds = chrono::duration<double, ratio<1> >;

	chrono::time_point<clock_t> m_beg;

public:
	Timer() : m_beg(clock_t::now())
	{
	}

	void reset()
	{
		m_beg = clock_t::now();
	}

	double elapsed() const
	{
		return chrono::duration_cast<milliseconds>(clock_t::now() - m_beg).count();
	}
};
int main()
{
	setlocale(LC_ALL, "ru");
	srand(time(NULL));
	const int size = 1000;
	int arr[size];
	int sravn = 0;
	int peres = 0;
	//запись случайных чисел в массив
	for (int i = 0; i < size; i++)
	{
		arr[i] = 1 + rand() % 1000;
	}
	//showArr(arr,size);//Печать исходного массива 
	cout << "Сортировка выбором:\n" << endl;
	Timer c;
	SelectionSort(arr, size);//Сортировка выбором и печать массива 
	cout << "Время: " << c.elapsed() << '\n';
	cout << "\nБыстрая сортировка:\n" << endl;
	Timer b;
	FastSort(arr, size, sravn, peres);//Быстрая сортировка
	cout << "Время: " << b.elapsed() << '\n';
	cout << sravn << "\n" << peres;
	return 0;
}
//Печать массива 
//void showArr(int arr[], int arrSize)
//{
//	for (int i = 0; i < arrSize; i++)
//	{
//		cout << setw(4) << arr[i];
//		if ((i + 1) % 10 == 0)
//		{
//			cout << endl;
//		}
//	}
//	cout << endl << endl;
//}

//Сортировка выбором
void SelectionSort(int arr[], int size)
{
	int sravn = 0;
	int peres = 0;
	for (int i = 0; i < size - 1; ++i)
	{
		int smallestIndex = i;
		for (int j = i + 1; j < size; ++j)
		{
			if (arr[j] < arr[smallestIndex])
			{
				smallestIndex = j;
				sravn++;
			}
		}
		int temp = arr[i];
		arr[i] = arr[smallestIndex];
		arr[smallestIndex] = temp;
		peres++;
	}
	cout <<"Число сравнений:" <<sravn<<endl;
	cout <<"Число пересылок:" << peres << endl;
	//showArr(arr, size);
}
void FastSort(int* arr, int size, int &sravn, int &peres)
{
	//Указатели в начало и в конец массива
	int i = 0;
	int j = size - 1;
	
	//Центральный элемент массива
	int mid = arr[size / 2];

	//Делим массив
	do {
		while (arr[i] < mid) i++;
		while (arr[j] > mid) j--;
		
		//Меняем элементы местами
		if (i <= j) 
		{
			peres++;
			int temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
			i++;
			j--;
		}
	} while (i <= j);

	//Рекурсивные вызовы, если осталось, что сортировать
	if (j > 0) {
		
		//"Левая часть"
		FastSort(arr, j + 1, sravn, peres);
	}
	if (i < size) {
		
		//"Правая часть"
		FastSort(&arr[i], size - i, sravn, peres);
	}
	//showArr(arr, size);
}