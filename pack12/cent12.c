/*
USAGE: ./09cent 03_V2.log str2 str3
str2: RESIDUE NUMBER ( "105" "114" etc )
str3: COEFFICIENT OF SIGMA ( "2" "0" etc )
	Especially "0" is selected as a coefficient, then all data of group are putout
INPUT: ./pdbtmp/...
OUTPUT: ./result/...
*/
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>

        typedef  struct{
                char atmn[21000][10],resn[21000][10],reco[21000][10],elem[21000][10],chai[21000][4];
                int anum[21000], rnum[21000];
                double cord[21000][3],occu[21000],ru[21000];
                }pdb;

 //show pdb data on screen 
int print(pdb *a,int i){int j;        for(j=0;j<i;j++){                if(strlen(a->atmn[j])==4){                printf("%5d,%-6s%5d%5s%4s%2s%4d%12.3f%8.3f%8.3f%6.2f%8.4f%12s\n",                        j+1,a->reco[j],a->anum[j],a->atmn[j],a->resn[j],a->chai[j],a->rnum[j],                        a->cord[j][0],a->cord[j][1],a->cord[j][2],a->occu[j],a->ru[j],a->elem[j]);                }else{                printf("%5d,%-6s%5d  %-3s%4s%2s%4d%12.3f%8.3f%8.3f%6.2f%8.4f%12s\n",                        j+1,a->reco[j],a->anum[j],a->atmn[j],a->resn[j],a->chai[j],a->rnum[j],                        a->cord[j][0],a->cord[j][1],a->cord[j][2],a->occu[j],a->ru[j],a->elem[j]);                }        }return 0;}

//output pdb data in text file
int print2(pdb *a,int i){FILE *fout;        if( (fout = fopen("cp_test.txt","w")) == NULL ){printf( "Cannot open input \n" ); exit(1); }        int j;        for(j=0;j<i;j++){                if(strlen(a->atmn[j])==4){                fprintf(fout,"%-6s%5d%5s%4s%2s%4d%12.3f%8.3f%8.3f%6.2f%8.4f%12s\n",                        a->reco[j],a->anum[j],a->atmn[j],a->resn[j],a->chai[j],a->rnum[j],                        a->cord[j][0],a->cord[j][1],a->cord[j][2],a->occu[j],a->ru[j],a->elem[j]);                }else{                fprintf(fout,"%-6s%5d  %-3s%4s%2s%4d%12.3f%8.3f%8.3f%6.2f%8.4f%12s\n",                a->reco[j],a->anum[j],a->atmn[j],a->resn[j],a->chai[j],a->rnum[j],                a->cord[j][0],a->cord[j][1],a->cord[j][2],a->occu[j],a->ru[j],a->elem[j]);                }        }
return 0;}


