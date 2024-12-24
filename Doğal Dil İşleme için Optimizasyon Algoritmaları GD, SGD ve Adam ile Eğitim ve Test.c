#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define MAX 4000
#define EPS 0.001
#define EPOCH 3000
#define B1 0.9
#define B2 0.999
#define e 0.00000001



int sozluk_olustur(FILE *dosya, char ***sozluk);
void hot_vektor(char *txt, char **sozluk, int kelimesayisi, int *x);
void train_and_test_set(FILE *dosyaA, FILE *dosyaB, char **train_A, char **train_B, char **test_A, char **test_B);
void train_gd(char **train, char **sozluk, double *w, int *x, double *loss, int kelimesayisi, int label, double *sure);
void test_gd(char **test, char **sozluk, double *w, int *x, double *loss, int kelimesayisi, int label, double *sure);
void train_sgd(char **train, char **sozluk, double *w, int *x, double *loss, int kelimesayisi, int label, double *sure);
void test_sgd(char **test, char **sozluk, double *w, int *x, double *loss, int kelimesayisi, int label, double *sure);
void train_adam(char **train, char **sozluk, double *w, int *x, double *loss, int kelimesayisi, int label, double *sure);
void test_adam(char **test, char **sozluk, double *w, int *x, double *loss, int kelimesayisi, int label, double *sure);

int main() {
    FILE *dosya;
    int i;
    dosya = fopen("AveB.txt", "r");
   

    char **sozluk = (char **)malloc(MAX * sizeof(char *));
    for ( i = 0; i < MAX; i++) {
        sozluk[i] = (char *)calloc(30, sizeof(char));
    }
    int kelimesayisi = sozluk_olustur(dosya, &sozluk);
    int *x = (int *)calloc(kelimesayisi, sizeof(int));

    fclose(dosya);

   char **train_A, **test_A, **train_B, **test_B;
   train_A = (char**)malloc(80 * sizeof(char *));
    test_A =(char**) malloc(20 * sizeof(char *));
    train_B =(char**) malloc(80 * sizeof(char *));
    test_B =(char**) malloc(20 * sizeof(char *));
    
    
    for (i = 0; i < 80; i++) {
        train_A[i] = malloc(50* sizeof(char));
        train_B[i] = malloc(50 * sizeof(char));
    }
    for (i = 0; i < 20; i++) {
        test_A[i] = malloc(50 * sizeof(char));
        test_B[i] = malloc(50 * sizeof(char));
    }


    FILE *dosyaA = fopen("A_copy.txt", "r");
    FILE *dosyaB = fopen("B.txt", "r");

    train_and_test_set(dosyaA, dosyaB, train_A, train_B, test_A, test_B);
	

    hot_vektor(train_A[0],sozluk,kelimesayisi,x);
    for(i=0;i<kelimesayisi;i++){
    	//printf("%d\n",x[i]);
	}
    double *w = calloc(kelimesayisi, sizeof(double));
    double *w1 = calloc(kelimesayisi, sizeof(double));
    double *w2= calloc(kelimesayisi, sizeof(double));
    double *w3 = calloc(kelimesayisi, sizeof(double));
    srand(time(NULL));
    for (i = 0; i < kelimesayisi; i++) {
        w[i] = ((double)rand() / RAND_MAX)*2.0-1.0;
        w1[i]=w[i];
        w2[i]=w[i];
        w3[i]=w[i];
      // printf("%lf\n",w[i]);
    }

    double *loss_train_gd = (double *)calloc(EPOCH, sizeof(double));
    double *loss_test_gd = (double *)calloc(EPOCH, sizeof(double));
    double *loss_train_sgd = (double *)calloc(EPOCH, sizeof(double));
    double *loss_test_sgd = (double *)calloc(EPOCH, sizeof(double));
    double *loss_train_adam = (double *)calloc(EPOCH, sizeof(double));
    double *loss_test_adam = (double *)calloc(EPOCH, sizeof(double));
    double *sure = (double *)calloc(EPOCH, sizeof(double));
	int epoch_train_a=0,epoch_test=0,epoch_train_b=0;
    train_gd(train_A, sozluk, w1, x, loss_train_gd, kelimesayisi, 1, sure);
	test_gd(test_A, sozluk, w1, x, loss_test_gd, kelimesayisi, 1, sure);
	train_sgd(train_A, sozluk, w2, x, loss_train_sgd, kelimesayisi, 1, sure);
	test_sgd(test_A, sozluk, w2, x, loss_test_sgd, kelimesayisi, 1, sure);
	train_adam(train_A, sozluk, w3, x, loss_train_adam, kelimesayisi, 1, sure);
	test_adam(test_A, sozluk, w3, x, loss_test_adam, kelimesayisi, 1, sure);
    for (i = 0; i < kelimesayisi; i++) {
        //printf("%lf\n", loss[i]);
      // printf("%lf\n",w[i]);
    }
    // traindeki w deðerini buraya koyman lazým
  // epoch_test=test_adam(test_A, sozluk, w, x, loss_test, kelimesayisi, 1, sure);
   // printf("loss:\n");
	for (i = 0; i < epoch_test; i++) {
      // printf("%lf\n", loss_test[i]);
    }
   // printf("adamda w:\n");
   // epoch_train_a= train_adam(train_A,sozluk,w,x,loss_train, kelimesayisi,1,sure);
   // epoch_test= test_adam(test_A,sozluk,w,x,loss_test, kelimesayisi,1,sure);
    for (i = 1; i < epoch_test; i++) {
       //printf("%lf\n", loss_test[i]);
    }
    // w yi 0 la
   // epoch_train_b=train_gd(train_B, sozluk, w, x, loss, kelimesayisi, -1, sure);
    //double cikis = test_gd(test_A, sozluk, w, x, loss, kelimesayisi, 1, sure);
    //printf("%lf\n", cikis);
	for (i = 0; i < kelimesayisi; i++) {
	       // w[i] = ((double)rand() / RAND_MAX)*2.0-1.0;
	        //printf("%lf\n",w[i]);
	    }
    for (i = 0; i < kelimesayisi; i++) {
        free(sozluk[i]);
    }
    free(sozluk);
    free(x);
    free(train_A);
    free(train_B);
    free(test_A);
    free(test_B);
	free(w);
	free(w1);
	free(w2);
	free(w3);
    fclose(dosyaA);
    fclose(dosyaB);

    return 0;
}

