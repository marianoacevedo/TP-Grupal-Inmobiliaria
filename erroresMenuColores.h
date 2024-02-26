#ifndef _erroresMenuColores_H_
#define _erroresMenuColores_H_
#include <stdio.h> // Esta libreria proporciona las funciones "scanf" y "printf", para las entradas y salidas de datos.
#include <string.h> // Esta libreria proporciona funciones para la manipulacion de cadena de caracteres.
#include <time.h> // Esta libreria proporciona funciones para trabajar con fechas y horas.
#include <ctype.h>  // Esta libreria proporciona funciones para realizar operaciones de caracteres, como convertir mayúsculas a minúsculas, verificar tipos de caracteres (números, letras, etc.).
#include <locale.h> // Esta libreria permite configurar la configuración regional. La forma en que se manejan caracteres especiales, números y formatos de fecha y hora.
#include <windows.h> // API del Sistema Operativo de Windows (Permite trabajar sobre la Consola).
#include <dirent.h> // Esta libreria sirve para manejar el acceso a directorios y archivos

// Funcion que se encarga de pasar el mensaje de error que sea solicitado.

int error( int num_err )
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);// Funcion que cambia los colores de texto.Solo sirve para sistemas Windows.

    char *errores[] =
    {
        "NO SE PUDO CREAR EL ARCHIVO DAT",
        "ERROR EN LA APERTURA DEL ARCHIVO",//1
        "OPCION INVALIDA. INGRESE LA OPCION CORRECTA",
        "CARACTER INVALIDO. INGRESE UN NUMERO ENTERO POSITIVO",
        "YA EXISTE ESE NUMERO DE ID, POR FAVOR INGRESE UN NUMERO DISTINTO",
        "NO SE PUDO OBTENER LA FECHA ACTUAL, CONSULTE CON EL DESARROLLADOR DE LA APP",
        "EL ANIO INGRESADO DEBE SER MENOR O IGUAL AL ANIO ACTUAL",
        "EL MES INGRESADO DEBE SER MAYOR O IGUAL A 1 Y MENOR O IGUAL 12",//7
        "EL MES INGRESADO DEBE SER IGUAL O MENOR AL MES ACTUAL",
        "EL DIA INGRESADO DEBE SER MENOR O IGUAL AL DIA ACTUAL",
        "NO SE HA INGRESADO NINGÚN ZONA",
        "NO SE HA INGRESADO NINGÚN CIUDAD",
        "LA CANTIDAD DE DORMITORIOS INGRESADOS DEBE SER UN NÚMERO MAYOR A 0",//12
        "LA CANTIDAD DE BAÑOS INGRESADOS DEBE SER UN NÚMERO MAYOR A 0",
        "LA CANTIDAD DE M2 INGRESADOS DEBE SER UN NÚMERO MAYOR A 0",
        "LA CANTIDAD DE M2 CUBIERTOS NO PUEDE SER MAYOR A LA CANTIDAD DE M2 TOTALES",
        "EL PRECIO INGRESADO DEBE SER UN NÚMERO MAYOR A 0",
        "CARACTER INVALIDO, SE DEBEN INGRESAR SOLO NUMEROS",//17
        "PROPIEDAD NO ENCONTRADA EN NUESTRA BASE DE DATOS",
        "NO SE HA INGRESADO NINGUN DATO",
        "OPCION INVALIDA. NO SE REALIZO NINGUNA MODIFICACION",
        "OPCION INVALIDA. NO SE REALIZO NINGUNA ELIMINACION",//21
        "NO SE PUDO CREAR EL ARCHIVO XYZ",
        "ERROR AL ABRIR EL DIRECTORIO",
        "EL ANIO INGRESADO DEBE SER MAYOR O IGUAL A 1810",//24
        "EL DIA INGRESADO DEBE SER MAYOR A 1 Y MENOR A 31", //25
        "EL MES INGRESADO TIENE 30 DIAS, ELIJA UN DIA EN ESE RANGO", //26
        "EL MES DE FEBRERO TIENE 28 DIAS (29 SI ES BISIESTO), ELIJA UN DIA EN ESE RANGO",//27
        "LA FECHA MAXIMA DEBE SER MAYOR O IGUAL A LA FECHA MINIMA",//28
    };

    SetConsoleTextAttribute(hConsole,FOREGROUND_RED);//Indicar el color del texto seleccionado
    printf( "\nError: %s.\n\n", errores[num_err] );
    SetConsoleTextAttribute(hConsole,FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);// Indica el color del fondo de la sección de la consola

    return 0;
}

// Funcion que da color a los distintos errores, titulos, aceptaciones, etc.

void verde()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole,FOREGROUND_INTENSITY | FOREGROUND_GREEN);
}
void blanco()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole,FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}
void azul()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
}
void rojo()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole,FOREGROUND_RED);

}
void gris()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, FOREGROUND_INTENSITY);
}
void amarillo()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole,FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
}

// Funcion del menu principal la cual retorna la opcion seleccionada por el usaurio.

int menu()
{
    int opcion=9;

    azul();
    printf("\n MENU PRINCIPAL\n\n");
    blanco();

    printf("\n OPCION 1: Crear Archivo");
    printf("\n OPCION 2: Listar archivo ");
    printf("\n OPCION 3: Dar de alta inmueble");
    printf("\n OPCION 4: Buscar inmueble");
    printf("\n OPCION 5: Modificar inmueble");
    printf("\n OPCION 6: Baja Logica",163);
    printf("\n OPCION 7: Baja Fisica");
    printf("\n OPCION 8: Listar XYZ",162);
    gris();
    printf("\n OPCION 0: Salir del programa\n\n");

    amarillo();
    printf("\n Elija la opci%cn que desee o presione 0 para salir:\n",162);
    blanco();

    scanf("%d",&opcion);
    fflush(stdin);

    return opcion;
}

#endif // erroresMenuColores_H_
