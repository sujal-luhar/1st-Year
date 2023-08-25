// C program for Huffman Coding
#include <stdio.h>
#include <stdlib.h>

struct Node {
	char data;
	int freq;
	struct Node *left, *right;
};

struct Heap {
	int size;
	int capacity;
	struct Node** nodes;
};

struct Node* newNode(char data, int freq)
{
	struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
	temp->left = temp->right = NULL;
	temp->data = data;
	temp->freq = freq;
	return temp;
}

struct Heap* formingHeap(int capacity)
{
	struct Heap* heap= (struct Heap*)malloc(sizeof(struct Heap));
	heap->size = 0;
	heap->capacity = capacity;
	heap->nodes = (struct Node**)malloc(heap->capacity * sizeof(struct Node*));
	return heap;
}

struct Heap* finalHeap(char data[],int freq[], int size)//O(n lg n)
{
	struct Heap* heap = formingHeap(size);
	int i;
	for (i = 0; i < size; ++i)
		heap->nodes[i] = newNode(data[i], freq[i]);
		
	heap->size = size;
	int n = heap->size - 1;
	
	for (i = (n - 1) / 2; i >= 0; --i)
		Heapify(heap, i);

	return heap;
}

void Heapify(struct Heap* heap, int i)//O(lg n)
{
	int smallest = i;
	int left = 2 * i + 1;
	int right = 2 * i + 2;

	if (left < heap->size
		&& heap->nodes[left]->freq
			< heap->nodes[smallest]->freq)
		smallest = left;

	if (right < heap->size
		&& heap->nodes[right]->freq
			< heap->nodes[smallest]->freq)
		smallest = right;

	if (smallest != i) {
		struct Node* t = heap->nodes[smallest];
		heap->nodes[smallest] = heap->nodes[i];
		heap->nodes[i] = t;
		
		Heapify(heap, smallest);
	}
}

struct Node* extractroot(struct Heap* heap)//O(n)
{
	struct Node* temp = heap->nodes[0];
	heap->nodes[0] = heap->nodes[heap->size - 1];
	--heap->size;
	Heapify(heap, 0);
	return temp;
}

void HeapAtOwnPlace(struct Heap* heap,struct Node* node)//O(ln n)
{
	++heap->size;
	int i = heap->size - 1;

	while (i
		&& node->freq
				< heap->nodes[(i - 1) / 2]->freq) {

		heap->nodes[i] = heap->nodes[(i - 1) / 2];
		i = (i - 1) / 2;
	}
	heap->nodes[i] = node;
}

void printCodes(struct Node* root, int arr[],int top)//O(n)
{	
	int i;
	if (root->left) {

		arr[top] = 0;
		printCodes(root->left, arr, top + 1);
	}

	if (root->right) {

		arr[top] = 1;
		printCodes(root->right, arr, top + 1);
	}
	if (!(root->left) && !(root->right)) {

		printf("%c: ", root->data);
		
		for (i = 0; i < top; ++i)
			printf("%d", arr[i]);
			
		printf("\n");
	}
}

void HuffmanCodes(char data[], int freq[], int size)//O(n lg n)
{
	struct Node *l, *r, *top;
	struct Heap* heap= finalHeap(data, freq, size);
	while (!(heap->size == 1)) {

		l = extractroot(heap);
		r = extractroot(heap);
		top = newNode('.', l->freq + r->freq);

		top->left = l;
		top->right = r;

		HeapAtOwnPlace(heap, top);
	}
	
	
	struct Node* root= extractroot(heap);
	int arr[30], top_code = 0;

	printCodes(root, arr, top_code);
}

int main()
{
	char a[] = { 'l', 'j', 'u', 'n', 'i', 'v', 'e', 'r', 'c', 't' };
	int freq[] = { 27, 3, 40, 18, 15, 8, 55, 34, 23, 34 };
	int size = sizeof(a) / sizeof(a[0]);
	HuffmanCodes(a, freq, size);
	return 0;
}

