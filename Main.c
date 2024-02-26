/*Documentacion de errores:

Error 1: En la funcion de crearArchivo(), se le agrego una condicion que si exite "propiedades.dat" no se vuelva a crear.
Aca se presentaron problemas ya que si se volvia a ejecutar la funcion se borraban todo los datos que contenia el archivo.
Un error mas que grave para la aplicacion.

Error 2: En los menues de toda la aplicacion se le aplicaron validaciones acerca de la opcion(int) que se ingresa. Un problema que tuvimos
fue que si se ingresaba un caracter(sea de manera o no involuntaria) salia del menu o cerraba sesion de la aplicacion, ya que nuestros menues
la opcion salir era ingresando un 0 y el caracter lo tomaba como un 0 o culquier otra cosa.

Error 3: En la funcion altaInmueble(), se le agregaron funciones de tiempo a la fecha de ingreso de una propiedad. Con esto se corrigio que
no se pueda ingresar una fecha mayor a la actual, ya que seria una fecha ilogica para el registro.
 */

#include <stdio.h> // Esta libreria proporciona las funciones "scanf" y "printf", para las entradas y salidas de datos.
#include <string.h>  // Esta libreria proporciona funciones para la manipulacion de cadena de caracteres.
#include <time.h>    // Esta libreria proporciona funciones para trabajar con fechas y horas.
#include <ctype.h>  // Esta libreria proporciona funciones para realizar operaciones de caracteres, como convertir mayúsculas a minúsculas, verificar tipos de caracteres (números, letras, etc.).
#include <locale.h> // Esta libreria permite configurar la configuración regional. La forma en que se manejan caracteres especiales, números y formatos de fecha y hora.
#include <windows.h> // API del Sistema Operativo de Windows (Permite trabajar sobre la Consola).
#include <dirent.h> // Esta libreria sirve para manejar el acceso a directorios y archivos

///Librerias propias
#include "erroresMenuColores.h" //Esta libreria de creacion propia la usamos para darle color a los distintos errores, aceptaciones y titulos. Tambien emite los errores y el menu.
#include "operaciones.h"        //Esta libreria de creacion propia tiene todas las funciones CRUD
#include "crearArchivoBajaFisica.h"  //Esta libreria de crecion propia  tiene las funciones de creacion del archivos .dat y la funcion que lista los archivos .XYZ

/*Desde la funcion main se maneja el menu de opciones, la cual dependiendo
  de la opcion que se eleja hace un llamado a la funcion en cuestion.*/

int main()
{

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    FILE *Pa;
    int opcion=1;
    struct unidad u;

    verde();
    printf("\n\n----------------------------- BIENVENIDO AL SISTEMA DE PROCESAMIENTO DE PROPIEDADES -----------------------------\n\n");
    blanco();

    while(opcion !=0)
    {
        opcion = menu();

        switch(opcion)
        {
        case 1:
            crearArchivo();
            break;
        case 2:
            listarArchivo();
            break;
        case 3:
            altaInmueble(Pa);
            break;
        case 4:
            buscarInmueble(Pa);
            break;
        case 5:
            modificarInmueble(Pa);
            break;
        case 6:
            bajaLogica(Pa);
            break;
        case 7:
            bajaFisica(Pa);
            break;
        case 8:
            listarXYZ();
            break;
        case 0:
            verde();
            printf("\n***-- Gracias por utilizar nuestro servicio ! --***\n\n");
            blanco();
            break;
        default:
            error(2);
            break;
        }

    }

    return 0;
};
