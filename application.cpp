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
		printf("1.插入节点\n");
		printf("2.删除节点\n");
		printf("3.退出");
		printf("\n\n");
		printf("请输入:");
		scanf("%d", &chiose);
		switch (chiose)
		{
		case 1:
		{
			printf("请输入要插入的数据:");
			scanf("%d", &key);
			node = insert(node, key);
			printf("\n");
			show_tree(node);
		}
			break;
		case 2:
			printf("请输入要删除的数据:");
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
