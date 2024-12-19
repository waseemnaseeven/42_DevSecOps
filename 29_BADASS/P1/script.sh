#!/bin/bash

sudo apt-get -y update && sudo apt-get -y upgrade && sudo apt-get autoremove -y

# GNS3
sudo apt-get -y install python3-pip
pip3 install gns3-gui gns3-server

# GNS3 - ubridge
sudo apt-get install -y libpcap-dev
git clone git@github.com:GNS3/ubridge.git
make -C ubridge
sudo make -C ubridge install
rm -rf ubridge

# GNS3 - xterm (needed for console on host)
sudo apt-get install -y xterm

# Install Docker
curl -fsSL https://get.docker.com -o get-docker.sh && sh get-docker.sh

# Dynamips
wget ppa.launchpad.net/gns3/ppa/ubuntu/pool/main/d/dynamips/dynamips_0.2.12-1~ppa1_amd64.deb
sudo dpkg -i dynamips_0.2.12-1~ppa1_amd64.deb
rm -rf dynamips_0.2.12-1~ppa1_amd64.deb

# Dynamips and vpcs
apt-get install -y dynamips vpcs

# Wireshark
sudo apt-get install -y wireshark
sudo usermod -aG wireshark $USER

reboot