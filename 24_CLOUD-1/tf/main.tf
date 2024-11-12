# WITH ASG

locals {
  vpc_cidr_block       = "192.168.0.0/16"
  public_subnet_cidr1  = "192.168.1.0/24"
  public_subnet_cidr2  = "192.168.5.0/24"
  private_subnet_cidr1 = "192.168.3.0/24"
  private_subnet_cidr2 = "192.168.4.0/24"
  ssh_user             = "ubuntu"
  key_name             = "wordpress_key"
  private_key_path     = "/Users/waseemnaseeven/Desktop/wordpress_key.pem" # To change
  db_user              = "wordpress"
  aws_region           = "eu-west-3"
  env_file_content = templatefile("${path.module}/env.tpl", {
    db_host          = aws_db_instance.wordpress_rds.endpoint
    db_name          = "wordpress_db"
    db_user          = local.db_user
    db_password      = var.db_password
    db_root_password = var.db_root_password
  })
}

provider "aws" {
  region = "eu-west-3"
}

# Creation du virtual private cloud, reseau prive qui va contenir tous mes services (ec2, rds)
resource "aws_vpc" "wordpress_vpc" {
  cidr_block           = local.vpc_cidr_block
  enable_dns_support   = true
  enable_dns_hostnames = true

  tags = {
    Name = "WordPress VPC"
  }
}

# Creation internet gateway pour connexion internet
resource "aws_internet_gateway" "wordpress_igw" {
  vpc_id = aws_vpc.wordpress_vpc.id

  tags = {
    Name = "WordPress Internet Gateway"
  }
}

# Créer un sous-réseau public
resource "aws_subnet" "wordpress_public_subnet" {
  vpc_id                  = aws_vpc.wordpress_vpc.id
  cidr_block              = local.public_subnet_cidr1
  availability_zone       = "eu-west-3a"
  map_public_ip_on_launch = true

  tags = {
    Name = "WordPress Public Subnet"
  }
}

# Créer un 2eme sous-réseau public
resource "aws_subnet" "wordpress_public_subnet_2" {
  vpc_id                  = aws_vpc.wordpress_vpc.id
  cidr_block              = local.public_subnet_cidr2
  availability_zone       = "eu-west-3c"
  map_public_ip_on_launch = true

  tags = {
    Name = "WordPress Public Subnet"
  }
}

# Créer un sous-réseau privé
resource "aws_subnet" "wordpress_private_subnet" {
  vpc_id            = aws_vpc.wordpress_vpc.id
  cidr_block        = local.private_subnet_cidr1
  availability_zone = "eu-west-3b"

  tags = {
    Name = "WordPress Private Subnet 1"
  }
}

# Créer un 2eme sous-réseau privé
resource "aws_subnet" "wordpress_private_subnet_2" {
  vpc_id            = aws_vpc.wordpress_vpc.id
  cidr_block        = local.private_subnet_cidr2
  availability_zone = "eu-west-3c"

  tags = {
    Name = "WordPress Private Subnet 2"
  }
}

# Créer une table de routage pour le VPC
resource "aws_route_table" "wordpress_public_route_table" {
  vpc_id = aws_vpc.wordpress_vpc.id

  # Route vers l'Internet Gateway pour le sous-réseau public
  route {
    cidr_block = "0.0.0.0/0"
    gateway_id = aws_internet_gateway.wordpress_igw.id
  }

  tags = {
    Name = "WordPress Route Table"
  }
}

# Associer la table de routage au sous-réseau public
resource "aws_route_table_association" "public_subnet_association" {
  subnet_id      = aws_subnet.wordpress_public_subnet.id
  route_table_id = aws_route_table.wordpress_public_route_table.id
}

# Table de routage privée pour le sous-réseau privé
resource "aws_route_table" "wordpress_private_route_table" {
  vpc_id = aws_vpc.wordpress_vpc.id

  tags = {
    Name = "WordPress Private Route Table"
  }
}

# Associer la table de routage privée au sous-réseau privé
resource "aws_route_table_association" "private_subnet_association" {
  subnet_id      = aws_subnet.wordpress_private_subnet.id
  route_table_id = aws_route_table.wordpress_private_route_table.id
}

