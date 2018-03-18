#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

typedef struct{
	char parent[256];
	char name[256];
	int priority,memory;
}proc;

struct proc_tree{
	proc process;
	struct proc_tree *left;
	struct proc_tree *right;
};

struct proc_tree *root = NULL;

void insert(proc key, struct proc_tree **leaf)
{
    if( *leaf == 0 )
    {
        *leaf = (struct proc_tree*) malloc( sizeof( struct proc_tree ) );
	strcpy ((*leaf)->process.parent, key.parent);
        (*leaf)->left = NULL;
        (*leaf)->right = NULL;
    }else{
	    if (strcmp(key.parent, (*leaf)->process.parent) < 0)
	    {
		insert( key, &(*leaf)->left );
	    }
	    else if(strcmp(key.parent, (*leaf)->process.parent) > 0)
	    {
		insert( key, &(*leaf)->right );
	    }
    }
}

void in_order(struct proc_tree *p_root)
{
    if( p_root != NULL ) {
        in_order(p_root->left);
        printf("   %s %s %d %d\n", p_root->process.parent,p_root->process.name,p_root->process.priority,p_root->process.memory);     
        in_order(p_root->right);
    }
}

int main(void)
{
	char buffer[1024];
	FILE *fp;
	fp = fopen("processes_tree.txt", "r");
	const char s[2] = ", ";
	char *token;
	int i;
	char* data;
	proc process;
	if(fp != NULL)
	{
		while(fgets(buffer, sizeof buffer, fp) != NULL)
		{
		    data = strdup(buffer);
		    token = strtok(data, s);
		    for(i=0;i<4;i++)
		    {
			if(i==0)
			{   
			    strcpy(process.parent,token);
			    token = strtok(NULL,s);
			} else if (i==1){
			    strcpy(process.name,token);
			    token = strtok(NULL,s);
			}else if (i==2){
			    process.priority = atoi(token);
			    token = strtok(NULL,s);
			}else if (i==3){
			    process.memory = atoi(token);
			    token = strtok(NULL,s);
			}                     
		    }
		    insert(process, &root);
		}
		fclose(fp);
	} else {
	perror("processes_tree.txt");
	} 
	in_order(root);
}  
