#!/bin/bash

# Définition des variables
VM_NAME="MaMachineVirtuelle"
ISO_PATH="/mnt/nfs/homes/wnaseeve/sgoinfre/ubuntu-22.04.3-desktop-amd64.iso"
VM_MEMORY=2048  # Mémoire en Mo
VM_CPU=2        # Nombre de CPU
VM_HDD_SIZE=20000  # Taille du disque en Mo

# Créer la machine virtuelle
VBoxManage createvm --name "$VM_NAME" --ostype "Ubuntu_64" --register

# Configurer les ressources de la machine virtuelle
VBoxManage modifyvm "$VM_NAME" --memory "$VM_MEMORY"
VBoxManage modifyvm "$VM_NAME" --cpus "$VM_CPU"

# Créer un disque dur virtuel
VBoxManage createhd --filename "$VM_NAME.vdi" --size "$VM_HDD_SIZE"

# Attacher le disque dur virtuel à la machine virtuelle
VBoxManage storagectl "$VM_NAME" --name "SATA Controller" --add sata --controller IntelAHCI
VBoxManage storageattach "$VM_NAME" --storagectl "SATA Controller" --port 0 --device 0 --type hdd --medium "$VM_NAME.vdi"

# Ajouter le lecteur de DVD pour l'ISO d'installation
VBoxManage storagectl "$VM_NAME" --name "IDE Controller" --add ide
VBoxManage storageattach "$VM_NAME" --storagectl "IDE Controller" --port 0 --device 0 --type dvddrive --medium "$ISO_PATH"

# Démarrer la machine virtuelle
VBoxManage startvm "$VM_NAME"

# Attendre que la machine virtuelle soit éteinte
while [ "$(VBoxManage showvminfo --machinereadable "$VM_NAME" | grep "VMState=" | cut -d'=' -f2)" != "poweroff" ]; do
    sleep 2
done

# Détacher le lecteur de DVD
VBoxManage storageattach "$VM_NAME" --storagectl "IDE Controller" --port 0 --device 0 --type dvddrive --medium "emptydrive"

# Redémarrer la machine virtuelle
VBoxManage startvm "$VM_NAME"

# Nettoyer les fichiers temporaires
rm "$VM_NAME.vdi"

echo "La machine virtuelle Ubuntu est prête !"
