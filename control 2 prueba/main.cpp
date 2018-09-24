#include <cstdlib>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <mpi.h>
#include "funciones.h"

struct label {
   int nodo;	/* numero del nodo */
   int anterior;	/* nodo precedente (-1 para el nodo inicial )*/
   int peso;	/* peso o coste total de la trayectoria que
				 * conduce al nodo, i.e., el coste total desde
				 * el nodo inicial hasta el actual. Un valor
				 * de -1 denota el infinito */
   int marca;	/* si el nodo ha sido marcado o no */
};
typedef struct label label_t;
using namespace std;
string estaciones[]={"SAN PABLO","NEPTUNO","PAJARITOS","LAS REJAS","ECUADOR","SAN ALBERTO HURTADO","UNIVERSIDAD DE SANTIAGO"
            ,"ESTACION CENTRAL","UNION LATINOAMERICANA","REPUBLICA","LOS HEROES","LA MONEDA","UNIVERSIDAD DE CHILE"
            ,"SANTA LUCIA","UNIVERSIDAD CATOLICA","BAQUEDANO","SALVADOR","MANUEL MONTT","PEDRO DE VALDIVIA"
            ,"LOS LEONES","TOBALABA","EL GOLF","ALCANTARA","ESCUELA MILITAR","MANQUEHUE","HERNANDO DE MAGALLANES","LOS DOMINICOS"
            ,"VESPUCIO NORTE","ZAPADORES","DORSAL","EINSTEIN","CEMENTERIOS"
            ,"CERRO BLANCO","PATRONATO","PUENTE CAL Y CANTO","SANTA ANA","TOESCA","PARQUE OHIGGINS","RONDIZZONI"
            ,"FRANKLIN","EL LLANO","SAN MIGUEL","LO VIAL","DEPARTAMENTAL","CIUDAD DEL NIÃ‘O","LO OVALLE","EL PARRON"
            ,"LA CISTERNA","CRISTOBAL COLON","FRANCISCO BILBAO","PRINCIPE DE GALES","SIMON BOLIVAR","PLAZA EGAÃ‘A"
            ,"LOS ORIENTALES","GRECIA","LOS PRESIDENTES","QUILIN","LAS TORRES","MACUL","VICUÃ‘A MACKENNA"
            ,"VICENTE VALDES","ROJAS MAGALLANES","TRINIDAD","SAN JOSE DE LA ESTRELLA","LOS QUILLAYES","ELISA CORREA"
            ,"HOSPITAL SOTERO DEL RIO","PROTECTORA DE LA INFANCIA","LAS MERCEDES","PLAZA DE PUENTE ALTO"
            ,"SANTA JULIA","LA GRANJA","SANTA ROSA","SAN RAMON","PLAZA DE MAIPU","SANTIAGO BUERAS","DEL SOL"
            ,"MONTE TABOR","LAS PARCELAS","LAGUNA SUR","BARRANCAS","PUDAHUEL","LO PRADO","BlANQUEADO"
            ,"GRUTA DE LOURDES","QUINTA NORMAL","CUMMING","PLAZA DE ARMAS","BELLAS ARTES","PARQUE BUSTAMANTE"
            ,"SANTA ISABEL","IRARRAZAVAL","Ã‘UBLE","RODRIGO DE ARAYA","CARLOS VALDOVINOS","CAMINO AGRICOLA"
            ,"SAN JOAQUIN","PEDRERO","MIRADOR","BELLAVISTA DE LA FLORIDA","CERRILLOS","LO VALLEDOR"
            ,"PEDRO AGUIRRE CERDA","BIO BIO","ESTADIO NACIONAL","Ã‘UÃ‘OA","INES DE SUAREZ"};

void Crear_Adyacente(int** Matriz);
void dijkstra( int N, int **A, int a, int b, int argc,char **argv);

