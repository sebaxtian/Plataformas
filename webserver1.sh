#!/bin/bash
#
#

sudo apt-get update
sudo apt-get install -y apache2
sudo sh -c "echo \<h1\>Hostname: WebServer1 \(10.11.12.101\)\<\/h1\> >> /var/www/index.html"
