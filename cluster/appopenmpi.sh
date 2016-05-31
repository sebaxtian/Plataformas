#!/bin/bash
#
#
# Este script permite Instalar la aplicacion OpenMPI
# 
#
# Autor: Sebastian Rios Sabogal - https://about.me/sebaxtian
# Fecha: lun may 30 22:53:44 COT 2016
# Actualizado: lun may 30 22:53:44 COT 2016
# Version: 0.1
#

# Actualiza la lista de repositorios del sistema
sudo apt-get update

echo "Inicia Instalacion de OpenMPI"
# Instala el paquete de aplicacion OpenMPI
sudo apt-get install -y openmpi-bin openmpi-doc libopenmpi-dev