int main(int argc, char** argv) {
     /**
     * 
     * @param argc Codigo Cantidad de Argumentos
     * @param argv Codigo Estacion de Destino
     * @return 
     */
    
    char* pa = argv[1];
    char* inicio = argv[2];
    char* fin = argv[3];
    //integrantes(pa);
       
  
    int** Metro;
    int filas = 107, columnas = 107;   /*Supongamos esos valores*/
    Metro = (int **)malloc(filas * sizeof(int *));
    int x,y;
    int vec_inicio,vec_fin;
    //variable para estacion inicial y linea inicial
    int find_ei,find_li;
    //variable para estacion final y linea final
    int find_ef,find_lf;
    
    //find_ei y find_ef muestran la posicion en que se encuentra esa estacion en su linea
   
    
    
   
    
    //estaciones del metro
    string lineas[12][30]={
    "SP","NP","PJ","LR","EC","AH","US","EL","LA","RP","LH","LM","CH","SL","UC","BA","SA","MM","PV","LE","TB","GO","AL","EM","MQ","HM","LD","0","0","0",
    "SAN PABLO","NEPTUNO","PAJARITOS","LAS REJAS","ECUADOR","SAN ALBERTO HURTADO","UNIVERSIDAD DE SANTIAGO","ESTACION CENTRAL","ULA","REPUBLICA","LOS HEROES","LA MONEDA","UNIVERSIDAD DE CHILE","SANTA LUCIA","UNIVERSIDAD CATOLICA","BAQUEDANO","SALVADOR","MANUEL MONTT","PEDRO DE VALDIVIA","LOS LEONES","TOBALABA","EL GOLF","ALCANTARA","ESCUELA MILITAR","MANQUEHUE","HERNANDO DE MAGALLANES","LOS DOMINICOS","0","0","0",
    "LC","EP","LO","CN","DE","LV","SM","LL","FR","RO","PQ","TO","HE","AN","CA","PT","CB","CE","EI","DO","ZA","AV","0","0","0","0","0","0","0","0",
    "LA CISTERNA","EL PARRON","LO OVALLE","CIUDAD DEL NIÃ‘O","DEPARTAMENTAL","LO VIAL","SAN MIGUEL","EL LLANO","FRANKLIN","RONDIZZONI","PARQUE OHIGGINS","TOESCA","LOS HEROES","SANTA ANA","PUENTE CAL Y CANTO","PATRONATO","CERRO BLANCO","CEMENTERIOS","EINSTEIN","DORSAL","ZAPADORES","VESPUCIO NORTE","0","0","0","0","0","0","0","0",
    "TOB","COL","BIL","PDG","SBO","PEG","LOR","RGR","LPR","RQU","LTO","MAC","VMA","VVA","RMA","TRI","SJE","LQU","ECO","HSR","LME","PIN","PPA","0","0","0","0","0","0","0",
    "TOBALABA","CRISTOBAL COLON","FRANCISCO BILBAO","PRINCIPE DE GALES","SIMON BOLIVAR","PLAZA EGAÃ‘A","LOS ORIENTALES","GRECIA","LOS PRESIDENTES","QUILIN","LAS TORRES","MACUL","VICUÃ‘A MACKENNA","VICENTE VALDES","ROJAS MAGALLANES","TRINIDAD","SAN JOSE DE LA ESTRELLA","LOS QUILLAYES","ELISA CORREA","HOSPITAL SOTERO DEL RIO","LAS MERCEDES","PROTECTORA DE LA INFANCIA","PLAZA DE PUENTE ALTO","0","0","0","0","0","0","0",
    "VIM","SJU","LGR","SRO","SRA","LCI","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0",
    "VICUÃ‘A MACKENNA","SANTA JULIA","LA GRANJA","SANTA ROSA","SAN RAMON","LA CISTERNA","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0",
    "PM","SB","DS","MT","LP","LS","BR","PU","SO","PR","BL","GL","QN","RC","NA","PZ","BE","BQ","PB","SI","IR","NU","RA","CV","AG","SJ","PE","MA","LF","VV",
    "PLAZA DE MAIPU","SANTIAGO BUERAS","DEL SOL","MONTE TABOR","LAS PARCELAS","LAGUNA SUR","BARRANCAS","PUDAHUEL","SAN PABLO","LO PRADO","BLANQUEADO","GRUTA DE LOURDES","QUINTA NORMAL","CUMMING","SANTA ANA","PLAZA DE ARMAS","BELLAS ARTES","BAQUEDANO","PARQUE BUSTAMANTE","SANTA ISABEL","IRARRAZAVAL","Ã‘UBLE","RODRIGO DE ARAYA","CARLOS VALDOVINOS","CAMINO AGRICOLA","SAN JOAQUIN","PEDRERO","MIRADOR","BELLAVISTA DE LA FLORIDA","VICENTE VALDES",
    "CER","LVA","PAC","FRA","BIO","NUB","ESN","NUO","ISU","LEN","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0",
    "CERRILLOS","LO VALLEDOR","PEDRO AGUIRRE CERDA","FRANKLIN","BIO BIO","Ã‘UBLE","ESTADIO NACIONAL","Ã‘UÃ‘OA","INES DE SUAREZ","LOS LEONES","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0","0"
    };
     for(int i = 0; i < columnas; i++){
        Metro[i] = (int *)malloc(columnas * sizeof(int));
    }
    char* rightStr = "-f";
    char* leftStr = "-v";
    
       
        if(strcmp(pa,leftStr)==0)
        {
            cout<<endl;
            std::cout<<"*******************INTEGRANTES*******************"<<endl;
            cout<<"Felipe Campos"<<" - ";
            cout<<"Eloy Lopez"<<" - ";
            cout<<"Rodrigo MuÃ±oz"<<endl;
            cout<<"*************************************************"<<endl;
        }
    
    if (strcmp(pa,rightStr)==0)
    {
    //FUNCION QUE MUESTRA COMO LA ESTACION DE ORIGEN GUARDANDO SU FILA Y SU COLUMNA
    for(y=0;y<12;y++)
    {
        for(x=0;x<30;x++)
        {
            if(inicio==lineas[y][x])
            {
                //cout<<endl<<"inicio"<<endl;
                //cout<<lineas[y+1][x]<<endl;
                find_li=y;
                find_ei=x;
            }
        }        
    }
    for(y=0;y<12;y++)
    {
        for(x=0;x<30;x++)
        {
            if(fin==lineas[y][x])
            {
               // cout<<endl<<"fin"<<endl;
               // cout<<lineas[y+1][x]<<endl;
                find_lf=y;
                find_ef=x;
            }
        }        
}
    for(x=0;x<107;x++)
    {
       if(lineas[find_li+1][find_ei]==estaciones[x])
       {
           vec_inicio=x;
       }
    }
    for(x=0;x<107;x++)
    {
      
       if(lineas[find_lf+1][find_ef]==estaciones[x])
       {
           vec_fin=x;
       }
    }
    
    
    
     Crear_Adyacente(Metro);
    dijkstra(107,Metro,vec_inicio,vec_fin, argc, argv);
    }
    
    }
    

