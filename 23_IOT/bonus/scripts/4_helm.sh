#!/bin/bash

curl -fsSL -o get_helm.sh https://raw.githubusercontent.com/helm/helm/master/scripts/get-helm-3
chmod 755 get_helm.sh
./get_helm.sh
rm get_helm.sh


kubectl create namespace gitlab
helm install gitlab gitlab/gitlab \
  --set global.hosts.domain=gitlab.wnaseeve.fr \
  --set certmanager-issuer.email=wnaseeve@student.42.fr \
  --set global.hosts.https="false" \
  --set global.ingress.configureCertmanager="false" \
  --set gitlab-runner.install="false" \
  --set nginx-ingress.controller.hostNetwork=true \
  --set nginx-ingress.controller.kind=DaemonSet \
  --namespace=gitlab

kubectl get secret --namespace=gitlab gitlab-gitlab-initial-root-password -ojsonpath='{.data.password}' | base64 --decode ; echo

kubectl wait -n gitlab --for=condition=available deployment --all --timeout=-1s && echo ok

# gitlabT glpat-yfRExLcy5G_yLAZbBwCW