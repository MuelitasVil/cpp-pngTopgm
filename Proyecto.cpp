#include <stdio.h>
#include <iostream>
#include <fstream>

using namespace std;

void ImprimirMatriz(int **&matriz,int inicio, int filas, int columna){
    for(int i = inicio; i < filas; i++){
        for(int j = inicio; j < columna; j++){
            cout <<  matriz[i][j] << " ";
        }
        cout<<"\n";
    }
}


void escrbirInformacion(int **&matriz, int numrows, int numcols, string versionPgm, string commentPgm, int maxGray){
    
	ofstream fichero ("Informacion.txt");

   	fichero << "Version : " << versionPgm << endl;
   	fichero << "Comment : " << commentPgm << endl;
   	fichero << numcols << " columns and " << numrows << " rows" << endl;
   	fichero << "MaxGray : " <<  maxGray << endl;
    
	for(int i = 0; i < numrows; i++){
        for(int j = 0; j < numcols; j++){
            fichero <<  matriz[i][j] << " ";
        }
    }
    
	fichero << endl;
	
	cout << "Se ha guardado la informacion exitosamente ...\n";
  
}


int CantidadFilas(string NombreArchivo){

	ifstream archivo(NombreArchivo.c_str());
  	string linea;
  	int cont = 0;

   	while (getline (archivo, linea)){
    	cont++;
	}
  	
	  archivo.close ();
  	return cont;
}

int CantidadColumnas(string NombreArchivo){ 
    
  	string informacion = "";    
  	ifstream archivo (NombreArchivo.c_str());
  	string linea;
  	int cont = 0;

  	getline(archivo, linea);
    	for (int i = 0; i < linea.size(); i++){
        	if (linea[i] != ';'){
	       		informacion = informacion + linea[i];
	    	} else {
            	cont++;
        	}
        
    	}
  
  	archivo.close ();
 
 return cont;

}

int DesplazamientoFilas(int **&matriz, int tam){
	int desplazamiento;
	int mitad = tam - 2;
	for(int i = 0; i < tam; i++){
		desplazamiento = i - mitad;
		for(int j = 0; j < tam; j++){
			matriz[i][j] = desplazamiento;
		}
	}	
}

int DesplazamientoColumnas(int **&matriz, int tam){
	int desplazamiento;
	int mitad = tam - 2;
	for(int i = 0; i < tam; i++){
		desplazamiento = i - mitad;
		for(int j = 0; j < tam; j++){
			matriz[j][i] = desplazamiento;
		}
	}
	
}

int combolusion(int **&matriz, int fila, int columna, int **&DesplazamientoRows, int **&DesplazamientoColums, int **&matrizKernel, int tamKernel){
	int desplamientoFila, desplazamientoColum; 
	int sumatoria = 0;
	for(int i = 0; i < tamKernel; i++){
		for(int j = 0; j < tamKernel; j++){
			desplamientoFila = fila + DesplazamientoRows[i][j];
			desplazamientoColum = columna + DesplazamientoColums[i][j];
			sumatoria = sumatoria + (matrizKernel[i][j] * matriz[desplamientoFila][desplazamientoColum]);
			//cout << matriz[desplamientoFila][desplazamientoColum] << " " ; // Veficcar posiciones aledañas
		}
	//cout << "\n";
	}
	return sumatoria;
}

void GuardarPgm(int **editMatriz,int inicio, int numrows, int numcols, int maxGray){
	
	string nombreArchivo;
	cout << "\nIngrese el nombre del archivo donde desea guardar el nuevo pgm (No use espacios) : ";
	getline(cin, nombreArchivo);
	
	nombreArchivo = nombreArchivo + ".pgm";
	ofstream NuevoArchivo(nombreArchivo.c_str());	

	NuevoArchivo << "P2" << "\n";
	NuevoArchivo << "#Nueva imagen con kenel" << "\n";
	NuevoArchivo << numcols << " " << numrows << "\n";
	NuevoArchivo << maxGray << "\n";

    for(int i = 0; i < numrows; i++){
        for(int j = 0; j < numcols; j++){
            NuevoArchivo <<  editMatriz[i][j] << " ";
        }
        NuevoArchivo << endl;
    }
    
	NuevoArchivo << endl;
	
}


