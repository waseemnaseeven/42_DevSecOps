#!/bin/bash

PURPLE="\033[35m"
GREEN="\33[32m"
RED="\033[31m"
RESET="\033[0m"

echo -e "${GREEN} ~~  CREATING NAMESPACES ~~ ${RESET}"
kubectl create namespace argocd && kubectl create namespace dev

echo -e "${GREEN} ~~ CREATING ARGOCD ~~ ${RESET}"
kubectl apply -n argocd -f https://raw.githubusercontent.com/argoproj/argo-cd/stable/manifests/install.yaml

echo -e "${GREEN} ~~ USE THE CLUSTER wnaseeve ~~ ${RESET}"
kubectl config use-context wnaseeve

echo -e "${GREEN} ~~ LETS ACCESS THE ARGOCD SERVER ~~ ${RESET}"

echo -e "${PURPLE} ~~ 1) kubectl get secret argocd-initial-admin-secret -n argocd -o yaml | grep "password" | awk '{ print $2 }' | base64 --decode ~~ ${RESET}"
echo -e "${PURPLE} ~~ 2) (Username is 'admin') argocd login localhost:7447 ~~ ${RESET}"

sleep 15

echo -e "${PURPLE} ~~ 3) kubectl port-forward svc/argocd-server -n argocd 7447:443 ~~ ${RESET}"