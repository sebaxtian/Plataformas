#!/bin/bash
#
# Script para compilar y ejecutar programa Java en Hadoop
#
# La ejecucion del script recibe como entrada 3 parametros:
#
# $1 = Path del programa Java en Hadoop
# $2 = Path del directorio HDFS para datos de entrada
# $3 = Path del directorio HDFS para datos de salida
#
# Los archivos compilados del programa Java en Hadoop se
# generan en el directorio Make relativo al Path donde
# se encuentra este Script.
#
# Sebastian Rios Sabogal
# mar jun 28 11:53:44 COT 2016
# 0.1.0
#


echo "Make Progama Java en Hadoop"
echo "Programa: "$1
echo "Datos de Entrada: "$2
echo "Datos de Salida: "$3
echo ""


# Borra el directorio HDFS de salida de datos si no existe
hadoop fs -rm -R $3

# Borra el directorio de archivos compilados si existe
rm -rfv Make

# Crea el directorio de archivos compilados
mkdir Make

# Nombre del programa Java en Hadoop
nombrePrograma=$(echo $1 | cut -d'.' -f 1)

# Copia el programa al directorio Make
cp -rfv $1 Make

# Trabaja desde directorio Make
cd Make

# Compila el programa Java en Hadoop
hadoop com.sun.tools.javac.Main $1

# Empaqueta en un archivo .jar los archivos compilados
jar cf $nombrePrograma.jar $nombrePrograma*class

# Ejecuta el programa Java en Hadoop compilado
hadoop jar $nombrePrograma.jar $nombrePrograma $2 $3

# Termina ejecucion del programa
echo "Termina ejecucion"

# Vuelve al directorio de origen
cd -

# Lista archivos del directorio de datos de salida
hadoop fs -ls $3

# Muestra el resultado del directorio de salida de datos
hadoop fs -cat /output/part*