int Ru_convertion(pdb* in,pdb* orig,char* str1,char* str2){	// to convert temperature-factor into Ru
	int i=0,j=0,u,ret,buf3[21000],v=0,w=0;
	char buf1[100],buf2[100],str[10]="     1";
        FILE *fru,*fin;	
	char name[100];
	sprintf(name,"./pdbtmp/%s",str1);	
                if( (fru = fopen(str2, "r" )) == NULL ){
                printf( "Cannot open input rudata\n" );
                exit(1);
                }
                if( (fin = fopen(name, "r" )) == NULL ){
                printf( "Cannot open input pdbfile" );
                exit(1);
		}
	
		for(u=0;u<21000;u++){
		buf3[u]=30000;
		}

		while( fgets( buf1, sizeof( buf1 ), fru) != NULL){
			if(strncmp(buf1,str,6)==0){
			sscanf(buf1,"%*d%*lf%*lf%*lf%lf%*lf",&in->ru[i]);
 				if(in->ru[i] > 48){
				buf3[i]=i;
				v++;
//				printf("v=%d,ru[%d]=%f\n",v,i,in->ru[i]);
				}
//			printf("prog check in.ru[%d]=%f\n",i,in->ru[i]);
			i++;
			sprintf(str,"%6d",i+1);
			}
		}
	        while( fgets( buf2, sizeof( buf2 ), fin) != NULL){
                	if(strncmp(buf2,"ATOM",4)==0){
	                sscanf(buf2,"%s%d%s%s%s%d%lf%lf%lf%lf%*lf%s",in->reco[j],&in->anum[j],in->atmn[j],
				in->resn[j],in->chai[j],&in->rnum[j],&in->cord[j][0],&in->cord[j][1],
				&in->cord[j][2],&in->occu[j],/*&in->ru[j],*/in->elem[j]);
	
			j++;
	        	}
		}
	printf("on whole j=%d,on Ru i=%d,invalid v=%d,v+i=%d\n",j,i,v,i+v);
		if(i==j){
			for(u=0;u<j;u++){
				while(u==buf3[u]){
//				printf("prog check u=%d\n",u);
				u++;
				}
			strcpy(orig->reco[w],in->reco[u]);
                	orig->anum[w]=in->anum[u];
	                strcpy(orig->atmn[w],in->atmn[u]);    
        	        strcpy(orig->resn[w],in->resn[u]);    
                        strcpy(orig->chai[w],in->chai[u]);                	
			orig->rnum[w]=in->rnum[u];    
	                orig->cord[w][0]=in->cord[u][0];    
        	        orig->cord[w][1]=in->cord[u][1];
                	orig->cord[w][2]=in->cord[u][2];
	                orig->occu[w]=in->occu[u];
//                        printf("prog check in.ru[%d]=%f\n",u,in->ru[u]);
			orig->ru[w]=in->ru[u];      
        	        strcpy(orig->elem[w],in->elem[u]);    
//			printf("prog check orig.ru[%d]=%f\n",w,orig->ru[w]);
			w++;
			}
		}else if(j==i-v){
		u=0;
			for(w=0;w<i-v;w++){
				while(u==buf3[u]){
 	                       u++;
                               }
                        strcpy(orig->reco[w],in->reco[w]);
                        orig->anum[w]=in->anum[w];
                        strcpy(orig->atmn[w],in->atmn[w]);
                        strcpy(orig->resn[w],in->resn[w]);
                        strcpy(orig->chai[w],in->chai[w]);
                        orig->rnum[w]=in->rnum[w];
                        orig->cord[w][0]=in->cord[w][0];
                        orig->cord[w][1]=in->cord[w][1];
                        orig->cord[w][2]=in->cord[w][2];
                        orig->occu[w]=in->occu[w];
                        orig->ru[w]=in->ru[u];  
                        strcpy(orig->elem[w],in->elem[w]);
                        u++;
			}
		}else{
		puts("ERROR: The number of Data in input is not compatible with the number of Ru");
		printf("Data number(j)=%d\nRu number(i)=%d\nvalid Ru(i-v)=%d\n",j,i,i-v);
		exit(1);
		}
	
	fclose( fin );
	fclose( fru );

return i-v;
}


double ave(double *all, int i){		// to determine average
	double total=0;
	int u;
		for(u=0;u<i;u++){
		total+=all[u];
		}
return total/i;
}


int ascending(pdb* orig,pdb* sort,int i){	// to sort Ru in ascending order
	int j,k,l,m,n,o;
	double min=10000,diff;
		for(l=0;l<i;l++){
			if(min>=orig->ru[l]){
			min=orig->ru[l];
			m=l;
			}
		}
	o=m+1;	//o is a return value
//	printf("o=%d\n",o);
	strcpy(sort->reco[0],orig->reco[m]);
        sort->anum[0]=orig->anum[m];
        strcpy(sort->atmn[0],orig->atmn[m]);
        strcpy(sort->resn[0],orig->resn[m]);
        strcpy(sort->chai[0],orig->chai[m]);
        sort->rnum[0]=orig->rnum[m];
        sort->cord[0][0]=orig->cord[m][0];
        sort->cord[0][1]=orig->cord[m][1];
        sort->cord[0][2]=orig->cord[m][2];
        sort->occu[0]=orig->occu[m];
        sort->ru[0]=orig->ru[m];
        strcpy(sort->elem[0],orig->elem[m]);

		for(n=0;n<i-1;n++){
		diff=100000;
	                for(j=0;j<i;j++){
        	                if(j!=m && orig->ru[j] >= orig->ru[m] && orig->ru[j] - orig->ru[m] <= diff){
                	        diff= orig->ru[j] - orig->ru[m];	
                        	k=j;
	                     	}
                	}
                strcpy(sort->reco[n+1],orig->reco[k]);
		sort->anum[n+1]=orig->anum[k];
		strcpy(sort->atmn[n+1],orig->atmn[k]);
		strcpy(sort->resn[n+1],orig->resn[k]);
 		strcpy(sort->chai[n+1],orig->chai[k]);
                sort->rnum[n+1]=orig->rnum[k];
 	        sort->cord[n+1][0]=orig->cord[k][0];
                sort->cord[n+1][1]=orig->cord[k][1];
                sort->cord[n+1][2]=orig->cord[k][2];
                sort->occu[n+1]=orig->occu[k];
                sort->ru[n+1]=orig->ru[k];
                strcpy(sort->elem[n+1],orig->elem[k]);

			if(orig->ru[m]=orig->ru[k]){
			orig->ru[m]=0;
			}
		m=k;
		}
	printf("The Data Having The Highest Ru Data Number orig.Ru[%d]=%f\n",m+1,orig->ru[m]);
return o;
}


