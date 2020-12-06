//В упорядоченном АВЛ - дереве с целочисленными ключами
//возведите в квадрат корневой элемент.
//Восстановите свойства АВЛ дерева.

//Поиск вставка удаление
//find add del
#include "AVL.h"
#include <fstream>

void from_file(AVL& t)
{
	fstream f;
	int a = 0;
	f.open("file.txt");
	if (!f.is_open()) return;
	while (!f.eof())
	{
		f >> a;
		t.push(a);
	}
	f.close();
}

int input_n(string a) {
	int n = 1;
	do
	{
		if (n <= 0) cout << "Введите значение больше 0";
		cout << "\n" << a << "\n";
		cin >> n;
	} while (n <= 0);
	return n;
};

void from_hand(AVL& t)
{
	int num = 0;
	int n = input_n("Введите количество чисел");

	for (int i = 0; i < n; i++)
	{
		cout << "Введите число\n";
		cin >> num;
		t.push(num);
	}
}

int main()
{
	AVL tree;

	setlocale(LC_ALL, "rus");

	tree.push(100);
	tree.push(50);
	tree.push(75);
	tree.push(52);
	tree.push(60);
	tree.push(101);
	tree.push(80);

	from_file(tree);

	tree.print();

	int data = tree.GetRootData();
	cout << "У корня значение " << data << "\nЕго квадрат - " << data * data;

	return 0;
}