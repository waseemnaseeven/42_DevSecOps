sudo apt install nginx
cd /etc/nginx/sites-enabled
sudo vim prometheus

# server {
#     listen 80;
#     listen [::]:80;
#     server_name  localhost;

#     location / {
#         proxy_pass           http://localhost:9090/;
#     }
# }

# server {
#     listen 80;

#     server_name localhost;

#     location /prometheus/ {
#         proxy_pass http://localhost:9090/;
#         proxy_set_header Host $host; # contient le nom d'hote original tel qu'il a été reçu dans la requête client. Cela permet de transmettre le nom d'hôte d'origine au serveur backend
#         proxy_set_header X-Real-IP $remote_addr; # identifie IP address reelle du client
#         proxy_set_header X-Forwarded-For $proxy_add_x_forwarded_for; # suivre la chaine IP address a travers les proxys
#         proxy_set_header X-Forwarded-Proto $scheme; # savoir si la requete original utilisait http ou https
#     }

#     location /node_exporter/ {
#         proxy_pass http://localhost:9100/;
#         proxy_set_header Host $host;
#         proxy_set_header X-Real-IP $remote_addr; 
#         proxy_set_header X-Forwarded-For $proxy_add_x_forwarded_for;
#         proxy_set_header X-Forwarded-Proto $scheme;
#     }
# }

rm /etc/nginx/sites-enabled/default

sudo nginx -t

sudo service nginx restart
sudo service nginx status


