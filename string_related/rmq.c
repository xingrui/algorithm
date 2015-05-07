/*
 ============================================================================
 Name        : rmq.cpp
 Author      :
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#define MAXNODE 100000
struct node
{
	int left;
	int right;
};
int E[2 * MAXNODE - 1];//the nodes visited in an Euler Tour of T
int L[2 * MAXNODE - 1];//the levels of the nodes visited in the Euler Tour
int H[MAXNODE];//the index of the first occurrence of node i in E
//any occurrence would be good, so it's not bad if we consider the first one
int current_euler_index = 0;
int current_euler_level = 0;

int init_euler(int N)
{
	int i = 0;

	for (i = 0; i < N; ++i)
	{
		H[i] = -1;
	}

	current_euler_index = 0;
	current_euler_level = 0;
	return 0;
}
int convertTree(struct node *tree, int N, int *T)
{
	int root = -1;
	int i = 0;

	for (i = 0; i < N; ++i)
	{
		tree[i].left = -1;
		tree[i].right = -1;
	}

	for (i = 0; i < N; ++i)
	{
		if (T[i] == -1)
		{
			root = i;
			continue;
		}
		else
		{
			if (tree[T[i]].left == -1)
			{
				tree[T[i]].left = i;
			}
			else
			{
				tree[T[i]].right = i;
			}
		}
	}

	for (i = 0; i < N; ++i)
	{
		printf("father:%d left:%d right:%d\n", T[i], tree[i].left, tree[i].right);
	}

	return root;
}
void computeTree(int *A, int N, int *T)
{
	int st[MAXNODE], i, k, top = -1;

	//we start with an empty stack
	//at step i we insert A[i] in the stack
	for (i = 0; i < N; i++)
	{
		//compute the position of the first element that is
		//equal or smaller than A[i]
		k = top;

		while (k >= 0 && A[st[k]] > A[i])
			k--;

		//we modify the tree as explained above
		if (k != -1)
			T[i] = st[k];

		if (k < top)
			T[st[k + 1]] = i;

		//we insert A[i] in the stack and remove
		//any bigger elements
		st[++k] = i;
		top = k;
	}

	//the first element in the stack is the root of
	//the tree, so it has no father
	T[st[0]] = -1;
}
int add_node(int node, int level)
{
	E[current_euler_index] = node;
	L[current_euler_index] = level;

	if (H[node] == -1)
	{
		H[node] = current_euler_index;
	}

	++current_euler_index;
	return 0;
}
int euler(int *T, struct node *tree, int node)
{
	if (node == -1)
	{
		return 0;
	}

	add_node(node, current_euler_level);
	++current_euler_level;

	if (tree[node].left != -1)
	{
		euler(T, tree, tree[node].left);
		add_node(node, current_euler_level - 1);
	}

	if (tree[node].right != -1)
	{
		euler(T, tree, tree[node].right);
		add_node(node, current_euler_level - 1);
	}

	--current_euler_level;
	return 0;
}
int preorder(int *T, struct node *tree, int node)
{
	if (node == -1)
	{
		return 0;
	}

	printf("pre order:%d\n", node);
	preorder(T, tree, tree[node].left);
	preorder(T, tree, tree[node].right);
	return 0;
}
int inorder(int *T, struct node *tree, int node)
{
	if (node == -1)
	{
		return 0;
	}

	inorder(T, tree, tree[node].left);
	printf("in order:%d\n", node);
	inorder(T, tree, tree[node].right);
	return 0;
}
int postorder(int *T, struct node *tree, int node)
{
	if (node == -1)
	{
		return 0;
	}

	postorder(T, tree, tree[node].left);
	postorder(T, tree, tree[node].right);
	printf("in order:%d\n", node);
	return 0;
}
int rmq(int *A, int left, int right)
{
	int res = 0;
	printf("left:%d H:%d A:%d\n", left, H[left], A[left]);
	printf("right:%d H:%d A:%d\n", right, H[right], A[right]);
	printf("rmq:%d H:%d A:%d\n", res, H[res], A[res]);
	return res;
}
void print_euler_result(int N)
{
	int i = 0;

	for (i = 0; i < 2 * N - 1; ++i)
	{
		printf("%d\t", E[i]);
	}

	puts("");

	for (i = 0; i < 2 * N - 1; ++i)
	{
		printf("%d\t", L[i]);
	}

	puts("");

	for (i = 0; i < N; ++i)
	{
		printf("%d\t", H[i]);
	}

	puts("");
}
int main(void)
{
#define N 10
	int A[N] = {100, 10, 90, 20, 80, 30, 70, 40, 60, 50};
	int T[N] = {0};
	computeTree(A, N, T);
	struct node tree[MAXNODE];
	int root = convertTree(tree, N, T);
	init_euler(N);
	euler(T, tree, root);
	print_euler_result(N);
	int res = rmq(A, 5, 8);
	printf("res:%d\n", res);
	return EXIT_SUCCESS;
}
