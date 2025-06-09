/*
    Creation d'un reseau, une plage d'IP en notation CIDR, sur lequel mes ressources pourront utiliser
*/

resource "outscale_net" "net02" {
    ip_range = "10.15.0.0/16"
    tags {
        key = "osc.fcu.disable_lan_security_groups" // desactivation du sg lan ?
        value = "1"  
    }
}

/*
    Creation subnet dans une sous-region particuliere 
*/

resource "outscale_subnet" "subnet01" {
    net_id   = outscale_net.net02.net_id
    ip_range = "10.15.0.0/18"
    subregion_name = "cloudgouv-eu-west-1a" 
}

/*
    Creation d'une route table afin de controler le routage du trafic d'un subnet grace a des routes. Si ip src doit rejoidnre ip dest, on check si ip dest se situe dans la table. 
*/

resource "outscale_route_table" "route_table01" {
    net_id = outscale_net.net02.net_id
}

resource "outscale_nat_service" "nat_service01" {
    subnet_id    = outscale_subnet.subnet01.subnet_id
    public_ip_id = outscale_public_ip.public_ip_subnet.public_ip_id
}

resource "outscale_route_table_link" "route_table_link01" {
    subnet_id      = outscale_subnet.subnet01.subnet_id
    route_table_id = outscale_route_table.route_table01.id
}
/*
    acces internet (box) + link a un reseau
*/

resource "outscale_internet_service" "internet_service01" {
} 

resource "outscale_internet_service_link" "internet_service_link01" {
    net_id              = outscale_net.net02.net_id
    internet_service_id = outscale_internet_service.internet_service01.id
}

/*
    Creation d'une route avec une target (ici, toutes les IP) afin qu'elle puisse indirectement etre connectees a internet
*/ 

resource "outscale_route" "route01" {
    destination_ip_range = "0.0.0.0/0"
    nat_service_id           = outscale_nat_service.nat_service01.nat_service_id
    route_table_id       = outscale_route_table.route_table01.route_table_id
}

resource "outscale_public_ip" "public_ip_subnet" {
}
