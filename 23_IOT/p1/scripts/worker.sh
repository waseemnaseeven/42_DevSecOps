
#!/bin/bash

GREEN="\033[32m"
RED="\033[31m"
RESET="\033[0m"

if export INSTALL_K3S_EXEC="agent -s https://192.168.56.110:6443 -t $(cat /vagrant/token.env) --node-ip=192.168.56.111"; then
        echo -e "${GREEN}export INSTALL_K3S_EXEC SUCCEEDED${RESET}"
else
        echo -e "${RED}export INSTALL_K3S_EXEC FAILED${RESET}"
fi 

if curl -sfL https://get.k3s.io | sh -; then
	echo -e "${GREEN}K3s WORKER installation SUCCEEDED${RESET}"
else
	echo -e "${RED}K3s WORKER installation FAILED${RESET}"
fi

# We delete the token for security, and also so that when restarting, a new token is used and not the previously created one

sudo rm /vagrant/token.env
