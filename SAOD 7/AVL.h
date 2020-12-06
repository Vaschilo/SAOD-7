#pragma once
#include <iostream>
using namespace std;

#define type int

class Node
{
	type data;
	int height;

	int delta(Node* ptr)
	{
		int r = 0, l = 0;
		if (ptr->right != nullptr) r = ptr->right->GetHeight();
		if (ptr->left != nullptr) l = ptr->left->GetHeight();
		return r - l;
	}

	void change_height(Node* ptr)
	{
		int r = 0, l = 0;
		if (ptr->right != nullptr) r = ptr->right->GetHeight();
		if (ptr->left != nullptr) l = ptr->left->GetHeight();
		ptr->SetHeight((l > r ? l : r) + 1);
	}

	Node* rotate_right(Node* p) //правый поворот
	{
		Node* q = p->left;
		p->left = q->right;
		q->right = p;
		change_height(p);
		change_height(q);
		return q;
	}

	Node* rotate_left(Node* q) //левый поворот
	{
		Node* p = q->right;
		q->right = p->left;
		p->left = q;
		change_height(q);
		change_height(p);
		return p;
	}

	Node* balance(Node* p)
	{
		change_height(p);
		if (delta(p) == 2)
		{
			if (delta(p->right) < 0)
				p->right = rotate_right(p->right);
			return rotate_left(p);
		}
		if (delta(p) == -2)
		{
			if (delta(p->left) > 0)
				p->left = rotate_left(p->left);
			return rotate_right(p);
		}
		return p;
	}

	Node* findmin(Node* p)
	{
		return p->left == nullptr ? findmin(p->left) : p;
	}

	Node* removemin(Node* p)
	{
		if (p->left == 0)
			return p->right;
		p->left = removemin(p->left);
		return balance(p);
	}

public:
	Node* left;
	Node* right;
	Node() 
	{ 
		this->left = nullptr; 
		this->right = nullptr; 
		this->height = 0; 
	}
	Node(type data)
	{
		this->left = nullptr;
		this->right = nullptr;
		this->height = 0;
		this->data = data;
	}
	~Node() {}

	type GetData() { return this->data; }
	void SetData(type a) { this->data = a; }

	int GetHeight() { return this->height; }
	void SetHeight(int a) { this->height = a; }

	Node* remove(Node* p, type k) // удаление k из дерева p
	{
		if (!p) return nullptr;
		if (k < p->GetData())
			p->left = remove(p->left, k);
		else if (k > p->GetData())
			p->right = remove(p->right, k);
		else
		{
			Node* q = p->left;
			Node* r = p->right;
			delete p;
			if (!r) return q;
			Node* min = findmin(r);
			min->right = removemin(r);
			min->left = q;
			return balance(min);
		}
		return balance(p);
	}

	Node* push(type data)
	{
		if (data > this->data)
		{
			if (this->right == nullptr)
				this->right = new Node(data);
			else
				this->right->push(data);
			this->height = this->right->GetHeight() + 1;
		}
		else
		{
			if (this->left == nullptr)
				this->left = new Node(data);
			else
				this->left->push(data);
			this->height = this->left->GetHeight() + 1;
		}
		return balance(this);
	}

	Node* find(type data)
	{
		if (this->data == data) return this;

		if (this->data > data)
		{
			if (this->right == nullptr) return nullptr;
			return this->right->find(data);
		}
		else
		{
			if (this->left == nullptr) return nullptr;
			return this->left->find(data);
		}
	}

	void print(int a)
	{
		for (int i = 0; i < a; i++) cout << "|";
		cout << data << endl;
		if (this->left != nullptr)this->left->print(a + 1); else { for (int i = 0; i < a + 1; i++) cout << "|"; cout << "NULL" << endl; }
		if (this->right != nullptr)this->right->print(a + 1); else { for (int i = 0; i < a + 1; i++) cout << "|"; cout << "NULL" << endl; }
	}
};

class AVL
{
private:
	Node* root;

	void clear_recurse(Node* current)
	{
		if (current == nullptr) return;
		if (current->left != nullptr) { clear_recurse(current->left); delete current->left; }
		if (current->right != nullptr) { clear_recurse(current->right); delete current->right; }
	}

public:
	AVL() { this->root = nullptr; }
	~AVL() { this->clear(); }
	void clear()
	{
		clear_recurse(this->root);
		delete this->root;
		this->root = nullptr;
	}

	void insert(type data)
	{
		this->push(data);
	}
	void push(type data)
	{
		if (this->root == nullptr) this->root = new Node(data);
		else this->root = this->root->push(data);
	}

	void find(type data)
	{
		Node* ptr = this->root->find(data);
		if (ptr == nullptr)
			cout << "Узел не найден" << endl;
		else cout << "Узел найден" << endl;
	}

	void remove(type data)
	{
		if (this->root == nullptr) return;
		this->root->remove(this->root, data);
	}

	void print()
	{
		if (this->root == nullptr) return;
		this->root->print(0);
	}

	type GetRootData()
	{
		if (this->root == nullptr) return type();
		return this->root->GetData();
	}
};