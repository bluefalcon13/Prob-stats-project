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
	FILE * wr = fopen("/media/jfisher/Games/project_output/output.csv","w");
	srand(time(NULL));
	uint64_t max = 0;
	uint64_t i,iterations;
	iterations = 0;
	for(i=0;i<32;i++){
		max = (max<<1)+1;
	}
	omp_set_num_threads(16);
	#pragma omp parallel
	{
        #pragma omp for
        for(i=0;i<((max+1)/100);i++){
	        //for ret_vals, slot 0 is upper64bits, slot 1 is lower 64bits
	        int j;
	        uint64_t ret_vals[2][2]={0};
	        uint32_t states[2][4]={0};
	        uint8_t temp_init[8]={0};
	        uint64_t init_vector = rand()%(max+1);
	        for(j=0; j<8; j++){
		        temp_init[j]=(i>>(7-j))&0xff;
	        }
	        gmr1_a5_getstates(temp_init,0,states);
	        convert_states(states[0],ret_vals[0]);
	        convert_states(states[1],ret_vals[1]);
	        convert_states(states[2],ret_vals[2]);
	        fprintf(wr,"%lu,%lu%lu,%lu%lu\n",i,ret_vals[0][0],ret_vals[0][1],ret_vals[1][0],ret_vals[1][1]);
	        iterations +=1;
	        printf("%.2f percent complete, i = %lu\n",(((double)iterations)/(max+1))*100,i);
        }
    }
	fclose(wr);
	return 0;
}
