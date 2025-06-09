# Vault-cert

Issues a certificate based on Vault's PKI engine.

Renews the certificate four weeks before expiration.

## Parameters

`vault_cert`: a list of `certificate`s

`certificate`:

| Parameter                                  | Comment                                                                                                                                       | Example               |
| ------------------------------------------ | --------------------------------------------------------------------------------------------------------------------------------------------- | --------------------- |
| issue_path `(string: <required>)`          | Specifies path of the PKI's issuer.                                                                                                           | pki/foo/issue/my-role |
| base_path `(string: "")`                   | Specifies remote base path that will prefix all subsequent paths with a `/`.                                                                  | /etc/ssl              |
| cert_path `(string)`                       | Specifies remote path of the certificate. If not provided, no file will be created.                                                           | foo.pem               |
| key_path `(string)`                        | Specifies remote private key path. If not provided, no file will be created.                                                                  | subdir/foo-key.pem    |
| ca_chain_path `(string)`                   | Specifies remote Certificate Authority chain path. If not provided, no file will be created.                                                  | chains/bundle.pem     |
| concat_path `(string)`                     | Specifies remote path of a concatenated file containing the certificate and private key. If not provided, no file will be created.            | concat.pem            |
| common_name `(string: <required>)`         | Specifies requested CN for the certificate. If more than one `common_name` is desired, specify the alternative names in the `alt_names` list. | bar.com               |
| alt_names `(string: "")`                   | Specifies requested Subject Alternative Names, in a comma-delimited list. These can be host names or email addresses.                         | baz.fr,input.io       |
| ip_sans `(string: "")`                     | Specifies requested IP Subject Alternative Names, in a comma-delimited list.                                                                  | 192.168.0.1,127.0.0.1 |
| ttl `(string: the issuer's default value)` | Specifies requested Time To Live, in Golang Duration format. Cannot be greater than the role's `max_ttl` value.                               | 60d                   |
| permitted_dns_domains `(string)`           | Specifies DNS domains for which certificates are allowed to be issued or signed by this CA certificate.                                       | .bar.com              |
| max_path_length `(int)`                    | Specifies the maximum path length to encode in the generated certificate.                                                                     | 1                     |
| country `(string)`                         | Specifies the C (Country) values in the subject field of the resulting certificate.                                                           | Ireland               |
| province `(string)`                        | Specifies the ST (Province) values in the subject field of the resulting certificate.                                                         | Cork                  |
| locality `(string)̀`                        | Specifies the L (Locality) values in the subject field of the resulting certificate.                                                          | Cork                  |
| postal_code `(string)̀`                     | Specifies the Postal Code values in the subject field of the resulting certificate.                                                           | 12345                 |
| street_address `(string)̀`                  | Specifies the Street Address values in the subject field of the resulting certificate.                                                        | 21 Baker Street       |
| organization `(string)̀`                    | Specifies the O (Organization) values in the subject field of the resulting certificate.                                                      | Google                |
| ou `(string)̀`                              | Specifies the OU (OrganizationalUnit) values in the subject field of the resulting certificate.                                               | Finance               |
| owner `(string: <required>)`               | Specifies user of the created files, by name or ID.                                                                                           | root                  |
| group `(string: <required>)`               | Specifies group of the created files, by name or ID.                                                                                          | false                 |
| add_owner `(bool: true)`                   | Specifies wether to create the user or not, if it does not already exist.                                                                     | root                  |
| add_group `(bool: true)`                   | Specifies wether to create the group or not, if it does not already exist. The owner will be appended to the group.                           | false                 |
| force_renew `(bool: false)`                | Specifies wether to renew the certificate or not.                                                                                             | true                  |
