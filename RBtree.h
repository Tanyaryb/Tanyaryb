#pragma once
#include <iostream>

typedef int dataType;   // чтоб можно было выбрать любой тип хранения данных за секунду
enum color {RED, BLACK};


struct Node
{
	Node* left;
	Node* right;
	Node* parent;
	color color;
	dataType data;
	dataType key;
};

class RBtree
{
private:
	Node* root;
	void insertfix(Node*);			// балансировка после ввода узла
	void leftrotate(Node*);			// левый  поворот
	void rightrotate(Node*);		// правый поворот
	Node* successor(Node*);			// балансировка
	void delfix(Node*);				// балансировка после удаления узла
	bool display(Node*);			// вывод узла
	bool get_values2(Node* p);		// вывод одних данных
	bool get_keys2(Node* p);		// вывод одного ключа
	void cl(Node* p);
	bool searchbool(dataType x);	// есть такой узел в дереве или нет, дополнение поиска
	void insertpriv(Node* t);			// ввод узла в дерево
	void Destruct(Node *current);	// дополнение к деструктору
public:
	RBtree() :root(nullptr) {};		// конструктор
	~RBtree();						// деструктор
	void insert(dataType inskey, dataType insdata);			// метод добавления узла в дерево
	bool find(dataType data);						// метод поиска в дереве
	void remove(dataType x);							// метод удаления узла из дерева
	bool print();									// метод вывода всего дерева
	bool get_values();								// метод вывода значений
	bool get_keys();								// метод вывода ключей
	void clear();									// метод очищения ассоциативного массива
};
