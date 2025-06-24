#include <sstream>
#include <string.h>
#include <stdio.h>
#include <string>

int main(int argc, char *argv[])
{
  FILE *connections_file;
  connections_file = fopen("tmpConnectionFile", "r");

  FILE *py_py_conn_file;
  py_py_conn_file = fopen("py_py_conn", "r");

  FILE *new_conn_file;
  new_conn_file = fopen("trainedWeights", "w");
  
  int x_size;
  int y_size;
  int x_loc;
  int y_loc;
  int py_x_loc;
  int py_y_loc;
  
  int iter = 0;
  char line[1000];
  int type, py_type, Num_Types;

  int in_type;
  int in_x_loc;
  int in_y_loc;
  char syn_type[250];
  double strength = 0.0;
  double mini_s = 0.0;
  double mini_fre = 0.0;
  int short_range = 0;

  
  if(fscanf(connections_file,"%d\n",&Num_Types) != 1){
    printf("bad input file could not get number of types\n");
  } else{
    fprintf(new_conn_file, "%d\n",Num_Types);
  }

  while(fscanf(connections_file,"%d %d\n",&x_size,&y_size) == 2){
    fprintf(new_conn_file, "%d %d\n",x_size,y_size);
  }

  while (fgets(line, sizeof(line), connections_file) != NULL) {
    if (sscanf(line,"In: %d %d %d\n",&type,&x_loc,&y_loc)==3) {
      fprintf(new_conn_file,"%s",line);
      if (type==4){
        fpos_t position;
        fgetpos(py_py_conn_file, &position);
        if (fscanf(py_py_conn_file, "In: %d %d %d\n",&py_type,&py_x_loc,&py_y_loc)==3){
          if (x_loc!=py_x_loc){
            printf("Some serious error in neuron number !!!\n");
          }
          
          while(1){
            if(fscanf(py_py_conn_file,"%d %d %d %s %lf %lf %lf %d\n",&in_type,&in_x_loc,&in_y_loc,syn_type,&strength,&mini_s,&mini_fre,&short_range) != 8){
              break;
            }
            fprintf(new_conn_file, "%d %d %d %s %lf %lf %lf %d\n",in_type,in_x_loc,in_y_loc,syn_type,strength,mini_s,mini_fre,short_range);
          }
        }
      }
    }else {
      fprintf(new_conn_file,"%s",line);
    }
  }

  fclose(connections_file);
  fclose(py_py_conn_file);
  fclose(new_conn_file);  
  return 0;
}



