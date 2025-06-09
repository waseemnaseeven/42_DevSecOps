resource "outscale_security_group" "monitoring" {
    description         = "Security group between monitoring stack"
    security_group_name = "sg_monitoring"
    net_id              = outscale_net.net02.net_id
}

resource "outscale_security_group_rule" "http_inbounb_between" {
    flow              = "Inbound"
    security_group_id = outscale_security_group.monitoring.security_group_id
    from_port_range   = "80"
    to_port_range     = "80"
    ip_protocol       = "tcp"
    ip_range          = "10.15.0.0/16" 
}

resource "outscale_security_group_rule" "https_inbounb_between" {
    flow              = "Inbound"
    security_group_id = outscale_security_group.monitoring.security_group_id
    from_port_range   = "443"
    to_port_range     = "443"
    ip_protocol       = "tcp"
    ip_range          = "10.15.0.0/16" 
}

resource "outscale_security_group_rule" "https_Outbounb_between" {
    flow              = "Outbound"
    security_group_id = outscale_security_group.monitoring.security_group_id
    from_port_range   = "443"
    to_port_range     = "443"
    ip_protocol       = "tcp"
    ip_range          = "0.0.0.0/0" 
}

resource "outscale_security_group_rule" "ssh_inbounb" {
    flow              = "Inbound"
    security_group_id = outscale_security_group.monitoring.security_group_id
    from_port_range   = "22"
    to_port_range     = "22"
    ip_protocol       = "tcp"
    ip_range          = "10.15.0.0/16" 
}

resource "outscale_security_group_rule" "node_exporter_inbound" {
    flow              = "Inbound"
    security_group_id = outscale_security_group.monitoring.security_group_id
    from_port_range   = "9100"
    to_port_range     = "9100"
    ip_protocol       = "tcp"
    ip_range          = "10.15.0.0/16" 
}

resource "outscale_security_group_rule" "alertmanager_inbound" {
    flow              = "Inbound"
    security_group_id = outscale_security_group.monitoring.security_group_id
    from_port_range   = "9093"
    to_port_range     = "9094"
    ip_protocol       = "tcp"
    ip_range          = "10.15.0.0/16" 
}

resource "outscale_security_group_rule" "grafana_inbound" {
    flow              = "Inbound"
    security_group_id = outscale_security_group.monitoring.security_group_id
    from_port_range   = "3000"
    to_port_range     = "3000"
    ip_protocol       = "tcp"
    ip_range          = "10.15.0.0/16" 
}

resource "outscale_security_group_rule" "minio_inbound" {
    flow              = "Inbound"
    security_group_id = outscale_security_group.monitoring.security_group_id
    from_port_range   = "9000"
    to_port_range     = "9001"
    ip_protocol       = "tcp"
    ip_range          = "10.15.0.0/16" 
}

resource "outscale_security_group_rule" "thanos_inbound" {
    flow              = "Inbound"
    security_group_id = outscale_security_group.monitoring.security_group_id
    from_port_range   = "10901"
    to_port_range     = "10909"
    ip_protocol       = "tcp"
    ip_range          = "10.15.0.0/16" 
}

