/*
    Daniel Rios Rodriguez 372800
    25-nov-23

    ACTIVIDAD 14
    Archivos Binarios (archivos indexados)
    programa que tiene un menu donde te permite agregar o eliminar registros, se hace uso de archivos binarios y de texto.
    DRR_act14_1_932
*/

#include <stdbool.h>
#include "DR.h"
#define N_AUTO 1

int menu(void);
void Leer_Nom_Archivo(char nomArchivo[]);
TWrkr Datos_Random(void);
void ImpArchivoBin(Tindice indice[], int n, int ordenado);
void ImprimirReg(TWrkr pers);
void AgregarReg(Tindice indice[], int *n, int *ordenado);
void EliminarReg(Tindice indice[], int *n, int ordenado);
void BuscarReg(Tindice indice[], int n, int ordenado);
void ordenarReg(Tindice indice[], int n, int *ordenado);
void Archivo_Texto(char nomArchivo[], Tindice vect[], int n, int ordenado);
void empaquetar(Tindice indice[], int *n);
bool cargarIndice(Tindice vect[], int *n);
int contarRegArch(char nomArchivo[]);

int main()
{
    srand(time(NULL));
    int op;
    int Num_Personas = 0;
    int ordenado = 0;
    char nomArchivo[15];

    int N = contarRegArch("datos");
    N *= 1.25;

    Tindice indice[N];
    cargarIndice(indice, &Num_Personas);

    system("CLS");
    do
    {
        op = menu();

        switch (op)
        {
        case 1:
            AgregarReg(indice, &Num_Personas, &ordenado);
            break;

        case 2:
            EliminarReg(indice, &Num_Personas, ordenado);
            break;
        case 3:
            BuscarReg(indice, Num_Personas, ordenado);
            break;
        case 4:
            ordenarReg(indice, Num_Personas, &ordenado);
            break;
        case 5:
            ImpArchivoBin(indice, Num_Personas, 0);
            break;
        case 6:
            ImpArchivoBin(indice, Num_Personas, 1);
            break;
        case 7:

            Leer_Nom_Archivo(nomArchivo);

            if (validarnumeros("1 - Archivo\n2 - Indice\n\nElija una opcion: ", 1, 2) == 1)
            {
                Archivo_Texto(nomArchivo, indice, Num_Personas, 0);
            }
            else
            {
                Archivo_Texto(nomArchivo, indice, Num_Personas, 1);
            }
            break;
        case 8:
            empaquetar(indice, &Num_Personas);
            break;
        }

        printf("\n");
    } while (op != 9);

    return 0;
}

int menu()
{
    int op;
    printf("\n   ---MENU--- \n");
    printf("1.- AGREGAR REGISTRO \n");
    printf("2.- ELIMINAR REGISTRO \n");
    printf("3.- BUSCAR REGISTRO \n");
    printf("4.- ORDENAR INDICE \n");
    printf("5.- IMPRIMIR ARCHIVO \n");
    printf("6.- IMPRIMIR INDICE \n");
    printf("7.- GENERAR ARCHIVO TEXTO \n");
    printf("8.- EMPAQUETAR \n");
    printf("9.- SALIR  \n");
    op = validarnumeros("ESCOGE UNA OPCION:\t", 1, 9);
    return op;
}

TWrkr Datos_Random(void)
{
    TWrkr pers;
    int sexo;

    pers.status = 1;
    pers.enrollment = matriAlea();
    pers.cellphone = numTelAlea();

    genEdo(pers.state);
    genAp(pers.LastName1);
    genAp(pers.LastName2);
    genPuesto(pers.JobPstion);

    sexo = numAleatorio(1, 2);
    pers.age = numAleatorio(18, 31);

    if (sexo == 1)
    {
        genNomH(pers.name);
        strcpy(pers.sex, "HOMBRE");
    }
    else
    {
        genNomM(pers.name);
        strcpy(pers.sex, "MUJER");
    }

    return pers;
}

