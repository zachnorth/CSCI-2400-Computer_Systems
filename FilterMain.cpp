#include <stdio.h>
#include "cs1300bmp.h"
#include <iostream>
#include <fstream>
#include "Filter.h"

using namespace std;

#include "rdtsc.h"

//
// Forward declare the functions
//
Filter * readFilter(string filename);
double applyFilter(Filter *filter, cs1300bmp *input, cs1300bmp *output);

int
main(int argc, char **argv)
{

  if ( argc < 2) {
    fprintf(stderr,"Usage: %s filter inputfile1 inputfile2 .... \n", argv[0]);
  }

  //
  // Convert to C++ strings to simplify manipulation
  //
  string filtername = argv[1];

  //
  // remove any ".filter" in the filtername
  //
  string filterOutputName = filtername;
  string::size_type loc = filterOutputName.find(".filter");
  if (loc != string::npos) {
    //
    // Remove the ".filter" name, which should occur on all the provided filters
    //
    filterOutputName = filtername.substr(0, loc);
  }

  Filter *filter = readFilter(filtername);

  double sum = 0.0;
  int samples = 0;

  for (int inNum = 2; inNum < argc; inNum++) {
    string inputFilename = argv[inNum];
    string outputFilename = "filtered-" + filterOutputName + "-" + inputFilename;
    struct cs1300bmp *input = new struct cs1300bmp;
    struct cs1300bmp *output = new struct cs1300bmp;
    int ok = cs1300bmp_readfile( (char *) inputFilename.c_str(), input);

    if ( ok ) {
      double sample = applyFilter(filter, input, output);
      sum += sample;
      samples++;
      cs1300bmp_writefile((char *) outputFilename.c_str(), output);
    }
    delete input;
    delete output;
  }
  fprintf(stdout, "Average cycles per sample is %f\n", sum / samples);

}

struct Filter *
readFilter(string filename)
{
  ifstream input(filename.c_str());

  if ( ! input.bad() ) {
    int size = 0;
    input >> size;
    Filter *filter = new Filter(size);
    int div;
    input >> div;
    filter -> setDivisor(div);
    for (int i=0; i < size; i++) {
      for (int j=0; j < size; j++) {
	int value;
	input >> value;
	filter -> set(i,j,value);
      }
    }
    return filter;
  } else {
    cerr << "Bad input in readFilter:" << filename << endl;
    exit(-1);
  }
}


double applyFilter(struct Filter *filter, cs1300bmp *input, cs1300bmp *output)
{
    
    //Used -Ofast to significantly increase the speed at which this compiles
    //added a few other flags but none of them seemed to give me too much of an increase if any at all

    long long cycStart, cycStop;

    cycStart = rdtscll();

    int width = (output -> width = input -> width) - 1; //minor increase but still reduces the total access time.
    int height = (output -> height = input -> height) - 1;//minor increase but still reduces the total access time
    
    
    int size = filter->getSize(); //Initializes size to the call to getSize()
    int divisor = filter->getDivisor(); //Initializes divisor to the call to getDivisor()
    
    int temp_filter[size][size]; //temp variable initialization
    
    for(int i = 0; i < size; i++)
    {
        for(int j = 0; j < size; j++)
        {
            temp_filter[i][j] = filter->get(i, j);          //Call to get(i, j) and setting the temp_filter = to that value.
        }
    }
    
    for(int row = 1; row <= height; row += 2)
    {
        for(int col = 1; col <= width; col += 2)
        {
            
            int plane1_1 = 0;       //Initializes temporary planes to 0 every time the inner of the outter two loops executes.
            int plane2_1 = 0; 
            int plane3_1 = 0; 
            int plane1_2 = 0;
            int plane2_2 = 0;
            int plane3_2 = 0;
            int plane1_3 = 0;
            int plane2_3 = 0;
            int plane3_3 = 0;
            
            
            for(int i = 0; i < size; i++)
            {
                
                int temp_row = row + i - 1; //Variables to help unroll the loop
                int temp_row_2 = temp_row + 1;
                
                for(int j = 0; j < size; j++)
                {
                    int a = temp_filter[i][j];      //temp_filter[][] was already initialized with two loops that were moved outside the main loops along with                                                         //moving the call to get(i, j) into those two loops. This significantly increased the speed.
                    int temp_col = col + j - 1;     //variables to help unroll the loop
                    int temp_col_2 = temp_col + 1;
                    
                    
                    plane1_1 += input->color[0][temp_row][temp_col] * a;            //Loop unrolled by creating multiple varialbes to access the correct row and  
                    plane2_1 += input->color[1][temp_row][temp_col] * a;            //column while getting 9 done per iteration.
                    plane3_1 += input->color[2][temp_row][temp_col] * a;
                    plane1_2 += input->color[0][temp_row][temp_col_2] * a;
                    plane2_2 += input->color[1][temp_row][temp_col_2] * a;
                    plane3_2 += input->color[2][temp_row][temp_col_2] * a;
                    plane1_3 += input->color[0][temp_row_2][temp_col] * a;
                    plane2_3 += input->color[1][temp_row_2][temp_col] * a;
                    plane3_3 += input->color[2][temp_row_2][temp_col] * a;
                }
            }
            
            if(divisor != 1)
            {
                plane1_1 = plane1_1 / divisor;          //Moved the call to getDivisor() out of the loops and set it equal to a variable. Unrolled the calls so as 
                plane2_1 = plane2_1 / divisor;          //to get 9 done at a time
                plane3_1 = plane3_1 / divisor;
                plane1_2 = plane1_2 / divisor;
                plane2_2 = plane2_2 / divisor;
                plane3_2 = plane3_2 / divisor;
                plane1_3 = plane1_3 / divisor;
                plane2_3 = plane2_3 / divisor;
                plane3_3 = plane3_3 / divisor; 
            }
            
            output->color[0][row][col] = plane1_1 < 0 ? 0: plane1_1 > 255 ? 255: plane1_1;      //Tournary operators to get rid of if statements and loop unrolled 
            output->color[1][row][col] = plane2_1 < 0 ? 0: plane2_1 > 255 ? 255: plane2_1;      //it to do 9 at a time
            output->color[2][row][col] = plane3_1 < 0 ? 0: plane3_1 > 255 ? 255: plane3_1;
            output->color[0][row][col + 1] = plane1_2 < 0 ? 0: plane1_2 > 255 ? 255: plane1_2;
            output->color[1][row][col + 1] = plane2_2 < 0 ? 0: plane2_2 > 255 ? 255: plane2_2;
            output->color[2][row][col + 1] = plane3_2 < 0 ? 0: plane3_2 > 255 ? 255: plane3_2;
            output->color[0][row + 1][col] = plane1_3 < 0 ? 0: plane1_3 > 255 ? 255: plane1_3;
            output->color[1][row + 1][col] = plane2_3 < 0 ? 0: plane2_3 > 255 ? 255: plane2_3;
            output->color[2][row + 1][col] = plane3_3 < 0 ? 0: plane3_3 > 255 ? 255: plane3_3;
        }
    }

  cycStop = rdtscll();
  double diff = cycStop - cycStart;
  double diffPerPixel = diff / (output -> width * output -> height);
  fprintf(stderr, "Took %f cycles to process, or %f cycles per pixel\n",
	  diff, diff / (output -> width * output -> height));
  return diffPerPixel;
}




