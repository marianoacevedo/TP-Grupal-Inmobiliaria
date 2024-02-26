#ifndef _operaciones_H_
#define _operaciones_H_
#include <stdio.h> // Esta libreria proporciona las funciones "scanf" y "printf", para las entradas y salidas de datos.
#include <string.h> // Esta libreria proporciona funciones para la manipulacion de cadena de caracteres.
#include <time.h> // Esta libreria proporciona funciones para trabajar con fechas y horas.
#include <ctype.h>  // Esta libreria proporciona funciones para realizar operaciones de caracteres, como convertir mayúsculas a minúsculas, verificar tipos de caracteres (números, letras, etc.).
#include <locale.h> // Esta libreria permite configurar la configuración regional. La forma en que se manejan caracteres especiales, números y formatos de fecha y hora.
#include <windows.h> // API del Sistema Operativo de Windows (Permite trabajar sobre la Consola).
#include <dirent.h> // Esta libreria sirve para manejar el acceso a directorios y archivos
#include "erroresMenuColores.h" //Esta libreria de creacion propia la usamos para darle color a los distintos errores, aceptaciones y titulos. Tambien emite los errores y el menu.
#define N 30
#define M 100

typedef struct unidad
{
    int id;
    int diaI;
    int mesI;
    int anioI;
    char zona[N];
    char ciudad[N];
    int dormitorios;
    int banios;
    float supTotal;
    float supCubierta;
    float precio;
    char moneda[N];
    char tipoProp[N];
    char operacion[N];
    int diaS;
    int mesS;
    int anioS;
    int estado;

} unidad;

/*Esta funcion lee y emite todos los datos del archivo propiedades.dat.
  Si el mismo no existe la funcion emite un mensaje de error.*/

void listarTodo()
{
    struct unidad u;
    FILE *pArchivo;
    pArchivo=fopen("propiedades.dat","rb");

    printf("\n| Id | Fecha de Ingreso |         Zona         |        Ciudad        |Dormitorios|Banos|  Sup Cub  |  Sup Tot  |  Precio  |Moneda| Tipo de Prop |    Operacion    | Fecha de salida | Estado | ");

    if(pArchivo!=NULL)
    {
        fread(&u,sizeof(struct unidad),1,pArchivo);
        while(!feof(pArchivo))
        {
            printf("|%4d|    %2d/%2d/%4d    |%22s|%22s|%11d|%5d|%9.1fM2|%9.1fM2|%10.1f|%6s|%14s|%17s|   %2d/%2d/%4d    |%5d   |\n",
                   u.id,u.diaI,u.mesI,u.anioI,u.zona,u.ciudad,u.dormitorios,u.banios,u.supTotal,u.supCubierta,
                   u.precio,u.moneda,u.tipoProp,u.operacion,u.diaS,u.mesS,u.anioS,u.estado);
            fread(&u,sizeof(struct unidad),1,pArchivo);

        }

        fclose(pArchivo);
    }
    else
    {
        error(1);
    }

}

//Esta funcion emite las propiedades activas. Estos son los que estan setiados en u.estado = 1

void listarActivo()
{
    struct unidad u;
    FILE *pArchivo;
    pArchivo=fopen("propiedades.dat","rb");

    if(pArchivo!=NULL)
    {
        printf("\n| Id | Fecha de Ingreso |         Zona         |        Ciudad        |Dormitorios|Banos|  Sup Cub  |  Sup Tot  |  Precio  |Moneda| Tipo de Prop |    Operacion    | Fecha de salida | Estado | ");

        while(fread(&u,sizeof(struct unidad),1,pArchivo)==1)
        {
            if(u.estado==1)
            {
                printf("|%4d|    %2d/%2d/%4d    |%22s|%22s|%11d|%5d|%9.1fM2|%9.1fM2|%10.1f|%6s|%14s|%17s|   %2d/%2d/%4d    |%5d   |\n",
                       u.id,u.diaI,u.mesI,u.anioI,u.zona,u.ciudad,u.dormitorios,u.banios,u.supTotal,u.supCubierta,
                       u.precio,u.moneda,u.tipoProp,u.operacion,u.diaS,u.mesS,u.anioS,u.estado);
            };

        }

        fclose(pArchivo);
    }
    else
    {
        error(1);
    }
}

// Funcion que se le indica por teclado desde hasta que fecha se quiere buscar, y imprime todos las propiedades dentro de ese rango de fecha.

