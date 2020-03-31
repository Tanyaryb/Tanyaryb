#include <iostream>
#include "RBTree.h"
using namespace std;

int main()
{
	setlocale(LC_ALL, "ru");
	RBtree Tree;
	int y = 0, max, switchTwo, i = 0;
	dataType data;
	cout << "Красно-черное дерево:\n";
	cout << "Введите целое положительное число для определения количества узлов\n";
	cin >> max;
	cout << "Введите данные, разделяя их пробелами\n";
	for (i = 0; i < max; i++)
	{
		cin >> data;
		Tree.insert(i + 1, data);
	}
	cout << "\nДерево было созданно и заполнено, доступные операции";
	cout << "\n\t 1. Добавление нового узла в дерево";
	cout << "\n\t 2. Удаление узла из дерево";
	cout << "\n\t 3. Поиск узла в дереве";
	cout << "\n\t 4. Удаление ассоциативного массива";
	cout << "\n\t 5. Вывод ключей";
	cout << "\n\t 6. Вывод значений";
	cout << "\n\t 7. Вывод дерева на экран";
	cout << "\n\t 8. Выход";
	cout << "\nВаш выбор: ";
	do
	{
		cin >> switchTwo;
		switch (switchTwo)
		{
		case 1:
			cout << "\nВведите данные для внесения в дерево.\n";
			cin >> data;
			Tree.insert(i + 1, data);
			cout << "\nДанные были внесены в дерево.\n";
			break;
		case 2:
			cout << "\nВведите ключ, который подлежит удалению.\n";
			dataType key;
			cin >> key;
			Tree.remove(key);
			break;
		case 3:
			cout << "\nВведите ключ, по которому будем делать поиск.\n";
			dataType key2;
			cin >> key2;
			Tree.find(key2);
			break;
		case 4:
			cout << "\nОчищение ассоциативного массива\n";
			Tree.clear();
			break;
		case 5:
			cout << "\n Вывод ключей на экран\n";
			Tree.get_keys();
			break;
		case 6:
			cout << "\n Вывод значений на экран\n";
			Tree.get_values();
			break;
		case 7:
			cout << "\n Вывод дерева на экран\n";
			Tree.print();
			break;
		case 8:
			y = 1;
			break;
		default:
			cout << "\nОшибка! Введите правильный вариант.";
			break;
		}
		cout << "\nВведите следующую операцию:  ";
	} while (y != 1);

	return 0;
}

RBtree::~RBtree()   // деструктор
{
	if (root != NULL)
	{
		Destruct(root);  // потому что нельзя вызвать деструктор рекурсивно
	}
}

void RBtree::Destruct(Node *current)  // для деструктора -- рекурсивное удаление дерева
{
	if (current != nullptr) 
	{
		Destruct(current->left);
		Destruct(current->right);
		delete current;
	}
}

void RBtree::insert(dataType inskey, dataType insdata)  // создание узла -- данные вводятся с клавиатуры
{


	Node* t = new Node;
	t->data = insdata;
	t->key = inskey;
	t->left = NULL;
	t->right = NULL;
	t->color = RED;
	if (searchbool(t->data))
		delete t;  // если уже есть -- удаляем
	else 
		insertpriv(t);					 // если в дереве нету -- заносим
}

void RBtree::insertpriv(Node *t)	// t -- вставляемый в деререво узел
{
	Node* rootCopy = root, * q = NULL;
	if (root == NULL)  // если дерево не существует, то добавляемый узел становится корнем
	{
		root = t;
		t->parent = NULL;
	}
	else  // если дерево существует... находим место куда вставить узел
	{
		while (rootCopy != NULL)	// смотрим в дерево, пока не дошли до листов
		{
			q = rootCopy;
			if (rootCopy->data < t->data)		// если вставляемый больше корня/узла то ГО в правое поддерево
				rootCopy = rootCopy->right;
			else								// иначе ГО в левое поддерево
				rootCopy = rootCopy->left;
		}
		t->parent = q;						// q усонавливает t
		if (q->data < t->data)				// исходя из значения t, ставим либо правым
			q->right = t;
		else								// либо левым потомком q
			q->left = t;
	}
	insertfix(t);	// балансируем, перекрашиваем, делаем повороты...
}