int sozluk_olustur(FILE *dosya, char ***sozluk) {
    char word[100];
    int count = 0;

    while (fscanf(dosya, "%s", word) == 1) {
    	
        int i = 0;
        while (i < count && strcmp((*sozluk)[i], word) != 0) {
            i++;
        }
        if (i == count) {
            (*sozluk)[count] = (char *)realloc((*sozluk)[count], (strlen(word) + 1) * sizeof(char));
            strcpy((*sozluk)[count], word);
            count++;
        }
    }

    *sozluk = (char **)realloc(*sozluk, count * sizeof(char *));
    return count;
}
void hot_vektor(char *txt, char **sozluk, int kelimesayisi, int *x) {
    int j = 0;
	char *kopya=strdup(txt);
    char *kelime = strtok(kopya, " \t\n");
    while (kelime != NULL) {
        j = 0;
        while (j < kelimesayisi) {
            if (strcmp(kelime, sozluk[j]) == 0) {
                x[j] = 1;
            }
            j++;
        }
        kelime = strtok(NULL, " \t\n");
    }
    free(kopya); 
}


void train_and_test_set(FILE *dosyaA, FILE *dosyaB, char **train_A, char **train_B, char **test_A, char **test_B) {
    char satir[2000];
    int i = 0;
    while (i<100 && fgets(satir,sizeof(satir),dosyaA)!=NULL) {
    	
        if (i < 80) {
            train_A[i] = malloc((strlen(satir)+1)*sizeof(char));
            strcpy(train_A[i], satir);
        } else {
            test_A[i-80]=malloc((strlen(satir)+1)*sizeof(char));
            strcpy(test_A[i - 80], satir);
        }
        i++;
    }
    //for (i = 0; i < 80; i++) {
       // printf("%s\n", train_A[i]);
    //}
    i=0;
    while (i < 100 && fgets(satir, sizeof(satir), dosyaB) != NULL) {
    	
        if (i < 80) {
            train_B[i] = malloc((strlen(satir) + 1) * sizeof(char));
            strcpy(train_B[i], satir);
        } else {
            test_B[i - 80] = malloc((strlen(satir) + 1) * sizeof(char));
            strcpy(test_B[i - 80], satir);
        }
        i++;
    }
}