# ACM Certificate SSL/TLS
data "aws_acm_certificate" "existing_cert" {
  domain      = var.domain_name
  statuses    = ["ISSUED"]
  types       = ["AMAZON_ISSUED"]
  most_recent = true
}

data "aws_route53_zone" "wordpress_zone" {
  name         = var.domain_name
  private_zone = false
}

resource "aws_route53_record" "wordpress_alias" {
  zone_id = data.aws_route53_zone.wordpress_zone.zone_id
  name    = var.domain_name
  type    = "A"

  # zone_id : Identifie la zone hébergée où l'enregistrement sera créé.
  # name : Le nom de l'enregistrement DNS, généralement votre nom de domaine.
  # type : Le type d'enregistrement, "A" pour une adresse IPv4.
  # alias : Spécifie que l'enregistrement est un alias pointant vers votre ALB.

  alias {
    name                   = aws_lb.wordpress_alb.dns_name
    zone_id                = aws_lb.wordpress_alb.zone_id
    evaluate_target_health = true
  }
}


# Autorise l'accès MySQL depuis l'instance EC2.
resource "aws_security_group" "wordpress_rds_sg" {
  vpc_id = aws_vpc.wordpress_vpc.id
  name   = "wordpress_rds_sg"

  egress {
    from_port   = 0
    to_port     = 0
    protocol    = "-1"
    cidr_blocks = ["0.0.0.0/0"]
  }

  tags = {
    Name = "WordPress RDS Security Group"
  }
}

resource "aws_security_group_rule" "rds_sg_mysql" {
  type                     = "ingress"
  from_port                = 3306
  to_port                  = 3306
  protocol                 = "tcp"
  security_group_id        = aws_security_group.wordpress_rds_sg.id
  source_security_group_id = aws_security_group.wordpress_sg.id
  description              = "Allow MySQL access from EC2"
}

# Instance RDS MySQL
resource "aws_db_instance" "wordpress_rds" {
  identifier             = "wordpress-rds"
  allocated_storage      = 20
  engine                 = "mysql"
  engine_version         = "8.0.37"
  instance_class         = "db.t3.micro"
  parameter_group_name   = "default.mysql8.0"
  db_name                = "wordpress_db"
  username               = local.db_user
  password               = var.db_password
  vpc_security_group_ids = [aws_security_group.wordpress_rds_sg.id]
  db_subnet_group_name   = aws_db_subnet_group.wordpress_db_subnet_group.name
  skip_final_snapshot    = true
  publicly_accessible    = false

  tags = {
    Name = "WordPress RDS Instance"
  }
}

# Sous-réseaux privés pour le groupe de sous-réseaux RDS
resource "aws_db_subnet_group" "wordpress_db_subnet_group" {
  name = "wordpress-db-subnet-group"
  subnet_ids = [
    aws_subnet.wordpress_private_subnet.id,
    aws_subnet.wordpress_private_subnet_2.id
  ]

  tags = {
    Name = "WordPress DB Subnet Group"
  }
}

# Creation de l'ALB, pour distribuer le trafic vers l'instance EC2.
resource "aws_lb" "wordpress_alb" {
  name               = "wordpress-alb"
  internal           = false
  load_balancer_type = "application"
  security_groups    = [aws_security_group.wordpress_alb_sg.id]
  subnets = [
    aws_subnet.wordpress_public_subnet.id,
    aws_subnet.wordpress_public_subnet_2.id
  ]

  tags = {
    Name = "Wordpress Application Load Balancer"
  }
}

# Définit les règles pour l'ALB, autorisant le trafic HTTP/HTTPS entrant.
resource "aws_security_group" "wordpress_alb_sg" {
  name   = "wordpress_alb_sg"
  vpc_id = aws_vpc.wordpress_vpc.id

  ingress {
    description = "Allow HTTP traffic"
    from_port   = 80
    to_port     = 80
    protocol    = "tcp"
    cidr_blocks = ["0.0.0.0/0"]
  }

  ingress {
    description = "Allow HTTPS traffic"
    from_port   = 443
    to_port     = 443
    protocol    = "tcp"
    cidr_blocks = ["0.0.0.0/0"]
  }

  egress {
    from_port   = 0
    to_port     = 0
    protocol    = "-1"
    cidr_blocks = ["0.0.0.0/0"]
  }

  tags = {
    Name = "WordPress ALB Security Group"
  }
}

