resource "outscale_vm" "vm_thanos_query" {
    image_id           = data.outscale_image.image01.image_id
    vm_type            = "tinav6.c4r8p3" 
    keypair_name       = outscale_keypair.keypair03.keypair_name
    security_group_ids = [
        outscale_security_group.common.security_group_id,
        outscale_security_group.monitoring.security_group_id
    ]
    subnet_id          = outscale_subnet.subnet01.subnet_id
    tags {
        key   = "name"
        value = "thanos query + node_exporter"
    }
}

output "private_ip_thanos_query" {
    description = "private_ip of my vm_thanos_query"
    value = outscale_vm.vm_thanos_query.private_ip
}