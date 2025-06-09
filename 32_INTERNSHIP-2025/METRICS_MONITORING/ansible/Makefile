ANSIBLE_PLAYBOOK = ansible-playbook
INVENTORY = -i inventory/hosts.yml
PLAYBOOK_DIR = playbook

# -------------- Targets -------------- #

exporters: node_exporter_tls blackbox_tls

monitoring_stack: prometheus_mtls alertmanager_gossip grafana 

thanos_stack: prometheus_sidecar thanos_store thanos_query thanos_rule 

monitoring_stack_HA: prometheus_sidecar thanos_store thanos_query thanos_rule  alertmanager_gossip grafana

# -------- Clean / Helpers -------- #

remove_exporters: remove_node_exporter remove_blackbox

remove_monitoring_stack: remove_alertmanager remove_prometheus remove_grafana

remove_monitoring_stack_HA: remove_store remove_query remove_compactor remove_rule remove_prometheus remove_alertmanager remove_grafana

# -------- haproxy -------- #

haproxy:
	@echo "$(_ORANGE)Exécution du playbook haproxy$(_NO)"
	$(ANSIBLE_PLAYBOOK) $(INVENTORY) $(PLAYBOOK_DIR)/haproxy.yml

# -------- keepalived -------- #

keepalived:
	@echo "$(_ORANGE)Exécution du playbook keepalived$(_NO)"
	$(ANSIBLE_PLAYBOOK) $(INVENTORY) $(PLAYBOOK_DIR)/keepalived.yml

# -------- ntp -------- #

ntp_server:
	@echo "$(_ORANGE)Exécution du playbook ntp$(_NO)"
	$(ANSIBLE_PLAYBOOK) $(INVENTORY) $(PLAYBOOK_DIR)/ntp.yml

# -------- ntp clients -------- #

ntp_client:
	@echo "$(_ORANGE)Exécution du playbook ntp client$(_NO)"
	$(ANSIBLE_PLAYBOOK) $(INVENTORY) $(PLAYBOOK_DIR)/ntp_client.yml

# -------- Certificates -------- #

certificates:
	@echo "$(_ORANGE)Exécution du playbook certificates$(_NO)"
	$(ANSIBLE_PLAYBOOK) $(INVENTORY) $(PLAYBOOK_DIR)/generate_certificate.yml

# -------- Alertmanager -------- #

alertmanager:
	@echo "$(_ORANGE)Exécution du playbook alertmanager.yml en HTTP$(_NO)"
	$(ANSIBLE_PLAYBOOK) $(INVENTORY) $(PLAYBOOK_DIR)/alertmanager.yml

alertmanager_tls:
	@echo "$(_ORANGE)Exécution du playbook alertmanager.yml avec TLS$(_NO)"
	$(ANSIBLE_PLAYBOOK) $(INVENTORY) $(PLAYBOOK_DIR)/alertmanager.yml -e "alertmanager_tls_server_enabled=True"

alertmanager_mtls:
	@echo "$(_ORANGE)Exécution du playbook alertmanager.yml avec mTLS$(_NO)"
	$(ANSIBLE_PLAYBOOK) $(INVENTORY) $(PLAYBOOK_DIR)/alertmanager.yml -e "alertmanager_tls_server_enabled=True" -e "alertmanager_tls_client_enabled=True"

alertmanager_gossip:
	@echo "$(_ORANGE)Exécution du playbook alertmanager.yml avec mTLS et gossip tls$(_NO)"
	$(ANSIBLE_PLAYBOOK) $(INVENTORY) $(PLAYBOOK_DIR)/alertmanager.yml -e "alertmanager_tls_server_enabled=True" -e "alertmanager_tls_client_gossip=True"

remove_alertmanager:
	@echo "$(_RED)Suppression d'Alertmanager$(_NO)"
	$(ANSIBLE_PLAYBOOK) $(INVENTORY) $(PLAYBOOK_DIR)/alertmanager.yml -e "alertmanager_enabled=False"

# -------- Node Exporter -------- #

node_exporter:
	@echo "$(_ORANGE)Exécution du playbook node_exporter.yml en HTTP$(_NO)"
	$(ANSIBLE_PLAYBOOK) $(INVENTORY) $(PLAYBOOK_DIR)/node_exporter.yml