void train_gd(char **train, char **sozluk, double *w, int *x, double *loss, int kelimesayisi, int label, double *sure) {
    int epoch = 0,maxiterasyon=1000,i,j,k=0;
    double y_predicted=0.0,jacobian[80][2000],error,er_onceki=0.0,temp,r[80],jac_tr,accuracy;
    FILE *dosya_acc;
    clock_t baslangic, bitis;
    double zaman;
	//dosya_acc=fopen("train_gd_loss.txt","w");
	FILE *dosya;
	dosya=fopen("gd_w5.txt","a");
	baslangic = clock();
    do{
    	er_onceki=error;
		error=0.0;
		accuracy=0;
		for(i=0;i<80;i++){
			y_predicted=0.0;
			for(j=0;j<kelimesayisi;j++){
				x[j]=0;
			}
			hot_vektor(train[i],sozluk,kelimesayisi,x);
			for(j=0;j<kelimesayisi;j++){
				y_predicted+=w[j]*(double)x[j];
			}
			//printf("%lf\n",y_predicted);
		//	printf("%lf\n",tanh(y_predicted));
			r[i]=(double)label-tanh(y_predicted);
			//printf("%lf\n",r);
			for(j=0;j<kelimesayisi;j++){
				jacobian[i][j] = (-1.0) * (double)x[j] * (1.0 - pow(tanh(y_predicted), 2));
				//printf("%lf\n",jacobian[i][j]);	
			}
			error+=pow((label-tanh(y_predicted)),2);
			if(fabs(label-tanh(y_predicted))<0.4){
				accuracy++;
			}
		}
			for(j=0;j<kelimesayisi;j++){
				
				jac_tr=0.0;
				for(k=0;k<80;k++){
					jac_tr+=jacobian[k][j]*r[k];
				}
				//printf("%lf\n",jac_tr);
				w[j]=w[j]-EPS*jac_tr;
				fprintf(dosya,"%lf ",w[j]);
			//	printf("%lf\n",w[j]);
			}
		accuracy=(accuracy/80.0)*100.0;
		//fprintf(dosya_acc,"%lf\n",accuracy);
				
		error/=80.0;
		//printf("%lf\n",error);
		loss[epoch]=error;
	//	printf("%lf\n",loss[epoch]);
	//	fprintf(dosya_acc,"%lf\n",loss[epoch]);
		epoch++;
		bitis= clock();
		zaman = (double)(bitis - baslangic) / CLOCKS_PER_SEC;
		sure[epoch]=zaman;
		//printf("%lf\n",sure[epoch]);
		
	}while(epoch<maxiterasyon);// durdurma koþulun yanlýþ düzgün bir durdurma koþulu bul
	//printf("%d\n",epoch);

	//fclose(dosya_acc);
	fprintf(dosya,"\n");
	fclose(dosya);
}