void rellenarArriba(int **&editMatriz, int elemento, int fila, int columna){
	for(int i = fila; i >= 0; i--){
		editMatriz[i][columna] = elemento;
	}
}

void rellenarAbajo(int **&editMatriz, int elemento, int fila, int columna, int numrows){
	for(int i = fila; i < numrows; i++){
		editMatriz[i][columna] = elemento;
	}
}

void rellenarIzquierda(int **&editMatriz, int elemento, int fila, int columna){
	for(int i = columna; i >= 0; i--){
		editMatriz[fila][i] = elemento;
	}
}

void rellenarDerecha(int **&editMatriz, int elemento, int fila, int columna, int numcols){
	for(int i = columna; i < numcols; i++){
		editMatriz[fila][i] = elemento;
	}
}

void rellenarIzUp(int **&editMatriz, int elemento, int pos){
	for(int i = pos; i >= 0; i--){
		editMatriz[i][i] = elemento;
	}
}

void rellenarIzDown(int **&editMatriz, int elemento, int fila, int col){
	
	int movefil = 0;
	for(int i = col; i >= 0; i--){
		editMatriz[fila + movefil][i] = elemento;
		movefil++;
	}

}

void rellenarDeUp(int **&editMatriz, int elemento, int fila, int col){
	int movecol = 0;
	for(int i = fila; i >= 0; i--){
		editMatriz[i][col+movecol] = elemento;
		movecol++;
	}
}

void rellenarDeDown(int **&editMatriz, int elemento, int fila, int col, int numrows){
	int movecol = 0;
	for(int i = fila; i < numrows; i++){
		editMatriz[i][col+movecol] = elemento;
		movecol++;
	}
}

