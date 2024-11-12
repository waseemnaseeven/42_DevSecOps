#output.tf

output "rds_endpoint" {
  description = "RDS Endpoint to use in Docker Compose"
  value       = aws_db_instance.wordpress_rds.endpoint
}

output "alb_dns_name" {
  value = aws_lb.wordpress_alb.dns_name
}

output "website_url" {
  value = "https://${var.domain_name}"
}

# output "ec2_public_ip" {
#   value = aws_instance.wp-web.public_ip
# }

output "ec2_public_ips" {
  value = [
    aws_instance.wp-web-1.public_ip,
    aws_instance.wp-web-2.public_ip
  ]
}