int separation(pdb *sort,pdb *out,int g,int h,int i){
        int j,k,l=0;
	j=i*g/100+0.5;
	k=i*h/100+0.5;	// to add +0.5 for rounding k 
		for(j=i*g/100+0.5; j<k; j++){
                strcpy(out->reco[l],sort->reco[j]);
                out->anum[l]=sort->anum[j];
                strcpy(out->atmn[l],sort->atmn[j]);
                strcpy(out->resn[l],sort->resn[j]);
                strcpy(out->chai[l],sort->chai[j]);
                out->rnum[l]=sort->rnum[j];
                out->cord[l][0]=sort->cord[j][0];
                out->cord[l][1]=sort->cord[j][1];
                out->cord[l][2]=sort->cord[j][2];
                out->occu[l]=sort->occu[j];
                out->ru[l]=sort->ru[j];
                strcpy(out->elem[l],sort->elem[j]);
		l++;
		}
return l;
}


double stddev(double *x,int n){
	double s,sm=0,av;
	int a;

	av=ave(x,n);
		for(a=0;a<n;a++){
		sm=sm+pow(x[a]-av,2);
		}
	s=sqrt(sm/n);
return s;
}


double population(double *x,double *y,double *z,double *s,int i,float l){
	int j,k=0;
	double av_x=ave(x,i),av_y=ave(y,i),av_z=ave(z,i);
		for(j=0;j<i;j++){
			if(        av_x-s[0]*l<=x[j] && x[j]<=av_x+s[0]*l
				&& av_y-s[1]*l<=y[j] && y[j]<=av_y+s[1]*l
				&& av_z-s[2]*l<=z[j] && z[j]<=av_z+s[2]*l){
			k++;
			}
		}
return (double)100*k/i;
}


