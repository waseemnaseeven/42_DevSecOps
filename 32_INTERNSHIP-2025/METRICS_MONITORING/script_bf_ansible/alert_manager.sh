sudo useradd -M -U alertmanager

wget https://github.com/prometheus/alertmanager/releases/download/v0.28.0/alertmanager-0.28.0.linux-amd64.tar.gz
tar -xvf alertmanager-0.28.0.linux-amd64.tar.gz 
sudo mv alertmanager-0.28.0.linux-amd64 /opt/alertmanager

sudo chown alertmanager:alertmanager -R /opt/alertmanager

# test with : testalert42@proton.me mdp: dontwatchme

sudo setcap CAP_NET_BIND_SERVICE=+eip # dans /opt/alertmanager

