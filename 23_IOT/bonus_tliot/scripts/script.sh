#!/bin/bash

PURPLE="\033[35m"
GREEN="\033[32m"
RED="\033[31m"
RESET="\033[0m"


PORT_ARGOCD=30443

NAMESPACES_ARGOCD="argocd"
NAMESPACES_DEV="dev"

# ---- CONFIG ---- #

# echo -e "${GREEN} ~~  INSTALLING EVERY TOOLS ~~ ${RESET}"
# sudo apt-get update -y
# sudo apt-get install vim git curl ncdu -y 
# 
# 
# echo -e "${GREEN} ~~  INSTALLING DOCKER ~~ ${RESET}"
# curl -fsSL https://get.docker.com -o get-docker.sh
# sh get-docker.sh
# sudo chmod 666 /var/run/docker.sock
# rm get-docker.sh
# 
# echo -e "${GREEN} ~~  INSTALLING KUBECTL ~~ ${RESET}"
# curl -LO "https://dl.k8s.io/release/$(curl -L -s https://dl.k8s.io/release/stable.txt)/bin/linux/amd64/kubectl"
# chmod +x kubectl
# sudo mv kubectl /usr/local/bin
# 
# 
# echo -e "${GREEN} ~~  INSTALLING K3D ~~ ${RESET}"
# curl -s https://raw.githubusercontent.com/k3d-io/k3d/main/install.sh | bash
# mkdir -p ~/.kube
# touch ~/.kube/config
# 
# echo -e "${GREEN} ~~  INSTALLING ARGOCD ~~ ${RESET}"
# 
# curl -sSL -o argocd-linux-amd64 https://github.com/argoproj/argo-cd/releases/latest/download/argocd-linux-amd64 
# sudo install -m 555 argocd-linux-amd64 /usr/local/bin/argocd
# rm argocd-linux-amd64


echo -e "${PURPLE} ~~  K3S CONTAINER CLUSTER CREATION WITH K3D ~~ ${RESET}"
k3d cluster create wnaseeve --port "8081:80@loadbalancer" --kubeconfig-update-default 
k3d cluster start wnaseeve

export KUBECONFIG=$(k3d kubeconfig write wnaseeve)

# ---- CREAT NAMESPACES ---- #

echo -e "${PURPLE} ~~  CREATING NAMESPACES ~~ ${RESET}"
kubectl create namespace $NAMESPACES_ARGOCD 
kubectl create namespace $NAMESPACES_DEV

#---- LAUNCH ARGOCD ---- #

echo -e "${PURPLE} ~~ CREATING ARGOCD ~~ ${RESET}"


kubectl apply -n $NAMESPACES_ARGOCD -f https://raw.githubusercontent.com/argoproj/argo-cd/stable/manifests/install.yaml
kubectl apply -f ../confs/argocd-service.yaml

NODE_IP=$(kubectl get nodes -o wide | awk '/master/ {print $6}')
echo -e "${GREEN} ~~  SERVER IP:PORT https://$NODE_IP:$PORT_ARGOCD ~~ ${RESET}"

echo -e "${PURPLE} ~~ LETS ACCESS THE ARGOCD SERVER ~~ ${RESET}"

kubectl rollout status deployment/argocd-server -n $NAMESPACES_ARGOCD --timeout=160s
sleep 10
ARGOCD_PASSWORD=$(kubectl get secret argocd-initial-admin-secret -n $NAMESPACES_ARGOCD -o yaml | grep 'password' | awk '{ print $2 }' | base64 --decode)
argocd login $NODE_IP:$PORT_ARGOCD --username admin --password $ARGOCD_PASSWORD --insecure
echo $ARGOCD_PASSWORD


#--- GITLAB ---#

echo -e "${GREEN} ~~ INSTALLING HELM ~~ ${RESET}"

curl -fsSL -o get_helm.sh https://raw.githubusercontent.com/helm/helm/master/scripts/get-helm-3
chmod 755 get_helm.sh
./get_helm.sh

rm get_helm.sh
echo -e "${GREEN} ~~ CREATING GITLAB NAMESPACE AND CHANGING CONTEXT ~~ ${RESET}"
kubectl create namespace gitlab
kubectl config set-context --current --namespace=gitlab

helm repo add gitlab https://charts.gitlab.io
helm repo update

kubectl apply -f https://raw.githubusercontent.com/kubernetes/ingress-nginx/main/deploy/static/provider/cloud/deploy.yaml

helm install gitlab gitlab/gitlab \
    --namespace gitlab \
    --set global.hosts.domain=wnaseeve.local \
    --set global.hosts.externalIP=0.0.0.0 \
    --set global.hosts.https=false \
    --set service.type=NodePort \
    --set service.nodePort.http=30080 \
    --set service.nodePort.ssh=30022 \
    --timeout 600s 

kubectl get secret gitlab-gitlab-initial-root-password -ojsonpath='{.data.password}' | base64 --decode ; echo

echo -e "${RED} ~~ LETS CONNECT TO MY LOCAL GITLAB ~~ ${RESET}"

echo -e "${RED} ~~ LETS START SYNC GITLAB REPO AND ARGO IN OUR CLUSTER KUBERNETES ~~ ${RESET}"

kubectl config set-context --current --namespace=argocd

echo -e "${GREEN} ~~ apply yaml file ~~ ${RESET}"

echo -e "${PURPLE} go to /bonus and /confs and kubectl apply -f deployment.yaml ${RESET}"
kubectl apply -f ../confs/deployment.yaml
sleep 10

echo -e "${GREEN} ~~ display application infos ~~ ${RESET}"
argocd app get bonus