int group_pdb(int m,char *I,char fil,char* str,pdb *in,double *com,double *sigma,int l){
        int k=0,j;
	char rename[100];
		sprintf(rename,"result12/outpdb_cor/%d/%d_%s%s.pdb",m,m,str,I);
	FILE *fout;
                if( (fout = fopen(rename,"w")) == NULL ){
                printf("ERROR: cannot make file AB.pdb\n");
		printf("make the directory: ./result12/outpdb_cor/\n");
                exit(1);
                }

if(m==0){
for(j=0;j<l;j++){
	if(strlen(in->atmn[j])==4){                                fprintf(fout,"%-6s%5d%5s%4s%2s%4d%12.3f%8.3f%8.3f%6.2f%8.4f%12s\n",in->reco[j],in->anum[j],in->atmn[j],in->resn[j],in->chai[j],in->rnum[j],in->cord[j][0],in->cord[j][1],in->cord[j][2],in->occu[j],in->ru[j]*100,in->elem[j]);                                }else{                                fprintf(fout,"%-6s%5d  %-3s%4s%2s%4d%12.3f%8.3f%8.3f%6.2f%8.4f%12s\n",in->reco[j],in->anum[j],in->atmn[j],in->resn[j],in->chai[j],in->rnum[j],in->cord[j][0],in->cord[j][1],in->cord[j][2],in->occu[j],in->ru[j]*100,in->elem[j]);                                }
k++;	}
}else{
                for(j=0;j<l;j++){
                        if(        com[0]-sigma[0]*m <= in->cord[j][0] && in->cord[j][0] <= com[0]+sigma[0]*m
                                && com[1]-sigma[1]*m <= in->cord[j][1] && in->cord[j][1] <= com[1]+sigma[1]*m
                                && com[2]-sigma[2]*m <= in->cord[j][2] && in->cord[j][2] <= com[2]+sigma[2]*m){

				if(strlen(in->atmn[j])==4){
				fprintf(fout,"%-6s%5d%5s%4s%2s%4d%12.3f%8.3f%8.3f%6.2f%8.4f%12s\n",in->reco[j],in->anum[j],in->atmn[j],in->resn[j],in->chai[j],in->rnum[j],in->cord[j][0],in->cord[j][1],in->cord[j][2],in->occu[j],in->ru[j]*100,in->elem[j]);
				}else{
				fprintf(fout,"%-6s%5d  %-3s%4s%2s%4d%12.3f%8.3f%8.3f%6.2f%8.4f%12s\n",in->reco[j],in->anum[j],in->atmn[j],in->resn[j],in->chai[j],in->rnum[j],in->cord[j][0],in->cord[j][1],in->cord[j][2],in->occu[j],in->ru[j]*100,in->elem[j]);
				}
			k++;
                        }
                }
}
	fprintf(fout,"TER\nHETATM%5d  %-4s%3s%5d%12.3f%8.3f%8.3f%6.2f%6.2f%12s\n",0,"O","HOH",0,
		com[0],com[1],com[2],1.00,1.00,"O");	

        fclose( fout );
float f=(float)100*k/l;
return k;
}


// convert only mode of file
int group_pdb_copy(int m,char *I,char fil,char* str,pdb *in,double *com,double *sigma,int l){        int k=0,j;        char rename[100];                sprintf(rename,"result12/outpdb_cor/%d/%d_%s%s.pdb",m,m,str,I);        FILE *fout;                if( (fout = fopen(rename,"a")) == NULL ){                printf("ERROR: cannot make file AB.pdb\n");                printf("make the directory: ./result12/outpdb_cor/\n");                exit(1);                }if(m==0){for(j=0;j<l;j++){        if(strlen(in->atmn[j])==4){                                fprintf(fout,"%-6s%5d%5s%4s%2s%4d%12.3f%8.3f%8.3f%6.2f%8.4f%12s\n",in->reco[j],in->anum[j],in->atmn[j],in->resn[j],in->chai[j],in->rnum[j],in->cord[j][0],in->cord[j][1],in->cord[j][2],in->occu[j],in->ru[j]*100,in->elem[j]);                                }else{                                fprintf(fout,"%-6s%5d  %-3s%4s%2s%4d%12.3f%8.3f%8.3f%6.2f%8.4f%12s\n",in->reco[j],in->anum[j],in->atmn[j],in->resn[j],in->chai[j],in->rnum[j],in->cord[j][0],in->cord[j][1],in->cord[j][2],in->occu[j],in->ru[j]*100,in->elem[j]);                                }k++;    }}else{                for(j=0;j<l;j++){                        if(        com[0]-sigma[0]*m <= in->cord[j][0] && in->cord[j][0] <= com[0]+sigma[0]*m                                && com[1]-sigma[1]*m <= in->cord[j][1] && in->cord[j][1] <= com[1]+sigma[1]*m                                && com[2]-sigma[2]*m <= in->cord[j][2] && in->cord[j][2] <= com[2]+sigma[2]*m){                                if(strlen(in->atmn[j])==4){                                fprintf(fout,"%-6s%5d%5s%4s%2s%4d%12.3f%8.3f%8.3f%6.2f%8.4f%12s\n",in->reco[j],in->anum[j],in->atmn[j],in->resn[j],in->chai[j],in->rnum[j],in->cord[j][0],in->cord[j][1],in->cord[j][2],in->occu[j],in->ru[j]*100,in->elem[j]);                                }else{                                fprintf(fout,"%-6s%5d  %-3s%4s%2s%4d%12.3f%8.3f%8.3f%6.2f%8.4f%12s\n",in->reco[j],in->anum[j],in->atmn[j],in->resn[j],in->chai[j],in->rnum[j],in->cord[j][0],in->cord[j][1],in->cord[j][2],in->occu[j],in->ru[j]*100,in->elem[j]);
                                }
                        k++;
                        }
                }
}
        fprintf(fout,"TER\nHETATM%5d  %-4s%3s%5d%12.3f%8.3f%8.3f%6.2f%6.2f%12s\n",0,"O","HOH",0,
                com[0],com[1],com[2],1.00,1.00,"O");

        fclose( fout );
float f=(float)100*k/l;
return k;
}



