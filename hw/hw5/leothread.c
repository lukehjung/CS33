#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

//global variable to access how threads we want to make
int nthreads;

//structure holds the thread id and decrements the count of threads
struct node{
	int id;
	int totalnum;
};

//iterative function that calculates the leonardo number
int leonums(int n)
{
	int i, result;
	if(n < 2)
		return 1;
	int prevalue1 = 1, prevalue2 = 1;
	for(i = 2; i <= n; i ++)
	{
		result = prevalue1 + prevalue2 + 1;
		prevalue1 = prevalue2;
		prevalue2 = result;
	}
	return result;
}

void *thread(void *vargp)
{
	pthread_t idl, idr; //each thread has two children, left and right threads
	struct node left_node; //create new structs for each of the children
	struct node right_node; 

	//set local variables to struct variables from previous thread
	int id = ((struct node*)vargp)->id; 
	int totalnum = ((struct node*)vargp)->totalnum; 

	//if the total number of threads are 0 or 1, we can't make children for them
	//so we print the leaves and return null
	if(totalnum == 0 || totalnum == 1)
	{
		printf("[%d]\n",id);
        return NULL;
	}

	//the thread is then printed with an open parentheses to open the tree
    printf("(%d\n",id);
   
   	//now we need to reduce the total number of threads for the tree and put
   	//them in the next nodes.
    left_node.totalnum = totalnum - 1;
    right_node.totalnum = totalnum - 2;
    //And now we change the id's to what the spec says, adding one and adding
    //the leonumber to the right node
    left_node.id = id + 1;
    right_node.id = id + 1 + leonums(totalnum - 1);

    //and this goes on recursively, until the totalnum goes to 0
    if(left_node.totalnum >= 0)
    {
    	pthread_create(&idl, NULL, thread, (void*)&left_node);
        pthread_join(idl, NULL);
    }

    if(right_node.totalnum >= 0)
    {
    	pthread_create(&idr, NULL, thread, (void*)&right_node);
        pthread_join(idr, NULL);
    }

    //once it starts returning null, we close the tree with a right parentheses.
    printf("%d)\n", id);
    return NULL;
}

int main(int argc, char ** argv)
{
	//first check for number of arguments, i'm not checking for neg values
	if(argc != 2)
	{
		printf("Wrong number of arguments.");
		exit(1);
	}

	//create the first structure for the first root and initialize values.
	struct node root;
	pthread_t rid;
	nthreads = atoi(argv[1]);
	root.id = 0;
	root.totalnum = nthreads;

	//if the total num threads is 1, then we can print the first number and exit
	if(nthreads == 1)
	{
		printf("[0]\n");
		return 0;
	}

	//this starts the function call to the threads function above.
	pthread_create(&rid, NULL, thread, (void*)&root);
	pthread_join(rid, NULL);

	return 0;
}