/*
* https://docs.google.com/document/d/1VxU2uxJV10rJNZtLycOV64xSbVmx7V0-/edit

������� ����� ���������� 1000, 10000 � 100000 ����������� ���������� ������� (������� ������������ �� 100 ��������, �������-��������� ����� ����� �� ����������);
������� ����� ������ ���������� ����� � ����������� ���������� �� 1000, 10000 � 100000 ��������� (������� ������������ �� 1000 ��������);
������� ����� ���������� � �������� ���������� ����� ��� ������������ ���������� �� 1000, 10 000 � 100 000 ��������� (������� ������������ �� 1000 ��������);

*/

#include <iostream>
# include <clocale>
#include <conio.h>
#include<vector>

using namespace std;
class Three {
	struct Leaves {
		int value;
		Leaves* Left = nullptr;
		Leaves* Right = nullptr;
	};
	int count = 0;
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
			this->count--;

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
		this->count = src.count;
	}
	~Three() { clear (root); this->count = 0;
	}
	Three(int key) {
		//Leaves* root = new Leaves;
		root->value = key;
		this->count = 1;
	}
	void print() {
		rec_print(this->root);
	}
	
	Three &operator=(const Three& src)
	{
		if (this == (&src)) { return *this; }
		clear(root);
		copy(root, src.root);
		this->count = src.count;
		return *this;
	}
	bool insert(int key) {

		bool tmp=rec_insert(this->root, key);
		if (tmp) this->count++;
		return tmp;

	}//������� ��������
	bool contains(int key) {
		if (rec_contains(this->root, key)) return true;
		return false;
	} //�������� ������� ��������

	int FindM() {
		if (this->count == 0) {
			cout << "��� ���������";
			return 0;
		}
		else return (FindMin(this->root))->value;
	}
	void erase(int key) { 
		this->root=rec_erase(this->root, key);
		
	} //�������� ��������
};


size_t lcg() {
	static size_t x = 0;
	x = (1021 * x + 24631) % 116640;
	return x;
}
#include <chrono>
using namespace std::chrono;
double TestFirst(int value) {
	 double sum = 0;

	//��� 100 ���
	for (int j = 0; j < 100; j++) {
		//������  �����
		auto start = high_resolution_clock::now();
		Three B(lcg());
		for (int i = 0; i < value - 1; i++) B.insert(lcg());
		auto stop = high_resolution_clock::now();
		chrono::duration<double> duration = stop - start;
		sum+=(double)duration.count();
	}
	//���������� �����
	//����� �������� � ������

	//����� ������� ������� ����� �� 100 � ����������
	return sum/100;
}
double TestSecond(int value) {
	double  sum = 0;
	//��� 1000 ���
	//������  �����
	for (int j = 0; j < 1000; j++) {
		Three B(lcg());
		for (int j=0;j<value;j++) B.insert(lcg());
		auto start = high_resolution_clock::now();
		for (int i = 0; i < value - 1; i++)B.contains(lcg());
		auto stop = high_resolution_clock::now();
		chrono::duration<double> duration = stop - start;
		sum += (double)duration.count();
	}
	//���������� �����
	//����� �������� � ������

	//����� ������� ������� ����� �� 1000 � ����������
	return sum/1000;
}
double TestThird(int value) {

	double  sum = 0;
	//��� 1000 ���
	//������  �����
	for (int j = 0; j < 1000; j++) {
		auto start = high_resolution_clock::now();
		Three B(lcg());
		for (int i = 0; i < value - 1; i++)B.insert(lcg());
		for (int i = 0; i < value - 1; i++)B.erase(lcg());
		auto stop = high_resolution_clock::now();
		chrono::duration<double> duration = stop - start;
		sum += (double)duration.count();
	}
	//���������� �����
	//����� �������� � ������

	//����� ������� ������� ����� �� 1000 � ����������
	return sum/1000;
}

