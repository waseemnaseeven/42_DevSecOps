# creation dossier pour key
sudo mkdir -p /etc/apt/keyrings/

# requete recuperation cle | convertit de pgp a gpg file format | puis lis la cle et l'ecrit sur la sortie standard, sauf qu'on renvoie vers un black hole
wget -q -O - https://apt.grafana.com/gpg.key | gpg --dearmor | sudo tee /etc/apt/keyrings/grafana.gpg > /dev/null

# ajoute un repo a la liste
echo "deb [signed-by=/etc/apt/keyrings/grafana.gpg] https://apt.grafana.com stable main" | sudo tee -a /etc/apt/sources.list.d/grafana.list

# extraction d'un package
sudo apt-get update -y

# installs the latest OSS release:
sudo apt-get install grafana

# change capabilities on 
cd /usr/lib/systemd/system
sudo vim 

# copy-pasta below Service

# Give the CAP_NET_BIND_SERVICE capability
CapabilityBoundingSet=CAP_NET_BIND_SERVICE
AmbientCapabilities=CAP_NET_BIND_SERVICE

# A private user cannot have process capabilities on the host's user
# namespace and thus CAP_NET_BIND_SERVICE has no effect.
PrivateUsers=false

# then change the default port by removing ';' and put '80' instead of 3000
cd /etc/grafana
sudo vim grafana.ini

# start server 
sudo systemctl daemon-reload 
# configure grafana server to start at boot using systemd
sudo systemctl enable grafana-server.service
sudo systemctl start grafana-server.service

# verify 
sudo systemctl status grafana-server

# restart if necessary 
sudo systemctl restart grafana-server

#optional; remove grafana repository
sudo rm -i /etc/apt/sources.list.d/grafana.list