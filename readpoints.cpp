#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

void main(){
	FILE *fin;
	FILE *fout;
	char t[11], preword1[20] = "#", preword2[20] = "vertices", preword3[20] = "faces", preword4[20] = "Vertex", preword5[20] = "Face";
	int num,Vnum,Fnum,p1[20000],p2[20000],p3[20000];
	float x[20000],y[20000],z[20000];


	if((fin = fopen("legoman.m","r"))==NULL)
	{
		printf("\nerror on open input file!");

		getchar();
		exit(1);
	}

	if((fout = fopen("haha.txt","w"))==NULL)
	{
		printf("\nerror on open output file!");
		
		getchar();
		exit(1);
	}

	fprintf(fout, "hha");

	while(fgetc(fin)!=EOF){
		fscanf(fin,"%s",t);
		//printf("%s", t);
		
		if(strcmp(t,preword4)==0){
			fscanf(fin,"%d",&num);
			fscanf(fin,"%f",&x[num]);
			fscanf(fin,"%f",&y[num]);
			fscanf(fin,"%f",&z[num]);
			Vnum = num;
		}
		else if(strcmp(t,preword5)==0){
			fscanf(fin,"%d",&num);
			fscanf(fin,"%d",&p1[num]);
			fscanf(fin,"%d",&p2[num]);
			fscanf(fin,"%d",&p3[num]);
			Fnum = num;
		}
		
	}

//	printf("haha");
//	fprintf(fout,"hahajh");

	for(int i = 0; i < Vnum + 1; i++){
		fprintf(fout,"\nvertices %d %f %f %f", i, x[i], y[i], z[i]);
		printf("\nvertices %d %f %f %f", i, x[i], y[i], z[i]);
	}

	for(int l = 0; l < Fnum + 1; l++){
		fprintf(fout,"\nfaces %d %d %d %d", l, p1[l], p2[l], p3[l]);
		printf("\nfaces %d %d %d %d", l, p1[l], p2[l], p3[l]);
	}


	fclose(fin);
	fclose(fout);
}

