#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<osmo_a5.h>
#include<omp.h>
#include<time.h>


//function to convert initial states to single uint128_t
void convert_states(uint32_t r[4],uint64_t ret_vals[2]){
	ret_vals[0]=r[0]>>2;
	uint64_t temp_r[4]={0};
	int i;
	for(i=0; i<4; i++){
		temp_r[i]=(uint64_t)r[i];
	}
	ret_vals[1]=temp_r[3]+(temp_r[2]<<17)+(temp_r[1]<<40)+((temp_r[0]&0x3)<<62);	
}

int main(){
	//random gen, 10million datapoints
	FILE * wr = fopen("output_rand1.csv","w");
	srand(time(NULL));
	uint64_t max = 0;
	uint64_t i,iterations;
	iterations = 0;
	for(i=0;i<64;i++){
		max = (max<<1)+1;
	}
	omp_set_num_threads(16);
	#pragma omp parallel
	{
        #pragma omp for
        for(i=0;i<10000000;i++){
	        //for ret_vals, slot 0 is upper64bits, slot 1 is lower 64bits
	        int j;
	        uint64_t ret_vals[2][2]={0};
	        uint32_t states[2][4]={0};
	        uint8_t temp_init[8]={0};
	        uint64_t init_vector = rand()%(max);
	        for(j=0; j<8; j++){
		        temp_init[j]=(init_vector>>(7-j))&0xff;
	        }
	        gmr1_a5_getstates(temp_init,0,states);
	        convert_states(states[0],ret_vals[0]);
	        convert_states(states[1],ret_vals[1]);
	        convert_states(states[2],ret_vals[2]);
	        fprintf(wr,"%lu,%lu%lu\n",init_vector,ret_vals[0][0],ret_vals[0][1]);
	        iterations +=1;
	        printf("%.2f percent complete, init_vector = %lu\n",(((double)iterations)/(40000000))*100,init_vector);
        }
    }
    fclose(wr);
    //loop to generator 10million data points, with init vector 0<=init<=10million
    iterations =0;
    FILE * wr2 = fopen("output.csv","w");
    #pragma omp parallel
	{
        #pragma omp for
        for(i=0;i<10000000;i++){
	        //for ret_vals, slot 0 is upper64bits, slot 1 is lower 64bits
	        int j;
	        uint64_t ret_vals[2][2]={0};
	        uint32_t states[2][4]={0};
	        uint8_t temp_init[8]={0};
	        uint64_t init_vector = i;
	        for(j=0; j<8; j++){
		        temp_init[j]=(init_vector>>(7-j))&0xff;
	        }
	        gmr1_a5_getstates(temp_init,0,states);
	        convert_states(states[0],ret_vals[0]);
	        convert_states(states[1],ret_vals[1]);
	        convert_states(states[2],ret_vals[2]);
	        fprintf(wr2,"%lu,%lu%lu\n",init_vector,ret_vals[0][0],ret_vals[0][1]);
	        iterations +=1;
	        printf("%.2f percent complete, init_vector = %lu\n",(((double)iterations)/(40000000))*100,init_vector);
        }
    }
	fclose(wr2);
	FILE * wr3 = fopen("output_rand2.csv","w");
    #pragma omp parallel
	{
        #pragma omp for
        for(i=0;i<10000000;i++){
	        //for ret_vals, slot 0 is upper64bits, slot 1 is lower 64bits
	        int j;
	        uint64_t ret_vals[2][2]={0};
	        uint32_t states[2][4]={0};
	        uint8_t temp_init[8]={0};
	        uint64_t init_vector = rand()%(max);
	        for(j=0; j<8; j++){
		        temp_init[j]=(init_vector>>(7-j))&0xff;
	        }
	        gmr1_a5_getstates(temp_init,0,states);
	        convert_states(states[0],ret_vals[0]);
	        convert_states(states[1],ret_vals[1]);
	        convert_states(states[2],ret_vals[2]);
	        fprintf(wr3,"%lu,%lu%lu\n",init_vector,ret_vals[0][0],ret_vals[0][1]);
	        iterations +=1;
	        printf("%.2f percent complete, init_vector = %lu\n",(((double)iterations)/(40000000))*100,init_vector);
        }
    }
	fclose(wr3);
	FILE * wr4 = fopen("output_rand3.csv","w");
    #pragma omp parallel
	{
        #pragma omp for
        for(i=0;i<10000000;i++){
	        //for ret_vals, slot 0 is upper64bits, slot 1 is lower 64bits
	        int j;
	        uint64_t ret_vals[2][2]={0};
	        uint32_t states[2][4]={0};
	        uint8_t temp_init[8]={0};
	        uint64_t init_vector = rand()%(max);
	        for(j=0; j<8; j++){
		        temp_init[j]=(init_vector>>(7-j))&0xff;
	        }
	        gmr1_a5_getstates(temp_init,0,states);
	        convert_states(states[0],ret_vals[0]);
	        convert_states(states[1],ret_vals[1]);
	        convert_states(states[2],ret_vals[2]);
	        fprintf(wr4,"%lu,%lu%lu\n",init_vector,ret_vals[0][0],ret_vals[0][1]);
	        iterations +=1;
	        printf("%.2f percent complete, init_vector = %lu\n",(((double)iterations)/(40000000))*100,init_vector);
        }
    }
	fclose(wr4);
	return 0;
}
