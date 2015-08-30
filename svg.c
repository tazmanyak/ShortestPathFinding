
#include "svg.h"


void generate_svg(char *input, char *output)
{
     
    //INPUT OPERATÝONS //
    
    FILE *fp, *fp_out;  SVG *svg;  Coord *coord;
    int array_size = 0, i=0, max_lines = 0;  // Line counters
    char c;  // To store a character read from file to check whether newline or not
    char *str_joined = NULL;
	size_t total_length=0, length=0;
    
    // Open the file
    fp = fopen(input, "r");
	if (fp == NULL)
	{
		perror("Error");
	}
	else
	{
		 //Count the number of lines for the array size 
		for (c = getc(fp); c != EOF; c = getc(fp))
			if (c == '\n') 
				array_size = array_size + 1;
		fclose(fp);
	}

   


    // read the file into an array of coordinates
    coord = (Coord*)malloc(array_size * sizeof(Coord)); //preallocation for performance
    fp = fopen(input, "r");
	if (fp == NULL)
	{
		perror("Error");
	}
	else
	{
		while(!feof(fp))
		{
		   //check whether input getting correctly             
		   if(fscanf(fp, "%d, %d", &coord[i].x, &coord[i].y)==2)      
			  i++;           
		
		}
		fclose(fp);
	}
   

    //OUTPUT OPERATIONS
    max_lines = i;
    svg = (SVG*)malloc(array_size * sizeof(SVG)); // allocate memory
     //total length and length of string
    for(i=0; i<max_lines; i++)
    {
        sprintf(svg[i].xy , "%d,%d ", coord[i].x, (-1) * coord[i].y); // -y direction
        total_length += strlen(svg[i].xy); 
        //printf("%s\n", svg[i].xy);
    }
    
    str_joined = (char*)malloc(total_length * sizeof(char)); // allocate memory for joined strings
    str_joined[0] = '\0'; // empty string we can append to
    
    for(i=0; i<max_lines; i++)
    {
        strcat(str_joined, svg[i].xy);

    }
    
    fp_out = fopen(output,"w+"); //erase the content and write on it if exists or create the file and write on it
	if (fp_out==NULL)
	{
		perror("Error");
	}
	else
	{
		fprintf(fp_out, "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\">\n\t<polyline points=\"%s\"/>\n</svg>" , str_joined);

		printf("Operation successful.\n");
	}
}