double ave2(pdb *p,double *c,int l){	//calculate an average of length from center of mass
        double sum;
	int j;
	
	for(j=0;j<l;j++){
        sum+=sqrt(pow(p->cord[j][0]-c[0],2)+pow(p->cord[j][1]-c[1],2)+pow(p->cord[j][2]-c[2],2));
        }
return sum/l;
}


double stddv2(pdb *p,double *c,int l){	//calculate a standard deviaton from length
	double s2,sum=0,ave,x[21000],y[21000],z[21000],leng;
	int j;

        for(j=0;j<l;j++){
        x[j]=p->cord[j][0];y[j]=p->cord[j][1];z[j]=p->cord[j][2];
	}
	for(j=0;j<l;j++){
	sum+=sqrt(pow(x[j]-c[0],2)+pow(y[j]-c[1],2)+pow(z[j]-c[2],2));
	}
	ave=sum/l;
	sum=0;
	for(j=0;j<l;j++){
	leng=sqrt(pow(x[j]-c[0],2)+pow(y[j]-c[1],2)+pow(z[j]-c[2],2));
	sum+=pow(leng-ave,2);
	s2=sqrt(sum/l);
	}
	
return s2;
}


//reconstruct a group from a standard deviation of length
int group_pdb2(int m,char *I,char fil,char* str,pdb *in,double *com,double c,double s,int l){
        int k=0,j;
	char rename[100];
		sprintf(rename,"result12/outpdb_dis/%d/%d_L%s%s.pdb",m,m,str,I);
	FILE *fout;
	double leng;
                if( (fout = fopen(rename,"w")) == NULL ){
                printf("ERROR: cannot make file L.pdb \n");
		printf("make the directory: ./result/outpdb_dis/\n");
                exit(1);
                }
if(m==0){
	for(j=0;j<l;j++){
	if(strlen(in->atmn[j])==4){                                fprintf(fout,"%-6s%5d%5s%4s%2s%4d%12.3f%8.3f%8.3f%6.2f%8.4f%12s\n",in->reco[j],in->anum[j],in->atmn[j],in->resn[j],in->chai[j],in->rnum[j],in->cord[j][0],in->cord[j][1],in->cord[j][2],in->occu[j],in->ru[j]*100,in->elem[j]);
                                }else{                                fprintf(fout,"%-6s%5d  %-3s%4s%2s%4d%12.3f%8.3f%8.3f%6.2f%8.4f%12s\n",in->reco[j],in->anum[j],in->atmn[j],in->resn[j],in->chai[j],in->rnum[j],in->cord[j][0],in->cord[j][1],in->cord[j][2],in->occu[j],in->ru[j]*100,in->elem[j]);
	}k++;}
}else{
	for(j=0;j<l;j++){
        leng=sqrt(pow(in->cord[j][0]-com[0],2)+pow(in->cord[j][1]-com[1],2)+pow(in->cord[j][2]-com[2],2));
		        if(leng <= s*m){
				if(strlen(in->atmn[j])==4){
				fprintf(fout,"%-6s%5d%5s%4s%2s%4d%12.3f%8.3f%8.3f%6.2f%8.4f%12s\n",in->reco[j],in->anum[j],in->atmn[j],in->resn[j],in->chai[j],in->rnum[j],in->cord[j][0],in->cord[j][1],in->cord[j][2],in->occu[j],in->ru[j]*100,in->elem[j]);
				}else{
				fprintf(fout,"%-6s%5d  %-3s%4s%2s%4d%12.3f%8.3f%8.3f%6.2f%8.4f%12s\n",in->reco[j],in->anum[j],in->atmn[j],in->resn[j],in->chai[j],in->rnum[j],in->cord[j][0],in->cord[j][1],in->cord[j][2],in->occu[j],in->ru[j]*100,in->elem[j]);
				}
			k++;
                        }
        }
	fprintf(fout,"TER\n");
	double r1,r2,x,y,z;
	double pi=M_PI;
	for(r1=0; r1<2*pi; r1+=pi/18){
		for(r2=0; r2<2*pi; r2+=pi/18){
		x=com[0]+m*(s*cos(r1))*cos(r2);
		y=com[1]+m*(s*cos(r1))*sin(r2);
		z=com[2]+m*s*sin(r1);
		fprintf(fout,"HETATM%5d  %-4s%3s%5d%12.3f%8.3f%8.3f%6.2f%6.2f%12s\n",0,"S","S",0,
			x,y,z,1.00,1.00,"S");
		}
	}
}
	fprintf(fout,"TER\nHETATM%5d  %-4s%3s%5d%12.3f%8.3f%8.3f%6.2f%6.2f%12s\n",0,"O","HOH",0,
		com[0],com[1],com[2],1.00,1.00,"O");	

        fclose( fout );
float f=(float)100*k/l;
return k;
}