void ImpArchivoBin(Tindice indice[], int n, int ordenado)
{
    int i, activos, op;

    FILE *fa;
    TWrkr reg;
    fa = fopen("datos.dat", "rb");

    printf("Registros 1 - 40\n");
    printf("------------------------------------------------------------------------------------------------------------------------------\n");
    printf("  No  | MATRICULA | TELEFONO   | ESTADO | PUESTO         | NOMBRE        | APELLIDO P.  |  APELLIDO MAT.     | EDAD  | SEXO \n");
    printf("------------------------------------------------------------------------------------------------------------------------------\n");
    for (i = 0, activos = 1; i < n; i++)
    {
        if (ordenado == 1)
        {
            fseek(fa, indice[i].indice * sizeof(TWrkr), SEEK_SET);
        }
        else
        {
            fseek(fa, i * sizeof(TWrkr), SEEK_SET);
        }

        fread(&reg, sizeof(TWrkr), 1, fa);

        if (reg.status == 1)
        {
            printf("%4d.-  %6d      %-7d      %-2s       %-11s      %-10s      %-10s      %-10s          %2d      %-7s\n", activos - 1, reg.enrollment, reg.cellphone, reg.state, reg.JobPstion, reg.name, reg.LastName1, reg.LastName2, reg.age, reg.sex);
            activos++;
        }

        if (activos % 41 == 0 && activos < n)
        {
            printf("\n\n");
            op = validarnumeros("Desea continuar? \n1. Si\n2. No ", 1, 2);

            if (op == 0)
            {
                system("CLS");
                printf("Registros %d - %d\n", activos + 1, (activos + 40) > n ? n : (activos + 40));
                printf("------------------------------------------------------------------------------------------------------------------------------\n");
                printf("  No  | MATRICULA | TELEFONO   | ESTADO | PUESTO         | NOMBRE        | APELLIDO P.  |  APELLIDO MAT.     | EDAD  | SEXO \n");
                printf("------------------------------------------------------------------------------------------------------------------------------\n");
            }
            else
            {
                fclose(fa);
                return;
            }
        }
    }

    fclose(fa);
}


void ImprimirReg(TWrkr pers)
{
    printf("STATUS: ");
    printf("%s\n", pers.status == 1 ? "ACTIVO" : "NO ACTIVO");
    printf("MATRICULA: ");
    printf("%d\n", pers.enrollment);
    printf("TELEFONO: ");
    printf("%d\n", pers.cellphone);
    printf("ESTADO: ");
    printf("%s\n", pers.state);
    printf("PUESTO: ");
    printf("%s\n", pers.JobPstion);
    printf("NOMBRE: ");
    printf("%s\n", pers.name);
    printf("AP. PATERNO: ");
    printf("%s\n", pers.LastName1);
    printf("AP. MATERNO: ");
    printf("%s\n", pers.LastName2);
    printf("EDAD: ");
    printf("%d\n", pers.age);
    printf("SEXO: ");
    printf("%s\n", pers.sex);
}

// Lee el nombre de un archivo de texto especificado.
void Leer_Nom_Archivo(char nomArchivo[])
{
    do
    {
        system("CLS");
        printf("Ingresa el nombre del archivo (sin extension): ");
        fflush(stdin);
        gets(nomArchivo);
    } while (strcmp(nomArchivo, "\n") == 0);
}

void Archivo_Texto(char nomArchivo[], Tindice indice[], int n, int ordenado)
{
    int i, cont = 0;
    TWrkr reg;

    FILE *fa;
    FILE *fb;

    char temp[30];
    strcpy(temp, nomArchivo);
    strcat(temp, ".txt");

    fa = fopen(temp, "w");
    fb = fopen("datos.dat", "rb");

    fprintf(fa, "------------------------------------------------------------------------------------------------------------------------------\n");
    fprintf(fa, "  No  | MATRICULA | TELEFONO   | ESTADO | PUESTO         | NOMBRE        | APELLIDO P.  |  APELLIDO MAT.     | EDAD  | SEXO \n");
    fprintf(fa, "------------------------------------------------------------------------------------------------------------------------------\n");

    for (i = 0, cont = 1; i < n; i++)
    {
        if (ordenado == 1)
        {
            fseek(fb, indice[i].indice * sizeof(TWrkr), SEEK_SET);
        }
        else
        {
            fseek(fb, i * sizeof(TWrkr), SEEK_SET);
        }

        fread(&reg, sizeof(TWrkr), 1, fb);

        if (reg.status == 1)
        {
            fprintf(fa, "%4d.-  %6d      %-7d      %-2s       %-11s      %-10s      %-10s      %-10s          %2d      %-7s\n", cont - 1, reg.enrollment, reg.cellphone, reg.state, reg.JobPstion, reg.name, reg.LastName1, reg.LastName2, reg.age, reg.sex);
            cont++;
        }
    }

    fclose(fa);
    fclose(fb);
}

