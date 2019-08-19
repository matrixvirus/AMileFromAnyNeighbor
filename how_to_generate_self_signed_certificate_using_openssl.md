# how to generate self signed certificate using openssl

# method one

*   create a private key

        openssl genrsa -out abc.key

*   create the certificate

        openssl req -x509 -new -key abc.key -out abc.crt

# method two
*   create a certificate signing request

        openssl req -new -out abc.csr

*   remove the private key PEM pass phrase of the private key created at above
	,

        openssl rsa -in privkey.pem -out abc.key

*   create the certificate

        openssl x509 -in abc.csr -out abc.crt -req -signkey abc.key
	
