// Programa para consultar los datos de la base de datos
#include <mysql.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>


int main(int argc, char **argv)
{
	MYSQL *conn;
	int err;
	// Almacenar resultados de consultas
	MYSQL_RES *resultado;
	MYSQL_ROW row;
	// Creamos conexión al servidor MYSQL
	conn = mysql_init(NULL);
	if (conn==NULL)
	{
		printf ("Error al crear la conexión: %u %s\n",
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	// Inicializar la conexión
	conn = mysql_real_connect (conn, "localhost","root", "mysql",
							   "datos_juego",0, NULL, 0);
	if (conn==NULL)
	{
		printf ("Error al inicializar la conexión: %u %s\n",
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
		
	
		
	// Consulta en mysql
	
	/*La consulta propuesta la he adaptado para que el codigo funcione. Destaco que la consulta
	deberia de ser: SELECT PARTIDA.ID, PARTIDA.DURACION, PARTIDA.GANADOR FROM (JUGADOR,DATOS,PARTIDA) WHERE JUGADOR.NOMBRE='entrar_por_teclado' 
	AND JUGADOR.ID=DATOS.ID_J AND DATOS.ID_P=PARTIDA.ID;
		
	Esta consulta coge la ID de la partida, la duración y el ganador, de las partidas en las cuales
	jugó la persona que se entra por teclado*/
		
	char name[50];
	printf("Dame el nombre del jugador:\n");
	err = scanf("%s",name);
	if (err!=1) {
		printf("Error al introducir los datos\n");
		exit(1);
	}
	char consulta[200];
	strcpy(consulta,"SELECT * FROM (PARTIDA,JUGADOR,DATOS) WHERE JUGADOR.NOMBRE='");
	strcat(consulta,name);
	strcat(consulta, "'AND JUGADOR.ID=DATOS.ID_J AND DATOS.ID_P=PARTIDA.ID");
	err=mysql_query (conn, consulta);
	if (err!=0)
	{
		printf ("Error al consultar datos de la base %u %s\n",
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	// Recoger el resultado de la consulta
	resultado = mysql_store_result (conn);
	row = mysql_fetch_row (resultado);
	if (row == NULL)
		printf ("No se han obtenido datos en la consulta\n");
	else
		printf("\n");
		printf("Las partidas donde ha jugado %s son:\n",name);
		printf("\n");
		while (row !=NULL)
	{
			printf("La ID de la partida es:%s, su duración:%s, y el ganador:%s\n", row[0], row[3], row[4]);
			row = mysql_fetch_row (resultado);
	}
	printf("\n");
		
	
		
	// Consulta en mysql
	
	/*Esta consulta recibe el nombre de un jugador por teclado y devuelve el listado de
	partidas donde ha jugado con los respectivos puntos del jugador*/
	
	printf("Dame el nombre del jugador:\n");
	err = scanf("%s",name);
	if (err!=1) {
		printf("Error al introducir los datos\n");
		exit(1);
	}
	strcpy(consulta,"SELECT * FROM (DATOS,JUGADOR) WHERE JUGADOR.NOMBRE='");
	strcat(consulta,name);
	strcat(consulta, "'AND JUGADOR.ID=DATOS.ID_J");
	err=mysql_query (conn, consulta);
	if (err!=0)
	{
		printf ("Error al consultar datos de la base %u %s\n",
				mysql_errno(conn), mysql_error(conn));
		exit (1);
	}
	// Recoger el resultado de la consulta
	resultado = mysql_store_result (conn);
	row = mysql_fetch_row (resultado);
	if (row == NULL)
		printf ("No se han obtenido datos en la consulta\n");
	else
		printf("\n");
		printf("El listado de partidas de %s con sus respectivos puntos es:\n",name);
		printf("\n");
	while (row !=NULL)
	{
		printf("La ID de la partida es:%s, y su puntuación:%s\n", row[0], row[2]);
		row = mysql_fetch_row (resultado);
	}
		
	// Cerrar la conexión de mysql
	mysql_close (conn);
}

