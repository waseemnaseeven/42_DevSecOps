/*
    Creation d'un sg afin de gerer le traffic entre mes VM et le host
    Suppression des flux standard (80, 443)
*/

resource "outscale_security_group" "common" {
    remove_default_outbound_rule = true
    description         = "SG pour gérer le trafic entre les VM et le host - suppression des flux standards (80, 443) et gestion des règles pour SSH, HTTP, DNS et NTP"
    security_group_name = "sg_common"
    net_id              = outscale_net.net02.net_id
}

/*
    J'autorise mes VM a taper l'IP du Ponant sur le port 22
*/

resource "outscale_security_group_rule" "ssh" {
    flow              = "Inbound" // flux entrant
    security_group_id = outscale_security_group.common.security_group_id 
    from_port_range   = "22"
    to_port_range     = "22"
    ip_protocol       = "tcp"
    ip_range          = "217.108.6.170/32" // /32 donc seul mon IP est autorise
}

/*
    J'autorise les requetes sur le port 80 depuis ma machine vers toutes les autres
*/

resource "outscale_security_group_rule" "http_outbound" {
    flow              = "Outbound" 
    security_group_id = outscale_security_group.common.security_group_id
    from_port_range   = "80"
    to_port_range     = "80"
    ip_protocol       = "tcp"
    ip_range          = "0.0.0.0/0"
}

resource "outscale_security_group_rule" "https" {
    flow              = "Outbound" 
    security_group_id = outscale_security_group.common.security_group_id
    from_port_range   = "443"
    to_port_range     = "443"
    ip_protocol       = "tcp"
    ip_range          = "0.0.0.0/0"
}

resource "outscale_security_group_rule" "dns" {
    flow              = "Outbound" 
    security_group_id = outscale_security_group.common.security_group_id
    from_port_range   = "53"
    to_port_range     = "53"
    ip_protocol       = "udp"
    ip_range          = "0.0.0.0/0"
}

/*
    NTP : protocole de synchronisation de l'horloge d'une machine avec celle d'un serveur de ref, port : 123
*/

resource "outscale_security_group_rule" "ntp" {
    flow              = "Outbound" 
    security_group_id = outscale_security_group.common.security_group_id
    from_port_range   = "123"
    to_port_range     = "123"
    ip_protocol       = "udp"
    ip_range          = "0.0.0.0/0"
}

