#include <lcthw/bstree.h>
#include <lcthw/dbg.h>
#include <lcthw/bstrlib.h>
#include <stdlib.h>

static int default_compare(void *a, void *b)
{
	return bstrcmp((bstring) a, (bstring) b);
}

BSTree *BSTree_create(BSTree_compare compare)
{
	BSTree *map = calloc(1, sizeof(BSTree));
	check_mem(map);
	
	map->compare = compare == NULL ? default_compare : compare;

	return map;
error:
	if(map) {
		BSTree_destroy(map);
	}
	return NULL;
}

static int BSTree_destroy_cb(BSTreeNode *node)
{
	free(node);
	return 0;
}

void BSTree_destroy(BSTree *map)
{
	if(map) {
		BSTree_traverse(map, BSTree_destroy_cb);
		free(map);
	}
}

static inline int BSTree_traverse_nodes(BSTreeNode *node, 
					BSTree_traverse_cb traverse_cb)
{
	int rc = 0;
	
	if(node->left) {
		rc = BSTree_traverse_nodes(node->left, traverse_cb);
		if(rc != 0)
			return rc;
	}
	
	if(node->right) {
		rc = BSTree_traverse_nodes(node->right, traverse_cb);
		if(rc != 0)
			return rc;
	}
	
	return traverse_cb(node);
}

int BSTree_traverse(BSTree * map, BSTree_traverse_cb traverse_cb)
{
	if(map->root) {
		return BSTree_traverse_nodes(map->root, traverse_cb);
	}
	
	return 0;
}

static inline BSTreeNode *BSTreeNode_create(BSTreeNode * parent, void *key, void *data)
{
	BSTreeNode *node = calloc(1, sizeof(BSTreeNode));
	check_mem(node);

	node->key = key;
	node->data = data;
	node->parent = parent;
	return node;

error:
	return NULL;
}
//again recursive technique
static inline void BSTree_setnode(BSTree * map, BSTreeNode * node,
				void *key, void *data)
{
	int cmp = map->compare(node->key, key);

	if (cmp <= 0) {
		if (node->left) {
			BSTree_setnode(map, node->left, key, data);
		} else {
			node->left = BSTreeNode_create(node, key, data);
		}
	} else {
		if (node->right) {
			BSTree_setnode(map, node->right, key, data);
		} else {
			node->right = BSTreeNode_create(node, key, data);
		}
	}
}

int BSTree_set(BSTree *map, void *key, void *data)
{
	if(map->root == NULL) {
	// first so just make it and get out
	map->root = BSTreeNode_create(NULL, key, data);
	check_mem(map->root);
	} else {
		BSTree_setnode(map, map->root, key, data);
	}
	
	return 0;
error:
	return -1;
}
