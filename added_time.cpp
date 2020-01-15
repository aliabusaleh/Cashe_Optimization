

#include <immintrin.h>  // portable to all x86 compilers
#include <stdio.h>
#include <time.h>

#define DATA float
#define SIZE 1024
#define block_size 64

DATA A[SIZE][SIZE] ;
DATA B[SIZE][SIZE] ;
DATA C[SIZE][SIZE] ;
DATA C2[SIZE][SIZE] ;
DATA C3[SIZE][SIZE] ;
DATA C4[SIZE][SIZE] ;



double seconds()
{

  struct timespec now;
  clock_gettime(CLOCK_MONOTONIC, &now);
  return now.tv_sec + now.tv_nsec / 1000000000.0;
}

void initialize_array(DATA a[], int size)
{
	for (int i = 0 ;  i < size ; i++)
	{
		a[i] = rand()%2;
	}
}
void initialize_2d_array(DATA a[SIZE][SIZE])
{
    for (int i = 0 ; i < SIZE ; i++)
        for (int j = 0 ; j < SIZE ; j++)
        {
            a[i][j] = rand()%2;
        }
}

void zero_2d_array(DATA a[SIZE][SIZE])
{
    for (int i = 0 ; i < SIZE ; i++)
        for (int j = 0 ; j < SIZE ; j++)
        {
            a[i][j] = 0;
        }
}

int compare(DATA A[SIZE][SIZE],DATA B[SIZE][SIZE])
{

    for (int i = 0 ; i < SIZE ; i++)
        for (int j = 0 ; j < SIZE ; j++)
            if ( A[i][j] != B[i][j])
                return 0;

    return 1;
}

void mat_mat(DATA A[SIZE][SIZE], DATA B[SIZE][SIZE],DATA C[SIZE][SIZE]) 
{
    for (int i = 0 ; i < SIZE ; i++)
        for (int j = 0 ; j < SIZE ; j++)
        {
            C[i][j] = 0;

            for (int k = 0 ; k < SIZE ; k++)
                C[i][j]+= A[i][k]*B[k][j];
        }
}

void mat_mat_interchanged(DATA A[SIZE][SIZE], DATA B[SIZE][SIZE],DATA C[SIZE][SIZE]) 
{
   for (int i = 0 ; i < SIZE ; i++)
        for (int k = 0 ; k < SIZE ; k++)
        {
            //C[i][k] = 0;

            for (int j = 0 ; j < SIZE ; j++)
                C[i][j]+= A[i][k]*B[k][j];
        }
}

void mat_mat_blocked(DATA A[SIZE][SIZE], DATA B[SIZE][SIZE],DATA C[SIZE][SIZE]) 
{
      for(int ii=0; ii<SIZE; ii=ii+block_size){
        for(int jj=0; jj<SIZE; jj=jj+block_size){
            {
                for(int kk =0; kk<SIZE; kk=kk+block_size){
                    
                             for (int i = ii ; i < (ii+block_size) ; i++)
                                for (int j = jj ; j < (jj+block_size) ; j++)
                                {
                                

                                    for (int k = kk ; k < (kk+block_size) ; k++)
                                        C[i][j]+= A[i][k]*B[k][j];
                                }
                    
                }
            }
            
    }
    }
    
}

void mat_mat_blocked_interchanged(DATA A[SIZE][SIZE], DATA B[SIZE][SIZE],DATA C[SIZE][SIZE]) 
{
      for(int ii=0; ii<SIZE; ii=ii+block_size){
        for(int kk=0; kk<SIZE; kk=kk+block_size){
            {
                for(int jj =0; jj<SIZE; jj=jj+block_size){
                    
                             for (int i = ii ; i < (ii+block_size) ; i++)
                                for (int k = kk ; k < (kk+block_size) ; k++)
                                {
                                

                                    for (int j = jj ; j < (jj+block_size) ; j++)
                                        C[i][j]+= A[i][k]*B[k][j];
                                }
                    
                }
            }
            
    }
    
  
}
}

void print_array(DATA A[SIZE][SIZE]) 
{
    for(int i=0 ; i< SIZE; i++){
        for(int j=0; j< SIZE; j++){
            printf("%d\t",&A[i][j]);
        }
    }
  
}

void clear_array(DATA A[SIZE][SIZE]) {
    for(int i=0; i< SIZE; i++){
        for(int j=0; j< SIZE; j++){
            A[i][j] = 0 ;
        }
    }
}

int main()
{


	DATA r;
	double before,after;
    double interchange, blocking, inter_blok, normal =0;
	initialize_2d_array(A);
	initialize_2d_array(B);
    clear_array(C3);
    clear_array(C2);
    clear_array(C4);
    printf("----- ----- ----- Matrix Size: %d, Block Size %d ----- ------ -----\n",SIZE,block_size );
    printf("# \t Normal \t Interchanged \t Blocked \t Blocked_Interchanged \n");
    for (int i=0; i<10; i++){
        printf("%d \t ",i );
	before = seconds();

	mat_mat(A,B,C);

	after = seconds();
    normal+= (after-before );
	//printf("Conventional Time:%f\n",after-before);
    printf("%f \t ",after-before);

   
    
    before = seconds();

    mat_mat_interchanged(A,B,C2);
    
    after = seconds();
    interchange+= (after-before );
    printf("%f \t ",after-before);
   // printf("Interchanged Time:%f\n",after-before);

   // printf("verification:%d\n",compare(C,C2));
    
     before = seconds();

    mat_mat_blocked(A,B,C3);
   
    after = seconds();
    blocking+= (after-before );
    printf("%f \t ",after-before);
    //printf("Blocked Time:%f\n",after-before);

    //printf("verification:%d\n",compare(C,C3));


     before = seconds();

    mat_mat_blocked_interchanged(A,B,C4);

    after = seconds();
      inter_blok+= (after-before );
      printf("%f \n",after-before);
   // printf("Blocked Interchanged Time:%f\n",after-before);

    //printf("verification:%d\n",compare(C,C4));
    }
    printf("----------------------- ----------- Avarage ----------- --------------------------\n");
    printf(" \t %f \t %f \t %f \t %f\n",(normal/10),(interchange/10), (blocking/10),(inter_blok/10) );
    
    return 0;
}