#include "avltree_h.h"
#include <stdio.h>
#include <stdlib.h>
int main()
{
	pnode node = NULL;
	int chiose;
	int key;
	while (1)
	{
		printf("1.����ڵ�\n");
		printf("2.ɾ���ڵ�\n");
		printf("3.�˳�");
		printf("\n\n");
		printf("������:");
		scanf("%d", &chiose);
		switch (chiose)
		{
		case 1:
		{
			printf("������Ҫ���������:");
			scanf("%d", &key);
			node = insert(node, key);
			printf("\n");
			show_tree(node);
		}
			break;
		case 2:
			printf("������Ҫɾ��������:");
			scanf("%d", &key);
			node = delete_node(node, key);
			printf("\n");
			show_tree(node);
			break;
		case 3:exit(0);
			break;
		default:
			break;
		}
	}
	return 0;
}