void filtrarKernell(int **&editMatriz,int **&matriz, int numrows, int numcols, int maxGray){

	int tamKernel, CantRowsOfKernel, CantColumnsOfKernel;
	string NameOfKernel;
	
	cout << "\nNota : Recuerde que las matrices kernel deben ser ingresadas con sus valores separados por ';'";
	cout << "\nEjemplo :";
	cout << "\n1;2;1;";
	cout << "\n2;4;2;";
	cout << "\n1;2;1;";
	cout << "\n\nIngrese el nombre del archivo txt donde tiene guardado el kernel\n (Sin espacios sin extension)\n -> ";
	cin >> NameOfKernel;
	
	NameOfKernel = NameOfKernel + ".txt";
	ifstream archivoKernel(NameOfKernel.c_str());	
	
	CantRowsOfKernel = CantidadFilas(NameOfKernel);
	CantColumnsOfKernel = CantidadColumnas(NameOfKernel);
	
	if(CantRowsOfKernel != CantColumnsOfKernel){
		cout << "\nKernell invalido : Recuerde que los kernel son matrices nxn";
		cout << "\nFilas del kernel -> " << CantRowsOfKernel;  
		cout << "\nColumnas del kernel -> " << CantColumnsOfKernel;
		return;
	}
	
	if(CantRowsOfKernel % 2 == 0){
		cout << "Kernell invalido : Recuerde que los kernel deben tener tamaño impar";
		cout << "\nTamaño nxn del kernel -> " << CantRowsOfKernel; 
		return;
	}
	
	tamKernel = CantRowsOfKernel; 
	
	int **matrizKernel;
  	matrizKernel = new int*[tamKernel];
    for(int i = 0; i < tamKernel; i++){
        matrizKernel[i] = new int[tamKernel];
    }
	
	char ignorar;
	for(int i = 0; i < tamKernel; i++){
		for(int j = 0; j < tamKernel; j++){
			archivoKernel >> matrizKernel[i][j];	
			archivoKernel >> ignorar;
		}
	}
	
	//ImprimirMatriz(matrizKernel,0, tamKernel, tamKernel); Verificar que la matriz se este llenando 	
		
	int **DesplazamientoRows, **DesplazamientoColums;
	
	DesplazamientoRows = new int*[tamKernel];
    for(int i = 0; i < tamKernel; i++){
        DesplazamientoRows[i] = new int[tamKernel];
    }
    
    DesplazamientoColums = new int*[tamKernel];
    for(int i = 0; i < tamKernel; i++){
        DesplazamientoColums[i] = new int[tamKernel];
    }
    
    
    DesplazamientoFilas(DesplazamientoRows, tamKernel); 
    DesplazamientoColumnas(DesplazamientoColums, tamKernel);

	//Matriz posicion aledañas :
	
	int Borde = tamKernel - 2;
	for(int i = Borde; i < numrows - Borde; i++){
		for(int j = Borde; j < numcols - Borde; j++){
			editMatriz[i][j] = combolusion(matriz,i,j,DesplazamientoRows,DesplazamientoColums,matrizKernel,tamKernel);
			if(editMatriz[i][j] > maxGray){
				editMatriz[i][j] = maxGray;
			}
		}
	} 

	int opc = 0;
	
	while(opc != 3 and opc != 2 and opc != 1){
		cout << "\nIngrese el tipo de filtrado de imagen que desea aplicar : ";
		cout << "\n1. Sin Borde (Disminute el tamaño de la imagen)";
		cout << "\n2. Borde de ceros";
		cout << "\n3. Duplicacion de bordes";
		cout << "\n -> "; 
		cin >> opc;
		cin.ignore();
		if(opc != 3 and opc != 2 and opc != 1 ){
			cout << "\nPorfavor ingrese una opcion valida\n";
		}
	}
	
	switch(opc) {
   		case 1:
   			cout << "\nMatriz de pixeles resultantes : \n";
   			ImprimirMatriz(editMatriz,Borde,numrows - Borde,numcols - Borde);
      		GuardarPgm(editMatriz,Borde,numrows - Borde,numcols - Borde,maxGray);
			break; //optional
   		case 2:		
			for(int i = 0; i < Borde;i++){
   				for(int j = 0; j < numcols; j++){
   					//cout << "\n" << i << " " << j;
					editMatriz[i][j] = 0;
   				}
   			}
   			
   			//cout << "\n----" << 1;
   			
   			for(int i = (numrows - 1); i > (numrows - 1) - Borde; i--){
   				for(int j = 0; j < numcols; j++){
   					//cout << "\n" << i << " " << j;
					editMatriz[i][j] = 0;
   				}
   			}
   			
   			//cout << "\n----" << 2;
   			
			for(int i = 0; i < Borde;i++){
   				for(int j = 0; j < numrows; j++){
   					//cout << "\n" << j << " " << i;
   					editMatriz[j][i] = 0;
   				}
   			}
   			
   			//cout << "\n----" << 3;
   			
   			for(int i = (numcols - 1); i > (numcols - 1) - Borde; i--){
   				for(int j = 0; j < numrows; j++){
   					//cout << "\n" << j << " " << i;
   					editMatriz[j][i] = 0;
   				}
   			}
   			//cout << "\n----" << 4;
   			cout << "\nMatriz de pixeles resultantes : \n";
   			ImprimirMatriz(editMatriz,0,numrows,numcols);
   			GuardarPgm(editMatriz,Borde,numrows,numcols,maxGray);
			break;
			
		case 3:
			// Rellenar pading superior 
			for(int i = Borde; i < numcols - Borde;i++){
				rellenarArriba(editMatriz,editMatriz[Borde][i],Borde,i);
				rellenarAbajo(editMatriz,editMatriz[(numrows-1-Borde)][i],(numrows-1-Borde),i,numrows);
			}
			
			// Rellenar pading inferior
			for(int i = Borde; i < numrows - Borde;i++){
				rellenarIzquierda(editMatriz,editMatriz[i][Borde],i,Borde);
				rellenarDerecha(editMatriz,editMatriz[i][(numcols-1-Borde)],i,(numcols-1-Borde), numcols);
			}
			
			// Rellenar esquina izquierda
			rellenarIzUp(editMatriz,editMatriz[Borde][Borde],Borde);
			rellenarIzDown(editMatriz,editMatriz[numrows-1-Borde][Borde],numrows-1-Borde,Borde);
			rellenarDeUp(editMatriz,editMatriz[Borde][numcols-1-Borde],Borde,numcols-1-Borde);
			rellenarDeDown(editMatriz,editMatriz[numrows-1-Borde][numcols-1-Borde],numrows-1-Borde,numcols-1-Borde,numrows);
			//rellenarEsquinasDe(editMatriz,editMatriz[numrows-1-Borde)][numcols-1-Borde)],numrows-1-Borde,numcols-1-Borde,numcols);
			
			ImprimirMatriz(editMatriz,0, numrows, numcols);
			GuardarPgm(editMatriz,Borde,numrows,numcols,maxGray);
			break;
		default : //Optional
      		cout << "Error : Ingrese una opcion valida.";
			break;
	}
	
	// Verificar matrices de desplazamiento : 
	//ImprimirMatriz(DesplazamientoRows,0, tamKernel, tamKernel);
	//ImprimirMatriz(DesplazamientoColums,0, tamKernel, tamKernel);	
	
    
}

