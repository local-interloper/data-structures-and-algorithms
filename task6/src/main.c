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

typedef struct
{
	Node *nodes;
	size_t count;
} PriortiyQueue;

PriortiyQueue new_priority_queue()
{
	PriortiyQueue queue = {
		.nodes = (Node *)calloc(N, sizeof(Node)),
		.count = 0};

	return queue;
}

void print_node(Node *node)
{
	printf("{%d}", node->priority);
}

void print_nodes(PriortiyQueue *queue)
{
	Node *nodes = queue->nodes;
	for (int i = 0; i < queue->count; i++)
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

void fix_tree_iter(Node *nodes, size_t count)
{
	for (int _ = 0; _ < count; _++)
	{
		for (int index = 0; index < count; index++)
		{
			int parent_index = PARENT(index);
			if (nodes[parent_index].priority < nodes[index].priority)
			{
				swap_nodes(nodes, parent_index, index);
			}
		}
	}
}

void fix_tree_rev(Node *nodes, int index, int size)
{

	int l = LEFT_CHILD(index);
	int d = RIGHT_CHILD(index);

	if (l >= size && index >= size)
	{
		return;
	}

	if (index >= size && l < size && nodes[l].priority > nodes[index].priority)
	{
		swap_nodes(nodes, index, l);
		return;
	}

	if (nodes[index].priority < nodes[l].priority || nodes[index].priority < nodes[d].priority)
	{
		if (nodes[l].priority > nodes[d].priority)
		{
			swap_nodes(nodes, index, l);
			fix_tree_rev(nodes, l, size);
			return;
		}
		else
		{
			swap_nodes(nodes, index, d);
			fix_tree_rev(nodes, d, size);
			return;
		}
	}

}

void fix_tree_rev_iter(Node *nodes, size_t count)
{
	for (int _ = 0; _ < count; _++)
	{
		for (int index = 0; index < count; index++)
		{
			int l = LEFT_CHILD(index);
			int d = RIGHT_CHILD(index);

			if (l >= count && index >= count)
			{
				continue;
			}

			if (index >= count && l < count && nodes[l].priority > nodes[index].priority)
			{
				swap_nodes(nodes, index, l);
				continue;
			}

			if (nodes[index].priority < nodes[l].priority || nodes[index].priority < nodes[d].priority)
			{
				if (nodes[l].priority > nodes[d].priority)
				{
					swap_nodes(nodes, index, l);
					continue;
				}
				else
				{
					swap_nodes(nodes, index, d);
					continue;
				}
			}
		}
	}
}

void add(PriortiyQueue *queue, int value)
{
	Node *nodes = queue->nodes;
	nodes[queue->count].priority = value;

	fix_tree(nodes, queue->count);
	// fix_tree_iter(nodes, queue->count);

	queue->count++;
}

void delete (PriortiyQueue *queue)
{
	Node *nodes = queue->nodes;
	int size = queue->count;

	nodes[0].priority = nodes[size - 1].priority;
	nodes[size - 1].priority = 0;

	fix_tree_rev(nodes, 0, size);
	// fix_tree_rev_iter(nodes, size);

	queue->count--;
}

int main()
{
	// Node *nodes[N];
	PriortiyQueue queue = new_priority_queue();

	add(&queue, 50);
	add(&queue, 20);
	add(&queue, 80);
	add(&queue, 85);
	add(&queue, 60);
	add(&queue, 25);
	add(&queue, 30);
	add(&queue, 70);
	add(&queue, 23);
	add(&queue, 10);
	print_nodes(&queue);
	delete (&queue);
	delete (&queue);
	delete (&queue);
	delete (&queue);
	print_nodes(&queue);

	return 0;
}