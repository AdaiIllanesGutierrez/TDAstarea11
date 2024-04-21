
#include "tdas/list.h"
#include "tdas/stack.h"
#include "tdas/queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Define los niveles de prioridad
typedef enum {
    ALTO,
    MEDIO,
    BAJO
} Prioridad;

// Define la estructura del paciente
typedef struct {
    char nombre[50];
    int edad;
    char sintoma[100];
    Prioridad prioridad;
    time_t hora_registro;
} Paciente;

// Función para limpiar la pantalla
void limpiarPantalla() { system("clear"); }

// Espera a que el usuario presione una tecla para continuar
void presioneTeclaParaContinuar() {
    puts("Presione una tecla para continuar...");
    getchar(); // Consume el '\n' del buffer de entrada
    getchar(); // Espera a que el usuario presione una tecla
}

// Menú principal
void mostrarMenuPrincipal() {
    limpiarPantalla();
    puts("========================================");
    puts("     Sistema de Gestión Hospitalaria");
    puts("========================================");
    puts("1) Registrar paciente");
    puts("2) Asignar prioridad a paciente");
    puts("3) Mostrar lista de espera");
    puts("4) Atender al siguiente paciente");
    puts("5) Mostrar pacientes por prioridad");
    puts("6) Salir");
}
/*
void mostrarMenuPrioridad() {
  limpiarPantalla();
  puts("===========================");
  puts("  SELECCION DE PRIORIDAD ");
  puts("===========================");
  puts("|  1) ALTA                |");
  puts("|  2) MEDIA               |");
  puts("|  3) BAJA                |");
  puts("===========================");
}
*/
// Función para registrar un nuevo paciente
void registrarPaciente(List *pacientes) {
    limpiarPantalla();
    printf("REGISTRAR NUEVO PACIENTE\n");

    Paciente *nuevoPaciente = (Paciente *)malloc(sizeof(Paciente));

    printf("Ingrese el nombre del paciente: ");
    scanf("%s", nuevoPaciente->nombre);

    printf("Ingrese la edad del paciente: ");
    scanf("%d", &nuevoPaciente->edad);

    printf("Ingrese el síntoma del paciente: ");
    scanf("%s", nuevoPaciente->sintoma);

    nuevoPaciente->prioridad = BAJO; // Prioridad por defecto
    nuevoPaciente->hora_registro = time(NULL); // Hora actual
    
    list_pushBack(pacientes, nuevoPaciente); // Agrega el paciente al final de la lista

    printf("Paciente registrado con éxito\n");
}

// Función de comparación para buscar pacientes por nombre
int compareNames(void *data, void *target) {
    Paciente *paciente = (Paciente *)data;
    char *nombre = (char *)target;
    return strcmp(paciente->nombre, nombre);
}

// Función para asignar prioridad a un paciente
void asignarPrioridad(List *pacientes) {
    limpiarPantalla();
    printf("Asignar prioridad a paciente\n");

    char nombre[50];
    Prioridad prioridad;

    printf("Ingrese el nombre del paciente: ");
    scanf("%s", nombre);

    printf("Ingrese la nueva prioridad (Alto, Medio, Bajo): ");
    char prioridadStr[10];
    scanf("%s", prioridadStr);

    if (strcmp(prioridadStr, "Alto") == 0) {
        prioridad = ALTO;
    } else if (strcmp(prioridadStr, "Medio") == 0) {
        prioridad = MEDIO;
    } else if (strcmp(prioridadStr, "Bajo") == 0) {
        prioridad = BAJO;
    } else {
        printf("Prioridad no válida.\n");
        return;
    }

    // Buscar el paciente por nombre
    Paciente *paciente = (Paciente *)list_search(pacientes, nombre, compareNames);
    if (paciente != NULL) {
        paciente->prioridad = prioridad;
        printf("Prioridad actualizada con éxito\n");
    } else {
        printf("Paciente no encontrado\n");
    }
}

// Función para mostrar la lista de espera
void mostrarListaPacientes(List *pacientes) {
  limpiarPantalla();
  puts("==========================================");
  puts("            LISTA DE PACIENTES     ");
  puts("==========================================");

  if (list_size(pacientes) == 0) {
    puts("NO HAY PACIENTES EN ESPERA...");
  } else {
    // Recorremos la lista de pacientes y los mostramos por pantalla
      for (Paciente *p = list_first(pacientes); p != NULL; p = list_next(pacientes)) {
        printf("Nombre: %s, Edad: %d, Síntoma: %s, Prioridad: %d\n",
          p->nombre, p->edad, p->sintoma, p->prioridad);
        puts("--------------------------------------");
      }
    }
}

