# Thanos Query Useful Things

Ci-dessous, les commandes utiles afin d'installer thanos_query en http, https (TLS ou mTLS), suppression...

## Thanos Query Enable HTTP

ansible-playbook -i inventory/hosts.yml playbook/thanos_query.yml 

## Thanos Query Enable TLS

ansible-playbook -i inventory/hosts.yml playbook/thanos_query.yml -e "thanos_query_tls_server_enabled=True" 

## Thanos Query Enable mTLS

ansible-playbook -i inventory/hosts.yml playbook/thanos_query.yml -e "thanos_query_tls_server_enabled=True" -e "thanos_query_tls_client_enabled=True" 

## Thanos Query Remove

ansible-playbook -i inventory/hosts.yml playbook/thanos_query.yml -e "thanos_query_enabled=False"


