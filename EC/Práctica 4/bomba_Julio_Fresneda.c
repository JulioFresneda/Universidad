// gcc -m32 bomba_Julio_Fresneda.c -o bomba_Julio_Fresneda


#include <stdio.h>	// para printf()
#include <stdlib.h>	// para exit()
#include <string.h>	// para strncmp()/strlen()
#include <sys/time.h>	// para gettimeofday(), struct timeval

char password[]="uo{eiiqlf\n";	// povedilla
int  passcode  = 84062;		// 71717

void boom(){
	printf("***************\n");
	printf("*** BOOM!!! ***\n");
	printf("***************\n");
	exit(-1);
}

void defused(){
	printf("*************************\n");
	printf("*** bomba desactivada ***\n");
	printf("*************************\n");
	exit(0);
}

void cifrar_password( char pass[] ){
	for( int i=0; i<strlen(password)-1; i++ ){
		if( i % 2 == 0 )
			pass[i] = pass[i]+5;
		
	} 	
	
}

int cifrar_passcode( int pasv ){
	return pasv + 12345;
}



int main(){
#define SIZE 100
	char pass[SIZE];
	int  pasv;
#define TLIM 5
	struct timeval tv1,tv2;	// gettimeofday() secs-usecs

	gettimeofday(&tv1,NULL);

	printf("Introduce la contraseña: ");
	fgets(pass,SIZE,stdin);

	cifrar_password(pass);
	


	if (strncmp(pass,password,strlen(password)))
	    boom();

	gettimeofday(&tv2,NULL);
	if (tv2.tv_sec - tv1.tv_sec > TLIM)
	    boom();

	printf("Introduce el código: ");
	scanf("%i",&pasv);

	pasv = cifrar_passcode(pasv);	
	
	if (pasv!=passcode) boom();

	gettimeofday(&tv1,NULL);
	if (tv1.tv_sec - tv2.tv_sec > TLIM)
	    boom();

	defused();

	
}
