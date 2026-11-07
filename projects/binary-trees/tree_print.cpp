
#include <iostream>
#include "lab_compat.h"
using namespace std;
// our structure
struct node
{
	int info; // information (data) field
	node * l, * r; // left and right parts of the tree
};
node* tree = NULL; // declare a variable whose type is the tree structure
/* FUNCTION THAT INSERTS AN ELEMENT INTO THE BINARY TREE */
void push(int a, node **t)
{
	if ((*t) == NULL) // if the tree does not exist
	{
		(*t) = new node; // allocate memory
		(*t)->info = a; // put the argument a into the allocated node
		(*t)->l = (*t)->r = NULL; // clear the child pointers so the tree can grow
		return;  // the root is planted, return
	}
		if (a > (*t)->info) push(a, &(*t)->r); // if the argument
			// is greater than the current element, put it to the right
		else push(a, &(*t) ->l); // otherwise put it to the left
}
/* FUNCTION THAT DISPLAYS THE TREE ON THE SCREEN */
void print(node * t, int u)
{
	if (t == NULL) return; // if the tree is empty there is
		// nothing to show, return
	else // otherwise
	{
	print(t -> l,++u);// visit the left subtree recursively
	for (int i = 0; i < u; ++i) cout << "|" ;
	cout << t->info << endl; // then show the element
	u--;
	}
	print(t -> r, ++u); // visit the right subtree recursively
}
int main()
{
	int n; // number of elements
	int s; // number passed to the tree
	cout << "уведіть кількість елементів" ;
	cin >> n; // enter the number of elements
	for (int i = 0; i < n; ++i)
	{
		cout << "уведіть число ";
			cin >> s;  // read the elements one by one
			push(s, &tree); // and put each of them into the tree
	}
	cout << "ваше дерево\n";
	print(tree, 0);
	lab::pause();
}