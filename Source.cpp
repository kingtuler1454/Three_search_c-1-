/*
* https://docs.google.com/document/d/1VxU2uxJV10rJNZtLycOV64xSbVmx7V0-/edit

������� ����� ���������� 1000, 10000 � 100000 ����������� ���������� ������� (������� ������������ �� 100 ��������, �������-��������� ����� ����� �� ����������);
������� ����� ������ ���������� ����� � ����������� ���������� �� 1000, 10000 � 100000 ��������� (������� ������������ �� 1000 ��������);
������� ����� ���������� � �������� ���������� ����� ��� ������������ ���������� �� 1000, 10000 � 100000 ��������� (������� ������������ �� 1000 ��������);

*/

#include <iostream>
# include <clocale>
#include <conio.h>
using namespace std;
class Three {
	struct Leaves {
		int value;
		Leaves* Left = nullptr;
		Leaves* Right = nullptr;
	};
	Leaves* root = new Leaves;
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
				struct Leaves* tmp = FindMin(elem->Right);
				elem->value = tmp->value;
				elem->Right = rec_erase(elem->Right, tmp->value);
			}
		}
		return elem;
	}
	bool rec_insert(Leaves* elem, int key) {

		if (elem == nullptr || key == elem->value) return false;
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
	Leaves* rec_contains(Leaves* elem, int key) {
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
	void rec_print(Leaves * elem)
		{
			if (elem != nullptr) {
				if (elem->Left)rec_print(elem->Left);
				cout << elem->value << ' ';
				if (elem->Right)rec_print(elem->Right);
			}
		}
	void clear(Leaves*& elem)
	{
		if (elem)
		{
			clear(elem->Left);
			clear(elem->Right);
			delete elem;
			elem = NULL;
		}

	}
	void copy(Leaves*& first, const Leaves* second)
	{
		if (!second)
		{
			first = NULL;
			return;
		}
		first = new Leaves;
		first->value = second->value;
		copy(first->Left, second->Left);
		copy(first->Right, second->Right);
	}
	Leaves* FindMin(Leaves* elem) {
		if (elem->Left) {
			return FindMin(elem->Left);
		}
		return elem;
	}
public:
	Three(Three &src) {
		root = NULL;
		copy(root, src.root);
	}
	~Three() { clear (root); }
	Three(int key) {
		//Leaves* root = new Leaves;
		root->value = key;
	}
	void print() {
		rec_print(this->root);
	}
	
	Three &operator=(const Three& src)
	{
		if (this == (&src)) { return *this; }
		clear(root);
		copy(root, src.root);
		return *this;
	}
	bool insert(int key) {
		return rec_insert(this->root, key);

	}//������� ��������
	bool contains(int key) {
		if (rec_contains(this->root, key)) return true;
		return false;
	} //�������� ������� ��������

	int Find() {
		
		return (FindMin(this->root))->value;
	}
	void erase(int key) { 
		rec_erase(this->root, key);
		
	} //�������� ��������
};

size_t lcg() {
	static size_t x = 0;
	x = (1021 * x + 24631) % 116640;
	return x;
}


int main() {
	/*Three A(20);
	A.insert(-110);
	A.insert(25);
	A.insert(5);
	A.insert(10);
	A.insert(30);
	A.insert(22);

	A.print();
	cout<<A.contains(100);
	cout << A.Find();
	A.erase(25);
	cout << endl;
	A.print();
	*/
	setlocale(LC_ALL, "Russian");
	int tmp_value;
	cout << "������� �������� ������� ������� ������: ";
	cin >> tmp_value;
	Three A(tmp_value);

	do {
		system("CLS");
		cout << "���� �������� :\n";
		A.print();
		cout << "\n�������� �������� : \n1)�������� ������� � ������\n2)������� ������� �� ������\n3)��������� ���������� �� �������\n4)����������� �������� ������\n5)���� �� ����������\n6)���� �� �����\n7)���� �� ��������� �������� \n8)�����";
		cin >> tmp_value;
		switch (tmp_value)
		{
		case 1:
			cout << "������� �������:";
			cin >> tmp_value;
			if (A.insert(tmp_value)) cout << "\n�������";
			else cout << "\n�� ����������";
			_getch();
			break;
		case 2:
			cout << "������� �������� ���������� ��������:";
			cin >> tmp_value;
			A.erase(tmp_value);
			break;
		case 3:
			cout << "������� �������:";
			cin >> tmp_value;
			if (A.contains(tmp_value)) cout << "\n����������";
			else cout << "\n�� ����������";
			_getch();
		case 4:
			cout << "����������� �������� ������ : "<<A.Find();
			_getch();
		default:
			break;
		}
		
	} while (tmp_value != 8);
	
}