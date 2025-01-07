FROM frrouting/frr:v8.2.2

# Bash using
RUN apk update 
RUN apk add --no-cache bash util-linux

WORKDIR /etc/frr

COPY daemons.conf /etc/frr/daemons

# # Démarrer les services FRR
# ENTRYPOINT ["/bin/bash", "-c", "/usr/lib/frr/docker-start & tail -f /dev/null"]