// Función para atender al siguiente paciente
void atenderSiguientePaciente(List *pacientes) {
  limpiarPantalla();
  printf("----ATENDER AL SIGUIENTE PACIENTE----\n");

  if (list_size(pacientes) == 0) {
    puts("NO HAY PACIENTES EN ESPERA...");
    return;
  }
  
  // Inicializamos el paciente atendido con el primero de la lista
  Paciente *pacienteAtendido = (Paciente *)list_first(pacientes);
  Prioridad prioridadAtendido = pacienteAtendido->prioridad;

  // Buscamos si hay un paciente con prioridad mayor
  for (Paciente *p = list_first(pacientes); p != NULL; p = list_next(pacientes)) {
    // Si encontramos un paciente con prioridad más alta, lo seleccionamos
    if (p->prioridad < prioridadAtendido) {
      pacienteAtendido = p;
      prioridadAtendido = p->prioridad;
    }
  }

  // Si no hay pacientes de prioridad alta, buscamos pacientes de prioridad media
  if (prioridadAtendido != ALTO) {
    for (Paciente *p = list_first(pacientes); p != NULL; p = list_next(pacientes)) {
      if (p->prioridad == MEDIO) {
        pacienteAtendido = p;
        break;
      }
    }
  }

  // Si no hay pacientes de prioridad alta ni media, seleccionamos al primero de prioridad baja
  if (prioridadAtendido != ALTO && prioridadAtendido != MEDIO) {
    pacienteAtendido = (Paciente *)list_first(pacientes);
  }

  // Mostramos la información del paciente atendido
  printf("Paciente atendido:\n");
  printf("Nombre: %s, Edad: %d, Síntoma: %s, Prioridad: %d\n", 
  pacienteAtendido->nombre, pacienteAtendido->edad, pacienteAtendido->sintoma,
  pacienteAtendido->prioridad);

  // Eliminamos al paciente atendido de la lista
  list_popCurrent(pacientes);
}

// Función para ordenar pacientes por prioridad
void PacientesOrdenados(List *pacientes) {
  // Crear una cola de prioridad para almacenar los pacientes
  List *colaPrioridad = list_create();
  // Insertar los pacientes en la cola de prioridad según su prioridad
  for (int i = ALTO; i <= BAJO; i++) {
    for (Paciente *p = list_first(pacientes); p != NULL; p = list_next(pacientes)) {
      if (p->prioridad == i) {
        list_pushBack(colaPrioridad, p);
      }
    }
  }
  // Mostrar los pacientes ordenados por prioridad
  mostrarListaPacientes(colaPrioridad);
  // Liberar memoria 
  list_clean(colaPrioridad);
}


// Función para mostrar pacientes por prioridad
void mostrarPacientesPorPrioridad(List *pacientes) {
  limpiarPantalla();
  printf("---------MOSTRAR PACIENTES POR PRIORIDAD---------\n");
  // Pedir al usuario que ingrese la prioridad deseada
  printf("Ingrese la prioridad deseada (Alto, Medio, Bajo): ");
  char prioridadStr[10];
  scanf("%s", prioridadStr);
  Prioridad prioridadDeseada;
  if (strcmp(prioridadStr, "Alto") == 0) {
    prioridadDeseada = ALTO;
  } else if (strcmp(prioridadStr, "Medio") == 0) {
    prioridadDeseada = MEDIO;
  } else if (strcmp(prioridadStr, "Bajo") == 0) {
    prioridadDeseada = BAJO;
  } else {
    printf("Prioridad no válida.\n");
     return;
  }
  // Crear una lista para almacenar los pacientes que coinciden con la prioridad deseada
  List *pacientesPrioridad = list_create();
  // Recorrer la lista de pacientes y agregar los que coinciden con la prioridad deseada
  for (Paciente *p = list_first(pacientes); p != NULL; p = list_next(pacientes)) {
    if (p->prioridad == prioridadDeseada) {
      list_pushBack(pacientesPrioridad, p);
    }
  }
  
  // Mostrar los pacientes ordenados por prioridad
  mostrarListaPacientes(pacientesPrioridad);
  // Liberar memoria de la lista de pacientes por prioridad
  list_clean(pacientesPrioridad);
}


int main() {
  char opcion;
  List *pacientes = list_create();
    
  do {
    mostrarMenuPrincipal();
    printf("Ingrese su opción: ");
    scanf(" %c", &opcion);
    
    switch (opcion) {
      case '1':
        registrarPaciente(pacientes);
        break;
      case '2':
        asignarPrioridad(pacientes);
        break;
      case '3':
        //mostrarListaPacientes(pacientes);
        PacientesOrdenados(pacientes);
        break;
      case '4':
        atenderSiguientePaciente(pacientes);
        break;
      case '5':
        mostrarPacientesPorPrioridad(pacientes);
        break;
      case '6':
        puts("Saliendo del sistema de gestión hospitalaria...");
        break;
      default:
        puts("Opción no válida. Por favor, intente de nuevo.");
    }
    presioneTeclaParaContinuar();
  } while (opcion != '6');

  // Liberar memoria
  list_clean(pacientes);
  return 0;
}