void RBtree::insertfix(Node* t)
{
	Node* uncle = NULL;
	if (root == t) // если в дереве только данный узел красим в ченое и все
	{
		t->color = BLACK;
		t->parent = NULL;
		return;
	}
	// иначе
	while (t->parent != NULL && t->parent->color == RED)
	{
		Node* grandpa = t->parent->parent;	// дед
		if (grandpa->left == t->parent)		// если отец t левый потомок деда
		{
			if (grandpa->right != NULL)		// и при этом нет правого потомка
			{
				uncle = grandpa->right;		// тогда дядя правый потомок деда
				if (uncle->color == RED)	// и если красный
				{
					t->parent->color = BLACK;	// то отец t -- черный
					uncle->color = BLACK;		// дядя тоже черный
					grandpa->color = RED;		// дед красный
					t = grandpa;				
				}
			}
			else  // если оба потомка существуют...
			{
				if (t->parent->right == t)  // если t правый потомок отца, тогда левый поворот от отца
				{
					t = t->parent;
					leftrotate(t);
				}
				t->parent->color = BLACK;	// отец черный
				grandpa->color = RED;		// дед красный
				rightrotate(grandpa);		// правый поворот от деда
			}
		}
		else  // если отец t правый потомок деда, тоже самое зеркально отображенное...
		{
			if (grandpa->left != NULL)
			{
				uncle = grandpa->left;
				if (uncle->color == RED)
				{
					t->parent->color = BLACK;
					uncle->color = BLACK;
					grandpa->color = RED;
					t = grandpa;
				}
			}
			else
			{
				if (t->parent->left == t)
				{
					t = t->parent;
					rightrotate(t);
				}
				t->parent->color = BLACK;
				grandpa->color = RED;
				leftrotate(grandpa);
			}
		}
		// сохраняем свойства корня
		root->color = BLACK;
		root->parent = NULL;
	}
}

void RBtree::remove(dataType x)
{
	if (root == NULL)
	{
		std::cout << "\nПустое дерево, нечего удалить!";
		return;
	}
	Node* p = root;
	Node* y = NULL;
	Node* q = NULL;
	bool found = false;
	while (p != NULL && found == false)  // ищем
	{
		if (p->key == x)
			found = true;
		if (found == false)
		{
			if (p->key < x)
				p = p->right;
			else
				p = p->left;
		}
	}
	if (found == false) // не нашли
	{
		std::cout << "\nТакого элемента нет в дереве!";
		return;
	}
	else // нашли, удаляем
	{
		std::cout << "\nУдаленный элемент: " << p->data;
		std::cout << "\nКлюч: " << p->key;
		std::cout << "\nЦвет: ";
		if (p->color == BLACK)
			std::cout << "Черный\n";
		else
			std::cout << "Красный\n";

		if (p->parent != NULL)
			std::cout << "\nРодитель: " << p->parent->data;
		else
			std::cout << "\nУ него нет родителя.  ";
		if (p->right != NULL)
			std::cout << "\nПравый потомок: " << p->right->data;
		else
			std::cout << "\nУ него нет правого потомка.  ";
		if (p->left != NULL)
			std::cout << "\nЛевый потомок: " << p->left->data;
		else
			std::cout << "\nУ него нет левого потомка.  ";
		
		if (p->left == NULL || p->right == NULL)  // если хотя бы один потомок лист
			y = p;
		else
			y = successor(p);
		if (y->left != NULL)		// если левый потомок существует
			q = y->left;
		else						// если нет
		{
			if (y->right != NULL)	// и при этом правый потомок тоже существует
				q = y->right;
			else					// если нет
				q = NULL;
		}
		if (q != NULL)		// после выше происходящего если q не лист то его отец это отец у тоже
			q->parent = y->parent;
		if (y->parent == NULL)			// если нет родителя, то он корень
			root = q;
		else							// иначе
		{
			if (y == y->parent->left)	// если у левый потомок отца
				y->parent->left = q;
			else						// если правый
				y->parent->right = q;
		}
		if (y != p)
		{
			p->color = y->color;
			p->data = y->data;
		}
		if (y->color == BLACK)  // если у был черным, нужно балансировать
			delfix(q);
		std::cout << "\nУзел был удален, дерево - сбалансировано!\n";
	}
	
}

void RBtree::clear()
{
	cl(root);
}