double TestVectorFirst(int value) {
	
	vector<int> TimeVector(value);
	//��� 100 ���
	double sum = 0;
	for (int j = 0; j < 100; j++)
	{
		auto start = high_resolution_clock::now();
		for (int i = 0; i < value - 1; i++)  TimeVector.push_back(lcg());
		auto stop = high_resolution_clock::now();
		chrono::duration<double> duration = stop - start;
		sum += (double)duration.count();
	}
	//����� �������� � ������

	//����� ������� ������� ����� �� 100 � ����������
	return sum/100;
}
double TestVectorSecond(int value) {

	//��� 1000 ���
	//������  �����
	vector<int> TimeVector(value);
	//��� 100 ���
	double sum = 0;
	for (int j = 0; j < 1000; j++) {
		auto start = high_resolution_clock::now();
		for (int i = 0; i < value - 1; i++)TimeVector.push_back(lcg());//=================
		auto stop = high_resolution_clock::now();
		chrono::duration<double> duration = stop - start;
		sum += (double)duration.count();
	}
	//���������� �����


	//����� ������� ������� ����� �� 1000 � ����������
	return sum/1000;
}
double TestVectorThird(int value) {
	vector<int> TimeVector(value);
	//��� 1000 ���
	//������  �����
	double sum = 0;
	for (int j = 0; j < 1000; j++)
	{
		auto start = high_resolution_clock::now();
		for (int i = 0; i < value - 1; i++)TimeVector.push_back(lcg());
		//for (int i = 0; i < value - 1; i++)TimeVector.erase(lcg()<int>);//////////////
		auto stop = high_resolution_clock::now();
		chrono::duration<double> duration = stop - start;
		sum += (double)duration.count();
	}



	//����� ������� ������� ����� �� 1000 � ����������
	return sum / 1000;
}

void RecElem() {
	/*
	������� ������2
	��� ������� �������� elem1 ������� 1:
		���� ������� ���� � �������2: ������
		�����:
			count=0
			��� ������� �������� elem2 �������1:
				���� elem1==elem2:
					count++;
			���� count>1:  elem1 ������� � ������2

	cout<<"������������� ��������: "<< ������2
}*/
}

