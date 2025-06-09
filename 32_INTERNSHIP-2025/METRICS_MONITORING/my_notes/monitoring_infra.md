# Monitoring infrastructure

- Il existe plusieurs type de supervision :
    - Infrastructure Monitoring
        - Server Monitoring (CPU, Memoire, Stockage, Reseau, DB)
    - Network Monitoring
        - check les connexions entre differents ordinateurs, 
        - check traffic in et out 
    - Cost Monitoring
        - Tracker les ressources utilises par rapport a leur cout
    - App Monitoring
        - check si ca run smoooooothly
    - Log Monitoring
        - identifier les erreurs, problemes potentiels

# Metrics

- *Definition*: 
    - Mesure quantifiable permettant de connaitre la distance entre deux points. Ici, on cherchera a savoir la difference entre un comportement habituel et anormal, sur des valeurs comme : CPU, Memoire, Stockage. On parle bcp de sante du systeme, divers aspect de performance....

## Node_exporter

- Sur chaque machine, le node_exporter expose les metriques systemes, sur le port 9100 (par defaut). Ces metriques sont collectees dans differents fichiers system, souvent dans les dossiers `/sys/`, `/proc` ... 
- Il existe une liste de collectors desactive par defaut (par ex: cgroups, network_route, processes, systemd...) pour differentes causes :  haute cardinalite (grande quantite de valeur avec un faible nb de repetitions), temps d'execution plus long, trop grandes ressources demandees.
- Les metriques sont les suivantes : 
    - Charge sur le CPU
    - Memoire
    - Stockage
    - Bande passante
    - Température
    - Kernel version

    - CPU:
        - node_cpu_seconds_totals : le nombre cumulé de secondes durant lesquelles le CPU a été occupé en mode ... (utilisateur systeme, inactif idle, attente I/O iowait, etc.) sur chaque coeur. 
        - Le mode "steal" est utilisé dans les environnements virtualisés et représente le temps pendant lequel le CPU n'est pas disponible pour une machine virtuelle parce qu'il est utilisé par l'hyperviseur (l'host) pour exécuter d'autres tâches ou pour d'autres VMs.
        - Le mode "idle" = temps d'inactivité du CPU.
        - Le mode "iowait" représente le temps pendant lequel le CPU est inactif car il attend que les opérations d'entrée/sortie (comme l'accès au disque ou au stockage) se terminent.
    
    - Memory: 
        - node_memory_MemAvailable_bytes: Memoire disponible pour les applications, incluant la memoire pouvant etre libéré (cache de pages, buffers). C'est l'estimation de la mémoire libre utilisable par le systeme. 
        - node_memory_MemTotal_bytes: Memoire physique totale de l'hôte (en octets). Correspond à la RAM installé. Peut servir de référence pour calculer les pourcentages d'utilisation mémoire. 
        Mémoire utilisée : MemTotal - MemAvailable. 
    
    - Network:
        - node_network_speed_bytes: détection d'une saturation du lien 

## Blackbox_exporter

- *Définition* : le terme "blackbox" fait référence a la technique de test d'un service sans connaitre son fonctionnement interne. Concrètement, on n'accède qu'à l'interface publique (endpoint) et on examine les réponses obtenues (code HTTP, latence...). Ce type de test permet de simuler la vision d'un utilisateur externe et d'identifier les problèmes de connectivité ou de latence.

- *Blackbox exporter* est un composant complémentaire à Prometheus qui permet d'effectuer des tests "blackbox" de disponibilité de performance et de latence sur divers protocoles (HTTP, TCP, ICMP, DNS...). Il fonctionne en se basant sur des modules configurables qui definissent le type de probe (test) à realiser pour chaque service. On va pouvoir scrapper l'exporter lui meme mais egalement l'exporter qui scrape une ou plusieurs targets. 


## Prometheus

- *Definition*: Collecte les donnees (ici, les metriques) fournis par les node_exporter et autres endpoints, via pull, cloud-native, TSDB stockage, ecoute sur le port 9090.

- Concernant le stockage: 
    - Chaque prometheus ecrit ses blocs TSDB
    - Ecrit en permanence dans un WAL (Write Ahead Log)
    - min-block-duration=2h, il scinde le TSDB toutes les deux heures, ferme un bloc apres les deux heures et en commence un nouveau

- Concernant la haute dispo:
    - 3 prom actif-actif
    - scrape les memes data

- Concernant la config prom.yml: 
    - champs global
    - config alertmanager:
        - labeldrop: Match regex against all label names. Any label that matches will be removed from the set of labels.
    - config rule_files: fichiers yaml des alertes
    - scrape_configs: 1 seul
        - enumerer les jobs
        - scheme: http, https
        - tls_config: 
        - labels: nommer en fonction des elements (IP, instances, job_name etc...) deja pre-stocke par prometheus

