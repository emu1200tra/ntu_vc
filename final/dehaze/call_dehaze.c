#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// argv[1]: # of image, argv[2]: method
// method = 1: dark channel  2: nonlocal

int main(int argc , char *argv[]){
  if(atoi(argv[2]) == 1){
    char tmp[2];
    tmp[0] = '"';
    tmp[1] = '\0';
    char cmd[512];
    strcpy(cmd , "matlab -nodisplay -nosplash -nodesktop -r ");
    strcat(cmd , tmp);
    strcat(cmd , "index=");
    strcat(cmd , argv[1]);
    strcat(cmd , ";demo(index);exit");
    strcat(cmd , tmp);
    printf("%s\n", cmd);
    system(cmd);
  }
  else if(atoi(argv[2]) == 2){
    char tmp[2];
    tmp[0] = '"';
    tmp[1] = '\0';
    char cmd[512];
    strcpy(cmd , "matlab -nodisplay -nosplash -nodesktop -r ");
    strcat(cmd , tmp);
    strcat(cmd , "index=");
    strcat(cmd , argv[1]);
    strcat(cmd , ";demo_non_local_dehazing(index);exit");
    strcat(cmd , tmp);
    printf("%s\n", cmd);
    system(cmd);
  }

  return 0;
}
