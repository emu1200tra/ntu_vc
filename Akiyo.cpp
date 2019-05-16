#include "stdio.h"
#include "iostream"
#include "stdlib.h"
#include <string>
#include <cstring>
#include <fstream>
#include <math.h>
#include <random>
#include <time.h>
#include <algorithm>    
#include <vector>  
#define b_size 4

using namespace std;

unsigned char videoy[300][176][144] = {0};
unsigned char videocb[300][88][72] = {0};
unsigned char videocr[300][88][72] = {0};

float SAD(int x0 , int y0 , int x , int y , int t){
  int sum = 0;
  for(int i = 0 ; i < b_size ; i++){
    for(int j = 0 ; j < b_size ; j++){
      sum += abs(videoy[t][x0+i][y0+j] - videoy[t-1][x+i][y+j]);
    }
  }
  return sum;
}

void read_in(){
  FILE *file;
  if (!(file = fopen("Akiyo.QCIF", "rb"))){
    printf("Cannot open file! :%s\n" , "Akiyo.QCIF");
    exit(1);
  }
  for(int i = 0 ; i < 300 ; i++){
    fread(videoy[i], sizeof(unsigned char), 176*144, file);
    fread(videocb[i], sizeof(unsigned char), 88*72, file);
    fread(videocr[i], sizeof(unsigned char), 88*72, file);
  }
  fclose(file);
}

float PSNR(unsigned char image1[176][144] , unsigned char image2[176][144]){
  float sum = 0.0;
  for(int i = 0 ; i < 176 ; i++){
    for(int j = 0 ; j < 144 ; j++){
      sum += pow(image1[i][j] - image2[i][j] , 2);
    }
  }
  sum /= 176*144;
  return 10*log10(1/sum);
}

void full_search(float PSNR_list[299] , int window_size){
  for(int i = 1 ; i < 300 ; i++){
    unsigned char image_record[176][144] = {0};
    for(int j = 0 ; j < 44 ; j++){
      for(int k = 0 ; k < 36 ; k++){
        int record[2] = {0};
        float min_SAD = 7122.0;
        for(int l = -window_size/2 ; l <= window_size/2 ; l++){
          for(int m = -window_size/2 ; m <= window_size/2 ; m++){
            if(j+l >= 0 && j+l < 44 && k+m >= 0 && k+m < 36 && SAD(j*b_size , k*b_size , (j+l)*b_size , (k+m)*b_size , i) < min_SAD){
              min_SAD = SAD(j*b_size , k*b_size , (j+l)*b_size , (k+m)*b_size , i);
              record[0] = j+l;
              record[1] = k+m;
            }
          }
        }
        for(int l = 0 ; i < b_size ; l++){
          for(int m = 0 ; m < b_size ; m++){
            image_record[j*b_size+l][k*b_size+m] = videoy[i-1][record[0]*b_size+l][record[1]*b_size+m];
          }
        }
      }
    }
    PSNR_list[i-1] = PSNR(videoy[i] , image_record);
  }
}

void write_out_PSNR(float PSNR_list[299] , string name){
  FILE *file;
  if (!(file = fopen(name.c_str(), "w"))){
    printf("Cannot open file! :%s\n" , name.c_str());
    exit(1);
  }
  for(int i = 0 ; i < 299 ; i++){
    fprintf(file, "%f ", PSNR_list[i]);
  }
  fprintf(file, "\n");
  fclose(file);
}

int main(){
  read_in();
  float PSNR_list[299] = {0.0};
  full_search(PSNR_list , 5);
  write_out_PSNR(PSNR_list , "Akiyo_full_search.txt");
  return 0;
}