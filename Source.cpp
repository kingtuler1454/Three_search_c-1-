/*
* https://docs.google.com/document/d/1VxU2uxJV10rJNZtLycOV64xSbVmx7V0-/edit
*  ласс должен представл€ть собой двоичное дерево поиска.
—тандартные контейнеры в качестве полей класса не использовать.

 ласс должен предоставл€ть, как минимум, следующие функции:

конструктор копировани€;
деструктор;
оператор присваивани€;
void print() Ц печать содержимого;
bool insert(int key) Ц вставка элемента;
bool contains(int key) -  проверка наличи€ элемента;
bool erase(int key) Ц удаление элемента;

*/

#include <iostream>

using namespace std;
class Three {
public:
	struct Leaves {
		int value;
		Leaves* Left = nullptr;
		Leaves* Right = nullptr;
	};
	Leaves* root= new Leaves;

	Three(int key) {
		//Leaves* root = new Leaves;
		root->value = key;
	}
	
	void rec_print(Leaves* elem)
	{
		if (elem != nullptr) {
			if (elem->Left)rec_print(elem->Left);
			cout << elem->value<<' ';
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

	Leaves* rec_contains(Leaves * elem,int key) {
		//if (elem == nullptr) return 0;
		//if (elem->value == key) return 1;
		//if (elem->value > key) return rec_contains(elem->Right, key);
		//else return rec_contains(elem->Left, key);
		if (elem != NULL && elem->value != key)
		{
			if (key < elem->value) elem = rec_contains(elem->Left, key);
			else elem = rec_contains(elem->Right, key);
		}
		return elem;
	}

	bool contains(int key) {
		if (rec_contains(this->root, key)) return true;
		return false;
	} //проверка наличи€ элемента

	//				200
	//		 190			210
	//	175		195	   205		215
	//
	Leaves* FindMin(Leaves* elem) {
		if (elem->Left) {
			return FindMin(elem->Left);
		}
		return elem;
	}
	int Find() {
		
		return (FindMin(this->root))->value;
	}


	Leaves* rec_erase(Leaves* elem, int key) {
		if (elem == NULL) return elem;
		else if (key < elem->value) elem->Left = rec_erase(elem->Left, key);
		else if (key > elem->value) elem->Right = rec_erase(elem->Right, key);
		else {
			// Case 1:  No child
			if (elem->Left == NULL && elem->Right == NULL) {
				delete elem;
				elem = NULL;
			}
			//Case 2: One child 
			else if (elem->Left == NULL) {
				struct Leaves* temp = elem;
				elem = elem->Right;
				delete temp;
			}
			else if (elem->Right == NULL) {
				struct Leaves* tmp = elem;
				elem = elem->Left;
				delete tmp;
			}
			// case 3: 2 children
			else {
				struct Leaves * tmp = FindMin(elem->Right);
				elem->value = tmp->value;
				elem->Right = rec_erase(elem->Right, tmp->value);
			}
		}
		return elem;
	}
	
	bool erase(int key) { 
		rec_erase(this->root, key);
	
	} //удаление элемента
};


int main() {
	Three A(20);
	A.insert(-110);
	A.insert(25);
	A.insert(5);
	A.insert(10);
	A.insert(30);
	A.insert(22);

	A.print();
	cout<<A.contains(100);
	cout << A.Find();


}