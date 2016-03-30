#include <stdlib.h>
#include <vector>
#include <fstream>
#include <string>
#include <cstring>
#include <sstream>
#include <iostream>
#include <pthread.h>
using namespace std;

int arrSize = 0;

/*struct maximum
{
	int max;
};

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *find_max(void *params) {
	struct maximum *m;
	int count;
	int *arr;
	arr = params;
	if(arr == NULL)
		return NULL;
	m = malloc(sizeof(struct maximum));
	if (m == NULL)
		return NULL;
	pthread_mutex_lock(&mutex);


}*/

int maxElement(int a[], int left, int right) {
	if (right - left == 1) return a[left];
	int mid = (left+right)/2;
	int leftMax = maxElement(a, left, mid);
	int rightMax = maxElement(a, mid, right);
	if (leftMax > rightMax) return leftMax;
	else return rightMax;
}

int main(int argc, char *argv[]) {
	int tmp, n = 0;
	int a[4096];
	if (argc != 2) {
		cout << "Incorrect number of arguments!" <<endl;
	} else if (strcmp(argv[1], "inData.txt") != 0) {
		cout << "Wrong file" << endl;
	} else {
		
		ifstream file(argv[1]);
		while(file >> tmp) {
			a[n] = tmp;
			n++;
		}
		arrSize = n;
		tmp = maxElement(a, 0, n);
		cout << arrSize << endl;
		//delete(a);
	}
	return 0;
}