void RBtree::cl(Node* p)
{
	if (root == NULL)
	{
		std::cout << "\nМассив очищен";
		return;
	}
	Node* y = NULL;
	Node* q = NULL;

	if (p->left != NULL)
		cl(p->left);
	if (p->right != NULL)
		cl(p->right);

	if (p->left == NULL || p->right == NULL)  // если хотя бы один потомок лист
		y = p;
	else
		y = successor(p);
	if (y->left != NULL)		// если левый потомок существует
		q = y->left;
	else						// если нет
	{
		if (y->right != NULL)	// и при этом правый потомок тоже существует
			q = y->right;
		else					// если нет
			q = NULL;
	}
	if (q != NULL)		// после выше происходящего если q не лист то его отец это отец у тоже
		q->parent = y->parent;
	if (y->parent == NULL)			// если нет родителя, то он корень
		root = q;
	else							// иначе
	{
		if (y == y->parent->left)	// если у левый потомок отца
			y->parent->left = q;
		else						// если правый
			y->parent->right = q;
	}
	if (y != p)
	{
		p->color = y->color;
		p->data = y->data;
	}
	if (y->color == BLACK)  // если у был черным, нужно балансировать
		delfix(q);
	std::cout << "\n!\n";
}

void RBtree::delfix(Node* p)
{
	Node* s = NULL; // дядя
	while (p != root && p->color == BLACK)	// пока не корень и не черный одновременно
	{
		if (p->parent->left == p)	// если р левый потомок
		{
			s = p->parent->right;	// s - дядя
			if (s->color == RED)	// если дядя красный
			{
				s->color = BLACK;		// дядя черный
				p->parent->color = RED;	// отец красный
				leftrotate(p->parent);	// левый поворот от отца
				s = p->parent->right;	// дядя стал правым потомком отца
			}
			if (s->right->color == BLACK && s->left->color == BLACK)  // племянники черные одновременно
			{
				s->color = RED; // тогда дядя красный
				p = p->parent;
			}
			else
			{
				if (s->right->color == BLACK)	//если правый племянник черный
				{
					s->left->color = BLACK; // левый тоже будет
					s->color = RED;			// дядя опять красный
					rightrotate(s);			// правый поворот от дяди
					s = p->parent->right;	// дядя стал правым потомком отца
				}
				s->color = p->parent->color;
				p->parent->color = BLACK;
				s->right->color = BLACK;
				leftrotate(p->parent);
				p = root;
			}
		}
		else  // если р правый потомок, аналогично зеркально отображенно
		{
			s = p->parent->left;
			if (s->color == RED)
			{
				s->color = BLACK;
				p->parent->color = RED;
				rightrotate(p->parent);
				s = p->parent->left;
			}
			if (s->left->color == BLACK && s->right->color == BLACK)
			{
				s->color = RED;
				p = p->parent;
			}
			else
			{
				if (s->left->color == BLACK)
				{
					s->right->color = BLACK;
					s->color = RED;
					leftrotate(s);
					s = p->parent->left;
				}
				s->color = p->parent->color;
				p->parent->color = BLACK;
				s->left->color = BLACK;
				rightrotate(p->parent);
				p = root;
			}
		}
		p->color = BLACK;
		root->color = BLACK;
		root->parent = NULL;
	}
}

void RBtree::leftrotate(Node* p)	// левый поворот
{
	if (p->right == NULL)
		return;
	else
	{
		Node* y = p->right;
		if (y->left != NULL)
		{
			p->right = y->left;
			y->left->parent = p;
		}
		else
			p->right = NULL;
		if (p->parent != NULL)
			y->parent = p->parent;
		if (p->parent == NULL)
			root = y;
		else
		{
			if (p == p->parent->left)
				p->parent->left = y;
			else
				p->parent->right = y;
		}
		y->left = p;
		p->parent = y;
	}
}
void RBtree::rightrotate(Node* p)	// правый поворот
{
	if (p->left == NULL)
		return;
	else
	{
		Node* y = p->left;
		if (y->right != NULL)
		{
			p->left = y->right;
			y->right->parent = p;
		}
		else
			p->left = NULL;
		if (p->parent != NULL)
			y->parent = p->parent;
		if (p->parent == NULL)
			root = y;
		else
		{
			if (p == p->parent->left)
				p->parent->left = y;
			else
				p->parent->right = y;
		}
		y->right = p;
		p->parent = y;
	}
}

Node* RBtree::successor(Node* p)	// от переданного узла возвращает возвращает 
{
	Node* y = NULL;					// 1. на NULL если нет потомков; 
	if (p->left != NULL)			// 2. на правый последний элемент левого поддерева
	{
		y = p->left;
		while (y->right != NULL)
			y = y->right;
	}
	else							// 2. на левый последний элемент правого поддерева
	{
		y = p->right;
		while (y->left != NULL)
			y = y->left;
	}
	return y;
}

