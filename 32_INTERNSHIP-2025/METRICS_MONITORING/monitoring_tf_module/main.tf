locals {
    reserved_ip = "10.15.63.250" # Reserve a keepalived
    reserved_ip2 = "10.15.63.249" # Reserve a keepalived

}

/*
    Une keypair se compose de deux parties : une clé publique et une clé privée.

    La clé publique est placée sur l'instance de machine virtuelle, tandis que la clé privée reste avec l'utilisateur. Lorsque connexion a l'instance : on utilise la clé privée pour prouver mon identité.

    base64encode va encoder des donnees binaires en une string afin de faciliter la transmission et le stockage de data.
*/

resource "outscale_keypair" "keypair03" {
    keypair_name = "terraform-keypair-import-text"
    public_key   = base64encode("ssh-ed25519 AAAAC3NzaC1lZDI1NTE5AAAAIEVjEobxnEF1S2YNdfrovfY4aUROnVo74iGltq2aLgQa")
}

# Reserve a keepalived
resource "null_resource" "vip" {
    triggers = {
        reserved_ip = "10.15.63.250"
        reserved_ip2 = "10.15.63.249"
    }
}

# resource "outscale_keypair" "keypair03" {
#     keypair_name = "terraform-keypair-import-text"
#     public_key   = file("~/.ssh/outscale_sshvm.pub")
# }