void listarRangoTiempo()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    struct unidad u;
    FILE *Pa;
    Pa=fopen("propiedades.dat","rb");


    int diaFechaMin =0, mesFechaMin=0, anioFechaMin=0, diaFechaMax=0, mesFechaMax=0, anioFechaMax =0;
    int flagIngresarDiaMin = 1;
    int flagIngresarDiaMax = 1;

    //colocamos 1810 porque no tiene sentido una fecha menor en una propiedad de Argentina
    //podriamos poner la fecha de creacion de la inmobiliaria mas antigua
    while(anioFechaMin<=1810)
    {
        amarillo();
        printf("\nIngrese una fecha minima\n\n");
        blanco();
        printf("Ingrese el anio de la fecha minima\n");
        scanf("%d",&anioFechaMin);
        fflush(stdin);
        if (anioFechaMin<=1810)
        {
            error(24);
        }
    }
    while(mesFechaMin<1 || mesFechaMin>12)
    {
        printf("\nIngrese el mes de la fecha minima\n");
        scanf("%d",&mesFechaMin);
        fflush(stdin);
        if (mesFechaMin<1 || mesFechaMin>12)
        {
            error(7);
        }
    }

    while(flagIngresarDiaMin)
    {
        printf("\nIngrese el dia de la fecha minima\n");
        scanf("%d",&diaFechaMin);
        fflush(stdin);
        if (diaFechaMin<1 || diaFechaMin>31)
        {
            error(25);
            flagIngresarDiaMin = 1;
        }
        //si es abril, junio, sep o nov tiene como maximo 30 dias
        else if ((mesFechaMin==4 || mesFechaMin==6 || mesFechaMin==9 || mesFechaMin==11) && diaFechaMin>30)
        {
            error(26);
            flagIngresarDiaMin = 1;
        }
        //si es febrero----> si es bisiesto no puede ser mayor a 29, si no es bisiesto no puede ser mayor a 28
        else if ((mesFechaMin==2)&&((anioFechaMin %4==0 && diaFechaMin>29) || (anioFechaMin %4!=0 && diaFechaMin>28 )))
        {
            error(27);
            flagIngresarDiaMin = 1;
        }
        else
        {
            flagIngresarDiaMin = 0;
        }

    }

    // Ahora trabajamos con la fecha maxima
    while(anioFechaMax<=1810)
    {
        amarillo();
        printf("\nIngrese una fecha maxima\n\n");
        blanco();
        printf("Ingrese el anio de la fecha maxima\n");
        scanf("%d",&anioFechaMax);
        fflush(stdin);
        if (anioFechaMax<=1810 )
        {
            error(24);
        }
        else if (anioFechaMax<anioFechaMin)
        {
            error(28);
            anioFechaMax=0;
        }
    }

    while(mesFechaMax<1 || mesFechaMax>12)
    {
        printf("\nIngrese el mes de la fecha maxima\n");
        scanf("%d",&mesFechaMax);
        fflush(stdin);
        if (mesFechaMax<1 || mesFechaMax>12)
        {
            error(7);
        }
        else if ((anioFechaMax==anioFechaMin) && (mesFechaMax<mesFechaMin))
        {
            error(28);
        }
    }

    while(flagIngresarDiaMax)
    {
        printf("\nIngrese el dia de la fecha maxima\n");
        scanf("%d",&diaFechaMax);
        fflush(stdin);
        if (diaFechaMax<1 || diaFechaMax>31)
        {
            error(25);
            flagIngresarDiaMax = 1;
        }
        //si es abril, junio, sep o nov tiene como maximo 30 dias
        else if ((mesFechaMax==4 || mesFechaMax==6 || mesFechaMax==9 || mesFechaMax==11) && diaFechaMax>30)
        {
            error(26);
            flagIngresarDiaMax = 1;
        }
        //si es febrero----> si es bisiesto no puede ser mayor a 29, si no es bisiesto no puede ser mayor a 28
        else if ((mesFechaMax==2)&&((anioFechaMax %4==0 && diaFechaMax>29) || (anioFechaMax %4!=0 && diaFechaMax>28 )))
        {
            error(27);
            flagIngresarDiaMax = 1;
        }
        else if ((anioFechaMax==anioFechaMin) && (mesFechaMax==mesFechaMin) && (diaFechaMax<diaFechaMin))
        {
            error(28);
            flagIngresarDiaMax = 1;
        }
        else
        {
            flagIngresarDiaMax = 0;
        }

    }
    //comparacion rango de fecha ingresada por el usuario con columna fecha de ingreso
    if (Pa != NULL)
    {
        printf("\n| Id | Fecha de Ingreso |         Zona         |        Ciudad        |Dormitorios|Banos|  Sup Cub  |  Sup Tot  |  Precio  |Moneda| Tipo de Prop |    Operacion    | Fecha de salida | Estado | \n");

        //fecha minima
        while (fread(&u, sizeof(struct unidad), 1, Pa) == 1)
        {
            if((anioFechaMin <= u.anioI)&& (u.anioI <= anioFechaMax))
            {
                if((((anioFechaMin == u.anioI)&&(mesFechaMin<= u.mesI)) || (anioFechaMin < u.anioI)) &&
                        (((anioFechaMax == u.anioI)&&(mesFechaMax>= u.mesI)) || (anioFechaMax > u.anioI)))
                {

                    //mismo anio o distinto anio
                    if (((anioFechaMin == u.anioI) && (mesFechaMin== u.mesI)&&(diaFechaMin <= u.diaI) || (anioFechaMin < u.anioI) ||  (mesFechaMin < u.mesI)) &&
                            ((anioFechaMax == u.anioI) && (mesFechaMax== u.mesI)&&(diaFechaMax >= u.diaI) || (anioFechaMax > u.anioI) ||  (mesFechaMax > u.mesI)))
                    {

                        printf("|%4d|    %2d/%2d/%4d    |%22s|%22s|%11d|%5d|%9.1fM2|%9.1fM2|%10.1f|%6s|%14s|%17s|   %2d/%2d/%4d    |%5d   |\n",
                               u.id,u.diaI,u.mesI,u.anioI,u.zona,u.ciudad,u.dormitorios,u.banios,u.supTotal,u.supCubierta,
                               u.precio,u.moneda,u.tipoProp,u.operacion,u.diaS,u.mesS,u.anioS,u.estado);
                    }
                }
            }
        }
        fclose(Pa);
    }
    else
    {
        error(1);
    }
}

//Esta funcion emite el listado de las propiedades segun el tipo de propiedad que elija el usuario.

void listarTipoProp()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    struct unidad u;
    FILE *Pa;
    Pa=fopen("propiedades.dat","rb");

    char tipoProp[20];
    int tProp=1, flagTprop=0;

    printf("\nOPCION 1: Casa\n");
    printf("OPCION 2: Departamento\n");
    printf("OPCION 3: PH\n");
    printf("OPCION 0: SALIR\n");

    while(tProp!=0)
    {
        tProp=4;
        amarillo();
        printf("\nElija el tipo de Propiedad:\n");
        blanco();
        scanf("%d",&tProp);
        fflush(stdin);

        switch(tProp)
        {
        case 1:
            strcpy(tipoProp,"Casa");
            tProp=0;
            flagTprop=1;
            break;
        case 2 :
            strcpy(tipoProp,"Departamento");
            tProp=0;
            flagTprop=1;
            break;
        case 3 :
            strcpy(tipoProp,"PH");
            tProp=0;
            flagTprop=1;
            break;
        case 0:
            break;
        default:
            error(2);
            break;
        }

    }

    if (Pa != NULL)
    {
        if(flagTprop==1)
        {
            printf("\n| Id | Fecha de Ingreso |         Zona         |        Ciudad        |Dormitorios|Banos|  Sup Cub  |  Sup Tot  |  Precio  |Moneda| Tipo de Prop |    Operacion    | Fecha de salida | Estado | \n");
            while (fread(&u, sizeof(struct unidad), 1, Pa) == 1)
            {
                if(strcmp(tipoProp, u.tipoProp)==0)
                {
                    printf("|%4d|    %2d/%2d/%4d    |%22s|%22s|%11d|%5d|%9.1fM2|%9.1fM2|%10.1f|%6s|%14s|%17s|   %2d/%2d/%4d    |%5d   |\n",
                           u.id,u.diaI,u.mesI,u.anioI,u.zona,u.ciudad,u.dormitorios,u.banios,u.supTotal,u.supCubierta,
                           u.precio,u.moneda,u.tipoProp,u.operacion,u.diaS,u.mesS,u.anioS,u.estado);
                };
            }
            fclose(Pa);
        }
    }
    else
    {
        error(1);
    }
}

//Funcion que emite el menu de opciones del listado de propiedades.

void listarArchivo()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int opcionMenu=1;

    while(opcionMenu!=0)
    {
        opcionMenu=5;
        azul();
        printf("\n MENU PRINCIPAL / OPCIONES DE LISTADO DE PROPIEDADES\n\n");
        blanco();

        printf("OPCION 1: Todas las propiedades.\n");
        printf("OPCION 2: Todas las propiedades activas.\n");
        printf("OPCION 3: Por tipo de propiedad.\n");
        printf("OPCION 4: Por rango de tiempo de fecha de ingreso.\n");
        gris();
        printf("OPCION 0: SALIR\n");


        amarillo();
        printf("\nIngrese la opcion que desea acceder:\n");
        blanco();

        scanf("%d",&opcionMenu);
        fflush(stdin);

        switch( opcionMenu )
        {
        case 0:
            break;
        case 1:
            listarTodo();
            break;
        case 2:
            listarActivo();
            break;
        case 3:
            listarTipoProp();
            break;
        case 4:
            listarRangoTiempo();
            break;
        default:
            error(2);
            break;
        }
    }
}

