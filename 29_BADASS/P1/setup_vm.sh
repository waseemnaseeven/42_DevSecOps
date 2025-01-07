#!/bin/bash

# General
sudo apt-get -y update && sudo apt-get -y upgrade && sudo apt-get autoremove -y
sudo apt-get install -y curl 

# Install Docker
curl -fsSL https://get.docker.com -o get-docker.sh && sh get-docker.sh && rm get-docker.sh

# GNS3
# Say no to everything during GNS3 installation
sudo add-apt-repository ppa:gns3/ppa
sudo apt update                                
sudo apt install gns3-gui gns3-server

# Permissions
sudo usermod -aG sudo,docker,gns3-server $USER

# Reboot
sudo reboot