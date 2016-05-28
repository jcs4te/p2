#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>

int remaining = 0, ret = -1;
std::vector<int> workSet;
std::vector<int> curSet;
struct thread_args
{
	int i1;
	int i2;

};

pthread_mutex_t mutex, valtex;
pthread_cond_t cond;

void* find_max(void *);



int Log2(int n) {
	int ans = 0;
	while (n>>=1) ans++;
	return ans;
}


int main(int argc, char *argv[])
{
	pthread_mutex_init(&mutex, NULL);
	pthread_mutex_init(&valtex, NULL);
	pthread_cond_init(&cond, NULL);
	int integers[8];
	int i = 0, tmp;
	std::ifstream read("inData.txt");
	while(read >> tmp) {
		workSet.push_back(tmp);
		i++;
	}
	printf("%d\n", i);
	int rounds = Log2(i);
	int to_process = i;
	pthread_t t_ids[i/2];
	int thread_size = 0;
	struct thread_args *t_args;
	//rounds = Log2(i);
	//workSet.assign(integers, integers+i);
	while(rounds != 0) {
		remaining = (to_process)/2;
		for (int val = 0; val < to_process; val+=2) {
			t_args = malloc(sizeof(struct thread_args));
			(*t_args).i1 = workSet[val];
			(*t_args).i2 = workSet[val+1];
			//printf("i1: %d\ni2: %d\n", t_args.i1, t_args.i2);
			pthread_create(&t_ids[thread_size], NULL, find_max, (void*)t_args);
			thread_size++;
		}
		if (ret == 0) {
			to_process = to_process / 2;
			rounds--;
		}
		//printf("%d\n", rounds);
	}
	//free(t_args);
	i = workSet[0];
	printf("%d\n", i);
	//pthread_mutex_destroy(&mutex);
	return 0;	
}

void* find_max(void *params) {
	struct thread_args *t_args = (struct thread_args*)params;
	int a = (*t_args).i1;
	int b = (*t_args).i2;
	pthread_mutex_lock(&valtex);
	if (a > b) {
		curSet.push_back(a);
	} else {
		curSet.push_back(b);
	}
	pthread_mutex_unlock(&valtex);
	pthread_mutex_lock(&mutex);	
	remaining--;

	if (remaining==0) {
		pthread_mutex_unlock(&mutex);
		pthread_mutex_lock(&valtex);
		//workSet.clear();
		workSet = curSet;
		curSet.clear();
		pthread_mutex_unlock(&valtex);
		pthread_mutex_lock(&mutex);
		ret = pthread_cond_broadcast(&cond);
	}
	else {
		while (remaining != 0) {pthread_cond_wait(&cond, &mutex);}
	}
	pthread_mutex_unlock(&mutex);
	free (params);
	pthread_exit(NULL);	
}