#!/bin/bash
#
# Este archivo ejecuta una serie de comandos en bash para crear maquinas virtuales
# en VirtualBox.
#
# La ejecucion del script recibe como entrada 8 parametros:
#
# $1 = Nombre de Maquina Virtual
# $2 = Tipo de Sistema Operativo
# $3 = Cantidad en MB del Disco Duro
# $4 = Cantidad en MB de Memoria RAM
# $5 = Numero de CPUs
# $6 = Nombre de Adaptador de Red en Host
# $7 = Descripcion de la Maquina Virtual
# $8 = PATH al archivo ISO del Instalador de OS
#
#
# Ejemplo de ejecucion del script:
#
# usuario@linux~$ ./CreateVirtualMachine.sh UbuntuServerXenial Ubuntu 2024 548 1 eth0 "Máquina Virtual para una instalación de Ubuntu Server 16.04 Xenial Xerus" /home/usuario/Desktop/Plataformas/ubuntu-16.04-server-amd64.iso
#
#
# Autor: Sebastian Rios Sabogal - https://about.me/sebaxtian
# Fecha: mar may  3 19:40:49 COT 2016
# Actualizado: mar may  3 19:40:49 COT 2016
# Version: 0.1
#



# Lista las maquinas virtuales ya creadas.
VBoxManage list vms

# Configura las variables con las entradas del usuario
VM=$1
TYPEOS=$2
HDSIZE=$3
RAMSIZE=$4
CPUS=$5
ADATRED=$6
DESC=$7
PATHTOISO=$8

if [[ -z $PATHTOISO ]]
then
	echo "ERROR::Debe ingresar todas las variables de entrada"
	# Muestra en pantalla las variables de entrada del usuario
	echo "---- Configuracion de variables de entrada del usuario ----"
	echo "Nombre de Maquina Virtual: "$VM
	echo "Tipo de Sistema Operativo: "$TYPEOS
	echo "Cantidad en MB del Disco Duro: "$HDSIZE
	echo "Cantidad en MB de Memoria RAM: "$RAMSIZE
	echo "Numero de CPUs: "$CPUS
	echo "Nombre de Adaptador de Red en Host: "$ADATRED
	echo "Descripcion de la Maquina Virtual: "$DESC
	echo "PATH al archivo ISO del Instalador de OS: "$PATHTOISO
else
	# Muestra en pantalla las variables de entrada del usuario
	echo "---- Configuracion de variables de entrada del usuario ----"
	echo "Nombre de Maquina Virtual: "$VM
	echo "Tipo de Sistema Operativo: "$TYPEOS
	echo "Cantidad en MB del Disco Duro: "$HDSIZE
	echo "Cantidad en MB de Memoria RAM: "$RAMSIZE
	echo "Numero de CPUs: "$CPUS
	echo "Nombre de Adaptador de Red en Host: "$ADATRED
	echo "Descripcion de la Maquina Virtual: "$DESC
	echo "PATH al archivo ISO del Instalador de OS: "$PATHTOISO
	
	# Lee confirmacion del usuario
	echo "Desea continuar ? y/N : "
	read continua
	
	# Valida la respuesta del usuario
	if [ "$continua" = "y" ]
	then
		echo "Inicia la creacion de maquina virtual"
	
		# Crear una maquina virtual
		VBoxManage createvm --name $VM --register

		# Crear disco duro para maquina virtual
		VBoxManage createhd --filename $VM.vdi --size $HDSIZE --format VDI

		# Crear controlador para dispositivos de almacenamiento
		VBoxManage storagectl $VM --name "IDE Controller" --add ide

		# Vincula un disco duro virtual al controlador
		VBoxManage storageattach $VM --storagectl "IDE Controller" --port 0 --device 0 --type hdd --medium $VM.vdi

		# Vincula una imagen de cd/dvd al controlador
		VBoxManage storageattach $VM --storagectl "IDE Controller" --port 1 --device 0 --type dvddrive --medium $PATHTOISO

		# Agrega una descripcion a la maquina virtual
		VBoxManage modifyvm $VM --description "$DESC"

		# Especifica el tipo de sistema operativo que tiene la maquina virtual
		VBoxManage modifyvm $VM --ostype $TYPEOS

		# Asigna una cantidad de memoria RAM a la maquina virtual
		VBoxManage modifyvm $VM --memory $RAMSIZE

		# Habilida I/O APIC si esta disponible
		VBoxManage modifyvm $VM --ioapic on

		# Asigna un numero de nucleos para CPUs de la maquina virtual
		VBoxManage modifyvm $VM --cpus $CPUS

		# Establece el porcentaje de procesamiento asignado a la CPU
		VBoxManage modifyvm $VM --cpuexecutioncap 100

		# Habilita virtualizacion por hardware si el host lo tiene disponible
		VBoxManage modifyvm $VM --hwvirtex on

		# Establece el orden de booteo
		VBoxManage modifyvm $VM --boot1 dvd --boot2 disk --boot3 none --boot4 none

		# Configura la tarjeta de red de la maquina virtual
		VBoxManage modifyvm $VM --nic1 bridged

		# Establece el adaptador puente de la tarjeta de red
		VBoxManage modifyvm $VM --bridgeadapter1 $ADATRED

		# Asigna memoria para la tarjeta grafica
		VBoxManage modifyvm $VM --vram 128

		# Lista las maquinas virtuales ya creadas.
		VBoxManage list vms

		# Ahora puede iniciar la maquina virtual
		VBoxManage startvm $VM
		
	else
		echo "Cancela la creacion de maquina virtual"
		echo "SUERTE"
	fi
fi
