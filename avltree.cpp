#include "avltree_h.h"
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Quene_node
{
	pnode key;
	Quene_node *next;
	int level;
	int step;
}quene_node, *pquene_node;

typedef struct Queue
{
	Quene_node *front;
	Quene_node *fail;
}queue,*pqueue;

pnode creat_node(type key, pnode lchild, pnode rchild)
{
	pnode p;
	p = (pnode)malloc(sizeof(node));
	p->key = key;
	p->height = 0;
	p->lchild = NULL;
	p->rchild = NULL;

	return p;
}

int get_height(const node *p)
{
	return p == NULL ? 0 : p->height;
}

int get_max(const node *p, const node *p1)
{
	return get_height(p) > get_height(p1) ? get_height(p) : get_height(p1);
}

pnode l_rotation(node * k1)
{
	pnode k2;

	k2 = k1->rchild;
	k1->rchild = k2->lchild;
	k2->lchild = k1;

	k1->height = get_max(k1->lchild, k1->rchild) + 1;
	k2->height = get_max(k2->lchild, k2->rchild) + 1;
	
	return k2;
}

pnode r_rotation(node *k1)
{
	pnode k2;

	k2 = k1->lchild;
	k1->lchild = k2->rchild;
	k2->rchild = k1;

	k1->height = get_max(k1->lchild, k1->rchild) + 1;
	k2->height = get_max(k2->lchild, k2->rchild) + 1;

	return k2;
}

pnode l_r_rotation(node *k1)
{
	k1->lchild = l_rotation(k1->lchild);
	return r_rotation(k1);
}

pnode r_l_rotation(node *k1)
{
	k1->rchild = r_rotation(k1->rchild);
	return l_rotation(k1);
}

pnode insert(node *p, type key)
{
	if (p == NULL)
	{
		p = creat_node(key, NULL, NULL);
	}
	else if (key < p->key)
	{
		p->lchild = insert(p->lchild, key);

		if (get_height(p->lchild) - get_height(p->rchild) == 2)
			if (key < p->lchild->key)
				p = r_rotation(p);
			else
				p = l_r_rotation(p);
	}
	else if (key > p->key)
	{
		p->rchild = insert(p->rchild, key);

		if (get_height(p->rchild) - get_height(p->lchild) == 2)
			if (key > p->rchild->key)
				p = l_rotation(p);
			else
				p = r_l_rotation(p);
	}
	else
	{
		printf("插入失败,不准插入key相同的节点!\n");
	}

	p->height = get_max(p->lchild, p->rchild) + 1;

	return p;
}

type get_maxnode(node *p)
{
	while (p->rchild)
		p = p->rchild;
	return p->key;
}

type get_minnode(node *p)
{
	while (p->lchild)
		p = p->lchild;
	return p->key;
}

pnode delete_node(node *p, type key)
{
	if (p == NULL)
	{
		printf("删除失败,没有该元素!");
		return NULL;
	}

	if (key < p->key)
	{
		p->lchild = delete_node(p->lchild, key);

		if (get_height(p->rchild) - get_height(p->lchild) == 2)
			if (get_height(p->rchild->lchild) > get_height(p->rchild->rchild))
				p = r_l_rotation(p);
			else
				p = l_rotation(p);
	}
	else if (key > p->key)
	{
		p->rchild = delete_node(p->rchild, key);
		if (get_height(p->lchild) - get_height(p->rchild) == 2)
			if (get_height(p->lchild->rchild) > get_height(p->lchild->lchild))
				p = l_r_rotation(p);
			else
				p = r_rotation(p);
	}
	else
	{
		if ((p->lchild) && (p->rchild))
		{
			if (get_height(p->lchild) > get_height(p->rchild))
			{
				type max = get_maxnode(p->lchild);
				p->key = max;
				p->lchild = delete_node(p->lchild, max);
			}
			else
			{
				type min = get_minnode(p->rchild);
				p->key = min;
				p->rchild = delete_node(p->rchild, min);
			}
		}
		else
		{
			pnode temp = p;
			p = p->lchild ? p->lchild : p->rchild;
			free(temp);
		}
	}
	if (p != NULL)
		p->height = get_max(p->lchild, p->rchild) + 1;

	return p;
}

pqueue creat_queue()
{
	pqueue q = (pqueue)malloc(sizeof(queue));
	q->fail = NULL;
	q->front = NULL;
	return q;
}

void push(queue *q, node *p,int level,int step)
{
	pquene_node temp = (pquene_node)malloc(sizeof(quene_node));
	temp->key = p;
	temp->next = NULL;
	temp->level = level;
	temp->step = step;
	if (q->fail == NULL && q->front == NULL)
	{
		q->front = q->fail = temp;
	}
	else
	{
		q->fail->next = temp;
		q->fail = temp;
	}
}

pquene_node pop(queue * q)
{
	pquene_node temp = (pquene_node)malloc(sizeof(quene_node));
	temp = q->front;
	q->front = q->front->next;
	if (q->front == NULL)
		q->fail = NULL;
	return temp;
}

void show_tree(node *p)
{
	system("mode con cols=200 lines=50");
	pqueue q = creat_queue();
	push(q, p, 0, 100);
	int level = 0;
	int step = 50;
	while (!(q->fail == NULL && q->front == NULL))
	{
		pquene_node t = pop(q);
		if (t->level == level)
			printf("%*d\r", t->step, t->key->key);
		else
		{
			printf("\n\n");
			printf("%*d\r", t->step, t->key->key);
			level++;
			step = step / 2;
		}
		if (t->key->rchild != NULL)
			push(q, t->key->rchild, t->level + 1, t->step + step);
		if (t->key->lchild != NULL)
			push(q, t->key->lchild, t->level + 1, t->step - step);
		free(t);
	}
	printf("\n\n");
}