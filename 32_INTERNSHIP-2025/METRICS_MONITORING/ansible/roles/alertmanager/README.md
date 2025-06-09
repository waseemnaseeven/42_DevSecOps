# Alertmanager useful commands 

Ci-dessous les commandes utiles afin d'installer plusieurs alertmanager en http, https (TLS ou mTLS), suppression...

## Alertmanager Enable HTTP

ansible-playbook -i inventory/hosts.yml playbook/alertmanager.yml 

## Alertmanager Enable TLS

ansible-playbook -i inventory/hosts.yml playbook/alertmanager.yml -e "alertmanager_tls_server_enabled=True" 

## Alertmanager Enable mTLS

ansible-playbook -i inventory/hosts.yml playbook/alertmanager.yml -e "alertmanager_tls_server_enabled=True" -e "alertmanager_tls_client_enabled=True"

## Alertmanager Remove

ansible-playbook -i inventory/hosts.yml playbook/alertmanager.yml -e "alertmanager_enabled=False"

