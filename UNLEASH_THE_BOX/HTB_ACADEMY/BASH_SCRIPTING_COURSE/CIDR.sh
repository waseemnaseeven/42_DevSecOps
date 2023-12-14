if [ $# -eq 0 ]
then
	echo -e "You need to specify the target domain.\n"
	echo -e "Usage:"
	echo -e "\t$0 <domain>"
	exit 1
else
	domain=$1
	echo $domain
	echo $2
	echo $@ | wc -c
	echo $$
	echo $?
	[!bash!]$ variable="this will result with an error."
	[!bash!]$ echo $variable
	domains=("www.inlanefreight.com ftp.inlanefreight.com vpn.inlanefreight.com" www2.inlanefreight.com)
	echo ${domains[0]}
	echo ${domains[1]}
fi