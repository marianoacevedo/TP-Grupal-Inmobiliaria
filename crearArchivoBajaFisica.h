#ifndef _crearArchivoBajaFisica_H_
#define _crearArchivoBajaFisica_H_
#include "erroresMenuColores.h" //Esta libreria de creacion propia la usamos para darle color a los distintos errores, aceptaciones y titulos. Tambien emite los errores y el menu.
#include <stdio.h>   // Esta libreria proporciona las funciones "scanf" y "printf", para las entradas y salidas de datos.
#include <ctype.h>  // Esta libreria proporciona funciones para realizar operaciones de caracteres, como convertir mayúsculas a minúsculas, verificar tipos de caracteres (números, letras, etc.).
#include <locale.h> // Esta libreria permite configurar la configuración regional. La forma en que se manejan caracteres especiales, números y formatos de fecha y hora.
#include <windows.h> // API del Sistema Operativo de Windows (Permite trabajar sobre la Consola).
#include <dirent.h> // Esta libreria sirve para manejar el acceso a directorios y archivos

//Funcion que crea el archivo "propiedades.dat". Si el archivo existe emite un mensaje que ya esta creado.

void crearArchivo()
{
    char nom[20]="propiedades.dat";
    printf("\n Creando archivo...\n");
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // Verifico si el archivo ya existe
    FILE* archivoExistente = fopen(nom, "rb");
    if (archivoExistente != NULL)
    {
        fclose(archivoExistente);
        verde();
        printf("\nEL ARCHIVO propiedades.dat YA EXISTE. NO FUE CREADO\n");
        blanco();
        return; // Si existe, arroja la advertencia y sale de la funcion.
    }

    FILE* archivo = fopen(nom, "wb");

    if (archivo == NULL)
    {
        error(0);
    }
    else
    {

        fclose(archivo);
        verde();
        printf("\nEL ARCHIVO propiedades.dat SE CREO EXITOSAMENTE.\n");
        blanco();
    }

}

//Funcion que lista los archivos .xyz creados.

void listarXYZ()
{
    DIR *directorio;
    struct dirent *entrada;

    directorio = opendir(".");
    if (directorio == NULL)
    {
        error(23);
        return;
    }

    printf("\nArchivos de bajas de propiedades .xyz:\n\n");

    while ((entrada = readdir(directorio)) != NULL)
    {
        char *nombreArchivo = entrada->d_name;
        int longitud = strlen(nombreArchivo);

        if (longitud >= 4 && strcmp(nombreArchivo + longitud - 4, ".xyz") == 0)
        {
            printf("- %s\n", nombreArchivo);
        }
    }

    closedir(directorio);
}

#endif //_crearArchivoBajaFisica_H_
