#!/bin/bash
#
#

sudo apt-get update
sudo apt-get install -y apache2
sudo sh -c "echo \<h1\>Hostname: $1 \($2\)\<\/h1\> >> /var/www/index.html"