// Funcion que sirve para dar de alta a las propiedades nuevas. Las agrega poniendolas al final del archivo.

void altaInmueble(FILE *Pa)
{
    char nom[20]="propiedades.dat";
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    struct unidad u;
    setlocale(LC_ALL, "");
    Pa = fopen(nom, "rb+");// Abre el archivo en modo lectura/escritura

    char opcion,acept,importeStr[50],anioIStr[50],mesIStr[50],diaIStr[50],anioSStr[50],mesSStr[50],diaSStr[50],cantCuotasStr[50], dormitorioStr[50], banoStr[50], SupTotalStr[50],SupCubStr[50];

    int flagOrden=0,orden,i,flagZona=0,flagCiud=0,valid,flagImp=0,flagOpc=0,flagAnioI=0,flagMesI=0,flagDiaI=0, flagAnioS=0,flagMesS=0,flagDiaS=0, flagCantCuotas=0, flagGen=0, flagDormitorios=0, flagBano=0, flagSupTotal=0, flagSupCub=0, flagMon=0, flagTipoProp=0, flagOperacion=0, flagFechaS=0;
    int lastOrden = 0; // Variable para almacenar el último número de orden existente.
    int posicion=0; //Variable que almacena el numero que hay en el numero de orden que se ingresa

    if(Pa!=NULL)
    {
        printf("Alta inmueble:\n");

        // Obtengo el último número de orden existente
        FILE *pLectura = fopen(nom, "rb"); //Abre el archivo en modo lectura
        if (Pa != NULL)
        {
            while (fread(&u, sizeof(struct unidad), 1, pLectura) == 1)
            {
                if (u.id > lastOrden)
                {
                    lastOrden = u.id;
                }
            }

            fclose(pLectura);
        }

        while (flagOrden <= 0)
        {
            orden = 0;
            posicion = 0;
            flagOrden = 1;
            printf("\nIngresa N° de orden:\n");
            scanf("%d", &orden);
            fflush(stdin);

            if (orden <= 0)
            {
                error(3);
                flagOrden = 0;
            }

            FILE *pLectura = fopen(nom, "rb");//Abre el archivo en modo lectura
            if (Pa != NULL)
            {
                for(int i=1; i <= orden; i++)
                {
                    fread(&u, sizeof(struct unidad), 1, pLectura);
                    posicion=u.id;
                }
                fclose(pLectura);
            }

            fseek(Pa, (orden - 1) * sizeof(struct unidad), SEEK_SET);

            if (fread(&u, sizeof(struct unidad), 1, Pa) == 1 && u.id == orden)
            {

                if (posicion == orden)
                {
                    error(4);
                    flagOrden = 0;  // Requiere que se ingrese un nuevo 'id'.
                }
            }

            if (flagOrden == 1 && orden > 0)
            {
                // Rellenar las filas intermedias con ceros
                for (i = lastOrden + 1; i < orden ; i++)
                {
                    memset(&u, 0, sizeof(struct unidad));
                    fwrite(&u, sizeof(struct unidad), 1, Pa);
                }
                u.id = orden;
            }
        }

        printf("\nIngrese la fecha de ingreso:\n");

        while(flagAnioI<=0)
        {
            printf("\nAnio: ");
            fgets(anioIStr, sizeof(anioIStr), stdin);
            fflush(stdin);
            int anioActual = 0;

            time_t now = time(NULL);
            if (now != -1)
            {
                struct tm *tm = localtime(&now);
                anioActual = tm->tm_year + 1900; // Obtengo el año actual
            }
            else
            {
                error(5);
            }

            // Elimina el salto de línea al final de la cadena
            if (strlen(anioIStr) > 0 && anioIStr[strlen(anioIStr) - 1] == '\n')
            {
                anioIStr[strlen(anioIStr) - 1] = '\0';
            }

            // Verifica si la cadena contiene solo dígitos
            if (strspn(anioIStr, "0123456789") == strlen(anioIStr))
            {
                int anio = atoi(anioIStr);

                if (anio <= anioActual)
                {
                    flagAnioI = 1;
                    u.anioI = anio;
                }
                else
                {
                    error(6);
                }
            }
            else
            {
                error(3);
            }

        }

        while(flagMesI<=0)
        {
            printf("\nMes: ");
            fgets(mesIStr, sizeof(mesIStr), stdin);
            fflush(stdin);

            int mesActual=0, anioActual=0;

            time_t now = time(NULL);
            if (now != -1)
            {
                struct tm *tm = localtime(&now);
                anioActual = tm->tm_year + 1900; // Año actual
                mesActual = tm->tm_mon + 1; // Obtengo el mes actual
            }
            else
            {
                error(5);
            }


            // Elimina el salto de línea al final de la cadena
            if (strlen(mesIStr) > 0 && mesIStr[strlen(mesIStr) - 1] == '\n')
            {
                mesIStr[strlen(mesIStr) - 1] = '\0';
            }

            // Verifica si la cadena contiene solo dígitos
            if (strspn(mesIStr, "0123456789") == strlen(mesIStr))
            {
                int mes = atoi(mesIStr);

                if (u.anioI < anioActual || (u.anioI == anioActual && mes <= mesActual))
                {

                    if (mes >= 1 && mes <= 12)
                    {
                        flagMesI = 1;
                        u.mesI = mes;
                    }
                    else
                    {
                        error(7);
                    }
                }
                else
                {
                    error(8);
                }
            }
            else
            {
                error(3);
            }

        }

        while(flagDiaI<=0)
        {
            printf("\nDia: ");
            fgets(diaIStr, sizeof(diaIStr), stdin);
            fflush(stdin);

            int cantDiaMeses[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
            int diaActual=0,mesActual=0, anioActual=0;

            time_t now = time(NULL);
            if (now != -1)
            {
                struct tm *tm = localtime(&now);
                anioActual = tm->tm_year + 1900; // Año actual
                mesActual = tm->tm_mon + 1; //      Mes actual
                diaActual = tm->tm_mday;        // Día actual
            }
            else
            {
                error(5);
            }

            // Elimina el salto de línea al final de la cadena
            if (strlen(diaIStr) > 0 && diaIStr[strlen(diaIStr) - 1] == '\n')
            {
                diaIStr[strlen(diaIStr) - 1] = '\0';
            }

            // Verifica si la cadena contiene solo dígitos
            if (strspn(diaIStr, "0123456789") == strlen(diaIStr))
            {
                int dia = atoi(diaIStr);

                if (u.anioI< anioActual || (u.anioI == anioActual && u.mesI < mesActual) || (u.mesI == mesActual && dia <= diaActual))
                {

                    if (dia >= 1 && dia <= cantDiaMeses[u.mesI-1])
                    {
                        flagDiaI = 1;
                        u.diaI = dia;
                    }
                    else
                    {
                        rojo();
                        printf("\nError: EL DIA INGRESADO DEBE SER MAYOR O IGUAL A 1 Y MENOR O IGUAL A %d.\n\n",cantDiaMeses[u.mesI-1]);
                        blanco();

                    }
                }
                else
                {
                    error(9);
                }
            }
            else
            {
                error(3);
            }

        }

        while(flagZona<=0)
        {
            printf("\nIngresa zona :\n");
            gets(u.zona);
            fflush(stdin);

            // Eliminar el salto de línea al final de la palabra
            u.zona[strcspn(u.zona, "\n")] = '\0';

            if(u.zona[0] != ' ' && u.zona[0] != '\0')
            {
                valid=1;
            }
            else
            {
                error(10);
                valid = 0;
            }

            if (valid)
            {
                flagZona = 1;

                // Convertir en mayusculas la primer letra de la palabra.
                for (int i = 0; u.zona[i]; i++)
                {
                    if(u.zona[i]==' ')
                    {
                        u.zona[i+1] = toupper(u.zona[i+1]);
                    }
                }
                u.zona[0] = toupper(u.zona[0]);
            }
            else
            {

                flagZona = 0;
            }
        }

        while(flagCiud<=0)
        {
            printf("\nIngresa ciudad:\n");
            gets(u.ciudad);
            fflush(stdin);

            // Elimina el salto de línea al final de la palabra
            u.ciudad[strcspn(u.ciudad, "\n")] = '\0';

            if(u.ciudad[0] != ' ' && u.ciudad[0] != '\0')
            {
                valid=1;
            }
            else
            {
                error(11);
                valid = 0;
            }

            if (valid)
            {
                flagCiud = 1;

                // Convertir en mayusculas la primer letra de la palabra.
                for (int i = 0; u.ciudad[i]; i++)
                {
                    if(u.ciudad[i]==' ')
                    {
                        u.ciudad[i+1] = toupper(u.ciudad[i+1]);
                    }
                }
                u.ciudad[0] = toupper(u.ciudad[0]);
            }
            else
            {

                flagCiud = 0;
            }
        }

        while (flagDormitorios <= 0)
        {
            printf("\nIngrese la cantidad de dormitorios:\n");
            fgets(dormitorioStr, sizeof(dormitorioStr), stdin);
            fflush(stdin);

            // Elimina el salto de línea al final de la cadena
            if (strlen(dormitorioStr) > 0 && dormitorioStr[strlen(dormitorioStr) - 1] == '\n')
            {
                dormitorioStr[strlen(dormitorioStr) - 1] = '\0';
            }

            // Verifica si la cadena contiene solo dígitos
            if (strspn(dormitorioStr, "0123456789,") == strlen(dormitorioStr))
            {
                int dormitorios = atoi(dormitorioStr);

                if (dormitorios > 0)
                {
                    flagDormitorios = 1;
                    u.dormitorios = dormitorios;
                }
                else
                {
                    error(12);
                }
            }
            else
            {
                error(3);
            }
        }

        while (flagBano <= 0)
        {
            printf("\nIngrese la cantidad de banos:\n");
            fgets(banoStr, sizeof(banoStr), stdin);
            fflush(stdin);

            // Elimina el salto de línea al final de la cadena
            if (strlen(banoStr) > 0 && banoStr[strlen(banoStr) - 1] == '\n')
            {
                banoStr[strlen(banoStr) - 1] = '\0';
            }

            // Verifica si la cadena contiene solo dígitos
            if (strspn(banoStr, "0123456789,") == strlen(banoStr))
            {
                int banos = atoi(banoStr);

                if (banos > 0)
                {
                    flagBano = 1;
                    u.banios = banos;
                }
                else
                {
                    error(13);
                }
            }
            else
            {
                error(3);
            }
        }

        while (flagSupTotal <= 0)
        {
            printf("\nIngrese los m2 de la superficie total:\n");
            fgets(SupTotalStr, sizeof(SupTotalStr), stdin);
            fflush(stdin);

            // Elimina el salto de línea al final de la cadena
            if (strlen(SupTotalStr) > 0 && SupTotalStr[strlen(SupTotalStr) - 1] == '\n')
            {
                SupTotalStr[strlen(SupTotalStr) - 1] = '\0';
            }

            // Verifica si la cadena contiene solo dígitos
            if (strspn(SupTotalStr, "0123456789,") == strlen(SupTotalStr))
            {
                float supTotal = atof(SupTotalStr);

                if (supTotal > 0)
                {
                    flagSupTotal = 1;
                    u.supTotal = supTotal;
                }
                else
                {
                    error(14);
                }
            }
            else
            {
                error(3);
            }
        }

        while (flagSupCub <= 0 )
        {
            printf("\nIngrese los m2 de la superficie cubierta:\n");
            fgets(SupCubStr, sizeof(SupCubStr), stdin);
            fflush(stdin);

            // Elimina el salto de línea al final de la cadena
            if (strlen(SupCubStr) > 0 && SupCubStr[strlen(SupCubStr) - 1] == '\n')
            {
                SupCubStr[strlen(SupCubStr) - 1] = '\0';
            }

            // Verifica si la cadena contiene solo dígitos
            if (strspn(SupCubStr, "0123456789,") == strlen(SupCubStr))
            {
                float supCub = atof(SupCubStr);

                if (supCub > 0)
                {
                    flagSupCub = 1;
                    u.supCubierta = supCub;
                }
                else
                {
                    error(14);
                }
                if (supCub <= atof(SupTotalStr))
                {
                    u.supCubierta = supCub;
                }
                else
                {
                    flagSupCub=0;
                    error(15);
                }
            }
            else
            {
                error(3);
            }
        }

        while (flagImp <= 0)
        {
            printf("\nIngresa Precio:\n");
            fgets(importeStr, sizeof(importeStr), stdin);
            fflush(stdin);

            // Elimina el salto de línea al final de la cadena
            if (strlen(importeStr) > 0 && importeStr[strlen(importeStr) - 1] == '\n')
            {
                importeStr[strlen(importeStr) - 1] = '\0';
            }

            // Verifica si la cadena contiene solo dígitos
            if (strspn(importeStr, "0123456789,") == strlen(importeStr))
            {
                float importe = atof(importeStr);

                if (importe > 0)
                {
                    flagImp = 1;
                    u.precio = importe;
                }
                else
                {
                    error(16);
                }
            }
            else
            {
                error(17);
            }
        }


        while(flagMon<=0)
        {
            printf("\nTipo de moneda\n\n");
            printf("Opcion A: Pesos\n");
            printf("Opcion B: USD\n");
            printf("\nIngrese la opcion que corresponda:\n");
            scanf("%c", &opcion);
            fflush(stdin);

            if(opcion=='a' || opcion=='A' || opcion=='b' || opcion=='B')
            {
                flagMon=1;
            }
            else
            {
                error(2);
            }
        }

        switch(opcion)
        {
        case 'a':
        case 'A':
            strcpy(u.moneda,"PESOS");
            break;
        case 'b':
        case 'B':
            strcpy(u.moneda,"USD");
            break;
        }

        while(flagTipoProp<=0)
        {
            printf("\nTipo de propiedad\n\n");
            printf("Opcion A: Casa\n");
            printf("Opcion B: Departamento\n");
            printf("Opcion C: PH\n");
            printf("\nIngrese la opcion que corresponda:\n");
            scanf("%c", &opcion);
            fflush(stdin);

            if(opcion=='a' || opcion=='A' || opcion=='b' || opcion=='B' || opcion=='c' || opcion=='C')
            {
                flagTipoProp=1;
            }
            else
            {
                error(2);
            }
        }

        switch(opcion)
        {
        case 'a':
        case 'A':
            strcpy(u.tipoProp,"Casa");
            break;
        case 'b':
        case 'B':
            strcpy(u.tipoProp,"Departamento");
            break;
        case 'c':
        case 'C':
            strcpy(u.tipoProp,"PH");
            break;
        }

        while(flagOperacion<=0)
        {
            printf("\nTipo de Operacion\n\n");
            printf("Opcion A: Venta\n");
            printf("Opcion B: Alquiler\n");
            printf("Opcion C: Alquiler Temporal\n");
            printf("\nIngrese la opcion que corresponda:\n");
            scanf("%c", &opcion);
            fflush(stdin);

            if(opcion=='a' || opcion=='A' || opcion=='b' || opcion=='B' || opcion=='c' || opcion=='C')
            {
                flagOperacion=1;
            }
            else
            {
                error(2);
            }
        }

        switch(opcion)
        {
        case 'a':
        case 'A':
            strcpy(u.operacion,"Venta");
            break;
        case 'b':
        case 'B':
            strcpy(u.operacion,"Alquiler");
            break;
        case 'c':
        case 'C':
            strcpy(u.operacion,"Alquiler Temporal");
            break;
        }

        while(flagFechaS<=0)
        {
            printf("\nDesea ingresar la fecha de salida de la propiedad?, ingrese s para 'si' o n para 'no':\n");
            scanf("%c", &acept);
            fflush(stdin);

            switch(acept)
            {
            case 's':
            case 'S':
                printf("\nIngrese la fecha de salida:\n");

                while(flagAnioS<=0)
                {
                    printf("\nAnio: ");
                    fgets(anioSStr, sizeof(anioSStr), stdin);
                    fflush(stdin);
                    int anioActual = 0;

                    time_t now = time(NULL);
                    if (now != -1)
                    {
                        struct tm *tm = localtime(&now);
                        anioActual = tm->tm_year + 1900; // Obtengo el año actual
                    }
                    else
                    {
                        error(5);
                    }

                    // Elimina el salto de línea al final de la cadena
                    if (strlen(anioSStr) > 0 && anioSStr[strlen(anioSStr) - 1] == '\n')
                    {
                        anioSStr[strlen(anioSStr) - 1] = '\0';
                    }

                    // Verifica si la cadena contiene solo dígitos
                    if (strspn(anioSStr, "0123456789") == strlen(anioSStr))
                    {
                        int anio = atoi(anioSStr);

                        if (anio <= anioActual)
                        {
                            flagAnioS = 1;
                            u.anioS = anio;
                        }
                        else
                        {
                            error(6);
                        }
                    }
                    else
                    {
                        error(3);
                    }

                }

                while(flagMesS<=0)
                {
                    printf("\nMes: ");
                    fgets(mesSStr, sizeof(mesSStr), stdin);
                    fflush(stdin);


                    // Elimina el salto de línea al final de la cadena
                    if (strlen(mesSStr) > 0 && mesSStr[strlen(mesSStr) - 1] == '\n')
                    {
                        mesSStr[strlen(mesSStr) - 1] = '\0';
                    }

                    // Verifica si la cadena contiene solo dígitos
                    if (strspn(mesSStr, "0123456789") == strlen(mesSStr))
                    {
                        int mes = atoi(mesSStr);

                        if (mes >= 1 && mes <= 12)
                        {
                            flagMesS = 1;
                            u.mesS = mes;
                        }
                        else
                        {
                            error(7);
                        }
                    }
                    else
                    {
                        error(3);
                    }

                }

                while(flagDiaS<=0)
                {
                    printf("\nDia: ");
                    fgets(diaSStr, sizeof(diaSStr), stdin);
                    fflush(stdin);

                    int cantDiaMeses[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

                    // Elimina el salto de línea al final de la cadena
                    if (strlen(diaSStr) > 0 && diaSStr[strlen(diaSStr) - 1] == '\n')
                    {
                        diaSStr[strlen(diaSStr) - 1] = '\0';
                    }

                    // Verifica si la cadena contiene solo dígitos
                    if (strspn(diaSStr, "0123456789") == strlen(diaSStr))
                    {
                        int dia = atoi(diaSStr);

                        if (dia >= 1 && dia <= cantDiaMeses[u.mesS-1])
                        {
                            flagDiaS = 1;
                            u.diaS = dia;
                        }
                        else
                        {
                            rojo();
                            printf("\nError: EL DIA INGRESADO DEBE SER MAYOR O IGUAL A 1 Y MENOR O IGUAL A %d.\n\n",cantDiaMeses[u.mesI-1]);
                            blanco();
                        }
                    }
                    else
                    {
                        error(3);
                    }

                }
                u.estado=0;
                flagFechaS=1;
                break;
            case 'n':
            case 'N':
                u.anioS=0;
                u.mesS=0;
                u.diaS=0;
                u.estado=1;
                flagFechaS=1;
                break;
            default:
                error(2);
                break;
            }
        }

        fseek(Pa, (orden - 1) * sizeof(struct unidad), SEEK_SET);
        fwrite(&u, sizeof(struct unidad), 1, Pa);
        fclose(Pa);
        verde();
        printf("\nALTA EXITOSA.\n");
        blanco();
    }

    else
    {
        error(1);
    }
}

//Funcion que se encarga de la busqueda de una propiedad por id o tipo de propiedad y operacion, segun la opcion que le pasemos.

void buscarInmueble(FILE *Pa)
{

    int opcion=1,flagError=0,flagOpcion=0,tipoOp=1,tProp=1,id;
    char operacion[20],tipoProp[20];
    struct unidad u;

    Pa=fopen("propiedades.dat","rb");

    azul();
    printf("\n MENU PRINCIPAL / OPCIONES DE BUSQUEDA\n\n");
    blanco();

    printf(" OPCION 1: Buscar por ID\n");
    printf(" OPCION 2: Buscar por Tipo de Propiedad y Operacion\n");
    gris();
    printf(" OPCION 0: Salir.\n\n");
    blanco();

    while(opcion!=0 && flagOpcion==0)
    {
        opcion=3;
        amarillo();
        printf("Elija la opcion deseada:\n");
        blanco();
        scanf("%d",&opcion);
        fflush(stdin);

        switch(opcion)
        {
        case 1:
            azul();
            printf("\n MENU PRINCIPAL / OPCIONES DE BUSQUEDA / ID\n\n");
            blanco();
            printf("Ingrese N de ID:\n");
            scanf("%d",&id);
            fflush(stdin);
            flagOpcion=1;
            break;
        case 2:
            azul();
            printf("\n MENU PRINCIPAL / OPCIONES DE BUSQUEDA / TIPO DE OPERACION\n\n");
            blanco();
            printf(" OPCION 1: Venta\n");
            printf(" OPCION 2: Alquiler\n");
            printf(" OPCION 3: Alquiler Temporal\n");
            gris();
            printf(" OPCION 0: Salir.\n\n");
            blanco();

            while(tipoOp!=0)
            {
                tipoOp=4;
                amarillo();
                printf("\nElija el tipo de Operacion:\n");
                blanco();
                scanf("%d",&tipoOp);
                fflush(stdin);

                switch(tipoOp)
                {
                case 1:
                    strcpy(operacion,"Venta");
                    tipoOp=0;
                    break;
                case 2 :
                    strcpy(operacion,"Alquiler");
                    tipoOp=0;
                    break;
                case 3 :
                    strcpy(operacion,"Alquiler Temporal");
                    tipoOp=0;
                    break;
                case 0:
                    opcion=0;
                    tProp=0;
                    break;
                default:
                    error(2);
                    break;
                }
            }

            if(tProp==1)
            {
                azul();
                printf("\n MENU PRINCIPAL / OPCIONES DE BUSQUEDA / TIPO DE OPERACION / TIPO DE PROPIEDAD\n\n");
                blanco();
                printf(" OPCION 1: Casa\n");
                printf(" OPCION 2: Departamento\n");
                printf(" OPCION 3: PH\n");
                gris();
                printf(" OPCION 0: Salir.\n\n");
                blanco();

                while(tProp!=0)
                {
                    tProp=4;
                    amarillo();
                    printf("\nElija el tipo de Propiedad:\n");
                    blanco();
                    scanf("%d",&tProp);
                    fflush(stdin);

                    switch(tProp)
                    {
                    case 1:
                        strcpy(tipoProp,"Casa");
                        tProp=0;
                        break;
                    case 2 :
                        strcpy(tipoProp,"Departamento");
                        tProp=0;
                        break;
                    case 3 :
                        strcpy(tipoProp,"PH");
                        tProp=0;
                        break;
                    case 0:
                        opcion=0;
                        break;
                    default:
                        error(2);
                        break;
                    }
                }
            }
            flagOpcion=1;
            break;
        case 0:
            break;
        default:
            error(2);
            break;
        }
    }

    if (Pa != NULL)
    {
        if(opcion!=0)
        {
            printf("\n| Id | Fecha de Ingreso |         Zona         |        Ciudad        |Dormitorios|Banos|  Sup Cub  |  Sup Tot  |  Precio  |Moneda| Tipo de Prop |    Operacion    | Fecha de salida | Estado | \n");

            while (fread(&u, sizeof(struct unidad), 1, Pa) == 1)
            {
                if(id == u.id && id != 0)
                {
                    printf("|%4d|    %2d/%2d/%4d    |%22s|%22s|%11d|%5d|%9.1fM2|%9.1fM2|%10.1f|%6s|%14s|%17s|   %2d/%2d/%4d    |%5d   |\n",
                           u.id,u.diaI,u.mesI,u.anioI,u.zona,u.ciudad,u.dormitorios,u.banios,u.supTotal,u.supCubierta,
                           u.precio,u.moneda,u.tipoProp,u.operacion,u.diaS,u.mesS,u.anioS,u.estado);
                    flagError=1;
                };

                if(strcmp(operacion, u.operacion)==0 && strcmp(tipoProp, u.tipoProp)==0 && tProp==0)
                {
                    printf("|%4d|    %2d/%2d/%4d    |%22s|%22s|%11d|%5d|%9.1fM2|%9.1fM2|%10.1f|%6s|%14s|%17s|   %2d/%2d/%4d    |%5d   |\n",
                           u.id,u.diaI,u.mesI,u.anioI,u.zona,u.ciudad,u.dormitorios,u.banios,u.supTotal,u.supCubierta,
                           u.precio,u.moneda,u.tipoProp,u.operacion,u.diaS,u.mesS,u.anioS,u.estado);
                    flagError=1;
                };
            }
            fclose(Pa);
        }
    }
    else
    {
        error(1); //En el caso que no se pueda abrir el archivo .dat emite un error.
    }

    //En caso de no encontrar el numero de id o tipo de propiedad y operacion emite error.
    if(flagError==0 && opcion!=0)
    {
        error(18);
    }

}

//Funcion para modificar los datos de una propiedad que buscaremos por numero de id.

void modificarInmueble(FILE *Pa)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    struct unidad u;
    Pa = fopen("propiedades.dat", "r+b"); //Lee y escribe el mismo archivo

    int id;
    char acept;
    char precioStr[50];
    int flagError=0;
    int flagCiudad=0;
    int flagPrecio=0;
    int flagAnioS=0, flagMesS=0, flagDiaS=0;
    char diaSStr[20];
    char mesSStr[20];
    char anioSStr[40];
    int valid=0;
    int opcion;
    int validOpcion=1;

    azul();
    printf("\n MENU PRINCIPAL / OPCIONES PARA MODIFICAR\n\n");
    blanco();

    printf(" OPCION 1: Precio de la propiedad.\n");
    printf(" OPCION 2: Ciudad o Barrio de la propiedad.\n");
    printf(" OPCION 3: Fecha de salida de la propiedad.\n");
    gris();
    printf(" OPCION 0: Salir.\n\n");
    blanco();


    while(validOpcion!=0)
    {
        opcion=4;
        printf("Elija la opcion que desea modificar:\n");
        scanf("%d",&opcion);
        fflush(stdin);
        if(opcion==1 || opcion==2 || opcion==3 || opcion==0)
        {
            validOpcion=0;
        }
        else
        {
            error(2);
        }
    }

    if(opcion !=0)
    {
        printf("\nIngrese el numero de id de la propiedad que desea modificar:\n");
        scanf("%d", &id);
        fflush(stdin);

        if (Pa != NULL)
        {
            while (fread(&u, sizeof(struct unidad), 1, Pa) == 1)
            {
                if(id == u.id && id != 0)
                {
                    printf("\n| Id | Fecha de Ingreso |         Zona         |        Ciudad        |Dormitorios|Banos|  Sup Cub  |  Sup Tot  |  Precio  |Moneda| Tipo de Prop |    Operacion    | Fecha de salida | Estado | \n");
                    printf("|%4d|    %2d/%2d/%4d    |%22s|%22s|%11d|%5d|%9.1fM2|%9.1fM2|%10.1f|%6s|%14s|%17s|   %2d/%2d/%4d    |%5d   |\n",
                           u.id,u.diaI,u.mesI,u.anioI,u.zona,u.ciudad,u.dormitorios,u.banios,u.supTotal,u.supCubierta,
                           u.precio,u.moneda,u.tipoProp,u.operacion,u.diaS,u.mesS,u.anioS,u.estado);

                    flagError=1;
                    break; // Salimos del bucle, ya que encontramos la propiedad que buscamos
                }
            }

            if(opcion==1 && flagError==1)
            {
                while (flagPrecio <= 0)
                {
                    printf("\nIngrese el precio que desea modificar de la propiedad:\n");
                    fgets(precioStr, sizeof(precioStr), stdin);
                    fflush(stdin);

                    // Elimina el salto de línea al final de la cadena
                    if (strlen(precioStr) > 0 && precioStr[strlen(precioStr) - 1] == '\n')
                    {
                        precioStr[strlen(precioStr) - 1] = '\0';
                    }

                    // Verifica si la cadena contiene solo dígitos
                    if (strspn(precioStr, "0123456789,") == strlen(precioStr))
                    {
                        float precio = atof(precioStr);

                        if (precio > 0)
                        {
                            flagPrecio = 1;
                            u.precio = precio;
                        }
                        else
                        {
                            error(16);
                        }
                    }
                    else
                    {
                        error(17);
                    }
                }
            };

            if(opcion==2 && flagError==1)
            {
                while(flagCiudad<=0)
                {
                    printf("\nIngresa la ciudad/barrio que deseas modificar:\n");
                    gets(u.ciudad);
                    fflush(stdin);

                    // Elimina el salto de línea al final de la palabra
                    u.ciudad[strcspn(u.ciudad, "\n")] = '\0';

                    if(u.ciudad[0] != ' ' && u.ciudad[0] != '\0')
                    {
                        valid=1;
                    }
                    else
                    {
                        error(19);
                        valid = 0;
                    }

                    if (valid)
                    {
                        flagCiudad = 1;

                        // Convertir en mayusculas la primer letra de la palabra.
                        for (int i = 0; u.ciudad[i]; i++)
                        {
                            if(u.ciudad[i]==' ')
                            {
                                u.ciudad[i+1] = toupper(u.ciudad[i+1]);
                            }
                        }
                        u.ciudad[0] = toupper(u.ciudad[0]);
                    }
                    else
                    {

                        flagCiudad = 0;
                    }
                }
            };

            if(opcion==3 && flagError==1)
            {
                printf("\nIngresa la nueva fecha de salida:\n");

                while(flagAnioS<=0)
                {
                    printf("\nAnio: ");
                    fgets(anioSStr, sizeof(anioSStr), stdin);
                    fflush(stdin);
                    int anioActual = 0;

                    time_t now = time(NULL);
                    if (now != -1)
                    {
                        struct tm *tm = localtime(&now);
                        anioActual = tm->tm_year + 1900; // Obtengo el año actual
                    }
                    else
                    {
                        error(5);
                    }

                    // Elimina el salto de línea al final de la cadena
                    if (strlen(anioSStr) > 0 && anioSStr[strlen(anioSStr) - 1] == '\n')
                    {
                        anioSStr[strlen(anioSStr) - 1] = '\0';
                    }

                    // Verifica si la cadena contiene solo dígitos
                    if (strspn(anioSStr, "0123456789") == strlen(anioSStr))
                    {
                        int anio = atoi(anioSStr);

                        if (anio <= anioActual)
                        {
                            flagAnioS = 1;
                            u.anioS = anio;
                        }
                        else
                        {
                            error(6);
                        }
                    }
                    else
                    {
                        error(3);
                    }

                }

                while(flagMesS<=0)
                {
                    printf("\nMes: ");
                    fgets(mesSStr, sizeof(mesSStr), stdin);
                    fflush(stdin);


                    // Elimina el salto de línea al final de la cadena
                    if (strlen(mesSStr) > 0 && mesSStr[strlen(mesSStr) - 1] == '\n')
                    {
                        mesSStr[strlen(mesSStr) - 1] = '\0';
                    }

                    // Verifica si la cadena contiene solo dígitos
                    if (strspn(mesSStr, "0123456789") == strlen(mesSStr))
                    {
                        int mes = atoi(mesSStr);

                        if (mes >= 1 && mes <= 12)
                        {
                            flagMesS = 1;
                            u.mesS = mes;
                        }
                        else
                        {
                            error(7);
                        }
                    }
                    else
                    {
                        error(3);
                    }

                }

                while(flagDiaS<=0)
                {
                    printf("\nDia: ");
                    fgets(diaSStr, sizeof(diaSStr), stdin);
                    fflush(stdin);

                    int cantDiaMeses[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

                    // Elimina el salto de línea al final de la cadena
                    if (strlen(diaSStr) > 0 && diaSStr[strlen(diaSStr) - 1] == '\n')
                    {
                        diaSStr[strlen(diaSStr) - 1] = '\0';
                    }

                    // Verifica si la cadena contiene solo dígitos
                    if (strspn(diaSStr, "0123456789") == strlen(diaSStr))
                    {
                        int dia = atoi(diaSStr);

                        if (dia >= 1 && dia <= cantDiaMeses[u.mesS-1])
                        {
                            flagDiaS = 1;
                            u.diaS = dia;
                        }
                        else
                        {
                            rojo();
                            printf("\nError: EL DIA INGRESADO DEBE SER MAYOR O IGUAL A 1 Y MENOR O IGUAL A %d.\n\n",cantDiaMeses[u.mesI-1]);
                            blanco();
                        }
                    }
                    else
                    {
                        error(3);
                    }

                }
                u.estado=0; //Pongo el estado en 0 ya que se esta ingresando una fecha de salida.
            }

            if(flagError==1)
            {
                printf("\nEsta seguro que desea modificar la Fecha?, ingrese S para 'si' o N para 'no':\n");
                scanf("%c", &acept);
                fflush(stdin);

                switch(acept)
                {
                case 's':
                case 'S':
                    fseek(Pa, -( int)sizeof(struct unidad), SEEK_CUR);//funcion que busca una posicion determinada del archivo segun los parametros que se le pasen.
                    fwrite(&u,sizeof(struct unidad),1,Pa);      //Funcion que escribe en formato que le indiquemos en el archivo.
                    verde();
                    if(opcion==1)
                    {
                        printf("\nEL PRECIO FUE MODIFICADO EXITOSAMENTE.\n\n");
                    };
                    if(opcion==2)
                    {
                        printf("\nLA CIUDAD/BARRIO FUE MODIFICADO EXITOSAMENTE.\n\n");
                    };
                    if(opcion==3)
                    {
                        printf("\n LA FECHA FUE MODIFICADA EXITOSAMENTE.\n\n");
                    };
                    blanco();
                    break;
                case 'n':
                case 'N':
                    rojo();
                    printf("\nOPERACION CANCELADA.\n\n");
                    blanco();
                    break;
                default:
                    error(20);
                    break;
                }
            }
        }
    }
    fclose(Pa);

    //En caso de no encontrar el numero de id emite un error.
    if(flagError ==0 && opcion !=0)
    {
        error(18);
    }
}

/*Funcion que hace la baja logica de la propiedad pasando el campo estado=1 a estado=0. Una vez que se acepta la baja, se invoqca la funcion listarActivo(), que muestra
  por pantalla solamente los que tengan el campo estado=1.*/

void bajaLogica(FILE *Pa)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    struct unidad u;
    Pa = fopen("propiedades.dat", "r+b"); //Lee y escribe el mismo archivo
    int orden;
    char acept;
    int flagError=0;


    printf("\nIngrese el numero de id de la propiedad que desea borrar:\n");
    scanf("%d", &orden);
    fflush(stdin);

    if (Pa != NULL)
    {
        while (fread(&u, sizeof(struct unidad), 1, Pa) == 1)
        {
            if(orden == u.id && orden != 0)
            {
                if(u.diaS == 0)
                {
                    printf("\n| Id | Fecha de Ingreso |         Zona         |        Ciudad        |Dormitorios|Banos|  Sup Cub  |  Sup Tot  |  Precio  |Moneda| Tipo de Prop |    Operacion    | Fecha de salida | Estado | \n");
                    printf("|%4d|    %2d/%2d/%4d    |%22s|%22s|%11d|%5d|%9.1fM2|%9.1fM2|%10.1f|%6s|%14s|%17s|   %2d/%2d/%4d    |%5d   |\n",
                           u.id,u.diaI,u.mesI,u.anioI,u.zona,u.ciudad,u.dormitorios,u.banios,u.supTotal,u.supCubierta,
                           u.precio,u.moneda,u.tipoProp,u.operacion,u.diaS,u.mesS,u.anioS,u.estado);

                    flagError=1;
                    break; // Salimos del bucle, ya que encontramos el préstamo que buscamos
                }
                else
                {
                    flagError=2;
                }
            }
        }
        if(flagError==1)
        {
            u.estado=0;

            printf("\nEsta seguro que desea borrar la propiedad de %s ?, ingrese s para 'si' o n para 'no':\n", u.ciudad);
            scanf("%c", &acept);
            fflush(stdin);

            switch(acept)
            {
            case 's':
            case 'S':
                fseek(Pa, -(long int)sizeof(struct unidad), SEEK_CUR);//funcion que busca una posicion determinada del archivo segun los parametros que se le pasen.
                fwrite(&u,sizeof(struct unidad),1,Pa);      //Funcion que escribe en formato que le indiquemos en el archivo.
                verde();
                printf("\nLA PROPIEDAD FUE ELIMINADA EXITOSAMENTE.\n\n");
                blanco();

                break;
            case 'n':
            case 'N':
                rojo();
                printf("\nOPERACION CANCELADA.\n\n");
                blanco();
                break;
            default:
                error(21);
                break;
            }
        }
        fclose(Pa);
    }
    //En caso de no encontrar el numero de orden emite un error.
    if(flagError==0)
    {
        error(18);
    }
    if(flagError==2)
    {
        verde();
        printf("\nESTA PROPIEDAD YA FUE DADA DE BAJA.\n");
        blanco();
    }

    if(acept == 's' || acept == 'S')
    {
        printf("\nLISTADO DE PROPIEDADES ACTIVAS\n");// Emite la lista de las propiedades activas, una vez que fue borrada exitosamente.
        listarActivo();
    }
}

/*Funcion que hace la baja fisica de la propiedad, poniendo la fila del cliente seleccionado en "0" en el archivo original y crea el archivo.xyz poniendo como nombre
 la fecha actual de cuando se crea el archivo. En este archivo se guarda la info de la propiedad dada de baja y se usa un contador para que se creen archivos
uno despues del otro aunque se haya cerrado y abierto sesion.*/

void bajaFisica(FILE *Pa)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    struct unidad u;
    char acept;

    Pa = fopen("propiedades.dat","rb+");
    if (Pa == NULL)
    {
        error(0);
        return;
    }

    printf("\nEsta seguro que desea hacer la eliminacion definitiva de las propiedades?, ingrese s para 'si' o n para 'no':\n");
    scanf("%c", &acept);
    fflush(stdin);

    if(acept=='s' || acept=='S')
    {

// Obtener la fecha actual
        time_t rawtime;
        struct tm *timeinfo;
        char fecha[20];
        time(&rawtime);
        timeinfo = localtime(&rawtime);
        strftime(fecha, sizeof(fecha), "%d-%m-%Y", timeinfo);

        // Leer el valor del contador desde el archivo
        int contadorArchivos = 0;
        FILE *contadorArchivo = fopen("contador.txt", "r");
        if (contadorArchivo != NULL)
        {
            fscanf(contadorArchivo, "%d", &contadorArchivos);
            fclose(contadorArchivo);
        }

        // Construir el nombre del archivo
        char nombre[50];
        sprintf(nombre, "propiedades_bajas_%s_%d.xyz", fecha, contadorArchivos);

        FILE* xyz = fopen(nombre, "wb");
        if (xyz == NULL)
        {
            error(22);
            fclose(xyz);
            return;
        }

        while (fread(&u, sizeof(struct unidad), 1, Pa) == 1)
        {
            if (u.estado == 0)
            {

                // Escribir los datos en el archivo "clientes_bajas_<fecha>.xyz"
                fwrite(&u, sizeof(struct unidad), 1, xyz);

                // Poner toda la fila en 0 en el archivo original
                long int currentPosition = ftell(Pa);
                fseek(Pa, currentPosition - sizeof(struct unidad), SEEK_SET);
                memset(&u, 0, sizeof(struct unidad));
                fwrite(&u, sizeof(struct unidad), 1, Pa);

                // Restaurar la posición del puntero de archivo después de la escritura
                fseek(Pa, currentPosition, SEEK_SET);
            }
        }

        fclose(xyz);

        // Incrementa el contador de archivos
        contadorArchivos++;

        // Guardar el nuevo valor del contador en el archivo
        contadorArchivo = fopen("contador.txt", "w");
        if (contadorArchivo != NULL)
        {
            fprintf(contadorArchivo, "%d", contadorArchivos);
            fclose(contadorArchivo);
        }

        verde();
        printf("\nEL ARCHIVO DE BAJA DE PROPIEDADES SE HA CREADO EXITOSAMENTE.\n");
        blanco();
    }
    else if(acept=='n' || acept=='N')
    {
        rojo();
        printf("\nOPERACION CANCELADA.\n\n");
        blanco();
    }
    else
    {
        error(21);
    }

    fclose(Pa);
}


#endif //_operaciones_H_
