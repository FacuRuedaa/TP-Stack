#include <stdio.h>
#include <stdlib.h>
#include "pila.h"
#include <conio.h>
#define ESC 27

void cargaPila (Pila *punteroPila);
void pasaPila (Pila *origen, Pila *destino);
void pasaPilaOrdenada (Pila *pOrigen, Pila *pDestino);
int buscaMenor (Pila *p);
void ordenadaPorSeleccion (Pila *pDesordenada, Pila *pOrdenada);
void insertarElemento (Pila *pilota, Pila *insertada, int elemento);
int sumaPila (Pila s);
int sumaElementos (Pila pSuma);
int cantidadElementos (Pila cont);
float divideElementos (int a, int b);
float promedio (Pila copia);


int main()
{
    Pila dada, pilita, ordenada;
    inicpila(&dada);
    inicpila(&pilita);
    inicpila(&ordenada);
    char control;
    int m, e, ejercicio, sumaDosElementos, cantidad;
    int suma=0;

    do {
        system("cls");
        printf("Ingrese el numero del ejercicio que desea realizar\n");
        printf("--------------------------------------------------\n");
        printf("1) Cargar una pila\n");
        printf("--------------------------------------------------\n");
        printf("2) Pasa pilar a otra\n");
        printf("--------------------------------------------------\n");
        printf("3) Pasar a una pila ordenada\n");
        printf("--------------------------------------------------\n");
        printf("4) Buscar el menor de una pila\n");
        printf("--------------------------------------------------\n");
        printf("5) Ordenar la pila por seleccion\n");
        printf("--------------------------------------------------\n");
        printf("6) Ordenar la pila por insercion\n");
        printf("--------------------------------------------------\n");
        printf("7) Sumar su tope y anterior\n");
        printf("--------------------------------------------------\n");
        printf("8) Muestra cantidad elementos, los suma y muestra el promedio de la pila\n");
        printf("--------------------------------------------------\n");
        scanf("%i", &ejercicio);
        switch (ejercicio) {
            case 1:
                cargaPila(&dada); /// Mando la direccion de memoria de la pila
                printf("\nLa pila dada: \n");
                mostrar(&dada);
            break;
            case 2:
                pasaPila(&dada, &pilita);
                printf("\nLa pila pilita: \n");
                mostrar(&pilita);
            break;
            case 3:
                pasaPilaOrdenada(&dada, &ordenada);
                printf("\nLa pila ordenada: \n");
                mostrar(&ordenada);
            break;
            case 4:
                m = buscaMenor(&dada);
                printf("\nEl menor es: %d", m);
            break;
            case 5:
                ordenadaPorSeleccion(&dada, &ordenada);
                printf("\nLa pila ordenada: \n");
                mostrar(&ordenada);
            break;
            case 6:
                printf("\nIngrese el elemento que desea insertar: \n");
                scanf("%d", &e);

                insertarElemento(&dada, &ordenada, e);
                printf("\nLa pila con el elemento insertado: \n");
                mostrar(&ordenada);
            break;
            case 7:
                sumaDosElementos = sumaPila(dada);
                printf("\nLa suma del tope y su anterior es: %d\n", sumaDosElementos);
                printf("\nLa pila dada: ");
                mostrar(&dada);
            break;
            case 8:
                suma = sumaElementos(dada);
                printf("\nLa suma de todos sus elementos es: %d\n", suma);
                cantidad = cantidadElementos(dada);
                printf("\nLa cantidad de elementos de la pila es: %d", cantidad);
                printf("\El promedio de los elementos es: %2.f", promedio(dada));
                printf("\nLa pila dada: ");
                mostrar(&dada);
            break;
            case 9:
            break;
            default:
                printf("\n Opcion incorrecta\n");
            break;
        }
        printf("Quiere ver otro ejercicio? s/n\n");
        fflush(stdin);
        printf("%c\n", control = getch());

    } while (control=='s');

    return 0;
}

/// Primer punto: Cargar una pila

