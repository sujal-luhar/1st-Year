#include<stdio.h>
#include <stdlib.h>

void swap(int arr[], int first, int second)
{
	int auxiliary = arr[first];
	arr[first] = arr[second];
	arr[second] = auxiliary;
}

int compare( int arr[], int left, int right, int root, int size)
{
	int location = -1;
	if ((left < size && arr[left] < arr[root]))
	{
		if ((right < size && arr[right] < arr[left]))
		{
			swap(arr, right, root);
			location = right;
		}
		else
		{
			swap(arr, left, root);
			location = left;
		}
	}
	else if ((right < size && arr[right] < arr[root]))
	{
		swap(arr, right, root);
		location = right;
	}
	return location;
}
void heap(int arr[], int size, int root)
{
	int left = 2 * root + 1;
	int right = 2 * root + 2;
	int step =compare(arr, left, right, root, size);
	if ((step != -1))
	{
		// Need to convert into min heap
		heap(arr, size, step);
	}
}
void minHeapImp(int arr[], int size)
{
	// Get middle of given array
	int i = (size / 2) - 1;
	while (i >= 0)
	{
		heap(arr, size, i);
		i--;
	}
}
void printData(int arr[], int size)
{
	int i = 0;
	while (i < size)
	{
		printf(" %d  ", arr[i]);
		i++;
	}
	printf("\n");
}

struct huffman_node {
    char data;
    unsigned int frequency;
    struct huffman_node *left;
    struct huffman_node *right;
};
typedef struct huffman_node huffman_node;
 
huffman_node *huffman_node_create(char data, unsigned int frequency)
{
    huffman_node *node = malloc(sizeof(huffman_node));
    if (node) {
        node->data = data;
        node->frequency = frequency;
        node->left = NULL;
        node->right = NULL;
    }
    return node;
}
 
void huffman_node_delete(huffman_node *node)
{
    if (node) {
        huffman_node_delete(node->left);
        huffman_node_delete(node->right);
        free(node);
    }
}
 
unsigned int max(unsigned int a, unsigned int b)
{
    return a > b ? a : b;
}
 
unsigned int huffman_node_height(const huffman_node *node)
{
    unsigned int height = 0;
    if (node->left || node->right) {
        height = max(node->left ? huffman_node_height(node->left) : 0,
                node->right ? huffman_node_height(node->right) : 0) + 1;
    }
    return height;
}
 
void huffman_node_print(const huffman_node *node, unsigned int indent)
{
    unsigned int i;
    for (i = 0; i < indent; i++) {
        printf("  ");
    }
    printf("%c %u\n", node->data, node->frequency);
    if (node->left != NULL) {
        huffman_node_print(node->left, indent + 1);
    }
    if (node->right != NULL) {
        huffman_node_print(node->right, indent + 1);
    }
}
 
typedef void huffmanfn(char, const unsigned int *, size_t);
 
void huffman_node_encodings(const huffman_node *node, unsigned int *arr, 
        unsigned int pos, huffmanfn fun)
{
    if (node->left) {
        arr[pos] = 0;
        huffman_node_encodings(node->left, arr, pos + 1, fun);
    }
    if (node->right) {
        arr[pos] = 1;
        huffman_node_encodings(node->right, arr, pos + 1, fun);
    }
    if (!(node->left || node->right)) {
        fun(node->data, arr, pos);
    }
}
 
void huffman(const char *letters, const int *frequencies, size_t size, huffmanfn fun)
{
    minheap *heap = minheap_create();
    unsigned int i;
    huffman_node *top;
    unsigned int *arr;
    /* Populate the heap */
    for (i = 0; i < size; i++) {
        minheap_add(heap, huffman_node_create(letters[i], frequencies[i]), frequencies[i]);
    }
    /* Build the tree */
    while (minheap_get_count(heap) != 1) {
        huffman_node *left = minheap_remove_min(heap);
        huffman_node *right = minheap_remove_min(heap);
        top = huffman_node_create('$', left->frequency + right->frequency);
        top->left = left;
        top->right = right;
        minheap_add(heap, top, top->frequency);
    }
    top = minheap_remove_min(heap);
    /* Generate the encodings */
    arr = malloc(huffman_node_height(top) * sizeof(unsigned int));
    huffman_node_encodings(top, arr, 0, fun);
    /* Clean up */
    huffman_node_delete(top);
    free(arr);
    minheap_delete(heap);
}

void print(char letter, const unsigned int *arr, size_t len)
{
    unsigned int i;
    printf("%c: ", letter);
    for (i = 0; i < len; i++) {
        printf("%u", arr[i]);
    }
    putchar('\n');
}
 
int main(void)
{
    char letters[] = {'a', 'b', 'c', 'd', 'e', 'f'};
    int frequencies[] = {45, 13, 12, 16, 9, 5};
    const size_t size = sizeof(letters) / sizeof(letters[0]);
    huffman(letters, frequencies, size, print);
    return 0;
}
