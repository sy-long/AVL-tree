#ifndef AVLTREE_H
#define AVLTREE_H

typedef int type;

typedef struct Treenode
{
	type key;
	int height;
	Treenode * rchild;
	Treenode * lchild;
}node, *pnode;

pnode creat_node(type, pnode, pnode);

//int get_height(const node *);

//int get_max(const node*, const node*);

//pnode l_rotation(node *);

//pnode r_rotation(node *);

//pnode l_r_rotation(node *);

//pnode r_l_rotation(node *);

pnode insert(node *, type);

pnode delete_node(node *, type);

//type get_maxnode(node *);

//type get_minnode(node *);

void show_tree(node *);

#endif