void Crear_Adyacente(int** Matriz){
    for(int i=0;i<107;i++){
        for(int j=0;j<107;j++){
            Matriz[i][j]=0;
        }
    }
    Matriz[0][1]=1; Matriz[0][81]=1;Matriz[0][82]=1;
    Matriz[1][0]=1;Matriz[1][2]=1;
    Matriz[2][1]=1;Matriz[2][3]=1;
    Matriz[3][2]=1;Matriz[3][4]=1;
    Matriz[4][3]=1;Matriz[4][5]=1;
    Matriz[5][4]=1;Matriz[5][6]=1;
    Matriz[6][5]=1;Matriz[6][7]=1;
    Matriz[7][6]=1;Matriz[7][8]=1;
    Matriz[8][7]=1;Matriz[8][9]=1;
    Matriz[9][8]=1;Matriz[9][10]=1;
    Matriz[10][9]=1;Matriz[10][11]=1;Matriz[10][35]=1;Matriz[10][36]=1;
    Matriz[11][10]=1;Matriz[11][12]=1;
    Matriz[12][11]=1;Matriz[12][13]=1;
    Matriz[13][12]=1;Matriz[13][14]=1;
    Matriz[14][13]=1;Matriz[14][15]=1;
    Matriz[15][14]=1;Matriz[15][16]=1;Matriz[15][88]=1;Matriz[15][89]=1;
    Matriz[16][15]=1;Matriz[16][17]=1;
    Matriz[17][16]=1;Matriz[17][18]=1;
    Matriz[18][17]=1;Matriz[18][19]=1;
    Matriz[19][18]=1;Matriz[19][20]=1;Matriz[19][106]=1;
    Matriz[20][19]=1;Matriz[20][21]=1;Matriz[20][48]=1;
    Matriz[21][20]=1;Matriz[21][22]=1;
    Matriz[22][21]=1;Matriz[22][23]=1;
    Matriz[23][22]=1;Matriz[23][24]=1;
    Matriz[24][23]=1;Matriz[24][25]=1;
    Matriz[25][24]=1;Matriz[25][26]=1;
    Matriz[26][25]=1;
    Matriz[27][28]=1;
    Matriz[28][27]=1;Matriz[28][29]=1;
    Matriz[29][28]=1;Matriz[29][30]=1;
    Matriz[30][29]=1;Matriz[30][31]=1;
    Matriz[31][30]=1;Matriz[31][32]=1;
    Matriz[32][31]=1;Matriz[32][33]=1;
    Matriz[33][32]=1;Matriz[33][34]=1;
    Matriz[34][33]=1;Matriz[34][35]=1;
    Matriz[35][34]=1;Matriz[35][86]=1;Matriz[35][87]=1;Matriz[35][10]=1;
    Matriz[36][37]=1;Matriz[36][10]=1;
    Matriz[37][36]=1;Matriz[37][38]=1;
    Matriz[38][37]=1;Matriz[38][39]=1;
    Matriz[39][38]=1;Matriz[39][40]=1;Matriz[39][102]=1;Matriz[39][103]=1;
    Matriz[40][39]=1;Matriz[40][41]=1;
    Matriz[41][40]=1;Matriz[41][42]=1;
    Matriz[42][41]=1;Matriz[42][43]=1;
    Matriz[43][42]=1;Matriz[43][44]=1;
    Matriz[44][43]=1;Matriz[44][45]=1;
    Matriz[45][44]=1;Matriz[45][46]=1;
    Matriz[46][45]=1;Matriz[46][47]=1;
    Matriz[47][46]=1;Matriz[47][73]=1;
    Matriz[48][49]=1; Matriz[48][20]=1;
    Matriz[49][48]=1;Matriz[49][50]=1;
    Matriz[50][49]=1;Matriz[50][51]=1;
    Matriz[51][50]=1;Matriz[51][52]=1;
    Matriz[52][51]=1;Matriz[52][53]=1;
    Matriz[53][52]=1;Matriz[53][54]=1;
    Matriz[54][53]=1;Matriz[54][55]=1;
    Matriz[55][54]=1;Matriz[55][56]=1;
    Matriz[56][55]=1;Matriz[56][57]=1;
    Matriz[57][56]=1;Matriz[57][58]=1;
    Matriz[58][57]=1;Matriz[58][59]=1;
    Matriz[59][58]=1;Matriz[59][60]=1;Matriz[59][70]=1;
    Matriz[60][59]=1;Matriz[60][61]=1;Matriz[60][99]=1;
    Matriz[61][60]=1;Matriz[61][62]=1;
    Matriz[62][61]=1;Matriz[62][63]=1;
    Matriz[63][62]=1;Matriz[63][64]=1;
    Matriz[64][63]=1;Matriz[64][65]=1;
    Matriz[65][64]=1;Matriz[65][66]=1;
    Matriz[66][65]=1;Matriz[66][67]=1;
    Matriz[67][66]=1;Matriz[67][68]=1;
    Matriz[68][67]=1;Matriz[68][69]=1;
    Matriz[69][68]=1;
    Matriz[70][71]=1;Matriz[70][59]=1;
    Matriz[71][70]=1;Matriz[71][72]=1;
    Matriz[72][71]=1;Matriz[72][73]=1;
    Matriz[73][72]=1;Matriz[73][47]=1;
    Matriz[74][75]=1;
    Matriz[75][74]=1;Matriz[75][76]=1;
    Matriz[76][75]=1;Matriz[76][77]=1;
    Matriz[77][76]=1;Matriz[77][78]=1;
    Matriz[78][77]=1;Matriz[78][79]=1;
    Matriz[79][78]=1;Matriz[79][80]=1;
    Matriz[80][79]=1;Matriz[80][81]=1;
    Matriz[81][80]=1;Matriz[81][0]=1;
    Matriz[82][83]=1;Matriz[82][0]=1;
    Matriz[83][82]=1;Matriz[83][84]=1;
    Matriz[84][83]=1;Matriz[84][85]=1;
    Matriz[85][84]=1;Matriz[85][86]=1;
    Matriz[86][85]=1;Matriz[86][35]=1;
    Matriz[87][35]=1;Matriz[87][88]=1;
    Matriz[88][87]=1;Matriz[88][15]=1;
    Matriz[89][15]=1;Matriz[89][90]=1;
    Matriz[90][89]=1;Matriz[90][91]=1;
    Matriz[91][90]=1;Matriz[91][92]=1;
    Matriz[92][91]=1;Matriz[92][93]=1;Matriz[92][103]=1;Matriz[92][104]=1;
    Matriz[93][92]=1;Matriz[93][94]=1;
    Matriz[94][93]=1;Matriz[94][95]=1;
    Matriz[95][94]=1;Matriz[95][96]=1;
    Matriz[96][95]=1;Matriz[96][97]=1;
    Matriz[97][96]=1;Matriz[97][98]=1;
    Matriz[98][97]=1;Matriz[98][99]=1;
    Matriz[99][98]=1;Matriz[99][60]=1;
    Matriz[100][101]=1;
    Matriz[101][100]=1;Matriz[101][102]=1;
    Matriz[102][101]=1;Matriz[102][39]=1;
    Matriz[103][39]=1;Matriz[103][92]=1;
    Matriz[104][92]=1;Matriz[104][105]=1;
    Matriz[105][104]=1;Matriz[105][106]=1;
    Matriz[106][105]=1;Matriz[106][19]=1;
}