bool RBtree::print()
{
	return display(root);
}

bool RBtree::display(Node* p)
{
	if (root == NULL)
	{
		std::cout << "\nДерево пусто!.";
		return false;
	}
	if (p != NULL)
	{
		if (p == root)
			std::cout << "\n Корень: ";
		else
			std::cout << " Узел: ";
		std::cout << "\n\tДанные:\t\t" << p->data;
		std::cout << "\n\tКлюч:\t\t" << p->key;
		std::cout << "\n\tЦвет:\t";
		if (p->color == BLACK)
			std::cout << "\tЧерный";
		else
			std::cout << "\tКрасный";
		if (p->parent != NULL)  // && p != root
			std::cout << "\n\tРодитель:\t" << p->parent->data;
		else
			std::cout << "\n\tУ него нет родителя.";
		if (p->right != NULL)
			std::cout << "\n\tПравый потомок:\t" << p->right->data;
		else
			std::cout << "\n\tУ него нет правого потомка.";
		if (p->left != NULL)
			std::cout << "\n\tЛевый потомок:\t" << p->left->data;
		else
			std::cout << "\n\tУ него нет левого потомка.";

		if (p->left)
		{
			std::cout << "\n Левый";
			display(p->left);
		}

		if (p->right)
		{
			std::cout << "\n Правый";
			display(p->right);
		}
		return true;

	}
}

bool RBtree::get_values()
{
	return get_values2(root);
}


bool RBtree::get_values2(Node* p)
{
	if (root == NULL)
	{
		std::cout << "\nДерево пусто!.";
		return false;
	}
	if (p != NULL)
	{
		std::cout << "\n\tДанные:\t\t" << p->data;
		if (p->left)
		{
			std::cout << "\t";
			get_values2(p->left);
		}
		if (p->right)
		{
			std::cout << "\t";
			get_values2(p->right);
		}
		return true;
	}
}

bool RBtree::get_keys()
{
	return get_keys2(root);
}


bool RBtree::get_keys2(Node* p)
{
	if (root == NULL)
	{
		std::cout << "\nДерево пусто!.";
		return false;
	}
	if (p != NULL)
	{
		std::cout << "\n\tКлюч:\t\t" << p->key;
		if (p->left)
		{
			std::cout << "\t";
			get_keys2(p->left);
		}
		if (p->right)
		{
			std::cout << "\t";
			get_keys2(p->right);
		}
		return true;
	}
}

bool RBtree::searchbool(dataType x)		// дополнение для поиска
{
	if (root == NULL)  //Дерево пусто!
		return false;
	Node* p = root;
	bool found = false;
	while (p != NULL && found == false)
	{
		if (p->key == x)
			found = true;
		if (found == false)
		{
			if (p->key < x)
				p = p->right;
			else
				p = p->left;
		}
	}
	if (found == false)
		return false;	// не нашел 
	else
		return true;	// нашел 
}


bool RBtree::find(dataType x) 
{
	if (root == NULL)
	{
		std::cout << "\nПустое дерево\n";
		return false;
	}
	Node* p = root;
	bool found = false;
	while (p != NULL && found == false)
	{
		if (p->key == x)
			found = true;
		if (found == false)
		{
			if (p->key < x)
				p = p->right;
			else
				p = p->left;
		}
	}
	if (found == false)
	{
		std::cout << "\nЭлемент не найден!";
		return found;
	}
	else
	{
		found = true;
		std::cout << "\n Найденный элемент: ";
		std::cout << "\n\tДанные:\t\t" << p->data;
		std::cout << "\n\tКлюч:\t\t" << p->key;
		std::cout << "\n\tЦвет:\t";
		if (p->color == BLACK)
			std::cout << "\tЧерный";
		else
			std::cout << "\tКрасный";
		if (p->parent != NULL)
			std::cout << "\n\tРодитель:\t" << p->parent->data;
		else
			std::cout << "\n\tУ него нет родителя.";
		if (p->right != NULL)
			std::cout << "\n\tПравый потомок:\t" << p->right->data;
		else
			std::cout << "\n\tУ него нет правого потомка.";
		if (p->left != NULL)
			std::cout << "\n\tЛевый потомок:\t" << p->left->data;
		else
			std::cout << "\n\tУ него нет левого потомка.";
		std::cout << std::endl;
		return found;
	}
}
