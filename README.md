# Proyecto: Compilador de Micro 馃捇

Este es un Compilador escrito en C para el lenguaje Micro, que genera c贸digo emsamblador y ejecuta dicho c贸digo.
El lenguaje Micro est谩 definido por un solo tipo de datos, numeral, trabajando con positivos y negativos.
Existen adem谩s identificadores, con una extensi贸n de 32 caracteres, teniendo en cuenta que existen palabras reservadas como WRITE, READ, BEGIN y END.
La ejecuci贸n del programa necesita estricatamente un archivo con el c贸digo fuente de Micro, este archivo obligatoriamente
es de extensi贸n ".txt".


## Instituto Tecnol贸gico de Costa Rica - Escuela de Ing. en Computaci贸n

## Miembros 鈽曪笍

* Diego Gerardo M茅ndez Valverde - 鉁夛笍: diegomvalverde@outlook.com - 2016078675
* Esteban Ignacio Dur谩n Vargas - 鉁夛笍: eiduran@estudiantec.cr - 2020388144
* David Francisco Hern谩ndez Calvo - 鉁夛笍: dahercal29@estudiantec.cr - 2020041924


### Datos del curso

* Profesor: Dr. francisco J. Torres-Rojas
* Nombre del curso: Compiladores e Int茅rpretes

### Dependencias de instalaci贸n para ejecuci贸n 馃洜锔?

0. Linux de preferencia
1. gcc
2. gcc-multilib
3. nasm
4. git

### Pasos de ejecuci贸n del proyecto 馃柋锔?

0. Clonar el proyecto desde GitHub
1. Abrir una terminal en la ra铆z del proyecto
2. Ejecutar el comando en terminal: make
3. Lanzar el ejecutable llamado micro junto con la entrada: ./micro archivo.txt, d贸nde el archivo
   de entrada contiene c贸digo de lenguaje Micro

#### Ejemplo de ejecuci贸n

0. git clone https://github.com/EstebanIDV/Proyecto0_MicroCompiler.git
1. cd Proyecto0_MicroCompiler
2. make
3. ./micro ejemplo.txt

Contenido de ejemplo.txt:
-- Este Compilador recibe una entrada del usuario y la muestra en pantalla restandole 2 y sumando 1
BEGIN
READ(A);
A:= A - 2 + 1;
WRITE(A);
END

### Construido con 馃洜锔?

* C
* ASM - Nasm
* Clion
* Linux