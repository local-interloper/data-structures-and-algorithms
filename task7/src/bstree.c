#include <stdio.h>
#include <malloc.h>
#include "bstree.h"

BSTree NewBSTree()
{
	Node *n = (Node *)malloc(sizeof(Node));
	n->left = NULL;
	n->right = NULL;
	n->word = NULL;

	return (BSTree *)n;
}

void AddNode(BSTree *bst, char *word)
{
	// Rekurzivno se tra�i mjesto za novi �vor u stablu. Ako rije� postoji u stablu, ne dodaje se.
	// bst parametar je dvostruki pokaziva�.

	Node *node = (Node *)*bst;

	if (node->word == NULL)
	{
		node->word = (char *)malloc(sizeof(char) * (strlen(word) + 1));
		strcpy(node->word, word);
		return;
	}

	int result = strcmp(node->word, word);

	if (result == 0)
	{
		return;
	}

	if (result > 0)
	{
		if (node->left == NULL)
		{
			Node *n = (Node *)NewBSTree();
			n->word = (char *)malloc(sizeof(char) * (strlen(word) + 1));
			strcpy(n->word, word);

			node->left = n;

			return;
		}

		AddNode(&node->left, word);
	}

	if (result < 0)
	{
		if (node->right == NULL)
		{
			Node *n = (Node *)calloc(1, sizeof(Node));
			n->word = (char *)malloc(sizeof(char) * (strlen(word) + 1));
			strcpy(n->word, word);

			node->right = n;

			return;
		}

		AddNode(&node->right, word);
	}
}

int BSTHeight(BSTree bst)
{
	// Rekurzivno se prolazi cijelo stablo da bi se prona�la najdu�a grana (visina stabla).
	Node *node = (Node *)bst;

	if (node == NULL)
	{
		return 0;
	}

	int lDepth = BSTHeight(node->left);
	int rDepth = BSTHeight(node->right);

	return (lDepth > rDepth ? lDepth : rDepth) + 1;
}

void PrintBSTree(BSTree bst)
{
	// Ispisuje rije�i u stablu na ekran po abecednom redu.
	// In-order �etnja po stablu (lijevo dijete, �vor, desno dijete)

	Node *node = (Node *)bst;

	if (node->left != NULL)
	{
		PrintBSTree(node->left);
	}

	printf("%s\n", node->word);

	if (node->right != NULL)
	{
		PrintBSTree(node->right);
	}
}

void SaveBSTree(BSTree bst, FILE *fd)
{
	// Snima rije� po rije� iz stabla u tekstualnu datoteku. Rije�i su odvojene razmakom.
	// Pre-order �etnja po stablu (ttenutni �vor pa djeca)
	Node *node = (Node *)bst;

	fpos_t pos;
	fgetpos(fd, &pos);

	if (node == NULL)
	{
		return;
	}

	fwrite(bst->word, sizeof(char), strlen(bst->word), fd);

	if (node->left != NULL)
	{
		fputc(' ', fd);
		SaveBSTree(node->left, fd);
	}

	if (node->right != NULL)
	{
		fputc(' ', fd);
		SaveBSTree(node->right, fd);
	}
}

void DeleteBSTree(BSTree bst)
{
	// Bri�e stablo (string word i sam �vor) iz memorije.
	// Post-order �etnja po stablu (prvo djeca pa trenutni �vor)

	Node *node = (Node *)bst;

	if (node->left == NULL)
	{
		DeleteBSTree(node->left);
	}

	if (node->right == NULL)
	{
		DeleteBSTree(node->right);
	}

	free(node->word);
	free(node);
}

BSTree LoadBSTree(FILE *fd)
{
	// U�itava rije� po rije� iz tekstualne datoteke i dodaje ih u stablo preko AddNode() funkcije.
	// Rije� duplicirati sa strdup().

	BSTree tree = NewBSTree();

	char buff[512] = "";

	while (1)
	{
		int c = fgetc(fd);

		if (c == EOF)
		{
			break;
		}

		if (c == ' ')
		{
			AddNode(&tree, buff);
			buff[0] = '\0';
			continue;
		}

		strncat(buff, &c, 1);
	}

	return tree;
}
