/*
* https://docs.google.com/document/d/1VxU2uxJV10rJNZtLycOV64xSbVmx7V0-/edit
* Класс должен представлять собой двоичное дерево поиска.
Стандартные контейнеры в качестве полей класса не использовать.

Класс должен предоставлять, как минимум, следующие функции:

конструктор копирования;
деструктор;
оператор присваивания;
void print() – печать содержимого;
bool insert(int key) – вставка элемента;
bool contains(int key) -  проверка наличия элемента;
bool erase(int key) – удаление элемента;

*/

#include <iostream>

using namespace std;
class Three {
public:
	struct Leaves {
		int value;
		Leaves* Left = nullptr;
		Leaves* Right = nullptr;
	}*root;

	Three(int key) {
		Leaves* root = new Leaves;
		root->value = key;
	}
	Three(Three& src)
	{
		Leaves* root = new Leaves;
	}
	~Three() {}
	void rec_print(Leaves* elem)
	{
		if (elem != nullptr) {
			if (elem->Left)rec_print(elem->Left);
			cout << elem->value;
			if (elem->Right)rec_print(elem->Right);
		}
		}
	void print() {
		rec_print(this->root);
	}

	bool rec_insert(Leaves* elem, int key) {

		if (elem==nullptr||key == elem->value) return false;
		if (key > elem->value) {
			if (elem->Right)
			{
				return rec_insert(elem->Right, key);
			}
			else {
				Leaves* tmp = new Leaves;
				elem->Right = tmp;
				tmp->value = key;
				
			}
		}
		else if (key < elem->value) {
			if (elem->Left) {
				return rec_insert(elem->Left, key);
			}
			else {
				Leaves* tmp = new Leaves;
				elem->Left = tmp;
				tmp->value = key;
			
			}
		}
		return true;

	}

	bool insert(int key) {
		return rec_insert(this->root, key);

	}//вставка элемента
	bool contains(int key) {} //проверка наличия элемента
	bool erase(int key) {} //удаление элемента
};
int main() {
	Three A(20);
	A.insert(1);
	A.insert(25);
	A.insert(5);
	A.insert(10);
	A.insert(30);
	A.insert(25);
	A.print();



}
