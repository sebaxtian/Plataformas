#!/bin/bash
#
#

sudo apt-get update
sudo apt-get install -y haproxy
#sudo echo "ENABLED=1" >> /etc/default/haproxy
sudo sed -i 's/ENABLED=0/ENABLED=1/g' /etc/default/haproxy
sudo mv /etc/haproxy/haproxy.cfg{,.original}
sudo cp -f /vagrant/haproxy.cfg /etc/haproxy/
sudo service haproxy start
