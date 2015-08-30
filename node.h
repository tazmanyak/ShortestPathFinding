#ifndef NODE_H_
#define NODE_H_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define ITERATE_TO 5 // Whatever want you, set it.

typedef struct
{
	int id;
	int node_id;
	int visited;
	float cost;
}Node;

typedef struct
{
	int *pathArray;

}Path;

typedef struct
{
	Path *Paths;

}AllPath;

float calculateDist(float x1, float y1, float x2, float y2);
int checkStatusNode(Node *Nodes);
int getNodeId(Node *Nodes,int node);
int getKthNode(int node, int k);
int calculateBestNode(AllPath *allPossiblePaths, int used, int calculateBest);


#endif


