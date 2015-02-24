//USAGE: (RESNUM) (INTERVAL)

#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>



double ave(double *all, int i){		// to determine average
	double total=0;
	int u;
		for(u=0;u<i;u++){
		total+=all[u];
		}
return total/i;
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


double stddv2(double *x,double *y,double *z,int l){	//calculate a standard deviaton from length
	double c[3],s2,sum=0,av,leng;
	int j;
	c[0]=ave(x,l); c[1]=ave(y,l); c[2]=ave(z,l);

	for(j=0;j<l;j++){
	sum+=sqrt(pow(x[j]-c[0],2)+pow(y[j]-c[1],2)+pow(z[j]-c[2],2));
	}
	av=sum/l;
	
	sum=0;
	for(j=0;j<l;j++){
	leng=sqrt(pow(x[j]-c[0],2)+pow(y[j]-c[1],2)+pow(z[j]-c[2],2));
	sum+=pow(leng-av,2);
	s2=sqrt(sum/l);
	}
	
return s2;
}


int count(double *x,double *y,double *z,double *c,double *s,int i,int l){
	int n=0;
        int j;

        for(j=0;j<i;j++){
	        if(	   c[0]-s[0]*l < x[j] && x[j] < c[0]+s[0]*l 
			&& c[1]-s[1]*l < y[j] && y[j] < c[1]+s[1]*l
			&& c[2]-s[2]*l < z[j] && z[j] < c[2]+s[2]*l
			){
		n++;
                }
        }
return n;
}


int count2(double *x,double *y,double *z,double *com,double s0,double s,int i,int l){
	int n=0;
	int j;
	double leng;

	for(j=0;j<i;j++){
	leng=sqrt(pow(x[j]-com[0],2)+pow(y[j]-com[1],2)+pow(z[j]-com[2],2));
		if(s0*l <= leng && leng < s*l){
		n++;
		}
	}
return n;
}


int count3(double *x,double s,double e,int i){
        int n=0;
        int j;
        for(j=0;j<i;j++){
                if( s <= x[j] && x[j] < e ){
                n++;
                }
        }
return n;
}


int exam(char *str,char *name,double *x,double *y,double *z,double *com,double *s1,double s2,int i,float inv){
        char rename[100];
                sprintf(rename,"./result12/exam/%s_%s_exam.dat",str,name);
        FILE *fout;
                if( (fout = fopen(rename,"w")) == NULL ){
                printf("ERROR: cannot open exam1.dat\n");
                exit(1);
                }
        int n;
        double j,k[3],p[3];

	fprintf(fout,"RESIDUE_%s/GROUP_%s/FROM LENGTH\n[ length ]    Sigma=%f\n	length    volume\n",str,name,s2);
                for(j=0;j<=20;j+=inv){
                n=count2(x,y,z,com,j,j+inv,i,1);
                fprintf(fout,"%6.2f%10d\n",j,n);
                }

        fprintf(fout,"\n\nRESIDUE_%s/GROUP_%s/FROM CORDINATE\n[ x*y*z ]    Sigma=%f\nlength    volume\n",str,name,ave(s1,3));
		for(j=0;j<=20;j+=inv){
                k[0]=j+inv;k[1]=j+inv;k[2]=j+inv;
		p[0]=j;p[1]=j;p[2]=j;
                n=count(x,y,z,com,k,i,1)-count(x,y,z,com,p,i,1);
                fprintf(fout,"%6.2f%10d\n",j,n);
                }
        fprintf(fout,"\n\nRESIDUE_%s/GROUP_%s/FROM CORDINATE\n[ only x ]    Sigma=%f Center=%f\nlength    volume\n",str,name,s1[0],com[0]);
		for(j=-10;j<=10;j+=inv){
		n=count3(x,com[0]+j,com[0]+j+inv,i);
                fprintf(fout,"%6.2f%10d\n",com[0]+j,n);
                }
	fprintf(fout,"\n\nRESIDUE_%s/GROUP_%s/FROM CORDINATE\n[ only y ]    Sigma=%f Center=%f\nlength    volume\n",str,name,s1[1],com[1]);
                for(j=-10;j<=10;j+=inv){
                n=count3(y,com[1]+j,com[1]+j+inv,i);
		fprintf(fout,"%6.2f%10d\n",com[1]+j,n);
                }
	fprintf(fout,"\n\nRESIDUE_%s/GROUP_%s/FROM CORDINATE\n[ only z ]    Sigma=%f Center=%f\nlength    volume\n",str,name,s1[2],com[2]);
                for(j=-10;j<=10;j+=inv){
                n=count3(z,com[2]+j,com[2]+j+inv,i);
		fprintf(fout,"%6.2f%10d\n",com[2]+j,n);
                }

        fclose(fout);
return 0;
}



int main(int argc,char *argv[]){
	if(argv[1]==NULL ){
	puts("ERROR: COMMAND MISTAKE");
	puts("USAGE: RESIDUE_NUMBER INTERVAL");
	return 1;
	}
	
	FILE *f1;
	int i=0,j=0,stat=0; 
	char name[100],buf[100],buf2[100];
	double xa[21000],ya[21000],za[21000],xb[21000],yb[21000],zb[21000],comA[3],comB[3],sigmaA[3],sigmaB[3];
	double s1,s2;
	float interval;
        if(argv[2]==NULL ){
	interval=0.5;
	}else{
	interval=atof(argv[2]);
	}

	sprintf(name,"./result12/outpdb_cor/0/0_%sAB.pdb",argv[1]);
               	if( (f1 = fopen(name, "r" )) == NULL ){
                printf( "Cannot open 0_%sAB.pdb",argv[1]);
                exit(1);
		}
/*	sprintf(name,"./result12/pdbB/0/0_%sB.pdb",argv[1]);
               	if( (f2 = fopen(name, "r" )) == NULL ){
               	printf( "Cannot open 0_%sB.pdb",argv[1]);
             	exit(1);
                }
*/	int loop;
/*		while( fgets( buf, sizeof( buf ), f1) == "TER"){
			if(strncmp(buf,"ATOM",4)==0){
	                sscanf(buf,"%*s%*d%*s%*s%*s%*d%lf%lf%lf",&xa[i],&ya[i],&za[i]);
			i++;
			}
	        	
		}*/
		while( fgets( buf, sizeof( buf ), f1) != NULL){
                        if(strncmp(buf,"ATOM",4)==0){
                        sscanf(buf,"%*s%*d%*s%*s%*s%*d%lf%lf%lf",&xb[j],&yb[j],&zb[j]);
                        j++;
			}
			else if(strncmp(buf,"TER",3)==0 && stat==0){
				for(loop=0; loop<j; loop++){
				xa[stat]=xb[stat];ya[stat]=yb[stat];za[stat]=zb[stat];
				stat++;
				}
			i=stat;
			j=0;
			}
                }
	printf("program check groupA number(i)=%d\ngroupB number(j)=%d\n",i,j);

	comA[0]=ave(xa,i); comA[1]=ave(ya,i); comA[2]=ave(za,i);
	comB[0]=ave(xb,j); comB[1]=ave(yb,j); comB[2]=ave(zb,j);
	sigmaA[0]=stddev(xa,i); sigmaA[1]=stddev(ya,i); sigmaA[2]=stddev(za,i);
	sigmaB[0]=stddev(xb,j); sigmaB[1]=stddev(yb,j); sigmaB[2]=stddev(zb,j);
	s1=stddv2(xa,ya,za,i);
	s2=stddv2(xb,yb,zb,j);
	exam(argv[1],"A",xa,ya,za,comA,sigmaA,s1,i,interval);
	exam(argv[1],"B",xb,yb,zb,comB,sigmaB,s2,j,interval);	

	fclose(f1);//fclose(f2);
return 0;
}
