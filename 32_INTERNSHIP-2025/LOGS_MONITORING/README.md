# MONITORING DES LOGS

## Types de log

1. Logs systeme 

- *Description*: Logs sys d'exploitation enregistrant les evenements du systeme (demarrage, arrets, errors...) et healthcheck des services, permet de verifier le fonctionnement correct des processus et du materiel mais egalement la securite, regroupant les evenements d'authentification, d'acces, et les alertes d'intrusion ou de violation de politique... tentative d'acces non autorise, comportements suspects.

- *Exemples concrets*: 
    - syslog indiquant l'execution d'une tache planifie
    - log kernel 
    - log sur temperature CPU
    - log d'authentification sur un serveur linux signant un echec de connexion SSH
    - log parefeu
    - log anti virus

- *Outils/Services generant ce type de logs*: 
    - syslog
    - journald (centralise log kernel, sshd, sudo, avec leur metadata)
    - daemon
    - SSH
    - Active Directory
    - iptables
    - UFW ou autre pare-feu
    - IDS/IPS

2. Logs de Web Server

- *Description*: log http server conservant la trace des requetes client et des erreurs cote serveurs web. Ils servent a analyser le trafic et diag les pb applicatifs lies au Web.

- *Exemples concrets*: 
    - log indiquant une requete http avec IP client, URL, code http, bytes sent, User-Agent [Access Log]
    - log errors : file not found, 500 internal server error [Error Log]

- *Outils/Services generant ce type de logs*: 
    - NGINX
    - Apache

3. Logs applicatifs

- *Description*: log applications metiers decrivant le deroulement de l'execution du code, transaction effectues (s'il y a), erreurs rencontres. Visibilite sur le comportement interne des applications (state, evenements metier).

- *Exemples concrets*: 
    - Trace d'exception, indiquant erreur et sa cause (NullPointerException...)
    - Un log fonctionnel dans une application web "Utilisateur X cree"

- *Outils/Services generant ce type de logs*:
    - API Node.js 
    - App django Python
    - tout programme qui ecrit des logs soit dans des fichiers (app.log) 
    - tout programme qui ecrit vers la stdout, stdout environnement conteneurise
    - tout framework de logging (Log4j, Winston) 

4. Logs Database

- *Description*: log database qui record les requete SQL executes, les modifications de donnees, et eventuelles erreur. Ils aident a diag les pb de performances ou integrite des donnees.

- *Exemples concrets*: 
    - requete trop lente, depassement du seuil timeout, slow query
    - echecs de connexion
    - erreur interne
    - table corrompue
    - transaction echoue retracant les modif pour replication ou recuperation apres incident

- *Outils/Services generant ce type de logs*:
    - Postgres
    - SQL : log errur, log request, log slow request

6. Log de reseau

- *Description*: log des equipenets ou services reseau retracant les flux de donnees, connexions et evenem,etns du reseau. Surveiller la connectivite, les performances reseau et de detecter les problemes.

- *Exemples concrets*: 
    - log de pare-feu qui bloque un pacquet
    - log routeur
    - log proxy web

- *Outils/Services generant ce type de logs*: 
    - parefeu
    - iptables
    - routeurs
    - switch
    - loadbalancer
    - serveur dns
    - proxies (squid)

7. Log conteneur et orchestrateur

- *Description*: log lies aux environnement Docker et K8s

- *Exemples concrets*: 
    - logs de conteneurs produits par les applications a l'interieur des conteneurs generalement via stdout/stderr
    - log du cluster, logs des composants (pods, services)

- *Outils/Services generant ce type de logs*: 
    - Docker/containerd logs docker daemon, output conteneur
    - Kubernetes avec cluster events, log composants maitre comme api-server, scheduler, kubelet. Par defaut Kubernetes stocke les logs de conteneurs sur chaque noeud (/var/log/containers/*) et events cluster via `kubectl get events` des outils comme `FileBeat`/`Fluentd` peuvent collecter et centraliser ces logs vers ELK.

## Stack monitoring de logs 

### Choix de collecteur de logs 

- Logstash
    - Avantages:
        - ETL (Extract Transform Load)
        - Input/Filter/Output
        - nbr plugin d'entree (nginx, postgres...)
        - filtres et grok
        - injection dans elasticsearch
    - Inconvenients:
        - grosse consommation en ressources
        - temps de demarrage et arrets + long

- Fluentbit:
    - Avantages: 
        - leger en memoire, quelques mega octets
        - ecrite en C
        - integration native k8s
        - supporte traitement en flux (SQL) et la plupart des filtres (grok basique, regex, multiline)
        - projet open-source tres actif et communaute DevOps large, adopte par de grands cloud providers (AWS pour son agent CloudWatch Logs dans EKS, GCP...)
    - Inconvenients:
        - legerement moins extensible que fluentd/logstash
        - moins de plugins disponible (moins de 100 vs plus de 100 pour fluentd)
        - pas de filtrage grok aussi puissant que logstash
        - en sortie, il ne tire pas parti des pipelines ingest d'elastic, oblige de faire des call HTTP

- Filebeat:
    - Avantages:
        - leger, specialement optimise pour fonctionner en agent sur tous types de serveurs
        - ecrite en Go
        - module system de filebeat va lire journald ou /var/log/auth.log et /var/log/syslog 
        - fourni pipeline Elasticsearch pour parser les msgs SSH, sudo, kern.log 
        - Integration native avec elastic search 
    - Inconvenients:
        - moins puissant en transformation locale que fluentd/logstash 
        - possibilites de parsing limitees
        - concu pour elastic search only a priori (?)


### Data base : Elastic Search

- Base de donnees nosql: facilite systeme distribue a tres large echelle
- forte volumetries
- specialiste recherche plain text
- index/sharding/replicas de tous les mots des documents
- moteur Lucene
- API REST json
- haute dispo
- communication via port 9300
- noeud est un serveur ayant un service elastic, differents type: master, data, client
- index est une instance de database
- shards est un decoupage logique d'un index 
- replicas sont les replicas de shards d'un index : redondance, mais aussi performance
- capacite a ecrire des TAGS pour differencier

### Kibana

- Visualisation et requetes
- Specialiste des donnees ElasticSearch
- dashboard
- concurrence grafana
