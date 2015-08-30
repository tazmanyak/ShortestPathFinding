#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "svg.h"
#include "reader.h"
#include "node.h"

#define INF 999



 /*char input[MAX_FILE_NAME];
    printf("Enter file name  (like : try.txt) , \nyou can type with directory like : data/Ankara.txt  \n Output file will be automatically assigned as svg_out.svg, \nso you can check from it\n\n\nEnter File Name: ");
    scanf("%s", input);
	
    generate_svg(input, OUTPUT_FILE_NAME);*/


int main()
{
   
	int pass_node=0,antecessor_node=0, active_node=0;
	int	node_begin=0, node_end=0,vector_size, count=1, i=0,path_counter=0;
	int source=0,temp_node=0, checkPassNode=0; // distance set from prev. nodes.
	float total_dist=0,dist=0,temp_distance=0, dist_set=0; //distances

	Node *Nodes; // node list
	Path *activeNodeKthPaths;
	AllPath *activeNodeAllPaths;

	printf("Enter start node : ");
	scanf("%d", &node_begin);
	printf("\nEnter final node : ");
	scanf("%d", &node_end);


	node_begin = 184119;
	node_end = 547385;


	vector_size = node_end - node_begin;

	


	Nodes = (Node*)malloc(vector_size * sizeof(Node));
	activeNodeKthPaths = (Path*)malloc(ITERATE_TO * sizeof(Path));
	activeNodeAllPaths = (AllPath*)malloc(20 * sizeof(AllPath));

	openData("testFeatureFile");


	//initialize nodes w.r.t 
	for(int i=node_begin; i<node_end; i++)
	{
		Nodes[count].id = count;
		Nodes[count].node_id = i;
		Nodes[count].cost = INF;
		Nodes[count].visited = 0;
		count++;
	}
	
	Nodes[0].id = 0;
	Nodes[0].node_id = 0;
	Nodes[0].cost = 0;
	Nodes[0].visited = 1;
	
	active_node = node_begin; //set active node => node_begin

	//Paths = (Path*)malloc(vector_size * sizeof(Path));

	vector v_final_node = readNodeLocation(node_end);
	//printf("Final Node -> X: %.2f, Y: %.2f\n", v_final_node.x,v_final_node.y);

	while(checkStatusNode(Nodes)) // repeat until all nodes left with permanent dist ,that is to say, viewed.
	{
		
	
		vector v_active_node = readNodeLocation(active_node);
		intlist l_active_node = readNodeNeighbourList(active_node); 
		int active_pathId = getNodeId(Nodes,active_node);
		Nodes[active_pathId].visited = 1; // visited node
		int n_used = l_active_node.used;
		free(l_active_node.array);

#ifdef DEBUG
		printf("Active node : %d\n", active_node);
		printf("# of array used in pointer : %d\n", n_used);
#endif

		if(n_used > 0)
		{
			int sNode=0, sNodepathId=0, next = 1, k = 0;	
			sNode = active_node;
			float cost = 0;
			vector v_sNode;


			for(k=0; k<n_used; k++) // goes to each kth neighbour node
			{
#ifdef DEBUG
				printf("k -> %d\n", k);
				printf("------------------------------\n");
#endif
				int nodePaths[ITERATE_TO];
				nodePaths[0] = active_node; // 0th iteration
				/*
				=> active node
						=> pick 1th neighbour node first
							1th neighbour node 
									=> pick 1th neighbour node's 1th neighbour node
										=> repeat again ( check whether neighbour node is same with active node, if so , pick 2th neighbour node and repeat process so and so forth like 3th and 4th if exists.
				*/
				

				// ------------------------- n=#ITERATE_TO possible iteration ( n=#ITERATE_TO possible path for active node for each neighbourhood ( kth) )--------------------------//
				// There could be same paths through the iteration. The more iteration, the more path can be revealed.
				for(next=1; next < ITERATE_TO; next++)
				{

					// NEED SOME MODIFICATION BUT THE STRUCTURE IS OKAY //
					
					nodePaths[next] = getKthNode(sNode,k); // pick kth neighbour node
					sNode= nodePaths[next]; // assign kth

					sNodepathId = getNodeId(Nodes,sNode); // get id of kth node

					if(Nodes[sNodepathId].visited)  // check whether it returns back !
					{
						//(k-> 0 -> 1 -> 2 -> 3 (used max : 4 neighbour node in selected node )
						// Possible Path Finding According to Visited Node and its kth value
						if (k == 0) 
						{
							nodePaths[next] = getKthNode(sNode, k + 1);	//  now -> k = 1
							sNodepathId = getNodeId(Nodes,nodePaths[next]); // check again whether k + 1 th node was visited
							if(Nodes[sNodepathId].visited)  // check whether it returns back !
							{
								nodePaths[next] = getKthNode(sNode, k + 2);	//  now -> k = 2
								sNodepathId = getNodeId(Nodes,nodePaths[next]); // check again whether k + 1 th node was visited

								

								if(n_used == 4) // for k = 3
								{
									if(Nodes[sNodepathId].visited)  // check whether it returns back !
									{
										nodePaths[next] = getKthNode(sNode, k + 3);	//  now -> k = 3
										sNodepathId = getNodeId(Nodes,nodePaths[next]); //
									}
								}

							}

						}
						
						if (k == 1)
						{
							nodePaths[next] = getKthNode(sNode, k + 1);	//  now -> k = 2
							sNodepathId = getNodeId(Nodes,nodePaths[next]); // check again whether k + 1 th node was visited
							if(Nodes[sNodepathId].visited)  // check whether it returns back !
							{
			
								if(n_used == 4)  // for k = 3
								{
									if(Nodes[sNodepathId].visited)  // check whether it returns back !
									{
										nodePaths[next] = getKthNode(sNode, k + 2);	//  now -> k = 3
										sNodepathId = getNodeId(Nodes,nodePaths[next]); //

										if(Nodes[sNodepathId].visited)  // check whether it returns back !
										{
											nodePaths[next] = getKthNode(sNode, k - 1);	//  now -> k = 0
											sNodepathId = getNodeId(Nodes,nodePaths[next]); //
										}


									}
								}
								else
								{
									if(Nodes[sNodepathId].visited)  // check whether it returns back !
									{
										nodePaths[next] = getKthNode(sNode, k - 1);	//  now -> k = 0
										sNodepathId = getNodeId(Nodes,nodePaths[next]); //
									}
								}
							}
						
						}
						
						if (k == 2)
						{
							nodePaths[next] = getKthNode(sNode, k - 1);	//  now -> k = 1
							sNodepathId = getNodeId(Nodes,nodePaths[next]); // check again whether k + 1 th node was visited
							if(Nodes[sNodepathId].visited)  // check whether it returns back !
							{
								nodePaths[next] = getKthNode(sNode, k - 2);	//  now -> k = 0
								sNodepathId = getNodeId(Nodes,nodePaths[next]); // check again whether k + 1 th node was visited
								if(Nodes[sNodepathId].visited)  // check whether it returns back !
								{
									if(n_used == 4)  // for k = 3
									{
										nodePaths[next] = getKthNode(sNode, k + 1);	//  now -> k = 3
										sNodepathId = getNodeId(Nodes,nodePaths[next]); // check again whether k + 1 th node was visited
									}
								}
			
								
							}
						
						
						}

						if (k == 3)
						{
							nodePaths[next] = getKthNode(sNode, k - 1);	//  now -> k = 2
							sNodepathId = getNodeId(Nodes,nodePaths[next]); //
							if(Nodes[sNodepathId].visited)  // check whether it returns back !
							{
								nodePaths[next] = getKthNode(sNode, k - 2);	//  now -> k = 1
								sNodepathId = getNodeId(Nodes,nodePaths[next]); //
								if(Nodes[sNodepathId].visited)  // check whether it returns back !
								{
									nodePaths[next] = getKthNode(sNode, k - 3);	//  now -> k = 0
									sNodepathId = getNodeId(Nodes,nodePaths[next]); //
								}

							}
						
						
						}
							
						sNode = nodePaths[next]; // update selected Node
						sNodepathId = getNodeId(Nodes,sNode); // update selected node's path id
					}

					Nodes[sNodepathId].visited = 1; // set visited neighbour
					v_sNode = readNodeLocation(sNode); // get vector of kth node

					cost =	calculateDist(v_active_node.x, v_active_node.y, v_sNode.x, v_sNode.y); // calculate distance from selected node to visited node
					cost += Nodes[active_pathId].cost; // total distance  = dist of prev. node + dist of from sNode to prev.node
					Nodes[sNodepathId].cost = cost; // put cost of kth node

					// store each best path
					for(int i=0; i<ITERATE_TO; i++)
						printf("%d ", nodePaths[i]); 
					printf("\n");
					activeNodeKthPaths[next- 1].pathArray = nodePaths;
				}
				//--------------------------------------------------------------------------------------------------------------------------------------//
				// After having all possible paths for active node, now calculate distance of each scenerio from final node then pick best one as active node
				activeNodeAllPaths[k].Paths = activeNodeKthPaths;
				//free(activeNodeKthPaths);
				//activeNodeKthPaths = (Path*)malloc(ITERATE_TO * sizeof(Path));
				

				sNode = active_node; // each time reset, start from initial node to get paths
				//k++;

	
				
#ifdef DEBUG
					printf("Best Node for this Path -> %d\n", nodePaths[ITERATE_TO-1]);
					printf("------------------------------\n\n\n\n\n");
					printf("Path -> ");
					for(int i=0; i<=ITERATE_TO - 1; i++)
						printf("%d -> ", nodePaths[i]);
					printf("\n-----------------------------\n\n");
					_sleep(1000);	
#endif
				
			}

			// Pick Best Node to Continue Searching
			// active_node = gonna be the next best node

			int try_node = calculateBestNode(activeNodeAllPaths, k, node_end);
			//active_node = sNode;

			active_node = sNode;
		
			//--------------------------------------------------------------------------------------------------------------------------------------//

		}
		
		
		if(active_node == node_end)
			break;

	}




	// Write Best Paths Coord into TXT


	// Generate SVG From TXT (Path)


    
    system("PAUSE");	
    return 0;
}


