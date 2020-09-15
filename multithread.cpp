#include <iostream>
#include <stdio.h>  
#include <thread>
#include "TestaPrimo.h"        

using namespace std;

//ra: 222.170.36-7
int P = 170 * 367;
int quantNumerosPrimos = 0;
int countPrimo = 0;
int numPrimos[222];

int checkPrimosPar(){			
 	int indexNum = P-2;
 	
	while(quantNumerosPrimos < 222){
		if (TestaPrimo3(indexNum)){
			if(indexNum != 2){
				countPrimo += indexNum;
				numPrimos[quantNumerosPrimos] = indexNum;
				quantNumerosPrimos++;
			}
			
		}
		indexNum-=2;
	}
}

int checkPrimosImp(){	
  	int indexNum = P-1;	
  	
	while(quantNumerosPrimos < 222){
		if (TestaPrimo3(indexNum)){
			numPrimos[quantNumerosPrimos] = indexNum;
			quantNumerosPrimos++;
			countPrimo+= indexNum;
		}
		indexNum-=2;
	}	
}

void imprimir(){
	for(int j = 221; j >= 0; j--){
		cout << "Numero " << j+1 << ": " << numPrimos[j] << endl;
	}
}

int main(int argc, char** argv) {
	
	if(P > 5000){
		thread imparT (checkPrimosImp);
		thread parT (checkPrimosPar);
		
		//thread 1
		imparT.join();  
		  
		//thread2            
		parT.join();
	}
	
	imprimir();
	
	cout << endl << "Multiplicacao: " << 170*367 << endl;
	cout << "Soma primos: " << countPrimo << endl;
		
	return 0;
}


int TestaPrimo3(int n) {
    int EhPrimo,
        d=3;
    if (n <= 1 || (n != 2 && n % 2 == 0))
        EhPrimo = 0;   
    else
        EhPrimo = 1;        

    while (EhPrimo  && d <= n / 2) {
        if (n % d == 0)
            EhPrimo = 0;
        d = d + 2;       
    }
    return EhPrimo;
}


int TestaPrimo1(int n) {
    int EhPrimo = 1, //em princÃ­pio, n Ã© primo
        d=2;
    if (n <= 1)
    EhPrimo = 0;

    while (EhPrimo == 1 && d <= n / 2) {
    if (n % d  == 0)
        EhPrimo = 0;
    d = d + 1;
    }
    return EhPrimo;
}


int TestaPrimo2(int n) {
    
    int EhPrimo = 1, //em princÃ­pio, n Ã© primo
        d=2,
        resto;
    if (n <= 1)
        EhPrimo = 0;

     while (EhPrimo == 1 && d <= n / 2) {
      resto = n % d;
          if (resto == 0)
              EhPrimo = 0;
          d = d + 1;
      }
    return EhPrimo;
}


int TestaPrimo4(int n) {
    int EhPrimo, //em princÃ­pio, n Ã© primo
        d=3;
    if (n <= 1 || (n != 2 && n % 6 == 1 && n % 6 == 5))
        EhPrimo = 0;    /* nenhum numero inteiro <= 1 ou ~ adjacente a 6 eh primo */
    else
        EhPrimo = 1;
    while (EhPrimo  && d <= n / 2) {
        if (n % d == 0)
            EhPrimo = 0;
        d = d + 2;
        }
    return EhPrimo;
}