#!/bin/bash
#
#
# Este script permite Instalar y Configurar la aplicacion NFS
# Se debe indicar si el destino de la aplicacion es una maquina
# con perfil Servidor o una maquina con perfil Cliente.
# 
# La ejecucion del script recibe como entrada 3 parametros:
# 
# $1 = Bandera que indica si el destino es Servidor o Cliente [S,C]
# $2 = Nombre del directorio compatido
# $3 = IP del Servidor, solo se tiene en cuenta cuando el destino es Cliente
#
# Ejemplo de ejecucion del script para un destino Servidor:
# 
# usuario@linux~$ ./appnfs.sh S compartido 
#
# Ejemplo de ejecucion del script para un destino Cliente:
#
# usuario@linux~$ ./appnfs.sh C compartido 10.10.10.2
#
#
# Autor: Sebastian Rios Sabogal - https://about.me/sebaxtian
# Fecha: lun may 30 21:54:38 COT 2016
# Actualizado: lun may 30 21:54:38 COT 2016
# Version: 0.1
#


# Configura las variables con los paramentros de entrada de ejecucion del script
DESTINO=$1
NOMBREDIR=$2
IPSERVER=$3


# Muestra en pantalla las variables de entrada del usuario
echo "---- Configuracion de variables de entrada del usuario ----"
echo "Destino: "$DESTINO
echo "Nombre Directorio Compartido: "$NOMBREDIR
echo "IP de Servidor: "$IPSERVER


# Actualiza la lista de repositorios del sistema
sudo apt-get update


# Si el destino es Servidor
if [ "$DESTINO" = "S" ]
then
	echo "Inicia Instalacion y Configuracion de NFS en Servidor"
	echo "Nombre de Directorio Compartido: "$NOMBREDIR
	# Instala el paquete de aplicacion NFS para Servidor
	sudo apt-get install -y nfs-kernel-server
	# Crea directorio compartido en servidor
	sudo mkdir /$NOMBREDIR
	sudo chown nobody:nogroup /$NOMBREDIR
	sudo chmod 1777 /$NOMBREDIR
	# Se notifica a NFS cuales son los directorios compartidos
	echo "/$NOMBREDIR *(rw,sync,no_subtree_check)" >> /etc/exports
	sudo exportfs -a
	# Reinicia el servicio NFS para aplicar los cambios
	sudo service nfs-kernel-server start
else
	# Si el destino es Cliente y existe IP del Servidor
	if [ "$DESTINO" = "C" ] && [[ -n $IPSERVER ]]
	then
		echo "Inicia Instalacion y Configuracion de NFS en Cliente"
		echo "Nombre de Directorio Compartido: "$NOMBREDIR
		# Instala el paquete de aplicacion NFS para Cliente
		sudo apt-get install -y nfs-common
		# Crea directorio que sera compartido desde el Servidor
		sudo mkdir /$NOMBREDIR
		# Importa directorio compartido desde Servidor
		sudo mount $IPSERVER:/$NOMBREDIR /$NOMBREDIR
		# Verifica que el directorio compartido ha sido montado
		df -h
	else
		echo "ERROR::Debe ingresar un destino valido [S, C] y una IP del Servidor"
		echo "SUERTE"
	fi
fi
