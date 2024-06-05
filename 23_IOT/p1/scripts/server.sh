#!/bin/bash

GREEN="\033[32m"
RED="\033[31m"
RESET="\033[0m"

if export INSTALL_K3S_EXEC="--write-kubeconfig-mode=0644 --tls-san wnaseeveS --node-ip 192.168.56.110 --bind-address=192.168.56.110 --advertise-address=192.168.56.110 --cluster-init "; then
    echo -e "${GREEN}export INSTALL_K3S_EXEC SUCCEEDED${RESET}"
else
    echo -e "${RED}export INSTALL_K3S_EXEC FAILED${RESET}"
fi

if curl -sfL https://get.k3s.io | sh -; then
    echo -e "${GREEN}K3s MASTER installation SUCCEEDED${RESET}"
else
    echo -e "${RED}K3s MASTER installation FAILED${RESET}"
fi

if sudo cat /var/lib/rancher/k3s/server/token >> /vagrant/token.env; then
    echo -e "${GREEN}TOKEN SUCCESSFULLY SAVED${RESET}"
else
    echo -e "${RED}TOKEN SAVING FAILED${RESET}"
fi
