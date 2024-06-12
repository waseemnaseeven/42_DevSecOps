#!/bin/bash

sudo apt-get update -y

# Install Docker
curl -fsSL https://get.docker.com -o get-docker.sh
sh get-docker.sh

# Install kubectl
curl -LO "https://dl.k8s.io/release/$(curl -L -s https://dl.k8s.io/release/stable.txt)/bin/linux/amd64/kubectl"

curl -LO "https://dl.k8s.io/release/$(curl -L -s https://dl.k8s.io/release/stable.txt)/bin/linux/amd64/kubectl.sha256"

echo "$(cat kubectl.sha256)  kubectl" | sha256sum --check

sudo install -o root -g root -m 0755 kubectl /usr/local/bin/kubectl

# Install k3d
curl -s https://raw.githubusercontent.com/k3d-io/k3d/main/install.sh | bash

# Cluster creation and context 
k3d cluster create newCluster

k3d kubeconfig get newCluster

sudo chmod 666 /etc/rancher/k3s/k3s.yaml

k3d kubeconfig get newCluster > /etc/rancher/k3s/k3s.yaml

k3d cluster start newCluster