# Attachement de l'instance EC2 au Target Group
resource "aws_lb_target_group_attachment" "wordpress_tg_attachment-1" {
  target_group_arn = aws_lb_target_group.wordpress_tg.arn
  target_id        = aws_instance.wp-web-1.id
  port             = 80
}

# Attachement de l'instance EC2 au Target Group
resource "aws_lb_target_group_attachment" "wordpress_tg_attachment-2" {
  target_group_arn = aws_lb_target_group.wordpress_tg.arn
  target_id        = aws_instance.wp-web-2.id
  port             = 80
}

# Définit le groupe cible pour l'ALB.
resource "aws_lb_target_group" "wordpress_tg" {
  name        = "wordpress-tg"
  port        = 80
  protocol    = "HTTP"
  vpc_id      = aws_vpc.wordpress_vpc.id
  target_type = "instance"

  health_check {
    path                = "/"
    protocol            = "HTTP"
    matcher             = "200-499"
    interval            = 30
    timeout             = 5
    healthy_threshold   = 5
    unhealthy_threshold = 2
  }

  tags = {
    Name = "WordPress Target Group"
  }
}

# Configure l'ALB pour listen sur le port 443 avec SSL
resource "aws_lb_listener" "wordpress_alb_listener_https" {
  load_balancer_arn = aws_lb.wordpress_alb.arn
  port              = "443"
  protocol          = "HTTPS"
  ssl_policy        = "ELBSecurityPolicy-2016-08"
  certificate_arn   = data.aws_acm_certificate.existing_cert.arn

  default_action {
    type             = "forward"
    target_group_arn = aws_lb_target_group.wordpress_tg.arn
  }
}

# Redirige le trafic HTTP vers HTTPS.
resource "aws_lb_listener" "wordpress_alb_listener_http" {
  load_balancer_arn = aws_lb.wordpress_alb.arn
  port              = "80"
  protocol          = "HTTP"

  default_action {
    type = "redirect"
    redirect {
      protocol    = "HTTPS"
      port        = "443"
      status_code = "HTTP_301"
    }
  }
}

# Autorise l'accès NFS pour EFS depuis l'instance EC2
resource "aws_security_group" "wordpress_efs_sg" {
  name   = "wordpress_efs_sg"
  vpc_id = aws_vpc.wordpress_vpc.id

  egress {
    from_port   = 0
    to_port     = 0
    protocol    = "-1"
    cidr_blocks = ["0.0.0.0/0"]
  }

  tags = {
    Name = "WordPress EFS Security Group"
  }
}

resource "aws_security_group_rule" "efs_sg_nfs" {
  type                     = "ingress"
  from_port                = 2049
  to_port                  = 2049
  protocol                 = "tcp"
  security_group_id        = aws_security_group.wordpress_efs_sg.id
  source_security_group_id = aws_security_group.wordpress_sg.id
  description              = "Allow NFS from EC2"
}


# Crée le système de fichiers EFS pour stocker les fichiers WordPress. data persistence 
resource "aws_efs_file_system" "wordpress_efs" {
  creation_token = "wordpress-efs"
  encrypted      = true

  tags = {
    Name = "WordPress EFS"
  }
}

# Crée des points de montage dans les sous-réseaux pour l'accès à EFS.
resource "aws_efs_mount_target" "wordpress_efs_mt_public" {
  file_system_id  = aws_efs_file_system.wordpress_efs.id
  subnet_id       = aws_subnet.wordpress_public_subnet.id
  security_groups = [aws_security_group.wordpress_efs_sg.id]
}

resource "aws_efs_mount_target" "wordpress_efs_mt_private" {
  file_system_id  = aws_efs_file_system.wordpress_efs.id
  subnet_id       = aws_subnet.wordpress_private_subnet.id
  security_groups = [aws_security_group.wordpress_efs_sg.id]
}

# Dealing with security network rules for Ec2
resource "aws_security_group" "wordpress_sg" {
  name   = "wordpress_security_ec2_access"
  vpc_id = aws_vpc.wordpress_vpc.id

  tags = {
    Name = "Wordpress Security Group"
  }
}