void test_gd(char **test, char **sozluk, double *w, int *x, double *loss, int kelimesayisi, int label, double *sure) {
   int epoch = 0,maxiterasyon=1000,i,j,k=0;
    double y_predicted=0.0,jacobian[80][2000],error,er_onceki=0.0,temp,r[80],jac_tr,accuracy;
     FILE *dosya_acc;
     clock_t baslangic, bitis;
    double zaman;
	//dosya_acc=fopen("test_gd_loss.txt","w");
	baslangic = clock();
    do{
    	er_onceki=error;
		error=0.0;
		accuracy=0.0;
		for(i=0;i<20;i++){
			y_predicted=0.0;
			for(j=0;j<kelimesayisi;j++){
				x[j]=0;
			}
			hot_vektor(test[i],sozluk,kelimesayisi,x);
			for(j=0;j<kelimesayisi;j++){
				y_predicted+=w[j]*(double)x[j];
			}
		//	printf("%lf\n",y_predicted);
			//printf("%lf\n",tanh(y_predicted));
			//printf("%lf\n",r);
				//printf("%lf\n",jacobian[i][j]);	
			
			error+=pow((label-tanh(y_predicted)),2);
			if(fabs(label-tanh(y_predicted))<0.4){
				accuracy++;
			}
			
		}
		
		error/=20.0;
		accuracy=(accuracy/20.0)*100.0;
		//printf("%lf\n",accuracy);
		//fprintf(dosya_acc,"%lf\n",accuracy);
	//	printf("%lf\n",error);
		loss[epoch]=error;
	//	fprintf(dosya_acc,"%lf\n",loss[epoch]);
	//	printf("%lf\n",loss[epoch]);
		epoch++;
		bitis= clock();
		zaman = (double)(bitis - baslangic) / CLOCKS_PER_SEC;
		sure[epoch]=zaman;
		//printf("%lf\n",sure[epoch]);
		
	}while(epoch<maxiterasyon);
	//printf("%d\n",epoch);
//	fclose(dosya_acc);
}

