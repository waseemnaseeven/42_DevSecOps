#!/bin/bash

kubectl config set-context --current --namespace=argocd

argocd app create wil-playground --repo https://github.com/waseemnaseeven/wnaseeve-configk8s.git --path wil_app --dest-server https://kubernetes.default.svc --dest-namespace dev

argoccd app sync wil-playground

echo "--sync policies--"
argocd app set wil-playground --sync-policy automated
argocd app set wil-playground --auto-prune
argocd app set wil-playground --self-heal

echo "--display application infos--"
argocd app get wil-playground

echo "--set current context changing current context--"
kubectl config set-context --current --namespace=dev

kubectl port-forward wil-playground-d44c7f4fc-zsrx5 8888:81