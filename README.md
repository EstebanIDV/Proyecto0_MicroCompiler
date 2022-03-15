# Proyecto: Compilador de Micro 💻

Este es un Compilador escrito en C para el lenguaje Micro, que genera código emsamblador y ejecuta dicho código.
El lenguaje Micro está definido por un solo tipo de datos, numeral, trabajando con positivos y negativos.
Existen además identificadores, con una extensión de 32 caracteres, teniendo en cuenta que existen palabras reservadas como WRITE, READ, BEGIN y END.
La ejecución del programa necesita estricatamente un archivo con el código fuente de Micro, este archivo obligatoriamente
es de extensión ".txt".


## Instituto Tecnológico de Costa Rica - Escuela de Ing. en Computación

## Miembros ☕️

* Diego Gerardo Méndez Valverde - ✉️: diegomvalverde@outlook.com - 2016078675
* Esteban Ignacio Durán Vargas - ✉️: eiduran@estudiantec.cr - 2020388144
* David Francisco Hernández Calvo - ✉️: dahercal29@estudiantec.cr - 2020041924


### Datos del curso

* Profesor: Dr. francisco J. Torres-Rojas
* Nombre del curso: Compiladores e Intérpretes

### Dependencias de instalación para ejecución 🛠️

0. Linux de preferencia
1. gcc
2. gcc-multilib
3. nasm
4. git

### Pasos de ejecución del proyecto 🖱️

0. Clonar el proyecto desde GitHub
1. Abrir una terminal en la raíz del proyecto
2. Ejecutar el comando en terminal: make
3. Lanzar el ejecutable llamado micro junto con la entrada: ./micro archivo.txt, dónde el archivo
   de entrada contiene código de lenguaje Micro

#### Ejemplo de ejecución

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

### Construido con 🛠️

* C
* ASM - Nasm
* Clion
* Linux