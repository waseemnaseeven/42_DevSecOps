# 1- local resource + provider aws 
# 2- security groups
# 3- egrtgeebwrbnv

locals {
    vpc_id              = "vpc-06955dff58950eef3"
    ssh_user            = "ubuntu"
    key_name            = "cloud1project"
    private_key_path    = "/Users/waseemnaseeven/Desktop/42_DevSecOps/24_CLOUD-1/cloud1project.pem" # To change
}

provider "aws" {
    region = "eu-west-3"
}

resource "aws_security_group" "wordpress" {
    name    = "wordpress_access"
    vpc_id  = local.vpc_id

    ingress {
    description = "Allow SSH traffic"
    from_port   = 22
    to_port     = 22
    protocol    = "tcp"
    cidr_blocks = ["0.0.0.0/0"]
    }

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
    description = "Allow all outbound traffic"
    from_port   = 0
    to_port     = 0
    protocol    = "-1" # -1 means every protocol
    cidr_blocks = ["0.0.0.0/0"]
    }

}

resource "aws_instance" "wordpress" {
    ami             = "ami-09d83d8d719da9808"
    instance_type   = "t2.micro"
    key_name        = local.key_name
    security_groups = [aws_security_group.wordpress.name] # bizarre....

    # provisioner "file" {
    #     source      = "/Users/waseemnaseeven/Desktop/42_DevSecOps/24_CLOUD-1/playbooks/deploy.yaml" # Update path if needed
    #     destination = "/home/${local.ssh_user}/deploy.yml"
    # }

    provisioner "remote-exec" {
        inline = [
            "echo = 'Wait until SSH is ready' ",
            "sudo apt-get install -y python3-pip",
            "sudo pip3 install ansible",
            "ansible-playbook /home/${local.ssh_user}/deploy.yml"
        ]

        connection {
            type        = "ssh"
            user        = local.ssh_user
            private_key = file(local.private_key_path)
            host        = self.public_ip
        }     
    }

    tags = {
        Name = "WordPress Website"
    }

}