void train_sgd(char **train, char **sozluk, double *w, int *x, double *loss, int kelimesayisi, int label, double *sure){
	  int epoch = 0,maxiterasyon=3000,i,j,k=0;
    double y_predicted=0.0,jacobian[80][2000],error,er_onceki=0.0,temp,r[80],jac_tr,accuracy=0.0;
    srand(time(NULL));
    FILE *dosya_acc;
    clock_t baslangic, bitis;
    double zaman;
	//dosya_acc=fopen("train_sgd_loss.txt","w");
	FILE *dosya;
	dosya=fopen("sgd_w5.txt","a");
	baslangic = clock();
    do{
    	er_onceki=error;
		error=0.0;
		//accuracy=0.0;	
		i=0;
		i=rand()%80;
		//printf("%d\n",i);
		for(j=0;j<kelimesayisi;j++){
				x[j]=0;
			}
			y_predicted=0.0;
			hot_vektor(train[i],sozluk,kelimesayisi,x);
			for(j=0;j<kelimesayisi;j++){
				y_predicted+=w[j]*(double)x[j];
			}
			//printf("%lf\n",tanh(y_predicted));
			
				if(fabs(label-tanh(y_predicted))<0.4){
				accuracy++;
		
			}
		for(k=0;k<80;k++){	
			for(j=0;j<kelimesayisi;j++){
				jacobian[k][j] = (-1.0) * (double)x[j] * (1.0 - pow(tanh(y_predicted), 2));
				//printf("%lf\n",jacobian[i][j]);	
			}	
		}
			for(j=0;j<kelimesayisi;j++){
				
				jac_tr=0.0;
				jac_tr+=jacobian[i][j]*((double)label-tanh(y_predicted));	
				//printf("%lf\n",jac_tr);
				w[j]=w[j]-0.95*EPS*jac_tr;
				fprintf(dosya,"%lf ",w[j]);
			//	printf("%lf\n",w[j]);
			}	
		//printf("%lf\n",error);
		error=pow((label-tanh(y_predicted)),2);
		error/=80.0;
		loss[epoch]=error;
	//	fprintf(dosya_acc,"%lf\n",loss[epoch]);
		
		
	//	printf("%lf\n",loss[epoch]);
		epoch++;
		if(epoch%10==0){	
		accuracy=(accuracy/10.0)*100.0;
		//printf("%lf\n",accuracy);
		//fprintf(dosya_acc, "%lf\n",accuracy);
		accuracy=0.0;
		}
		bitis= clock();
		zaman = (double)(bitis - baslangic) / CLOCKS_PER_SEC;
		sure[epoch]=zaman;
		//printf("%lf\n",sure[epoch]);
		
	}while(epoch<maxiterasyon);// durdurma koþulun yanlýþ düzgün bir durdurma koþulu bul
	//printf("%d\n",epoch);
//	fclose(dosya_acc);
fprintf(dosya,"\n");
	fclose(dosya);
		
}
void test_sgd(char **test, char **sozluk, double *w, int *x, double *loss, int kelimesayisi, int label, double *sure){
	int epoch = 0,maxiterasyon=3000,i,j,k=0;
    double y_predicted=0.0,jacobian[80][2000],error,er_onceki=0.0,temp,r[80],jac_tr,accuracy=0.0;
    FILE *dosya_acc;
//	dosya_acc=fopen("test_sgd_loss.txt","w");
	clock_t baslangic, bitis;
    double zaman;
	
    baslangic = clock();
    srand(time(NULL));
    do{
    	er_onceki=error;
		error=0.0;	
		i=0;
		i=rand()%20;
		//printf("%d\n",i);
		for(j=0;j<kelimesayisi;j++){
				x[j]=0;
			}
			y_predicted=0.0;
			hot_vektor(test[i],sozluk,kelimesayisi,x);
			for(j=0;j<kelimesayisi;j++){
				y_predicted+=w[j]*(double)x[j];
			}
		//	printf("%lf\n",tanh(y_predicted));
				if(fabs(label-tanh(y_predicted))<0.4){
				accuracy++;
		
			}
		
		//printf("%lf\n",error);
		error=pow((label-tanh(y_predicted)),2);
		error/=20;
		loss[epoch]=error;
	//	printf("%lf\n",loss[epoch]);
	//	fprintf(dosya_acc,"%lf\n",loss[epoch]);
		
		epoch++;
		if(epoch%10==0){	
		accuracy=(accuracy/10.0)*100.0;
		//fprintf(dosya_acc,"%lf\n",accuracy);
		accuracy=0.0;
		}
		bitis= clock();
		zaman = (double)(bitis - baslangic) / CLOCKS_PER_SEC;
		sure[epoch]=zaman;
	//	printf("%lf\n",sure[epoch]);
		
	}while( epoch<maxiterasyon);// durdurma koþulun yanlýþ düzgün bir durdurma koþulu bul
	//printf("%d\n",epoch);	
	//fclose(dosya_acc);
}
void train_adam(char **train, char **sozluk, double *w, int *x, double *loss, int kelimesayisi, int label, double *sure){
	int epoch = 1,maxiterasyon=3000,i,j,k=0;
	double error,er_onceki,gt[1100],mt[1100],vt[1100],mt_hat[1100],vt_hat[1100],y_predicted,eps=0.001,accuracy=0.0;
	for(i=0;i<kelimesayisi;i++){
		gt[i]=0.0; mt[i]=0.0; vt[i]=0.0; mt_hat[i]=0.0; vt_hat[i]=0.0;
	}
	srand(time(NULL));
	FILE *dosya_acc;
//	dosya_acc=fopen("train_adam_loss.txt","w");
	FILE *dosya;
	dosya=fopen("adam_w5.txt","a");
	clock_t baslangic, bitis;
    double zaman;
    baslangic = clock();
	do{
		er_onceki=error;
		error=0.0;	
		i=0;
		
		i=rand()%80;
		//printf("%d\n",i);
		for(j=0;j<kelimesayisi;j++){
				x[j]=0;
			}
		
			hot_vektor(train[i],sozluk,kelimesayisi,x);
			y_predicted=0.0;
		for(j=0;j<kelimesayisi;j++){
			y_predicted+=w[j]*(double)x[j];
		}//printf("%lf\n",y_predicted);
		//printf("%lf\n",tanh(y_predicted));
			if(fabs(label-tanh(y_predicted))<0.4){
				accuracy++;
			}
			for(j=0;j<kelimesayisi;j++){
				gt[j]= (-1.0) * (double)x[j]* (1.0 - pow(tanh(y_predicted), 2));
			//	printf("%lf",gt[j]);	
			}
			for(j=0;j<kelimesayisi;j++){
				mt[j]=B1*mt[j]+(1-B1)*gt[j];
			//	printf("%lf  ",mt[j]);
			}
			for(j=0;j<kelimesayisi;j++){
				vt[j]=B2*vt[j]+(1-B2)*pow(gt[j],2);
			}
			for(j=0;j<kelimesayisi;j++){
				mt_hat[j]=mt[j]/(1.0-pow(B1,epoch));
				vt_hat[j]=vt[j]/(1.0-pow(B2,epoch));
			}
			for(j=0;j<kelimesayisi;j++){
				w[j]=w[j]-EPS*mt_hat[j]/(sqrt(vt_hat[j])+e);
				fprintf(dosya,"%lf ",w[j]);
			//	printf("%lf\n",w[j]);
			}
			
		error=pow((label-tanh(y_predicted)),2);
		error/=80;
		loss[epoch-1]=error;
		//fprintf(dosya_acc,"%lf\n",loss[epoch-1]);
		//printf("%lf\n",tanh(y_predicted));
	//	printf("%lf\n",loss[epoch]);
		if(epoch%10==0){	
		accuracy=(accuracy/10.0)*100.0;
		//fprintf(dosya_acc," %lf\n",accuracy);
		accuracy=0.0;
		}	
		epoch++;
		bitis= clock();
		zaman = (double)(bitis - baslangic) / CLOCKS_PER_SEC;
		sure[epoch]=zaman;
		//printf("%lf\n",sure[epoch]);
		
	//	eps = eps * (sqrt((1-B2)))/ (1 -B1);
	}while(  epoch<maxiterasyon);
//	printf("%d\n",epoch-1);
//fclose(dosya_acc);
fprintf(dosya,"\n");
fclose(dosya);
}
void test_adam(char **test, char **sozluk, double *w, int *x, double *loss, int kelimesayisi, int label, double *sure){
	int epoch = 1,maxiterasyon=3000,i,j,k=0;
	double error,er_onceki,y_predicted,accuracy=0.0;
	
	srand(time(NULL));
		FILE *dosya_acc;
//	dosya_acc=fopen("test_adam_loss.txt","w");
	clock_t baslangic, bitis;
    double zaman;
    baslangic = clock();
	do{
		er_onceki=error;
		error=0.0;	
		i=0;
		
		i=rand()%20;
		//printf("%d\n",i);
		for(j=0;j<kelimesayisi;j++){
				x[j]=0;
			}
		
			hot_vektor(test[i],sozluk,kelimesayisi,x);
			y_predicted=0.0;
		for(j=0;j<kelimesayisi;j++){
			y_predicted+=w[j]*(double)x[j];
		}//printf("%lf\n",y_predicted);
		if(fabs(label-tanh(y_predicted))<0.4){
				accuracy++;
			}
		error=pow((label-tanh(y_predicted)),2);
		error/=20;
		loss[epoch-1]=error;
	//	fprintf(dosya_acc,"%lf\n",loss[epoch-1]);
		//printf("%lf\n",tanh(y_predicted));
	//	printf("%lf\n",loss[epoch]);
		if(epoch%10==0){	
		accuracy=(accuracy/10.0)*100.0;
	//	fprintf(dosya_acc," %lf\n",accuracy);
		accuracy=0.0;
		}		
		epoch++;
		bitis= clock();
		zaman = (double)(bitis - baslangic) / CLOCKS_PER_SEC;
		sure[epoch]=zaman;
		//printf("%lf\n",sure[epoch]);
		
	//	eps = eps * (sqrt((1-B2)))/ (1 -B1);
	}while( epoch<maxiterasyon);
	//printf("%d\n",epoch-1);
//	fclose(dosya_acc);
}
