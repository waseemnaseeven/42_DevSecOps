resource "outscale_vm" "bastion_ssh" {
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
        value = "bastion_ssh"
    }
}

resource "outscale_public_ip" "public_ip_bastion_ssh" {
}

output "public_ip_bastion_ssh" {
    description = "public ip of my bastion ssh"
    value = outscale_public_ip.public_ip_bastion_ssh.public_ip
}

resource "outscale_public_ip_link" "pub_ip_link_bastion_ssh" {
    vm_id     = outscale_vm.bastion_ssh.vm_id
    public_ip = outscale_public_ip.public_ip_bastion_ssh.public_ip
}

output "private_ip_bastion_ssh" {
    description = "private_ip of my bastion_ssh"
    value = outscale_vm.bastion_ssh.private_ip
}