void empaquetar(Tindice indice[], int *n)
{
    TWrkr reg;
    FILE *fa;
    FILE *fb;

    rename("datos.dat", "datos.bak");

    fa = fopen("datos.dat", "wb");
    fb = fopen("datos.bak", "rb");

    while (fread(&reg, sizeof(TWrkr), 1, fb) == 1)
    {
        if (reg.status == 1)
        {
            fwrite(&reg, sizeof(TWrkr), 1, fa);
        }
    }

    fclose(fa);
    fclose(fb);

    *n = 0;
    cargarIndice(indice, n);

    printf("Archivo empaquetado con exito\n");
}

bool cargarIndice(Tindice indice[], int *n)
{
    FILE *fa;
    TWrkr reg;

    fa = fopen("datos.dat", "rb");

    if (fa)
    {
        while (fread(&reg, sizeof(TWrkr), 1, fa) == 1)
        {
            indice[*n].key = reg.enrollment;
            indice[*n].indice = *n;
            (*n)++;
        }

        fclose(fa);
        return true;
    }

    return false;
}

int contarRegArch(char nomArchivo[])
{
    int cont;
    char fileName[50];
    char cmd[50];

    system("gcc Tamano_Archivo.c -o Tamano_Archivo");
    sprintf(cmd, "Tamano_Archivo.exe %s", nomArchivo);
    cont = system(cmd);

    return cont;
}

void AgregarReg(Tindice indice[], int *n, int *ordenado)
{
    TWrkr reg;
    FILE *fa;

    reg =Datos_Random();

    while (busqOpt(indice, *n, reg.enrollment, *ordenado) != -1)
    {
        reg.enrollment = matriAlea();
    }

    fa = fopen("datos.dat", "ab");
    fwrite(&reg, sizeof(TWrkr), 1, fa);
    fclose(fa);

    indice[*n].key = reg.enrollment;
    indice[*n].indice = *n;
    (*n)++;

    printf("Registro agregado con exito\n");

    if (*ordenado == 1)
    {
        *ordenado = 2;
    }
}

void EliminarReg(Tindice indice[], int *n, int ordenado)
{
    Tkey i;
    int num, op;
    FILE *fa;
    TWrkr reg;

    num = validarnumeros("Ingrese la matricula del estudiante que desea eliminar: \t", 300000, 399999);
    system("CLS");

    i = busqOpt(indice, *n, num, ordenado);

    if (i != -1)
    {
        fa = fopen("datos.dat", "rb+");

        fseek(fa, indice[i].indice * sizeof(TWrkr), SEEK_SET);
        fread(&reg, sizeof(TWrkr), 1, fa);

        if (reg.status == 0)
        {
            printf("Matricula se encuentra eliminada\n");
        }
        else
        {
            ImprimirReg(reg);
            op = validarnumeros("\n\nDesea eliminar el registro? \n1. Si\n2. No ", 1, 2);
            system("CLS");

            if (op == 1)
            {
                reg.status = 0;
                fseek(fa, indice[i].indice * sizeof(TWrkr), SEEK_SET);
                fwrite(&reg, sizeof(TWrkr), 1, fa);

                printf("Matricula eliminada con exito\n");
            }
            else
            {
                printf("Matricula no eliminada\n");
            }
        }

        fclose(fa);
    }
    else
    {
        printf("Matricula no encontrada\n");
    }
}

void BuscarReg(Tindice indice[], int n, int ordenado)
{
    Tkey i;
    int num;

    FILE *fa;
    TWrkr reg;

    printf("Ingrese la matricula del estudiante que desea buscar: ");
    num = validarnumeros("Ingrese la matricula del estudiante que desea buscar: \t", 300000, 399999);
    system("CLS");

    i = busqOpt(indice, n, num, ordenado);

    if (i != -1)
    {
        printf("Matricula encontrada\n\n", num);
        fa = fopen("datos.dat", "rb");

        fseek(fa, indice[i].indice * sizeof(TWrkr), SEEK_SET);
        fread(&reg, sizeof(TWrkr), 1, fa);
        ImprimirReg(reg);

        fclose(fa);
    }
    else
    {
        printf("La matricula %d no se encuentra en el vector\n", num);
    }
}

void ordenarReg(Tindice indice[], int n, int *ordenado)
{
    if (*ordenado == 0 || *ordenado == 2)
    {
        *ordenado = ordOpt(indice, n, *ordenado);
        printf("El vector ha sido ordenado\n");
    }
    else
    {
        printf("El vector ya estaba ordenado\n");
    }
}