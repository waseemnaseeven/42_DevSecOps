wget https://github.com/prometheus/node_exporter/releases/download/v1.8.2/node_exporter-1.8.2.linux-amd64.tar.gz
tar xvf node_exporter-1.8.2.linux-amd64.tar.gz
cd node_exporter-1.8.2.linux-amd64
./node_exporter

# permet au processus non root de se lier a un port < 1024
sudo setcap CAP_NET_BIND_SERVICE=+eip ./node_exporter 
./node_exporter --web.listen-address=:80

# ou 

sudo useradd -M -U node_exporter

# mv dans /opt/node_exporter le dossier node_exporter

sudo chown node_exporter:node_exporter -R /opt/node_exporter

sudo vim /etc/systemd/system/node_exporter.service

# [Unit]
# Description=Node_Exporter Server
# Documentation=https://github.com/prometheus/node_exporter
# After=network-online.target

# [Service]
# User=node_exporter
# Group=node_exporter
# Restart=on-failure
# ExecStart=/opt/node_exporter/node_exporter \
#     --web.listen-address=:80

# [Install]
# WantedBy=multi-user.target

sudo setcap CAP_NET_BIND_SERVICE=+eip ./node_exporter # dans le dossier /opt/node_exporter

sudo systemctl daemon-reload
sudo systemctl start node_exporter.service

sudo systemctl enable node_exporter.service

sudo systemctl status node_exporter.service

sudo journalctl -u node_exporter.service -f

# test load_average with 

while true; do find /; done