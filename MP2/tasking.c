#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <unistd.h>
#include <time.h>
#define SEED 0

struct list{
	long int val;
	struct list *next;
};

void insert(struct list *p);
struct timespec start_time,end_time;
long double elapsed1;
long int sleeptime;
struct list *head;
void compute(long int,int);

int main(int argc, char *argv[])
{
	struct list *p,*pre;
	long int num=100000, i=0;
	int threads;
	
	// read arguments
	if(argc!=3) { 
		 printf("Invalid arguments"); 
		 exit(1); 
	}
	sleeptime=atoi(argv[1]);
	threads=atoi(argv[2]);
	
	// init data structure
	head = (struct list*) malloc(sizeof(struct list));
	if (head==NULL) { 
		 printf("Cannot allocate memory"); 
		 exit(1); 
	}

	srand(SEED);
	p=head;
	head->val = (long int) 1000000 * ((double) rand() / ((double) (RAND_MAX) + (double) (1)));
	head->next=NULL;
	i++;
	while (i<=num) {
		p = (struct list*) malloc(sizeof(struct list));
		if(p==NULL) { 
			printf("Cannot allocate memory"); 
			exit(1); 
		}
		p->val = (long int) 1000000 * ((double) rand() / ((double) (RAND_MAX) + (double) (1)));
		p->next=NULL;
		insert(p); 
		i++;
	}

	p=head;

	omp_set_num_threads(threads); 

	clock_gettime(CLOCK_MONOTONIC,&start_time);
	
	// begin traversal sequentially or in parallel
	while(p!=NULL) {
		compute(p->val,sleeptime/4);
		p=p->next;
	} 

	clock_gettime(CLOCK_MONOTONIC,&end_time);

	elapsed1=((((end_time.tv_sec-start_time.tv_sec)*1000000000)+end_time.tv_nsec-start_time.tv_nsec)/100000.0);
p=head;

	printf("%ld,%Lf\n",sleeptime,elapsed1);

	p=head;
	while(p!=NULL) {
		pre=p; 
		p=p->next; 
		free(pre);
	}

	return 0;
}   

void insert(struct list *p)
{
	struct list *ptr,*ptr_prev;

	ptr = ptr_prev=head;
	while (ptr!=NULL&&(ptr->val<=p->val)) {
		ptr_prev=ptr; 
		ptr=ptr->next; 
	}
	
	if(ptr==head) {  
		p->next=head; 
		head=p; 
	} 
	else if(ptr==NULL) { 
		ptr_prev->next=p; 
		p->next=NULL;
	}
	else { 
		ptr_prev->next=p; 
		p->next=ptr; 
	} 
}

void compute(long int x, int y)
{
	int i;
	for(i=0;i<y;i++) ;
}

