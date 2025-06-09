ssh outscale@<public_ip> -o "StrictHostKeyChecking=no"
ssh outscale@<public_ip>

# Redirige vers "localhost:8080" ce qui etait sur localhost:9090
ssh -L 8080:localhost:9090 outscale@<public_ip> -o "StrictHostKeyChecking=no"

# Remove tasks
ansible-playbook -i inventory/hosts.ini playbook/node_exporter_playbook.yml -e "node_exporter_enabled=False"

# Charger les variables
load_vault_env

# Look requirements...
ansible-galaxy install -r requirements.yml 

# OpenSSL cmds
# Verifier signature certificat
openssl x509 -noout -text -in prometheus.crt

# Verifier a partir du client si bien connecte au serveur (en sudo)
openssl s_client -showcerts -servername nodeexporter.com -connect 10.15.56.16:9100 -CAfile /etc/prometheus/ca_client.crt -cert /etc/prometheus_ssl_client/prometheus_client.crt -key /etc/prometheus_ssl_client/prometheus_client.key </dev/null

# Copier la CA dans chaque librarie de certificate sur chaque machine
cp /etc/prometheus_ssl/ca.crt /usr/local/share/ca-certificates/MONITORING_CA.crt

# puis refresh
update-ca-certificates --fresh

# Sur la machine hote pour verifier la connexion https 
curl https://...

# Lire mon certificat ROOT
vault read rd/pki/monitoring/cert/ca -field=certificate

# ProxyJump + SSH Tunnel
ssh -J outscale@142.44.60.74 -L 9090:localhost:9090 outscale@10.15.17.190 -o StrictHostKeyChecking=no

# HAproxy 
watch "ss -s; netstat -ant | grep 9090"


# server query1 10.15.42.186:9090 check
# server query2 10.15.24.190:9090 check
# server query3 10.15.5.25:9090 check

