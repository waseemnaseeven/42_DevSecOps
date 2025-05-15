# Kind installation

[ $(uname -m) = x86_64 ] && curl -Lo ./kind https://kind.sigs.k8s.io/dl/v0.27.0/kind-linux-amd64

chmod +x ./kind

mv ./kind /usr/local/bin/kind

# Kubectl

curl -LO "https://dl.k8s.io/release/$(curl -L -s https://dl.k8s.io/release/stable.txt)/bin/linux/amd64/kubectl"
curl -LO "https://dl.k8s.io/release/$(curl -L -s https://dl.k8s.io/release/stable.txt)/bin/linux/amd64/kubectl.sha256"

# Helm 

curl -fsSL -o get_helm.sh https://raw.githubusercontent.com/helm/helm/master/scripts/get-helm-3
chmod 755 get_helm.sh
./get_helm.sh

# Docker

curl -fsSL https://get.docker.com -o get-docker.sh
sh get-docker.sh
sudo chmod 666 /var/run/docker.sock
rm get-docker.sh

# Creation fichier de config, voir confs/kind-config.yml
# Creation cluster 

kind create cluster --name wnaseeve --config kind-config.yaml

# Deploiement argocd

kubectl create namespace argocd
kubectl config set-context --current --namespace=argocd

# Deployer les manifests officiels

kubectl apply -n argocd -f https://raw.githubusercontent.com/argoproj/argo-cd/stable/manifests/install.yaml

# Acces a l'UI

kubectl port-forward svc/argocd-server -n argocd 8080:443

# Recuperer le mot de passe initial

kubectl get secret argocd-initial-admin-secret -n argocd \
  -o jsonpath='{.data.password}' | base64 --decode

# Creation gitlab

kubectl create namespace gitlab
kubectl config set-context --current --namespace=gitlab

# Ajouter le repo helm

helm repo add gitlab https://charts.gitlab.io/
helm repo update

# Installer ou mettre a jour Gitlab

helm upgrade --install gitlab gitlab/gitlab \
  --namespace gitlab \
  --timeout 600s \
  --values https://gitlab.com/gitlab-org/charts/gitlab/-/raw/master/examples/values-minikube-minimum.yaml \
  --set global.hosts.domain=localgitlab.com \
  --set global.hosts.externalIP=0.0.0.0 \
  --set global.hosts.https=false

# Recuperer le mdp root

kubectl get secret gitlab-gitlab-initial-root-password \
  -n gitlab -o jsonpath='{.data.password}' | base64 --decode


# SOURCES
https://surajsoni3332.medium.com/setting-up-elk-stack-on-kubernetes-a-step-by-step-guide-227690eb57f4
https://betterstack.com/community/guides/scaling-docker/kind/
https://www.blueshoe.io/blog/minikube-vs-k3d-vs-kind-vs-getdeck-beiboot/
https://www.linuxactionshow.com/kind-vs-minikube/
https://shashanksrivastava.medium.com/install-configure-argo-cd-on-kind-kubernetes-cluster-f0fee69e5ac4