void cargaPila (Pila *punteroPila)
{
    char option;

    printf("\nCargando la pila desde la funcion\n");

    do
    {
        leer(punteroPila);
        printf("\nPresione ESC para salir..\n");
        option=getch();
        system("cls");
    }
    while (option!=ESC);
}

/// 2. Hacer una función que pase todos los elementos de una pila a otra.

void pasaPila (Pila *origen, Pila *destino)
{
    while (!pilavacia(origen))
    {
        apilar(destino, desapilar(origen));
    }
}

/// 3. Hacer una función que pase todos los elementos de una pila a otra, pero conservando el orden.

void pasaPilaOrdenada (Pila *pOrigen, Pila *pDestino)
{
    Pila aux;
    inicpila(&aux);

    while (!pilavacia(pOrigen))
    {
        apilar(&aux, desapilar(pOrigen));
    }
    /// TENDRIA QUE HABER USADO LA FUNCION ANTERIOR DE PASAR PILA !
    while (!pilavacia(&aux))
    {
        apilar(pDestino, desapilar(&aux));
    }

}

/// 4. Hacer una función que encuentre el menor elemento de una pila y lo retorne. La misma debe eliminar ese dato de la pila.

int buscaMenor (Pila *p)
{
    Pila aux;
    inicpila(&aux);
    int menor;

    if (!pilavacia(p))
    {
        menor = desapilar(p);

        while (!pilavacia(p))
        {
            if (menor>tope(p))
            {
                apilar(&aux, menor);
                menor = desapilar(p);
            }
            else
            {
                apilar(&aux, desapilar(p));
            }
        }
        pasaPila(&aux, p);
    }

    return menor;
}

/// 5. Hacer una función que pase los elementos de una pila a otra,
/// de manera que se genere una nueva pila ordenada. Usar la función del ejercicio 4. (Ordenamiento por selección)

void ordenadaPorSeleccion (Pila *pDesordenada, Pila *pOrdenada)
{

    int buscaM;

    while (!pilavacia(pDesordenada))
    {
        buscaM = buscaMenor(pDesordenada);
        apilar(pOrdenada, buscaM);
    }
}

/// 6 y 7? Hacer una función que inserte en una pila ordenada un nuevo elemento, conservando el orden de ésta.

void insertarElemento (Pila *pilota, Pila *insertada, int elemento)
{
    Pila aux;
    inicpila(&aux);

    ordenadaPorSeleccion(pilota, insertada);

    while (!pilavacia(insertada) && tope(insertada)>elemento)
    {
        apilar(&aux, desapilar(insertada));
    }

    apilar(insertada, elemento);

    while (!pilavacia(&aux))
    {
        apilar(insertada, desapilar(&aux));
    }
}

/// 8. Hacer una función que sume y retorne los dos primeros elementos de una pila (tope y anterior), sin alterar su contenido.

int sumaPila (Pila s)
{
    int suma=0;
    int i=0;

    while (!pilavacia(&s) && i<2                                                )
    {
        suma = suma + desapilar(&s);
        i++;
    }
    return suma;
}

/// 9. Hacer una función que calcule el promedio de los elementos de una pila,
/// para ello hacer también una función que calcule la suma, otra para la cuenta y otra que divida.
/// En total son cuatro funciones, y la función que calcula el promedio invoca a las otras 3.

/// Funcion que suma los elementos de la pila
int sumaElementos (Pila pSuma)
{
    Pila aux;
    inicpila(&aux);
    int sumar=0;

    while (!pilavacia(&pSuma))
    {
        sumar = sumar + tope(&pSuma);
        apilar(&aux, desapilar(&pSuma));
    }
    return sumar;
}

int cantidadElementos (Pila cont)
{
    Pila aux;
    inicpila(&aux);
    int i=0;

    while (!pilavacia(&cont)) {
        apilar(&aux, desapilar(&cont));
        i++;
    }
    return i;
}

float divideElementos (int a, int b)
{
    float division=0;

    division = (float) a / b;

    return division;
}

float promedio (Pila copia)
{
    float rta=0;

    rta = (float) (sumaElementos(copia)/cantidadElementos(copia));

    return rta;
}

