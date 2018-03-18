#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define MEMORY 1024 

typedef struct{
	char name[256];
	int priority,pid,address,memory,runtime;
	bool suspended;
}proc;

typedef struct node{
    proc process;
    struct node* next;
}node_t;
node_t * head = NULL;
node_t * tail = NULL;
node_t * new_node;

proc priority;
proc secondary;

int avail_mem[MEMORY];

void push(proc process) {
    node_t * new_node;
    new_node = malloc(sizeof(node_t));

    new_node->process = process;
    new_node->next = NULL;
    if(head == NULL && tail == NULL){
	head = tail = new_node;
	return;
    }
    tail->next = new_node;
    tail = new_node;
}

void pop(proc process) {
	node_t * new_node = head;
	if(head == NULL) {
		printf("Queue is Empty\n");
		return;
	}
	printf("%s, %d, %d, %d\n", new_node->process.name,new_node->process.priority,new_node->process.pid,new_node->process.runtime);
	if(head == tail) {
		head = tail = NULL;
	}
	else {
		head = head->next;
	}
	free(new_node);
}

int main(void)
{
	char buffer[1024];
	FILE *fp;
	fp = fopen("processes_q2.txt", "r");
	const char s[2] = ", ";
	char *token;
	char* data;
	if(fp != NULL)
	{
		while(fgets(buffer, sizeof buffer, fp) != NULL)
		{
		    data = strdup(buffer);
		    token = strtok(data, s);  
		    token = strtok(NULL,s);
		    if (atoi(token)==0){
			    data = strdup(buffer);
		    	    token = strtok(data, s);
			    strcpy(priority.name,token);
			    token = strtok(NULL,s);
			    priority.priority = atoi(token);
			    token = strtok(NULL,s);
			    priority.memory = atoi(token);
			    token = strtok(NULL,s);
			    priority.runtime = atoi(token);
			    priority.pid = 0;
			    priority.address = 0;
			    push(priority);
		    }else if (atoi(token)!=0){
			    data = strdup(buffer);
		    	    token = strtok(data, s);
			    strcpy(secondary.name,token);
			    token = strtok(NULL,s);
			    secondary.priority = atoi(token);
			    token = strtok(NULL,s);
			    secondary.memory = atoi(token);
			    token = strtok(NULL,s);
			    secondary.runtime = atoi(token);
			    secondary.pid = 0;
			    secondary.address = 0;
			    push(secondary);
		    }
		}
		fclose(fp);
	} else {
	perror("processes.txt");
	}
}
