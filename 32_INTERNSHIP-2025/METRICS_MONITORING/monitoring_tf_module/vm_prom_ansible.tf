/*
    data, permet aux utilisateurs d'utiliser une data source particuliere
    ici, on filtre selon certains criteres pour trouver le bon OS
*/

data "outscale_image" "image01" {
    filter {
        name   = "image_names" 
        values = ["Ubuntu-24.04-2024.11.28-0"]
    }
}

/*
    Creation d'une VM:
        - identifier l'id de l'image, data source

        - les ressources :
            - taille en puissance de calcul
            - generation du CPU :
                - v2 intel Ivy Bridge : 
                    - architecture de 32nm a 22nm, meilleure efficacite energetique 
                    - perf grapgique w/ intel HD graphics 4000
                - v3 intel Haswell : 
                    - amelioration en terme de performance par watt
                    - introduction de intel Iris Graphics 
                - v4 intel Broadwell : 
                    - arch 14nm, 
                - v5 intel Skylake : 
                    - nouvelle archi de coeurs + amelioration dans la gestion de l'energie
                - v6 Ice Lake : 
                    - 10nm 
                - v7 Sapphir Rapids : 
                    - 10nm ou 7nm : une finesse de gravure plus petite permet de placer + de transistors (amplifie energie, basculer des signaux)
            - c : nb de cpu entre 1 et 78
            - r : quantite de memoire de 1 a 1039go
            - p : indicateur de performance des CPU allant de 1 (highest) a 3 (medium) 

        - cle acces VM : 
            - VM : acces a cette VM via la cle privee de la keypair
            - host : enregistrer IP dans authorized_keys
        
        - sg : j'autorise les connexions venant des rules

        - subnet : afin que les VM communiquent entre elles de maniere secur'
*/


resource "outscale_vm" "vm_prom_ansible" {
    image_id           = data.outscale_image.image01.image_id
    vm_type            = "tinav6.c1r2p3" 
    keypair_name       = outscale_keypair.keypair03.keypair_name
    security_group_ids = [
        outscale_security_group.common.security_group_id,
        outscale_security_group.monitoring.security_group_id
    ]
    subnet_id          = outscale_subnet.subnet01.subnet_id
    tags {
        key   = "name"
        value = "ansible_vm_prometheus_api + node_exporter"
    }
}

/*
    creation d'une IP publique unique et visible par tous, permet d'acceder a la VM
*/

# resource "outscale_public_ip" "public_ip_prom_ansible" {
# }

# output "public_ip_prom_ansible" {
#     description = "public ip of my vm_prom_ansible"
#     value = outscale_public_ip.public_ip_prom_ansible.public_ip
# }

/*
    attache l'IP a la VM
*/

# resource "outscale_public_ip_link" "pub_ip_link_prometheus_ansible" {
#     vm_id     = outscale_vm.vm_prom_ansible.vm_id
#     public_ip = outscale_public_ip.public_ip_prom_ansible.public_ip
# }

output "private_ip_prometheus_ansible" {
    description = "private_ip of my vm_prom_ansible"
    value = outscale_vm.vm_prom_ansible.private_ip
}