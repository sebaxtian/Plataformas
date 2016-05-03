#!/bin/bash
#
# Este archivo ejecuta una serie de comando en bash para crear maquinas virtuales
# en VirtualBox.
#


# Lista las maquinas virtuales ya creadas.
VBoxManage list vms

VM="UbuntuServerXenial"
PATHTOVDI=/home/user/Desktop/Plataformas/$VM.vdi
PATHTOISO=/home/user/Desktop/Plataformas/ubuntu-16.04-server-amd64.iso

echo $VM
echo $PATHTOVDI
echo $PATHTOISO

# Crear una maquina virtual
VBoxManage createvm --name $VM --register

# Crear disco duro para maquina virtual
VBoxManage createhd --filename $VM.vdi --size 2024 --format VDI

# Crear controlador para dispositivos de almacenamiento
VBoxManage storagectl $VM --name "IDE Controller" --add ide

# Vincula un disco duro virtual al controlador
VBoxManage storageattach $VM --storagectl "IDE Controller" --port 0 --device 0 --type hdd --medium $PATHTOVDI

# Vincula una imagen de cd/dvd al controlador
VBoxManage storageattach $VM --storagectl "IDE Controller" --port 1 --device 0 --type dvddrive --medium $PATHTOISO

# Agrega una descripcion a la maquina virtual
VBoxManage modifyvm $VM --description "Máquina Virtual para una instalación de Ubuntu Server 16.04 Xenial Xerus"

# Especifica el tipo de sistema operativo que tiene la maquina virtual
VBoxManage modifyvm $VM --ostype "Ubuntu"

# Asigna una cantidad de memoria RAM a la maquina virtual
VBoxManage modifyvm $VM --memory 524

# Habilida I/O APIC si esta disponible
VBoxManage modifyvm $VM --ioapic on

# Asigna un numero de nucleos para CPUs de la maquina virtual
VBoxManage modifyvm $VM --cpus 1

# Establece el porcentaje de procesamiento asignado a la CPU
VBoxManage modifyvm $VM --cpuexecutioncap 100

# Habilita virtualizacion por hardware si el host lo tiene disponible
VBoxManage modifyvm $VM --hwvirtex on

# Establece el orden de booteo
VBoxManage modifyvm $VM --boot1 dvd --boot2 disk --boot3 none --boot4 none

# Configura la tarjeta de red de la maquina virtual
VBoxManage modifyvm $VM --nic1 bridged

# Establece el adaptador puente de la tarjeta de red
VBoxManage modifyvm $VM --bridgeadapter1 eth0

# Asigna memoria para la tarjeta grafica
VBoxManage modifyvm $VM --vram 128
