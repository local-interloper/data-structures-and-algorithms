#include <stdio.h>
#include <stdlib.h>

#define N 10000

#define PARENT(i) (i - 1) / 2
#define LEFT_CHILD(i) 2 * i + 1
#define RIGHT_CHILD(i) 2 * i + 2

typedef struct
{
	int priority;
	void *data;
} Node;

Node *create_priority_queue() {
	return (Node *)calloc(N, sizeof(Node));
}

void print_node(Node *node)
{
	printf("{%d}", node->priority);
}

void print_nodes(Node *nodes, size_t length)
{
	for (int i = 0; i < length; i++)
	{
		print_node(nodes + i);
	}
	puts("");
}

void swap_nodes(Node *nodes, int i, int j)
{
	Node tmp = nodes[i];
	*(nodes + i) = nodes[j];
	*(nodes + j) = tmp;
}

void fix_tree(Node *nodes, int index)
{
	int parent_index = PARENT(index);
	if (nodes[parent_index].priority < nodes[index].priority)
	{
		swap_nodes(nodes, parent_index, index);
		fix_tree(nodes, parent_index);
	}
}

void fix_tree_rev(Node *nodes, int r, int size)
{

	int l = LEFT_CHILD(r);
	int d = RIGHT_CHILD(r);

    if (l >= size && r >= size)
    {
        return;
    }

    if (r >= size && l < size && nodes[l].priority > nodes[r].priority)
    {
		swap_nodes(nodes, r, l);
		return;
    }

    if (nodes[r].priority < nodes[l].priority && nodes[r].priority < nodes[d].priority)
    {
        if (nodes[l].priority > nodes[d].priority)
        {
			swap_nodes(nodes, r, l);
            fix_tree_rev(nodes, l, size);
			return;
        }
        else
        {
			swap_nodes(nodes, r, d);
            fix_tree_rev(nodes, d, size);
			return;
        }
    }
}

void add(Node *nodes, int *p_size, int value)
{
	int size = *p_size;
	nodes[size].priority = value;
	fix_tree(nodes, size);
	(*p_size)++;
}

int delete(Node *nodes, int* p_size)
{
	int size = *p_size;
    nodes[0].priority = nodes[size - 1].priority;
    nodes[size - 1].priority = 0;
    fix_tree_rev(nodes, 0, size);
	(*p_size)--;
}

int main()
{
	// Node *nodes[N];
	Node *nodes = create_priority_queue();
	int size = 0;

	add(nodes, &size, 50);
	add(nodes, &size, 20);
	add(nodes, &size, 80);
	add(nodes, &size, 85);
	add(nodes, &size, 60);
	add(nodes, &size, 25);
	add(nodes, &size, 30);
	add(nodes, &size, 70);
	add(nodes, &size, 23);
	add(nodes, &size, 10);
	print_nodes(nodes, size);
	delete(nodes, &size);
	delete(nodes, &size);
	delete(nodes, &size);
	delete(nodes, &size);
	delete(nodes, &size);
	delete(nodes, &size);
	delete(nodes, &size);
	delete(nodes, &size);
	print_nodes(nodes, size);

	return 0;
}