int main() {

	string nameOfPgm, versionPgm, commentPgm;
	int  numrows = 0, numcols = 0, maxGray = 0;
	
	cout << "------ Bienvenido al programa de edicion de pgm con kernels ------\n";
	cout << "Porfavor ingrese el nombre del pgm que va a editar (sin extension) : ";
	getline(cin, nameOfPgm);
	nameOfPgm = nameOfPgm + ".pgm";
	
  	ifstream Reader(nameOfPgm.c_str());
  	string inputLine = "";
	
	// Comprobar que el archivo exista
	
	if (Reader){
      cout << "\nEl archivo " << nameOfPgm << " se ha abierto exitosamente \n";
    } else {
    	cout << "\nLamentablemente el archivo " << nameOfPgm << " no se ha podido abrir \n";
    	return 0;
	}
    
  	// Comprobamos que el archivo se escriba en texto, para poder leerlo (Linea 1)
  	
	getline(Reader,versionPgm);
  	if(versionPgm.compare("P2") != 0){
  		cout << "El tipo de archivo es P5\n No se puede leer prorque son binarios." << endl;
  		return 0;
  	}

	// Se guarda el comentario del Pgm ingresado (Linea 2) :
	
  	getline(Reader,commentPgm);

  	// Leemos los tamoaños de la matriz (Linea 3) : 
  
  	Reader >> numcols;
  	Reader >> numrows;
  	
  	// Lemos el valor maximo (Linea 4) :
  	
  	Reader >> maxGray;
  

  	int **matrizPixels,**EditmatrizPixels;
  	
  	EditmatrizPixels = new int*[numrows];
    for(int i = 0; i < numrows; i++){
        EditmatrizPixels[i] = new int[numcols];
    }
    
    matrizPixels = new int*[numrows];
    for(int i = 0; i < numrows; i++){
        matrizPixels[i] = new int[numcols];
    }

  	// Ahora leemos la informacion de los pixeles
  	for(int row = 0; row < numrows; ++row){
  		for (int col = 0; col < numcols; ++col){
  	  	Reader >> matrizPixels[row][col];
		EditmatrizPixels[row][col] = matrizPixels[row][col];	
  		} 
  	}
    
  
  Reader.close();
  
  int opcion;
  while(opcion != 4){
  	cout << "\nOpciones del programa : ";
  	cout << "\n1. Visuaizar imagen pgm leida.";
  	cout << "\n2. Guardar informacion e un txt.";
  	cout << "\n3. Editar imagen con kernel.";
  	cout << "\n4. Salir.";
  	cout << "\nIngrese la opcion -> ";	
  	cin >>opcion;
  	cout << "\n";
	
	switch(opcion) {
   		case 1:
   			cout << "Version : " << versionPgm << endl;
   			cout << "Comment : " << commentPgm << endl;
   			cout << numcols << " columns and " << numrows << " rows" << endl;
   			cout << "MaxGray : " <<  maxGray << endl;
      		ImprimirMatriz(matrizPixels,0,numrows,numcols);
      		break; //optional
      	case 2:
      		escrbirInformacion(matrizPixels,numrows,numcols,versionPgm,commentPgm,maxGray);
      		break;
      	case 3:
      		filtrarKernell(EditmatrizPixels,matrizPixels,numrows,numcols, maxGray);
      		break;
      	case 4:
      		cout << "\nGracias por utilizar el programa ....";
      		break;
   		default : //Optional
      		cout << "Error : Ingrese una opcion valida.";
			break;
	}	
  
  }
  

}