# Autoriser le trafic SSH depuis votre IP
resource "aws_security_group_rule" "wordpress_sg_ssh" {
  type        = "ingress"
  from_port   = 22
  to_port     = 22
  protocol    = "tcp"
  cidr_blocks = ["0.0.0.0/0"] # A ne pas faire 
  #   cidr_blocks     = ["<votre_ip>/32"]  # Remplacez par votre IP publique
  security_group_id = aws_security_group.wordpress_sg.id
  description       = "Allow SSH traffic from your IP"
}

# Autoriser le trafic HTTP depuis le groupe de sécurité de l'ALB
resource "aws_security_group_rule" "wordpress_sg_http" {
  type                     = "ingress"
  from_port                = 80
  to_port                  = 80
  protocol                 = "tcp"
  security_group_id        = aws_security_group.wordpress_sg.id
  source_security_group_id = aws_security_group.wordpress_alb_sg.id
  description              = "Allow HTTP traffic from ALB"
}

# Autoriser le trafic HTTPS depuis le groupe de sécurité de l'ALB
resource "aws_security_group_rule" "wordpress_sg_https" {
  type                     = "ingress"
  from_port                = 443
  to_port                  = 443
  protocol                 = "tcp"
  security_group_id        = aws_security_group.wordpress_sg.id
  source_security_group_id = aws_security_group.wordpress_alb_sg.id
  description              = "Allow HTTPS traffic from ALB"
}

# Autoriser tout le trafic sortant
resource "aws_security_group_rule" "wordpress_sg_egress" {
  type              = "egress"
  from_port         = 0
  to_port           = 0
  protocol          = "-1"
  cidr_blocks       = ["0.0.0.0/0"]
  security_group_id = aws_security_group.wordpress_sg.id
  description       = "Allow all outbound traffic"
}

# Launch Template
resource "aws_launch_template" "wp_launch_template" {
  name_prefix   = "wp-launch-template-"
  image_id      = "ami-045a8ab02aadf4f88"
  instance_type = "t2.micro"
  key_name      = local.key_name

  network_interfaces {
    associate_public_ip_address = true
    security_groups             = [aws_security_group.wordpress_sg.id]
    subnet_id                   = aws_subnet.wordpress_public_subnet.id
  }

  user_data = base64encode(<<-EOF
    #!/bin/bash
    sudo apt-get update
    sudo apt-get install -y ca-certificates curl gnupg mysql-client nfs-common
    curl -fsSL https://get.docker.com -o get-docker.sh && sh get-docker.sh
    sudo rm get-docker.sh
    sudo apt install -y make
    sudo mkdir -p /mnt/efs
    sudo mount -t nfs4 -o nfsvers=4.1,tcp,port=2049 ${aws_efs_file_system.wordpress_efs.dns_name}:/ /mnt/efs
    sudo chown -R ubuntu:ubuntu /mnt/efs
    echo '${aws_efs_file_system.wordpress_efs.dns_name}:/ /mnt/efs nfs4 defaults,_netdev 0 0' | sudo tee -a /etc/fstab
    mkdir -p /home/ubuntu/app
    cd /home/ubuntu/app
    git clone https://github.com/votre-repo/dockerwp.git
    cd dockerwp
    echo "${local.env_file_content}" > .env
    sudo docker compose up -d
  EOF
  )

  tag_specifications {
    resource_type = "instance"
    tags = {
      Name = "wp-web"
    }
  }
}

# Auto Scaling Group
resource "aws_autoscaling_group" "wp_asg" {
  name                      = "wp-asg"
  max_size                  = 3
  min_size                  = 2
  desired_capacity          = 2
  vpc_zone_identifier       = [aws_subnet.wordpress_public_subnet.id, aws_subnet.wordpress_public_subnet_2.id]

  launch_template {
    id      = aws_launch_template.wp_launch_template.id
    version = "$Latest"
  }

  target_group_arns = [aws_lb_target_group.wordpress_tg.arn]

  tag {
    key                 = "Name"
    value               = "wp-web"
    propagate_at_launch = true
  }
}
