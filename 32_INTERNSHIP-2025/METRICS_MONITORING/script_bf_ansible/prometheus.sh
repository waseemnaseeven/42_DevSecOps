wget https://github.com/prometheus/prometheus/releases/download/v3.1.0/prometheus-3.1.0.linux-amd64.tar.gz
tar xvf prometheus-3.1.0.linux-amd64.tar.gz
cd prometheus-3.1.0.linux-amd64
./prometheus --web.listen-address=:80

# OU

sudo useradd -M -U prometheus 

# mv dans /opt/prometheus le dossier prometheus, dossier installation optionnelle

sudo chown prometheus:prometheus -R /opt/prometheus # changer proprietaire 

sudo vim /etc/systemd/system/prometheus.service

# [Unit]
# Description=Prometheus Server
# Documentation=https://prometheus.io/docs/introduction/overview/
# After=network-online.target # service doit demarre apres que le reseau soit en ligne

# [Service]
# User=prometheus # le service doit être exécuté sous l'utilisateur prometheus. 
# Group=prometheus
# Restart=on-failure
# ExecStart=/opt/prometheus/prometheus \
#   --config.file=/opt/prometheus/prometheus.yml \
#   --storage.tsdb.path=/opt/prometheus/data \ # speicifie le chemin ou les donnees seront stockees

# [Install]
# WantedBy=multi-user.target

sudo systemctl daemon-reload # charger dans le systemd
sudo systemctl start prometheus.service 

sudo systemctl enable prometheus.service # start au demarrage du systeme

sudo systemctl status prometheus.service

sudo journalctl -u prometheus.service -f

# # my global config
# global:
#   scrape_interval: 5s # Set the scrape interval to every 15 seconds. Default is every 1 minute.
#   evaluation_interval: 5s # Evaluate rules every 15 seconds. The default is every 1 minute.
#   # scrape_timeout is set to the global default (10s).

# # Alertmanager configuration
# alerting:
#   alertmanagers:
#     - static_configs:
#         - targets:
#           - 10.15.48.159

# # Load rules once and periodically evaluate them according to the global 'evaluation_interval'.
# rule_files:
#   - "/opt/prometheus/rules/first_rules.yml"
#   # - "second_rules.yml"

# # A scrape configuration containing exactly one endpoint to scrape:
# # Here it's Prometheus itself.
# scrape_configs:
#   # The job name is added as a label `job=<job_name>` to any timeseries scraped from this config, nom de bloc.
#   - job_name: "prometheus"

#     # metrics_path defaults to '/metrics' # route de scraping
#     # scheme defaults to 'http'.

#     static_configs:
#       - targets: ["localhost:9090"]

#   - job_name: "node_itself"

#     static_configs:
#       - targets: ["localhost:9100"]

#   - job_name: "node_exporter"

#     static_configs:

#       - targets:
#         - 10.15.61.201
#         - 10.15.6.68