node_exporter_tls:
	@echo "$(_ORANGE)Exécution du playbook node_exporter.yml avec TLS$(_NO)"
	$(ANSIBLE_PLAYBOOK) $(INVENTORY) $(PLAYBOOK_DIR)/node_exporter.yml -e "node_exporter_tls_server_enabled=True"

remove_node_exporter:
	@echo "$(_RED)Suppression de Node Exporter$(_NO)"
	$(ANSIBLE_PLAYBOOK) $(INVENTORY) $(PLAYBOOK_DIR)/node_exporter.yml -e "node_exporter_enabled=False"

# -------- Blackbox -------- #

blackbox:
	@echo "$(_ORANGE)Exécution du playbook blackbox.yml en HTTP$(_NO)"
	$(ANSIBLE_PLAYBOOK) $(INVENTORY) $(PLAYBOOK_DIR)/blackbox.yml

blackbox_tls:
	@echo "$(_ORANGE)Exécution du playbook blackbox.yml avec TLS$(_NO)"
	$(ANSIBLE_PLAYBOOK) $(INVENTORY) $(PLAYBOOK_DIR)/blackbox.yml -e "blackbox_tls_server_enabled=True"

remove_blackbox:
	@echo "$(_RED)Suppression de Blackbox$(_NO)"
	$(ANSIBLE_PLAYBOOK) $(INVENTORY) $(PLAYBOOK_DIR)/blackbox.yml -e "blackbox_enabled=False"

# -------- Prometheus -------- #

prometheus:
	@echo "$(_ORANGE)Exécution du playbook prometheus.yml en HTTP$(_NO)"
	$(ANSIBLE_PLAYBOOK) $(INVENTORY) $(PLAYBOOK_DIR)/prometheus.yml

prometheus_tls:
	@echo "$(_ORANGE)Exécution du playbook prometheus.yml avec TLS$(_NO)"
	$(ANSIBLE_PLAYBOOK) $(INVENTORY) $(PLAYBOOK_DIR)/prometheus.yml -e "prometheus_tls_server_enabled=True"

prometheus_mtls:
	@echo "$(_ORANGE)Exécution du playbook prometheus.yml avec mTLS$(_NO)"
	$(ANSIBLE_PLAYBOOK) $(INVENTORY) $(PLAYBOOK_DIR)/prometheus.yml -e "prometheus_tls_server_enabled=True" -e "prometheus_tls_client_enabled=True"

prometheus_sidecar:
	@echo "$(_ORANGE)Exécution du playbook prometheus.yml avec sidecar (HA)$(_NO)"
	$(ANSIBLE_PLAYBOOK) $(INVENTORY) $(PLAYBOOK_DIR)/prometheus.yml -e "prometheus_tls_server_enabled=True" -e "prometheus_tls_client_enabled=True" -e "prometheus_sidecar_enabled=True"

remove_prometheus:
	@echo "$(_RED)Suppression de Prometheus$(_NO)"
	$(ANSIBLE_PLAYBOOK) $(INVENTORY) $(PLAYBOOK_DIR)/prometheus.yml -e "prometheus_enabled=False"

# -------- Grafana -------- #

grafana:
	@echo "$(_ORANGE)Exécution du playbook grafana.yml$(_NO)"
	$(ANSIBLE_PLAYBOOK) $(INVENTORY) $(PLAYBOOK_DIR)/grafana.yml

grafana_datasource:
	@echo "$(_ORANGE)Exécution du playbook grafana.yml (HA)$(_NO)"
	$(ANSIBLE_PLAYBOOK) $(INVENTORY) $(PLAYBOOK_DIR)/grafana.yml -e "grafana_datasource=True"

remove_grafana:
	@echo "$(_RED)Suppression de Grafana$(_NO)"
	$(ANSIBLE_PLAYBOOK) $(INVENTORY) $(PLAYBOOK_DIR)/grafana.yml -e "grafana_enabled=False"

# -------- Thanos Store -------- #

