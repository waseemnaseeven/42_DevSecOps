resource "outscale_vm" "vm_prom3_ansible" {
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
        value = "ansible_vm_prometheus3 + node_exporter"
    }
}

output "private_ip_prometheus3_ansible" {
    description = "private_ip of my vm_prom3_ansible"
    value = outscale_vm.vm_prom3_ansible.private_ip
}