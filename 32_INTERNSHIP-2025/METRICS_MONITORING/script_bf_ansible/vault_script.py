import sys
import os
import hvac
import subprocess
import glob
import yaml

# renvoyer a "/v1/rd/monitoring/secrets/data/" puis ensuite /secret/group_vars/etc...

def import_secrets_from_directory(client: hvac.Client, directory: str, mount_point='rd/monitoring/secrets'):

    files = glob.glob(os.path.join(directory, '*.yml'))
    for file_path in files:
        # Extraire le nom sans du fichier sans l'extension
        file_name = os.path.basename(file_path).split('.')[0]
        print(f"file name is : {file_name}")
        # Le path secret sera donc sous la forme : <mount_point>/<directory>/<filename>
        secret_path = f"{directory}/{file_name}"

        #Lecture des secrets dans group_vars ou host_vars 
        try:
            with open(file_path, 'r') as vars_file:
                data = yaml.safe_load(vars_file)
        except Exception as e:
            print(f"Oopsi... error reading from {file_path} : {vars_file}")
            continue
        
        # Ecriture dans Vault KV v2
        try:
            client.secrets.kv.v2.create_or_update_secret(
                path=secret_path,
                secret=data,
                mount_point=mount_point
            )
            print(f"Import success from {file_path} to {mount_point}/{secret_path} !!! Watch it from the URI")
        except Exception as e:
            print(f"Oopsi... Error import from {file_path} : {e}")

def main():
    vault_addr = os.environ.get("VAULT_ADDR")
    vault_client_cert = os.environ.get("VAULT_CLIENT_CERT")
    vault_client_key = os.environ.get("VAULT_CLIENT_KEY")
    vault_token = subprocess.check_output("vault print token", shell=True)

    print(vault_addr)
    print(vault_token)

    if not vault_addr or not vault_token:
        print("Oopsi...")
        sys.exit(1)
    
    client = hvac.Client(
        url=vault_addr, 
        token=vault_token.strip()
    )

    if not client.is_authenticated():
        print("Oopsi... Authentication failure on vault API")
        sys.exit(1)
    
    directories = [
        'group_vars',
        'host_vars'
    ]

    for directory in directories:
        if not os.path.isdir(directory):
            print(f"The folder '{directory} doesn't exist")
            continue
        import_secrets_from_directory(client, directory)

if __name__ == '__main__':
    main()