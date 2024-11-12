# variables.tf

variable "db_password" {
  description = "password for RDS db"
  type        = string
  sensitive   = true
}

variable "db_root_password" {
  description = "root password for RDS db"
  type        = string
  sensitive   = true
}

variable "domain_name" {
  description = "domain name, certificate request"
  type        = string
}

# variable "instance_count" {
#   description = "number of ec2 instance"
#   type = number
#   default = 2
# }

# mon add IP ? 