/* Calcula el coste minimo de alcanzar un nodo final 'b'
 * grafo no dirigido con N nodos, a partir del nodo inicial 'a',
 * dada su matriz de adyacencia A */
void dijkstra( int N, int **A, int a, int b,int argc,char **argv) {
    int myid,numprocs;
    MPI_Init( &argc, &argv );
    MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD,&myid);
    int split1[1];
    
    MPI_Status stat;
   label_t *Labels;
   int i, i0, j, peso;
   int ruta[107];		/* array de nodos de la ruta minima */
   for (i=0;i<107;i++)
   {
       ruta[i]=-1;
   }
   
   /* Crea dinamicamente el arreglo de etiquetas de nodo */
   if ( ( Labels = new label_t[N] ) == NULL ) return;

   /* nodo inicial 'a' entre 0 y N - 1 */
   if ( a < 0 || a > N - 1 ) return;
   /* nodo final 'a' entre 0 y N - 1 */
   if ( b < 0 || b > N - 1 ) return;

    
   /* inicializar las etiquetas de nodo */
   for ( i = 0; i < N; i++ ) {
      Labels[i].nodo = i;
      if ( i != a ) {
         Labels[i].anterior = -1;	/* aun no se ha definido predecesor */
         Labels[i].peso = -1;	/* infinito */
         Labels[i].marca = 0;
         
      }
      else {
         Labels[i].anterior = -1;	/* aun no se ha definido predecesor */
         Labels[i].peso = 0;		/* coste del nodo inicial a si mismo es cero */
         Labels[i].marca = 0;
      }
   }
   
   /* continuamos este ciclo mientras existan nodos no marcados */
 if(myid==0)
 {
     
 cout<<endl;
            cout<<"*******************"<<endl;
            cout<<"OPCIONES ELEGIDAS DE ESTACIONES"<<endl;
            cout<<"*******************"<<endl;
            cout<<endl<<"inicio"<<endl;
            cout<<endl<<estaciones[a]<<endl;
            cout<<endl<<"fin"<<endl;
            cout<<estaciones[b]<<endl<<endl;
            
   while ( 1 ) {
      /* busca entre todos los nodos no marcados el de menor peso, descartando los
       * de peso infinito (-1) */
      peso = -1;
      i0 = -1;
    for ( i = 0; i < N; i++ ) {
         if ( Labels[i].marca == 0 && Labels[i].peso >= 0 )
            if ( peso == -1 ) {
               peso = Labels[i].peso;
               i0 = i;
            }
            else if ( Labels[i].peso <= peso ) {
               peso = Labels[i].peso;
               i0 = i;
            }
      }
      if ( i0 == -1 ) {	/* termina si no encuentra */
         
         break;
      }
      /* actualiza el peso de todos los sucesores (si los hay) del nodo
       * encontrado y luego seÃ±ala dicho nodo como marcado */

      for ( i = 0; i < N; i++ ) {
         if ( A[i0][i] > 0 ) {
            /* si el coste acumulado sumado al coste del enlace del nodo i0 al nodo i
             * es menor al coste del nodo i (o si el coste del nodo i es infinito),
             * debemos actualizar */
            if ( Labels[i].peso == -1) {
               Labels[i].peso = Labels[i0].peso + A[i0][i];
               Labels[i].anterior = i0;
           
            }
         }
      }
      Labels[i0].marca = 1;
 
   }
 
    /* Ruta desde el nodo 'a' hasta el nodo 'b' */
   int longitud = 2;
   i = b;
   
   while ( ( i = Labels[i].anterior ) != a ) 
   {
       longitud++;	/* primero estimamos la longitud de la ruta */
       
   }
  
   ruta[longitud - 1] = b;		/* luego rellenamos */
   i = b;
   j = 0;
   for ( j = 1; j < longitud; j++ ) {
      i = Labels[i].anterior;
      ruta[longitud - j - 1] = i;
   }
   MPI_Send(&ruta,107,MPI_INT,1,20,MPI_COMM_WORLD);
 }
if(myid==1)
 {
    int largo=0;
    MPI_Recv(&ruta,107,MPI_INT,0,20,MPI_COMM_WORLD,&stat);
    for (i=0;i<107;i++)
    {
        if(ruta[i]>=0)
        {
            largo=largo+1;
        }
    }
    for (i=0;i<largo;i++)
    {
        cout<<estaciones[ruta[i]];
        if(i<largo-1)
        {
            cout<<" - ";
        }
    }
    cout<<endl;
 }
   delete [] Labels;
   MPI_Finalize();
}

