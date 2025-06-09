resource "outscale_vm" "vm_ntp" {
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
        value = "vm_ntp"
    }
}

resource "outscale_public_ip" "public_ip_vm_ntp" {
}

output "public_ip_vm_ntp" {
    description = "public ip of my vm ntp"
    value = outscale_public_ip.public_ip_vm_ntp.public_ip
}

resource "outscale_public_ip_link" "pub_ip_link_vm_ntp" {
    vm_id     = outscale_vm.vm_ntp.vm_id
    public_ip = outscale_public_ip.public_ip_vm_ntp.public_ip
}

output "private_ip_vm_ntp" {
    description = "private_ip of my vm_ntp"
    value = outscale_vm.vm_ntp.private_ip
}