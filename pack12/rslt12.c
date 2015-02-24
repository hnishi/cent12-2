//USEGAE: ./rslt12 (START_RESNUM) (END_RESNUM) (COEFFICIENT)

#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>

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



int result(char *str1,char *str2,char *str3){
	FILE *fa,*fb,*fc;
        char rename[100];
		if(str3==NULL){
		str3="?";
		}
        sprintf(rename,"./result12/rslt/%s_%s_%sA-B.dat",str3,str1,str2);
              if((fa=fopen(rename,"w")) == NULL ){printf( "Cannot open a_dat file \n" ); exit(1); }
//        sprintf(rename,"./result12/rslt/%s_%s_%sA-B_b.dat",str3,str1,str2);
//	      if((fb=fopen(rename,"w")) == NULL ){printf( "Cannot open b_dat file \n" ); exit(1); }
        sprintf(rename,"./result12/rslt/%s_%s_%srslt.txt",str3,str1,str2);
	      if((fc=fopen(rename,"w")) == NULL ){printf( "Cannot open result.txt\n" ); exit(1); }

	double xa[21000],ya[21000],za[21000],xb[21000],yb[21000],zb[21000],o[3];
	int j,p,start,end;
	start=atoi(str1);
	end=atoi(str2);

// LOOP FOR READING FILE OF EACH RESIDUE NUMBERS
for(p=start;p<=end;p++){
		FILE *f1,*f2;	//FILE OPEN
		char name[100];
		int open_num;

		if(str3==NULL){
		sprintf(name,"./result12/outpdb_cor/0/0_%dAB.pdb",p);
		open_num=0;
			if( (f1 = fopen(name, "r" )) == NULL ){
			sprintf(name,"./result12outpdb_cor/1/1_%dAB.pdb",p);
        	        open_num=1;
				if( (f1 = fopen(name, "r" )) == NULL ){
	        	        sprintf(name,"./result12outpdb_cor/2/2_%dAB.pdb",p);
				open_num=2;
					if( (f1 = fopen(name, "r" )) == NULL ){
					sprintf(name,"./result12outpdb_cor/3/3_%dAB.pdb",p);
					open_num=3;
						if( (f1 = fopen(name, "r" )) == NULL ){
						printf( "Cannot open %dAB.pdb",p );exit(1);
						}
					}
				}
			}
/*		sprintf(name,"./pdbB/0/0_%dB.pdb",p);
		open_num=0;
			if( (f2 = fopen(name, "r" )) == NULL ){
			sprintf(name,"./pdbB/1/1_%dB.pdb",p);	
			open_num=1;
        		        if( (f2 = fopen(name, "r" )) == NULL ){
				sprintf(name,"./pdbB/2/2_%dB.pdb",p);
				open_num=2;
	                        	if( (f1 = fopen(name, "r" )) == NULL ){
			                sprintf(name,"./pdbB/3/3_%dB.pdb",p);
					open_num=3;
		                                if( (f1 = fopen(name, "r" )) == NULL ){
	        	                        printf( "Cannot open %dB.pdb",p );exit(1);
	                	                }
	                        	}
				}
			}*/
		}else{
		open_num=atoi(str3);
		sprintf(name,"./result12/outpdb_cor/%s/%s_%dAB.pdb",str3,str3,p);
			if( (f1 = fopen(name, "r" )) == NULL ){
			printf( "Cannot open %s_%dAB.pdb",str3,p );exit(1);
			}
/*		sprintf(name,"./result12/pdbB/%s/%s_%dB.pdb",str3,str3,p);
			if( (f2 = fopen(name, "r" )) == NULL ){
                        printf( "Cannot open %s_%dB.pdb",str3,p );exit(1);
                        }*/
		}
	//INPUT COEDINATE
		int h=0,i=0,loop,stat=0;
		char buf[100];
/*			while( fgets( buf, sizeof( buf ), f1) == "TER"){
				if(strncmp(buf,"ATOM",4)==0){
				sscanf(buf,"%*s%*d%*s%*s%*s%*d%lf%lf%lf%*lf%*lf%*s",&xa[h],&ya[h],&za[h]);
 				h++;
				}
			}*/
		        while( fgets( buf, sizeof( buf ), f1) != NULL){
                		if(strncmp(buf,"ATOM",4)==0){
	                	sscanf(buf,"%*s%*d%*s%*s%*s%*d%lf%lf%lf%*lf%*lf%*s",&xb[i],&yb[i],&zb[i]);
			        i++;
		        	}
				else if(strncmp(buf,"TER",3)==0 && stat==0){
					for(loop=0; loop<i; loop++){
					xa[stat]=xb[stat];ya[stat]=yb[stat];za[stat]=zb[stat];
					stat++;
					}
				h=stat;
				i=0;
				}
			}
	fclose( f1 );        //fclose( f2 );
	
	//DETERMINE PARAMETER
	double ca[3],cb[3],sa[3],sb[3],s1,s2;
	ca[0]=ave(xa,h); ca[1]=ave(ya,h); ca[2]=ave(za,h);
        cb[0]=ave(xb,i); cb[1]=ave(yb,i); cb[2]=ave(zb,i); 	
	sa[0]=stddev(xa,h); sa[1]=stddev(ya,h); sa[2]=stddev(za,h);
        sb[0]=stddev(xb,i); sb[1]=stddev(yb,i); sb[2]=stddev(zb,i);
	s1=stddv2(xa,ya,za,h);
	s2=stddv2(xb,yb,zb,i);	

	//PRINT IN FILE
	fprintf(fc,"%-9d%6c%6c%6s",p,'A','B',"A-B");
        fprintf(fc,"%6s%-9d%6c%6c%6s"," ",p,'A','B',"A-B");
        fprintf(fc,"%6s%-4d%5s%6c%6c%6s"," ",p,"_leng",'A','B',"A-B");
        fprintf(fc,"%6s%-4d%5s%6c%6c%6s\n"," ",p,"_leng",'A','B',"A-B");

	fprintf(fc,"all data%7d%6d%6d",h,i,h-i);
        fprintf(fc,"%5s all data%7d%6d%6d"," ",h,i,h-i);
        fprintf(fc,"%6sall data%7d%6d%6d"," ",h,i,h-i);
        fprintf(fc,"%5s all data%7d%6d%6d\n"," ",h,i,h-i);

	for(j=1;j<4;j++){
	fprintf(fc,"A_%d*sigma%6d%6d%6d",j,count(xa,ya,za,ca,sa,h,j),count(xb,yb,zb,ca,sa,i,j),
					count(xa,ya,za,ca,sa,h,j)-count(xb,yb,zb,ca,sa,i,j));
        fprintf(fc,"%6sB_%d*sigma%6d%6d%6d"," ",j,count(xa,ya,za,cb,sb,h,j),count(xb,yb,zb,cb,sb,i,j),
					count(xa,ya,za,cb,sb,h,j)-count(xb,yb,zb,cb,sb,i,j));    

	fprintf(fc,"%6sA_%d*sigma%6d%6d%6d"," ",j,count2(xa,ya,za,ca,0,s1,h,j),count2(xb,yb,zb,ca,0,s1,i,j),
					count2(xa,ya,za,ca,0,s1,h,j)-count2(xb,yb,zb,ca,0,s1,i,j));
        fprintf(fc,"%6sB_%d*sigma%6d%6d%6d\n"," ",j,count2(xa,ya,za,cb,0,s2,h,j),count2(xb,yb,zb,cb,0,s2,i,j),
					count2(xa,ya,za,cb,0,s2,h,j)-count2(xb,yb,zb,cb,0,s2,i,j));   
	}
	fprintf(fc,"average A_sigma =%10f%6saverage B_sigma =%10f%6sA_sigma =%18f%6sB_sigma =%18f\n\n",ave(sa,3)," ",ave(sb,3)," ",s1," ",s2);
// make a dat file to make a graph
	int d[3],e[3],f[3],g[3];
		for(j=1;j<4;j++){
			d[j-1]=count(xa,ya,za,ca,sa,h,j)-count(xb,yb,zb,ca,sa,i,j);
			e[j-1]=count(xa,ya,za,cb,sb,h,j)-count(xb,yb,zb,cb,sb,i,j);
			f[j-1]=count2(xa,ya,za,ca,0,s1,h,j)-count2(xb,yb,zb,ca,0,s1,i,j);
			g[j-1]=count2(xa,ya,za,cb,0,s2,h,j)-count2(xb,yb,zb,cb,0,s2,i,j);
		} 
	fprintf(fa,"%5d%5d%5d%5d%5d%5d%5d%5d%5d%5d%5d%5d%5d\n",p,d[0],d[1],d[2],e[0],e[1],e[2],f[0],f[1],f[2],g[0],g[1],g[2]);
/*
	        for(j=1;j<4;j++){
        	        d[j-1]=count(xa,ya,za,cb,sb,h,j)-count(xb,yb,zb,cb,sb,i,j);
                	f[j-1]=count2(xa,ya,za,cb,0,s2,h,j)-count2(xb,yb,zb,cb,0,s2,i,j);
	        }
        fprintf(fb,"%6d%6d%6d%6d%6d%6d%6d\n",p,d[0],d[1],d[2],f[0],f[1],f[2]);
*/
}
        fclose( fa );      /*fclose( fb );*/	fclose(fc);
return 0;
}


int main(int argc,char *argv[]){
        if(argv[1]==NULL || argv[2]==NULL ){
        puts("command mistake");
        puts("USEGAE: ./rslt12 (start_RESNUM) (end_RESNUM) (COEFFICIENT)");
        exit(1);
        }

//output data to make a graph and a list that show how many data are included.
        result(argv[1],argv[2],argv[3]);
return 0;
}
