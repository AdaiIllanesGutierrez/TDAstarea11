Tarea 1 
Correspondiente a Adai Illanes Gutierrez 
Materia Estructura de Datos
Universidad Pontificia Universidad Catolica de Valparaiso 

# Sistema de Gestión Hospitalaria

## Ejecucion del programa (main)
La ejecucion del programa se dejo por defecto como estaba
Para ejecutar el main primero debemos compilar (en la carpeta raíz)
````
gcc tdas/*.c main.c -Wno-unused-result -o main
````

Y luego ejecutar:
````
./main
````
## IMPLEMENTACIONES 
### 1. REGISTRAR PACIENTE 
La funcion de registrar paciente permite registrar un nuevo paciente donde se debe ingresar su nombre, edad y sintoma, para agregar la prioridad inicialmente se determino asignar la prioridad por defecto "Bajo" y se registrara la hora igual de manera automatica con la libreria time.h 

Para esta implementacion considerar que se uso cadenas simples es decir que si quiere aniadir nombre completo debe hacerlo junto o separado por una coma de igual forma si quiere aniadir varios sintomas hacerlo junto o separado por una coma, Para la edad considerar que sea un numero y no un caracter 

### 2. ASIGNAR PRIORIDAD A PACIENTE 
Esta opcion nos permitira cambiar la prioridad de un paciente que exista en la lista, funciona ingresando el nombre del paciente registrado anteriormente y escribiendo una nueva prioridad  "Alto", "Medio" o "Bajo".
Considerar que en esta funcion se verificara que el paciente exista es decir que el nombre que ingrese debe ser tal cual este en la lista, por otro lado tambien considerar que para asignar la prioridad debe ser si o si una las opciones ( "Alto", "Medio" o "Bajo"), si no de igual forma mandara un mensaje diciendo que la prioridad no existe, si la asignacion es favorable se enviara un mensaje diciendo actualizacion correcta y precionando una tecla se volvera al menu para continuar 

### 3. MOSTRAR LISTA DE ESPERA 
Esta opcion nos mostrara la lista de pacientes en espera mostrando los nombres,edades, sintomas y prioridades, ordenados por prioridad considerar que para la prioridad la representacion es la siguiente 
    1) 0 represenata al nivel ALTO 
    2) 1 represenata al nivel MEDIO
    3) 2 represenata al nivel BAJO 

### 4. ATENDER AL SIGUIENTE PACIENTE 
En esta opcion se atiende al paciente en espera con la prioridad más alta y, en caso de igual prioridad, al que llegó primero. eliminandolo asi de la lista 

### 5. MOSTRAR PACIENTES POR PRIORIDAD 
En esta opcion nos mostrara  nos mostrara la lista de pacientes que pertenecen a la prioridad que sea ingresada por el usuario en caso de no tener pacientes en esa prioridad se mostrara un mensaje diciendo que no hay pacientes de esa prioridad 

## EJEMPLO DE USO 

Inicialmente despues de ejecutar el main nos mostrara directamente lo que es el Menu Principal que es Gestion Hospitalaria 
````
$ ./main
````
```````````
========================================
     Sistema de Gestión Hospitalaria
========================================
1) Registrar paciente
2) Asignar prioridad a paciente
3) Mostrar lista de espera
4) Atender al siguiente paciente
5) Mostrar pacientes por prioridad
6) Salir
========================================
```````````
En aqui debes seleccionar una opcion con un numero del 1 al 6 caso de que sea otro te saldra error hasta que escojas una opcion valida 

### 1. REGISTRAR PACIENTE 
Para esta opcion del menu debes completar los siguientes campos como en aqui te ira pidiendo el nombre la edad y sintoma de manera secuencial a medida que los ingreses
````
REGISTRAR NUEVO PACIENTE
Ingrese el nombre del paciente: Ada
Ingrese la edad del paciente: 21
Ingrese el síntoma del paciente: Fiebre
Paciente registrado con éxito
````
si quieres aniadir mas sintomas o nombre completo procura que sea con comas sin espacios ya que no considerara los espacios y tomara solo la cadena antes del espacio, ejemplo aqui 
````
REGISTRAR NUEVO PACIENTE
Ingrese el nombre del paciente: Ada,Illanes
Ingrese la edad del paciente: 21
Ingrese el síntoma del paciente: Fiebre,Tos
Paciente registrado con éxito
````
### 2. ASIGNAR PRIORIDAD A PACIENTE 
para asignar la prioridad seleccionamos la opcion 2 y como se sabe se debe introducir el nombre del paciente al cual se le reasignara la nueva prioridad 
````
Asignar prioridad a paciente
Ingrese el nombre del paciente: Ada
Ingrese la nueva prioridad (Alto, Medio, Bajo): Alto
Prioridad actualizada con éxito
````
en caso que no se encuentre el paciente o la prioridad sea otra diferente a las mostradas se  mostrara 
  -Error: Si el paciente no se encuentra en la lista de espera.
  -Mensaje: "Paciente no encontrado."
  -Error: Si la prioridad ingresada no es válida.
  -Mensaje: "Prioridad no válida."
  
### 3. MOSTRAR LISTA DE ESPERA 
si se selecciona esta opcion se mostrara lo siguiente 
````
==========================================
            LISTA DE PACIENTES     
==========================================
Nombre: Ada, Edad: 21, Síntoma: Fiebre, Prioridad: 0
--------------------------------------
````
en caso de tener mas pacientes se mostrara ordenados 
````
==========================================
            LISTA DE PACIENTES     
==========================================
Nombre: Ada, Edad: 21, Síntoma: Fiebre, Prioridad: 0
--------------------------------------
Nombre: Dayli, Edad: 18, Síntoma: Tos, Prioridad: 2
--------------------------------------
````
### 4. ATENDER AL SIGUIENTE PACIENTE 
si se selecciona la opcion 4 directamente se mostrara el paciente el cual fue atendido y se lo eliminara de la lista, en este caso se elimina al que primero llego si hay 2 pacientes del mismo nivel o al paciente de mayor prioridad 

````
Ingrese su opción: 4
----ATENDER AL SIGUIENTE PACIENTE----
Paciente atendido:
Nombre: Ada, Edad: 21, Síntoma: Fiebre, Prioridad: 0, Hora de Registro: Mon Jan  1 00:00:00 2024
````
posibles errores si no hay pacientes en espera 
    -Error: Si no hay pacientes en espera.
    -Mensaje: "NO HAY PACIENTES EN ESPERA..."

### 5. MOSTRAR PACIENTES POR PRIORIDAD 
en esta opcion segun la prioridad que se escoja se mostrara a los pacientes de la lista inicialmente se le pedira que ingrese la prioridad que deseada a lo cual debe ingresar Alto,Medio o Bajo 
````
---------MOSTRAR PACIENTES POR PRIORIDAD---------
Ingrese la prioridad deseada (Alto, Medio, Bajo): Alto
````
si se ejecuta correctamente se mostrara al o a los pacientes que pertenezcan a esa prioridad 

````
==========================================
            PACIENTES POR PRIORIDAD     
==========================================
Nombre: Ada, Edad: 21, Síntoma: Fiebre, Prioridad: 0
````
en caso de encontrara algun error o excepcion se mostrara lo siguiente 

    -Error: Si la prioridad ingresada no es válida.
    -Mensaje: "Prioridad no válida."
    -Error: Si no hay pacientes con la prioridad deseada.
    -Mensaje: "No hay pacientes con esa prioridad."

## IMPLEMENTACION EN LIST.H Y LIST.C 
adicionalmente yo implemente las siguientes funciones para la lista y asi poder usarlas de manera abstracta en el codigo general 
````
1. list_search(List *list, void *target, int (*compare)(void *data, void *target)):
````
Esta función busca un elemento específico en la lista.
Recorre la lista buscando el elemento que coincida con el que estás buscando.
Si lo encuentra, devuelve ese elemento.
Si no lo encuentra, devuelve NULL.

````
2. list_size(List *L)
````
Esta función te dice cuántos elementos hay en la lista.
Devuelve el número total de elementos.
````
3. list_remove(List *L, void *target, int (*compare)(void *data, void *target)):**
````
Esta función elimina un elemento específico de la lista.
Busca el elemento que quieres eliminar.
Si lo encuentra, lo elimina de la lista.
Ajusta la lista para mantener todo en orden.