thanos_store:
	@echo "$(_ORANGE)Exécution du playbook thanos_store.yml$(_NO)"
	$(ANSIBLE_PLAYBOOK) $(INVENTORY) $(PLAYBOOK_DIR)/thanos_store.yml -e "thanos_tls_server_enabled=True" -e "thanos_tls_client_enabled=True"

remove_store: 
	@echo "$(_RED)Suppression de thanos_store$(_NO)"
	$(ANSIBLE_PLAYBOOK) $(INVENTORY) $(PLAYBOOK_DIR)/thanos_store.yml -e "thanos_store_enabled=False"

# -------- Thanos Query -------- #

thanos_query:
	@echo "$(_ORANGE)Exécution du playbook thanos_query.yml$(_NO)"
	$(ANSIBLE_PLAYBOOK) $(INVENTORY) $(PLAYBOOK_DIR)/thanos_query.yml -e "thanos_tls_server_enabled=True" -e "thanos_tls_client_enabled=True"

remove_query: 
	@echo "$(_RED)Suppression de thanos_query$(_NO)"
	$(ANSIBLE_PLAYBOOK) $(INVENTORY) $(PLAYBOOK_DIR)/thanos_query.yml -e "thanos_query_enabled=False"

# -------- Query Frontend -------- #

query_frontend:
	@echo "$(_ORANGE)Exécution du playbook query frontend.yml$(_NO)"
	$(ANSIBLE_PLAYBOOK) $(INVENTORY) $(PLAYBOOK_DIR)/query_frontend.yml 

remove_query_frontend: 
	@echo "$(_RED)Suppression de query frontend$(_NO)"
	$(ANSIBLE_PLAYBOOK) $(INVENTORY) $(PLAYBOOK_DIR)/query_frontend.yml -e "thanos_query_enabled=False"


# -------- Thanos Compactor -------- #

thanos_compactor:
	@echo "$(_ORANGE)Exécution du playbook thanos_compactor.yml$(_NO)"
	$(ANSIBLE_PLAYBOOK) $(INVENTORY) $(PLAYBOOK_DIR)/thanos_compactor.yml -e "thanos_tls_server_enabled=True" -e "thanos_tls_client_enabled=True"

remove_compactor: 
	@echo "$(_RED)Suppression de thanos_compactor$(_NO)"
	$(ANSIBLE_PLAYBOOK) $(INVENTORY) $(PLAYBOOK_DIR)/thanos_compactor.yml -e "thanos_compactor_enabled=False"

# -------- Thanos Rule -------- #

thanos_rule:
	@echo "$(_ORANGE)Exécution du playbook thanos_rule.yml$(_NO)"
	$(ANSIBLE_PLAYBOOK) $(INVENTORY) $(PLAYBOOK_DIR)/thanos_rule.yml -e "thanos_tls_server_enabled=True" -e "thanos_tls_client_enabled=True"

remove_rule: 
	@echo "$(_RED)Suppression de thanos_rule$(_NO)"
	$(ANSIBLE_PLAYBOOK) $(INVENTORY) $(PLAYBOOK_DIR)/thanos_rule.yml -e "thanos_rule_enabled=False"

# ----------- PHONY ----------- #

.PHONY: all all_ha alertmanager alertmanager_tls alertmanager_mtls remove_alertmanager \
	node_exporter node_exporter_tls node_exporter_mtls remove_node_exporter \
	prometheus prometheus_tls prometheus_mtls prometheus_sidecar remove_prometheus \
	grafana remove_grafana thanos_store thanos_query thanos_compactor clean

# -------------- Syntaxing -------------- #
_NO                    = \033[0m
_BOLD                  = \033[1m
_BLUE                  = \033[34m
_CYAN                  = \033[36m
_RED                   = \033[31m
_PURPLE                = \033[35m
_PINK_ORANGE           = \033[38;5;215m
_GREY                  = \033[38;5;234m
_STARLIGHT_BLUE        = \033[38;5;158m
_STARLIGHT_GREEN       = \033[38;5;157m
_DEEP_BLUE             = \033[38;5;69m
_YELLOW                = \033[38;5;226m
_ORANGE                = \033[38;5;209m\e[1m
# ------------------------------------- #