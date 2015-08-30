#include "node.h"
#include "reader.h"


float calculateDist(float x1, float y1, float x2, float y2)
{
	float dist = 0;
	dist = sqrt( (x2-x1) * (x2-x1)  + (y2-y1) * (y2-y1) );

#ifdef DEBUG
		
	printf("------------------------------\n");
	printf("Calculated Distance : %.2f\n", dist);
	printf("------------------------------\n");

#endif

	return dist;
}


int getNodeId(Node *Nodes,int node)
{
	int id=0;
	for(int i=0; i<sizeof(Nodes); i++)
	{
		if(Nodes[i].node_id == node)
		{
			id = Nodes[i].id;
			break;
		}
	}

	return id;
}



int checkStatusNode(Node *Nodes)
{
	int status=0;

	for(int i=0; i<sizeof(Nodes); i++)
	{
		if(Nodes[i].visited) // == 1 =>  permanent
		{
			status=1;
			break;
		}
		else // temporarily
		{
			status = 0;
			break;
		}
	}

	return status;

}


int getKthNode(int node,int k)
{
	int kth_node=0;
	int n_used = 0;
	intlist listNode = readNodeNeighbourList(node);
	int *array_list = listNode.array;
	n_used = listNode.used;

#ifdef DEBUG
	printf("------------------------------\n");
	printf("Selected Node -> %d\n", node);
	printf("------------------------------\n");
	for(int i=0; i<listNode.used; i++)
		printf("Node %d -> %d\n", i, *(array_list + i));
	printf("------------------------------\n");
	printf("Used : %d\n", n_used);
	printf("------------------------------\n");
#endif


	kth_node = *(array_list + k);
	free(listNode.array);
	free(array_list);

	return kth_node;
}

int calculateBestNode(AllPath *allPossiblePaths,int used, int final_node)
{
	int bestNodesForAll[10][ITERATE_TO-1][ITERATE_TO]; // K X ITERATE  MATRIX -> K can be btw 1 to 4 so set it 10.
	int bestNodes[10];
	
	for(int i=0; i<used; i++)
	{
		for(int j=0; j<ITERATE_TO-1; j++)
		{
			for(int k=0; k<ITERATE_TO; k++)
			{
				bestNodesForAll[i][j][k] = *(allPossiblePaths[i].Paths[j].pathArray + k);
				//printf("WTF : %d\n", bestNodesForAll[i][j]);
			}
		}
		//printf("%d\n", i);
	}

#ifdef DEBUG
	for(int i=0; i<used; i++)
	{
		for(int j=0; j<ITERATE_TO-1; j++)
		{
			for(int k=0; k<ITERATE_TO; k++)
			{
				printf("%d ", bestNodesForAll[i][j][k]);
				//_sleep(500);
			}
			printf("\n");
			
		}
		printf("\n");
	}
#endif
	/*for(int i=0; i<used; i++)
	{
			bestNodes[i] = bestNodesForAll[i][ITERATE_TO];
			printf("Best : %d\n", bestNodes[i]);
			
	
	}*/
	return 184119;

}