all:
	terraform init
	terraform apply -auto-approve \
	  -var "db_password=wordpress" \
	  -var "db_root_password=wordpress_root_password" \
	  -var "domain_name=cloud1projectv2.com"
