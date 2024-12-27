// lee.c   (Creado por Hugo Araya Carrasco)
#include <stdio.h>

/* Programa que permite la lectura y generacion de archivos en formato PGM
Este formato tiene la siguiente estructura:
P5									// Es la cadena magica que identifica al PGM
# Comentarios pueden ser varios		
ancho alto							// Pixel de ancho y pixel de alto en formato decimal
grises								// Escala de grises entre 0 y 255 en formato decimal
los ascii correspondientes a la cantidad ancho x alto pixeles.
*/

main()
{
	FILE *arch,*sali;
	unsigned char c,c1,c2;
	int fila, colu, i, j, gris;
	unsigned char dibu[500][500],otra[500][500];

	arch=fopen("Gatito.pgm","rb");
	c1=fgetc(arch);
	c2=fgetc(arch);
    if (c1!='P' || c2!='5')
    {
		printf("\nFormato no corresponde a una Imagen\n");
    }
	c=fgetc(arch);
    c=fgetc(arch);
	while (c!='\n')
		c=fgetc(arch);
	fscanf(arch,"%d",&colu);
	fscanf(arch,"%d",&fila);
	fscanf(arch,"%d",&gris);
	
	printf("\n%c%c",c1,c2);
	printf("\nfila : %d",fila);
	printf("\ncolu : %d",colu);
	printf("\ngris : %d",gris);

	for(i=0; i<fila; i++)
		for(j=0; j<colu; j++)
		{
			c=fgetc(arch);
			dibu[i][j]=c;
		}

// Proceso	
	for(i=0; i<fila; i++)
		for(j=0; j<colu; j++)
		    otra[i][j]=dibu[(fila-1)-i][j];

// Fin del Proceso	
    sali=fopen("puerto4.pgm","wb");
	fprintf(sali,"P5\n");
	fprintf(sali,"# Creado por Hugo Araya C. (2003)\n");
	fprintf(sali,"%d %d\n",colu,fila);
    fprintf(sali,"%d\n",gris);
	for(i=0; i<fila; i++)
		for(j=0; j<colu; j++)
		{
			fprintf(sali,"%c",otra[i][j]);
//			fputc(c,sali);
		}

	fclose(arch);
	fclose(sali);
}