- Concernant le type de query: [https://prometheus.io/docs/prometheus/latest/querying/functions/]
    - `rate` : calcule le taux de changements
    - `vector` : ensemble de series temporelles, qui contient une unique valeur
    - `up` : service actif/non-actif
    - `histogram_quantile` : estimer une valeur de quantile. Dans Prometheus, un histogramme génère plusieurs séries de données, chacune correspondant à un bucket défini par un seuil (le label généralement est « le »). Chaque bucket contient le nombre d’observations inférieures ou égales à la valeur du seuil. La fonction histogram_quantile prend en paramètre le quantile désiré (une valeur entre 0 et 1, par exemple 0.95 pour le 95ème percentile) et l’ensemble des buckets (les séries ayant le label « le »). Elle procède à une interpolation linéaire entre les buckets pour estimer la valeur de la métrique pour laquelle la fraction d’observations cumule la proportion donnée par le quantile. Concrètement, elle cherche le bucket tel que la proportion cumulée d’observations atteigne ou dépasse le quantile voulu, puis interpole entre ce bucket et le précédent pour donner une valeur approximative correspondant à ce quantile. EXEMPLE: histogram_quantile(0.95, rate(http_request_duration_seconds_bucket[5m])) permet d’estimer, sur une fenêtre de 5 minutes, la durée en dessous de laquelle se trouvent 95 % des requêtes.
    - `avg` : agrege et fait une moyenne
    - `on` : controle la correspondance des labels lors d'operations arithmethiques
    - `predict_linear`: utilisée pour prédire la valeur future d'une métrique en fonction de son comportement passé.
    - `sum` : agrege et additonne les valeurs, pour obtenir une somme ou un total

- *Limites*
    - Stockage courte duree : de 15 a 30 jours 
    - No HA, necessite deduplication. 
    - Prometheus ne supporte pas de Load Balancing http classique au niveau alertemanager car les AM run en 'gossip cluster' et Prometheus est design pour les envoyer à tout le monde. Prometheus effectue du 'client-side balancing and retries' donc il deduplique les notifications si l'un des serveurs alertmanagers est down. Prometheus doit connaitre la liste des targets pour gérer la résilience mais ne doit pas intéragir avec un seul endpoint distribué.
    - A grande echelle, probleme de surcharge si un seul prom déployé.
    - Pas de cache de requete.

## Alertmanager

- Envoyer des alertes sur des routes différentes : webhook, mail...
- Integrer des silences et les limiter via `--silences.max-silences` flag, disable by default
- Grouper les alertes

- *Limites*
    - Risque de plusieurs notifications lorsque alertmanager est désynchronisé : AM n'a pas encore formé son cluster via les gossip, Prom envoie les alertes a plusieurs instances

## Grafana

cf grafana.md
- Possibilite de creer des organisations
- Creation d'admin, de viewer ou de writer

## Thanos

1. Definition

- Permet de dedupliquer la donnée  
- Centraliser les requêtes faites a prometheus 
- Gestion des pannes et haute dispo
- Prometheus et Sidecars:
    - En cas de panne d'un prom ou de son sidecar, l'autre instance continue de collecter et de servir les metriques.
    - Thanos Query deduplique les donnees provenant de plusieurs sidecars, ce qui permet de maintenir la disponibilite des donnees meme si l'un des sidecars est temporairement indisponible.
    - Les blocs deja uploades sur S3 restent accessibles via le store gateway.

2. Thanos sidecar

- Chaque instance de prometheus est accompagne d'un sidecar, qui tourne a cote de prometheus, mieux car : 
    - Accès local aux données TSDB, sidecar lit les fichiers /data pour uploader les blocs vers S3, donc c'est fiable et sans latence réseau
    - Pas de configuration réseau a effectuer pour des acces distants
    - Simplicité de démarrage, le sidecar et prometheus repartent ensemble, donc pas de pb de désynchronisation ou d'état intermédiaire.
    - Moins de risques de corruption, acces concurrent a la TSDB de prometheus depuis l'extérieur peut être instable.
- Expose les donnees de prometheus en gRPC pour les requetes de thanos query
- Gere upload regulier des blocs de donnees historiques vers S3, protocole d'echange gRPC 
- Frequence reguliere (2h) de collecte, mais possibilite d'utiliser thanos receiver (pas une bonne pratique)

3. Thanos store ou store gateway

- Accede au backend de stockage S3 pour servir les blocs de metrics historiques, donc donnees deja uploades aux requetes de Thanos Query, port par defaut 10902
- Role tres centrale car le querier va venir l'interroger
- Si le store gateway rencontre un probleme les donnees historiques seront temporairement indisponibles, mais les donnees recentes restent accessibles via les sidecars.
- utile si on souhaite des donnees au dela de 2h
- Si tous les prometheus sont down, tous les clients (grafana par ex) peuvent requeter les blocs via le store sauf les 2h de collecte

4. Thanos query

- Interprete le promql fournit
- Agrege et deduplique les donnees provenant des differents prometheus via leurs sidecars ainsi que celles recuperees du store gateway, cela veut dire qu'il identifie les series identiques sauf pour le label replica, considere qu'elles sont les memes et n'en garde qu'une seule. Il choisit de cette facon :
    - La serie avec le plus grand nombre de samples dans la periode de requete
    - si egalite, il choisit la serie avec la source la plus rapide
    - en fonction de l'ordre d'apparition dans le store
- Propose une interface de requete unique pour les outils de visualisation, port par defaut 9090
- Thanos query est stateless, ca veut dire qu'il ne conserve aucun etat interne entre les requetes. Aucune info d'etat n'est stocke localement, il est simple d'ajouter ou de retirer des instances de thanos query sans necessiter de synchronisation de transfert de donnees d'etat. En bref, les instances ne dependent pas d'un etat partage.
- Thanos query peut etre redemarre rapidement ou replique derriere un load balancer, NLB.

5. Thanos compactor

- Responsable de la compaction, de la rétention des données, du downsampling et de la gestion des uploads partiels.
- Compaction : reduction nb de blocs = performances de lecture + requete donc fusionne les blocs TSDB, par ex: plusieurs blocs de 2h en 1 bloc de 24h
- Downsample les data pour améliorer les performances des longues requêtes
- Retention : supprime les data obsoletes selon la rétention définie + nettoie le bucket S3 et garde une structure optimisée
- Supporte la depduplication de data, utile pour eviter les doublons, notamment dans les scenarios de backfilling (Lors du backfilling, il est courant d'avoir des blocs de données qui se chevauchent dans le temps. Thanos supporte la compaction verticale, qui permet de fusionner ces blocs chevauchants en un seul bloc cohérent) ou de replication (processus de copier des données à travers plusieurs instances ou systèmes pour assurer la redondance et la haute disponibilité)
- Doit etre unique par bucket car plusieurs compactors peuvent provoquer des corruptions 
- Bien repartir en fonction des bonnes instances prom (via replica A ou B)

  --retention.resolution-raw=30d \ # Conservation data brutes 30 jours pour analyse detaillees et diagnostics rapides
  --retention.resolution-5m=180d \ # Conservation data downsamplées à une resolution de 5 minutes pdt 180 jours analyse moyen terme
  --retention.resolution-1h=1y \ # Conservation data downsamplées a une resolution de 1h pdt 1an pour du long terme
  --delete-delay=48h \ # Delai avant la suppression effective des blocs marques
  --compact.concurrency=2 \ # Controle le nb de go routines utilisees pour compacter les groupes 
  --compact.progress-interval=5m \ # Frequence a laquelle le progres de la compaction est calcule
  --enable-auto-gomemlimit \ 

- Verifier:
    thanos_objstore_bucket_operation_failures_total : Nombre total d'échecs d'opérations sur le bucket.
    thanos_objstore_bucket_operation_duration_seconds : Durée des opérations sur le bucket.
    thanos_compact_groups : Nombre de groupes de compaction.

6. Thanos Rule

- *Definition*:

7. Limites

- Consommation de ressources importantes
- Si perte d'1 prometheus, on perd 2h de donnees car frequence reguliere sauf s'il y en a un autre

# Logs

- *Definition*: 
    - Enregistrements séquentiels d’événements et des messages produits par un système ou une application. Ils fournissent des détails spécifiques sur ce qui s’est passé à un moment donné. Les logs sont particulièrement utiles pour le débogage, la recherche d’erreurs et la compréhension du flux d’exécution d’une application. Ils contiennent souvent des informations sur les exceptions, les messages d’erreur, les transactions réussies, etc.

1. ELK
    - Logstash : collecter et transformer
    - ElasticSearch : chercher et analyser
    - Kibana : visualiser et manager

- Avec ces 3 technos:
    - **Indexing et Stockage**: index full text of logs, more granular search, utilise un index inverse qui facilite la recherche. cout eleve en stockage et ressource
    - **Scalability** : ajout de nodes par logstash et scaled en distribuant les logs a travers multiple instances. 
    - **Querying et Visualisation** : robuste query language KQL, bon dashboard.
    - **Ease of Use** : un peu complexe car il y a plusieurs techno a interconnecte
    - **Cout** : depend du nb de machine

2. Grafana + Loki
    - Promtail : agent responsable de collecter les logs et les push sur le serveur Loki
    - Loki Server : enregistre et index les logs
    - Grafana : outil de visu integre avec Loki pour querying et afficher log data

- Avec ces 2 technos:
    - **Indexing et Stockage**: index seulement metadata, tres efficace en terme de stockage et de ressource. Grand volume de log ? Log sont stocke de maniere similaire a Prometheus, en chunk, et index par labels donc key-values.
    - **Scalability**: Large volume de log avec une infra tres faible en cout, mais struggle sur les grands volumes
    - **Querying et Visualisation** : bon dashboards + grafana query language LogQL
    - **Ease of Use** : apparemment simple
    - **Cout** : low

