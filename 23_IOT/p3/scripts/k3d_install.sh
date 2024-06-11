#!/bin/bash

sudo apt-get update -y

# Install Docker
curl -fsSL https://get.docker.com -o get-docker.sh
sh get-docker.sh

# Install k3d
curl -s https://raw.githubusercontent.com/k3d-io/k3d/main/install.sh | bash

k3d cluster create newCluster

k3d kubeconfig get newCluster

sudo chmod 777 /etc/rancher/k3s/k3s.yaml

k3d kubeconfig get newCluster > /etc/rancher/k3s/k3s.yaml

k3d cluster start newCluster