int main() {
	
	setlocale(LC_ALL, "Russian");
	int tmp_value;
	cout << "������� �������� ������� ������� ������: ";
	cin >> tmp_value;
	Three A(tmp_value);

	do {
		system("CLS");
		cout << "���� �������� :\n";
		A.print();
		cout << "\n�������� �������� : \n1)�������� ������� � ������\n2)������� ������� �� ������\n3)��������� ���������� �� �������\n4)����������� �������� ������\n\n__�����_���_������__\n\n5)���� �� ����������\n6)���� �� �����\n7)���� �� ��������� �������� \n\n__�����_���_��������__\n\n8)���� �� ����������\n9)���� �� �����\n10)���� �� ��������� �������� \n11)��������� ������ ���������� � ������� ������������ ��������\n12)�����";
		cin >> tmp_value;
		switch (tmp_value)
		{
		case 1:
			cout << "������� �������:";
			cin >> tmp_value;
			if (A.insert(tmp_value)) cout << "\n�������";
			else cout << "\n�� ����������";
			tmp_value = 0;
			_getch();
			break;
		case 2:
			cout << "������� �������� ���������� ��������:";
			cin >> tmp_value;
			A.erase(tmp_value);
			tmp_value = 0;
			break;
		case 3:
			cout << "������� �������:";
			cin >> tmp_value;
			if (A.contains(tmp_value)) cout << "\n����������";
			else cout << "\n�� ����������";
			tmp_value = 0;
			_getch();
		case 4:
			if (A.FindM())cout << "����������� �������� ������ : " << A.FindM();
			_getch();
			break;
		case 5:
			do {
				cout << "�������� ������� �������� ������������:\n1) 1000 \n2) 10 000\n3) 100 000  \n4)������";
				cin >> tmp_value;
				switch (tmp_value)
				{
				case 1:
					//��������� � ������ ������ 1
					cout << "������� ����� ��������� �����: " << TestFirst(1000);
					_getch();
					break;
				case 2:
					//��������� � ������ ������ 2
					cout << "������� ����� ��������� �����: " << TestFirst(10000);
					_getch();
					break;
				case 3:
					//��������� � ������ ������ 3
					cout << "������� ����� ��������� �����: " << TestFirst(100000);
					_getch();
					break;
				case 4:
					break;
				default:
					cout << "\n��� ������ ��������\n";
					_getch();
					break;
				}
				system("CLS");
			} while (tmp_value != 4);
			tmp_value = 0;
			break;
		case 6:
			do {
				cout << "�������� ������� �������� ������������:\n1) 1000 \n2) 10 000\n3) 100 000  \n4)������";
				cin >> tmp_value;
				switch (tmp_value)
				{
				case 1:
					//��������� � ������ ������ 4
					cout << "������� ����� ��������� �����: " << TestSecond(1000);
					_getch();
					break;
				case 2:
					//��������� � ������ ������ 5
					cout << "������� ����� ��������� �����: " << TestSecond(10000);
					_getch();
					break;
				case 3:
					//��������� � ������ ������ 6
					cout << "������� ����� ��������� �����: " << TestSecond(100000);
					_getch();
					break;
				case 4:
					break;
				default:
					cout << "\n��� ������ ��������\n";
					_getch();
					break;
				}
				system("CLS");
			} while (tmp_value != 4);
			tmp_value = 0;
			break;
		case 7:
			do {
				cout << "�������� ������� �������� ������������:\n1) 1000 \n2) 10 000\n3) 100 000  \n4)������";
				cin >> tmp_value;
				switch (tmp_value)
				{
				case 1:
					//��������� � ������ ������ 7
					cout << "������� ����� ��������� �����: " << TestThird(1000);
					_getch();
					break;
				case 2:
					//��������� � ������ ������ 8
					cout << "������� ����� ��������� �����: " << TestThird(10000);
					_getch();
					break;
				case 3:
					//��������� � ������ ������ 9
					cout << "������� ����� ��������� �����: " << TestThird(100000);
					_getch();
					break;
				case 4:
					break;
				default:
					cout << "\n��� ������ ��������\n";
					_getch();
					break;
				}
				system("CLS");
			} while (tmp_value != 4);
			tmp_value = 0;
			break;
		case 8:
			do {
				cout << "�������� ������� �������� ������������:\n1) 1000 \n2) 10 000\n3) 100 000  \n4)������";
				cin >> tmp_value;
				switch (tmp_value)
				{
				case 1:
					//��������� � ������ ������ 1
					cout << "������� ����� ��������� �����: " << TestVectorFirst(1000);
					_getch();
					break;
				case 2:
					//��������� � ������ ������ 2
					cout << "������� ����� ��������� �����: " << TestVectorFirst(10000);
					_getch();
					break;
				case 3:
					//��������� � ������ ������ 3
					cout << "������� ����� ��������� �����: " << TestVectorFirst(100000);
					_getch();
					break;
				case 4:
					break;
				default:
					cout << "\n��� ������ ��������\n";
					_getch();
					break;
				}
				system("CLS");
			} while (tmp_value != 4);
			tmp_value = 0;
			break;
		case 9:
			do {
				cout << "�������� ������� �������� ������������:\n1) 1000 \n2) 10 000\n3) 100 000  \n4)������";
				cin >> tmp_value;
				switch (tmp_value)
				{
				case 1:
					//��������� � ������ ������ 4
					cout << "������� ����� ��������� �����: " << TestVectorSecond(1000);
					_getch();
					break;
				case 2:
					//��������� � ������ ������ 5
					cout << "������� ����� ��������� �����: " << TestVectorSecond(10000);
					_getch();
					break;
				case 3:
					//��������� � ������ ������ 6
					cout << "������� ����� ��������� �����: " << TestVectorSecond(100000);
					_getch();
					break;
				case 4:
					break;
				default:
					cout << "\n��� ������ ��������\n";
					_getch();
					break;
				}
				system("CLS");
			} while (tmp_value != 4);
			tmp_value = 0;
			break;
		case 10:
			do {
				cout << "�������� ������� �������� ������������:\n1) 1000 \n2) 10 000\n3) 100 000  \n4)������";
				cin >> tmp_value;
				switch (tmp_value)
				{
				case 1:
					//��������� � ������ ������ 7
					cout << "������� ����� ��������� �����: " << TestVectorThird(1000);
					_getch();
					break;
				case 2:
					//��������� � ������ ������ 8
					cout << "������� ����� ��������� �����: " << TestVectorThird(10000);
					_getch();
					break;
				case 3:
					//��������� � ������ ������ 9
					cout << "������� ����� ��������� �����: " << TestVectorThird(100000);
					_getch();
					break;
				case 4:
					break;
				default:
					cout << "\n��� ������ ��������\n";
					_getch();
					break;
				}
				system("CLS");
			} while (tmp_value != 4);
			tmp_value = 0;
			break;
		case 11:
			//������� ������ 
			int tmp_value1;
			do {
				cout << "��� ������: \n";
				//������ ������ 
				cout << "\n�������� ���?\n1)��\n2)��� ";
				cin >> tmp_value1;
				switch (tmp_value1)
				{
				case 1:
					cout << "������� �������, ������� ������� � ������: ";
					cin >> tmp_value;
					//��������� � ������ ��������
				case 2:
					break;
				default:
					cout << "\n��� ������ ��������\n";
					_getch();
					break;
				}

			} while (tmp_value1 != 2);
			tmp_value = 0;

			cout << "��� ������:";
			RecElem();

		default:
			break;
		}
	
	} while (tmp_value != 12);
	
}