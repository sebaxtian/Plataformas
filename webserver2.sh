#!/bin/bash
#
#

sudo apt-get update
sudo apt-get install -y apache2
sudo sh -c "echo \<h1\>Hostname: WebServer2 \(10.11.12.102\)\<\/h1\> >> /var/www/index.html"
