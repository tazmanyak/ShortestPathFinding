# ShortestPathFinding
Shortest Path Finding A*Star Heuristic Approach

This is actually not finished project about A*star Shortest Path Finding Algorithm. I'm still working on it and it is good to share the idea behind it.


I will not share "reader class" since it is not coded by me and its belong to IT company that i might not have permission to share. So, look at it as if you know reader.h and reader.c. You can understand the logic behind it even though you donot see reader class.


##What is it about ? 

The purpose of this project is to find the best possible paths from initial to end node. You know the coordinates of nodes and neighbourhoods of each node. When the best path is found, the next step is to generate SVG to show on the real MAP so that we can visualize the output.


##What it is included in this project ? 

I coded Node and SVG generator class. The algorithm is in the "main.c". When you look at it, there are comments on each line so that you can understand what is really going on about it.


Pseudocode

The following pseudocode describes the algorithm:

    function A*(start,goal)
    closedset := the empty set    // The set of nodes already evaluated.
    openset := {start}    // The set of tentative nodes to be evaluated, initially containing the start node
    came_from := the empty map    // The map of navigated nodes.
 
    g_score := map with default value of Infinity
    g_score[start] := 0    // Cost from start along best known path.
    // Estimated total cost from start to goal through y.
    f_score = map with default value of Infinity
    f_score[start] := g_score[start] + heuristic_cost_estimate(start, goal)
     
    while openset is not empty
        current := the node in openset having the lowest f_score[] value
        if current = goal
            return reconstruct_path(came_from, goal)
         
        remove current from openset
        add current to closedset
        for each neighbor in neighbor_nodes(current)
            if neighbor in closedset
                continue
 
            tentative_g_score := g_score[current] + dist_between(current,neighbor)

            if neighbor not in openset or tentative_g_score < g_score[neighbor] 
                came_from[neighbor] := current
                g_score[neighbor] := tentative_g_score
                f_score[neighbor] := g_score[neighbor] + heuristic_cost_estimate(neighbor, goal)
                if neighbor not in openset
                    add neighbor to openset
 
            return failure
            
          
        


You can look at it in detail from https://en.wikipedia.org/wiki/A*_search_algorithm
