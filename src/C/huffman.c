#include "stdio.h"
#include "huffman.h"

typedef struct {
  unsigned short frequency;
  unsigned char left, right;
} node;
node nodes[512];
char values[256];

#define SIZE 256

void merge(node *arr1, node *arr2, int left, int mid, int right) {
  int i, j = mid + 1, k = left;

  for (i = left; i <= mid && j <= right; k++)
    if (arr1[i].frequency <= arr1[j].frequency)
      arr2[k] = arr1[i++];
    else
      arr2[k] = arr1[j++];

  for (;i <= mid; i++, k++)
    arr2[k] = arr1[i];

  for (;j <= right; j++, k++)
    arr2[k] = arr1[j];
}

void mergeSort(node *arr1, node *arr2, int left, int right) {
  if (left < right) {
    int mid = left + (right - left) / 2;
    mergeSort(arr2, arr1, left, mid);
    mergeSort(arr2, arr1, mid + 1, right);
    merge(arr2, arr1, left, mid, right);
  }
}

void sort() {
  node tmp_arr[SIZE];  // Auxiliary arrays
  mergeSort(nodes, tmp_arr, 0, SIZE - 1);
}

void resetNodes() {
  for (int i = 0; i < 256; i++)
    nodes[i] = (node) { .frequency=0, .left=i, .right=0 };
}

void countFrequency(unsigned char *data, long size) {
  for (long i = 0; i < size; i++)
    nodes[(unsigned char)data[i]].frequency ++;
}


#define create_node(a, b) write_nodes_idx++;nodes[write_nodes_idx] = ( node){ .frequency=nodes[a].frequency + nodes[b].frequency, .left=write_nodes_idx - a, .right=write_nodes_idx - b }

// Returns the index to the root
int huffmanMerge() {
  int i =  0;
  int read_nodes_idx = 256, write_nodes_idx = 255;
  while (nodes[i].frequency == 0) i++;
  unsigned int a = i, b = i + 1;
  if (i == 255) {
    create_node(a, a);
    return 0;
  }
  create_node(a, b); // KNOW BUG: FOR i = 0 => a = 256 - 0 = 0
  i += 2;

  while (i < 256) {
    // First step: Getting a
    if (nodes[read_nodes_idx].frequency > nodes[i].frequency)
      a = i++;
    else
      a = read_nodes_idx++;

    // And then, b
    if (i < 256 && (read_nodes_idx > write_nodes_idx || nodes[read_nodes_idx].frequency > nodes[i].frequency))
      b = i++;
    else
      b = read_nodes_idx++;

    // Make a new node
    create_node(a, b);
  }
  while (read_nodes_idx < write_nodes_idx) {
    create_node(read_nodes_idx, (read_nodes_idx + 1));
    read_nodes_idx += 2;
  }
  return write_nodes_idx;
}

void printBits(int v, int count) {
  while (count--)
    printf((v >> count) & 1 ? "1" : "0");
}
void showNodes(int root, int v, int count) {
  if (root <= 255) {
    printf("%c: ", nodes[root].left);
    printBits(v, count);
    printf("\n");
    return;
  }
  v <<= 1;
  if (nodes[root].left) showNodes(root - (int)nodes[root].left, v | 1, count + 1);
  if (nodes[root].right) showNodes(root - (int)nodes[root].right, v, count + 1);
}


char TEXT[] = "Hello world!\
I'm a programer\
No ?";


void huffmanTests() {
  resetNodes();
  countFrequency(TEXT, sizeof(TEXT));
  sort();

  printf("{ ");
  for (int i = 256; i >= 0; i--)
    if (nodes[i].frequency)
      printf("%c: %d,", nodes[i].left, nodes[i].frequency);
  printf(" }\n");

  int root = huffmanMerge();
  printf("Root: %d\n", root);

  showNodes(root, 0, 0);

}