// convert only the mode of file
int group_pdb2_copy(int m,char *I,char fil,char* str,pdb *in,double *com,double c,double s,int l){        int k=0,j;        char rename[100];                sprintf(rename,"result12/outpdb_dis/%d/%d_L%s%s.pdb",m,m,str,I);        FILE *fout;        double leng;                if( (fout = fopen(rename,"a")) == NULL ){                printf("ERROR: cannot make file L.pdb\n");                printf("make the directory: ./result12/outpdb_dis/\n");                exit(1);                }
if(m==0){        for(j=0;j<l;j++){        if(strlen(in->atmn[j])==4){                                fprintf(fout,"%-6s%5d%5s%4s%2s%4d%12.3f%8.3f%8.3f%6.2f%8.4f%12s\n",in->reco[j],in->anum[j],in->atmn[j],in->resn[j],in->chai[j],in->rnum[j],in->cord[j][0],in->cord[j][1],in->cord[j][2],in->occu[j],in->ru[j]*100,in->elem[j]);                                }else{                                fprintf(fout,"%-6s%5d  %-3s%4s%2s%4d%12.3f%8.3f%8.3f%6.2f%8.4f%12s\n",in->reco[j],in->anum[j],in->atmn[j],in->resn[j],in->chai[j],in->rnum[j],in->cord[j][0],in->cord[j][1],in->cord[j][2],in->occu[j],in->ru[j]*100,in->elem[j]);        }k++;}}else{        for(j=0;j<l;j++){        leng=sqrt(pow(in->cord[j][0]-com[0],2)+pow(in->cord[j][1]-com[1],2)+pow(in->cord[j][2]-com[2],2));                        if(leng <= s*m){                                if(strlen(in->atmn[j])==4){                                fprintf(fout,"%-6s%5d%5s%4s%2s%4d%12.3f%8.3f%8.3f%6.2f%8.4f%12s\n",in->reco[j],in->anum[j],in->atmn[j],in->resn[j],in->chai[j],in->rnum[j],in->cord[j][0],in->cord[j][1],in->cord[j][2],in->occu[j],in->ru[j]*100,in->elem[j]);                                }else{                                fprintf(fout,"%-6s%5d  %-3s%4s%2s%4d%12.3f%8.3f%8.3f%6.2f%8.4f%12s\n",in->reco[j],in->anum[j],in->atmn[j],in->resn[j],in->chai[j],in->rnum[j],in->cord[j][0],in->cord[j][1],in->cord[j][2],in->occu[j],in->ru[j]*100,in->elem[j]);                                }                        k++;                        }        }        fprintf(fout,"TER\n");        double r1,r2,x,y,z;        double pi=M_PI;        for(r1=0; r1<2*pi; r1+=pi/18){                for(r2=0; r2<2*pi; r2+=pi/18){                x=com[0]+m*(s*cos(r1))*cos(r2);                y=com[1]+m*(s*cos(r1))*sin(r2);                z=com[2]+m*s*sin(r1);                fprintf(fout,"HETATM%5d  %-4s%3s%5d%12.3f%8.3f%8.3f%6.2f%6.2f%12s\n",0,"S","S",0,                        x,y,z,1.00,1.00,"S");                }        }
}
        fprintf(fout,"TER\nHETATM%5d  %-4s%3s%5d%12.3f%8.3f%8.3f%6.2f%6.2f%12s\n",0,"O","HOH",0,                com[0],com[1],com[2],1.00,1.00,"O");        fclose( fout );
float f=(float)100*k/l;
return k;
}



