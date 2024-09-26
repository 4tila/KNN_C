#include <stdio.h>
#include <string.h>
#include "mnist.h"
#define K 5
unsigned char train[1000][28][28];
int train_labels[1000];
unsigned char test[1000][28][28];
int test_labels[1000];
DistanceType D[1000][1000]; //D[i][j] is distance of test image i to train image j together with label of train image j
int class[1000];
int digit_count[10];
int mx, idx, correct=0;
//	https://yann.lecun.com/exdb/mnist/
//
//	magic number
//	size in dimension 0
//	size in dimension 1
//	size in dimension 2
//	.....
//	size in dimension N
//	data
//	
//	The magic number is an integer (MSB first). The first 2 bytes are always 0.
//	
//	The third byte codes the type of the data:
//	0x08: unsigned byte
//	0x09: signed byte
//	0x0B: short (2 bytes)
//	0x0C: int (4 bytes)
//	0x0D: float (4 bytes)
//	0x0E: double (8 bytes)
//	The 4-th byte codes the number of dimensions of the vector/matrix: 1 for vectors, 2 for matrices....
//	2051 or 0x803 means a tensor of unsigned bytes
//	2049 or 0x801 means a vector of unsigned bytes

//	TRAINING SET LABEL FILE (train-labels-idx1-ubyte):
//	[offset] [type]          [value]          [description]
//	0000     32 bit integer  0x00000801(2049) magic number (MSB first)
//	0004     32 bit integer  60000            number of items
//	0008     unsigned byte   ??               label
//	0009     unsigned byte   ??               label
//	........
//	xxxx     unsigned byte   ??               label
//	The labels values are 0 to 9.
//	
//	TRAINING SET IMAGE FILE (train-images-idx3-ubyte):
//	[offset] [type]          [value]          [description]
//	0000     32 bit integer  0x00000803(2051) magic number
//	0004     32 bit integer  60000            number of images
//	0008     32 bit integer  28               number of rows
//	0012     32 bit integer  28               number of columns
//	0016     unsigned byte   ??               pixel
//	0017     unsigned byte   ??               pixel
//	........
//	xxxx     unsigned byte   ??               pixel
//	Pixels are organized row-wise. Pixel values are 0 to 255. 0 means background (white), 255 means foreground (black).
//	
//	TEST SET LABEL FILE (t10k-labels-idx1-ubyte):
//	[offset] [type]          [value]          [description]
//	0000     32 bit integer  0x00000801(2049) magic number (MSB first)
//	0004     32 bit integer  10000            number of items
//	0008     unsigned byte   ??               label
//	0009     unsigned byte   ??               label
//	........
//	xxxx     unsigned byte   ??               label
//	The labels values are 0 to 9.
//	
//	TEST SET IMAGE FILE (t10k-images-idx3-ubyte):
//	[offset] [type]          [value]          [description]
//	0000     32 bit integer  0x00000803(2051) magic number
//	0004     32 bit integer  10000            number of images
//	0008     32 bit integer  28               number of rows
//	0012     32 bit integer  28               number of columns
//	0016     unsigned byte   ??               pixel
//	0017     unsigned byte   ??               pixel
//	........
//	xxxx     unsigned byte   ??               pixel


/*typedef struct DT{
  double data;
  int idx;
}DistanceType;*/
double f(int x, int y){
	return (double) abs(x-y);
}
int main(){
	{
		FILE *fptr;
		fptr = fopen("train_imgs", "r");
		for (int i=0;i<16;i++) fgetc(fptr);
		for (int i=0;i<1000;i++)for (int j=0;j<28;j++)for (int k=0;k<28;k++)train[i][j][k]=fgetc(fptr);
		fclose(fptr);
	}
	{
		FILE *fptr;
		fptr = fopen("test_imgs", "r");
		for (int i=0;i<16;i++) fgetc(fptr);
		for (int i=0;i<1000;i++)for (int j=0;j<28;j++)for (int k=0;k<28;k++)test[i][j][k]=fgetc(fptr);
		fclose(fptr);
	}
	{
		FILE *fptr;
		fptr = fopen("train_labels", "r");
		for (int i=0;i<8;i++) fgetc(fptr);
		for (int i=0;i<1000;i++)train_labels[i]=(int) fgetc(fptr);
		fclose(fptr);
	}
	{
		FILE *fptr;
		fptr = fopen("test_labels", "r");
		for (int i=0;i<8;i++) fgetc(fptr);
		for (int i=0;i<1000;i++)test_labels[i]=(int) fgetc(fptr);
		fclose(fptr);
	}
	for (int i=0;i<1000;i++)for (int j=0;j<1000;j++){
		D[i][j].data=0e0;
		for (int k=0;k<28;k++)for (int l=0;l<28;l++)D[i][j].data+=f(test[i][k][l], train[j][k][l]);
		D[i][j].idx=train_labels[j];
	}
	for (int i=0;i<1000;i++)MergeSort(D[i], 1000);
	for (int i=0;i<1000;i++){
		for (int j=0;j<10;j++)digit_count[j]=0;
		for (int j=0;j<K;j++)digit_count[D[i][j].idx]++;
		mx=-1, idx=-1;
		for (int j=0;j<10;j++) if (digit_count[j]>=mx)mx=digit_count[j], idx=j;
		class[i]=idx;
	}
	for (int i=0;i<1000;i++)correct+=(class[i]==test_labels[i]);
	printf("%d\/1000\n", correct);
	return 0;
}
