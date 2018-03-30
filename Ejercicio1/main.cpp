#include <iostream>
#include <string.h>
#include <fstream>

using namespace std;

void metodo1(char *, int ,int );
void metodo2(char *, int ,int );

int main()
{
        char cade[] = "01000001011000100100001101100100";
        int tam,semilla;

        tam = strlen(cade);
        cout <<"Ingrese el valor de la semilla: ";cin >> semilla;

        metodo1(cade,tam,semilla);




    return 0;
}

void metodo1(char *cad, int tam , int sem){
    /*Para codificar se convierte el archivo a binario, luego se separa en bloques de n bits. En el
primer bloque se cambian todos los 1 por 0 y viceversa. Para los grupos siguientes se debe
contar el número de 1s y 0s en el grupo anterior y hacer cambios según la siguiente regla:
● Si hay igual cantidad de 1s y 0s se invierte cada bit del grupo.
● Si hay mayor cantidad de 0s se invierte cada 2 bits.
● Si hay mayor cantidad de 1s se invierte cada 3 bits.
     */

    int con1 =0,con0=0;

    char cadena[tam];

    for (int i=0; i < tam ; i += sem){

        //si i=0 es porque estamos en el primer bloque de bits solo se intercambiar
        if (i == 0 ){
            for(int k=i ; k  < (i+sem) ; k++){
                if(cad[k] == '0'){
                    cadena[k] = '1';
                }else{
                    cadena[k] = '0';
                }
            }
        //sino ya no es el primer bloque de bits debemos tener en cuenta los parametros
        }else if(i != 0){
            /*if ( con0 > con1){
                for(int k = i ; k < (i+sem) ; k ++){
                    if( k % 2 ==0){
                        if (cad[k] == '0'){
                            cadena[k] = '1';
                        }else{
                            cadena[k] = '0';
                        }
                    }else{
                        cadena[k] = cad[k];
                    }
                }
            }else if( con1 > con0){
                for(int k = i ; k < (i+sem) ; k ++){
                    if( k % 3 ==0){
                        if (cad[k] == '0'){
                            cadena[k] = '1';
                        }else{
                            cadena[k] = '0';
                        }
                    }else{
                        cadena[k] = cad[k];
                    }
                }
            }*/
            for (int k=i; k < (i+sem);k++){
                cadena[k] = cad[k];
            }
            if(con0 > con1){
                for(int k=i+1 ; k < (i+sem);k +=2){
                    if (cad[k] == '0'){
                        cadena[k] = '1';
                    }else{
                        cadena[k] = '0';
                    }
                }
            }else if(con1 > con0){
                for(int k=i+2 ; k < (i+sem);k +=3){
                    if (cad[k] == '0'){
                        cadena[k] = '1';
                    }else{
                        cadena[k] = '0';
                    }
                }
            }else{
                for(int k=i ; k < (i+sem) ; k++){
                    if (cad[k] == '0'){
                        cadena[k] = '1';
                    }else{
                        cadena[k] = '0';
                    }
                }
            }
        }

        con0=0;
        con1=0;
        //contamos la cantidad de '0' y '1' que hay en cada bloque de bits
        for(int j=i ; j < (i+sem) ; j++){
            if (cad[j] == '0'){
                con0 ++;
            }else{
                con1 ++;
            }
        }
    }


    cadena[tam] = '\0';
    cout << "Cadena original:  "<< cad << endl;
    cout << "Cadena modificada:"<< cadena<<endl;


}



