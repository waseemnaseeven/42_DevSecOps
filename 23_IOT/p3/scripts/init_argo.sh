#!/bin/bash

kubectl create namespace argocd && kubectl create namespace dev

kubectl apply -n argocd -f https://raw.githubusercontent.com/argoproj/argo-cd/stable/manifests/install.yaml

# kubectl config to use the newCluster
# kubectl config use-context k3d-newCluster

kubectl port-forward svc/argocd-server -n argocd 8080:443

# Username is "admin"

#For the password
kubectl get secret argocd-initial-admin-secret -n argocd -o yaml | grep "password" | awk '{ print $2 }' | base64 --decode