int main(int argc,char *argv[]){
puts("---------------------------------------------------------------------------------------------");
	if(argv[1]==NULL || argv[2]==NULL ){
	puts("command mistake");
	puts("usage:$ ./cent 03_V2.log RESIDUE_NUMBER COEFFICIENT_OF_SIGMA");
	puts("COEFFICIENT= 0 or 1 or 2 or 3 or .....");
	exit(1);
	}
	
	int i,l,j,k,m,l1,m1,o;
	double com1[3],comA[3],comB[3];
	double sigmaA[3],sigmaB[3];
	double x[21000],y[21000],z[21000];	
	pdb pin,orig,sort,groupA,groupB;
// "a" is a coefficient of Sigma 
        int a;        if(argv[3]==NULL ){        a=2;        }else{        a=atoi(argv[3]);        }

printf("Data number: %s\n",argv[2]);

	i=Ru_convertion(&pin,&orig,argv[2],argv[1]);	//make pin, orig, com1
	        for(j=0;j<i;j++){
                x[j]=orig.cord[j][0];
		y[j]=orig.cord[j][1];
		z[j]=orig.cord[j][2];
		}
	com1[0]=ave(x,i); com1[1]=ave(y,i); com1[2]=ave(z,i);	     

	o=ascending(&orig,&sort,i);
	printf("The Data Having The Lowest Ru Data Number orig.ru[%d]=%f\n",o,sort.ru[0]);
	printf("the number of valid data=%d\n",i);
//	print(&sort,i);
//	print2(&sort,i);

//make groupA
	l=separation(&sort,&groupA,0,25,i);
                for(j=0;j<l;j++){
                x[j]=groupA.cord[j][0];
                y[j]=groupA.cord[j][1];
                z[j]=groupA.cord[j][2];
                }
        comA[0]=ave(x,l); comA[1]=ave(y,l); comA[2]=ave(z,l);
	sigmaA[0]=stddev(x,l); sigmaA[1]=stddev(y,l); sigmaA[2]=stddev(z,l);
//except bad data by standard deviation
        l1=group_pdb(a,"AB",'A',argv[2],&groupA,comA,sigmaA,l);
//	printf("A Percentage within +-Sigma*%d=%.2f%%\n",a,population(x,y,z,sigmaA,l,a));

//make groupB
	m=separation(&sort,&groupB,75,100,i);
                for(j=0;j<m;j++){
                x[j]=groupB.cord[j][0];
                y[j]=groupB.cord[j][1];
                z[j]=groupB.cord[j][2];
                }
        comB[0]=ave(x,m); comB[1]=ave(y,m); comB[2]=ave(z,m);
        sigmaB[0]=stddev(x,m); sigmaB[1]=stddev(y,m); sigmaB[2]=stddev(z,m);
//except bad data 
        m1=group_pdb_copy(a,"AB",'B',argv[2],&groupB,comB,sigmaB,m);
//	printf("B Percentage within +-Sigma*%d=%.2f%%\n",a,population(x,y,z,sigmaB,m,a));

//output pdb file part2 that depends on its length from center of mass
	group_pdb(a,"AB_ba",'A',argv[2],&groupA,comB,sigmaB,l);
	group_pdb_copy(a,"AB_ba",'B',argv[2],&groupB,comA,sigmaA,m);	
//s2A,s2B are defined from length. c2A,c2B are average length from center.
	double s2A,s2B,c2A,c2B;
	s2A=stddv2(&groupA,comA,l);s2B=stddv2(&groupB,comB,m);	
	c2A=ave2(&groupA,comA,l);c2B=ave2(&groupB,comB,m);
	
	int l2,m2;
	l2=group_pdb2(a,"AB",'A',argv[2],&groupA,comA,c2A,s2A,l);
        m2=group_pdb2_copy(a,"AB",'B',argv[2],&groupB,comB,c2B,s2B,m);
	
	
puts("---------------------------------------------------------------------------------------------");
return 0;
}

