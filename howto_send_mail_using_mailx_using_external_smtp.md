# how to send mail using mailx command using external smtp server
the external mail server being used for testing is 163.

## an example
using 163 mailbox for example,my account is "matrixvirus@163.com",
i send a mail to myself

    mailx -v -r "matrixvirus@163.com" \
        -s "testing for mailx using external smtp" \
        -S smtp="smtp://smtp.163.com:25" \
        -S smtp-auth=login \
        -S smtp-auth-user="matrixvirus@163.com" \
        -S smtp-auth-password="1001001010000011"  \
        matrixvirus@163.com

*   -v show the details of connecting
*   the argu "-r" sets the FROM field of mail head to "matrixvirus@163.com",
*   argu "-s" sets the subject
*   -S smtp= sets the smtp server,here is "smtp.163.com",smtp protocal,
    port 25. the port 25 of smtp server of 163 means there is no ssl.

*   -S smtp-auth= sets the authentication method,here is "login"
*   -S smtp-auth-user=,-S smtp-auth-password is the username and password
    you used to login you 163 mail.
*   the "matrixvirus@163.com" at end is the recipient.  



## an example using ssl

    mailx -v -r "matrixvirus@163.com" \
        -s "test 163 smtp 994 port" \
        -S smtp="smtps://smtp.163.com:994" \
        -S smtp-auth=login \
        -S smtp-auth-user="matrixvirus@163.com" \
        -S smtp-auth-password="1001001010000011" \
        matrixvirus@163.com

the differences is,for non ssl,a argu is 
    "smtp://smtp.163.com:25",
    port:25
    protocol:smtp

for ssl,the argu is
    "smtps://smtp.163.com:994"
    port:994
    protocol:smtps

note,the 25,994 is just the situation for 163,for other mail servers it maybe 
different.

## using mail.rc
you can put the argus used in above to /etc/mail.rc,

    set from=matrixvirus@163.com
    set smtp=smtps://smtp.163.com:994
    set smtp-auth=login
    set smtp-auth-user=matrixvirus@163.com
    set smtp-auth-password=1001001010000011

then send mail from command,

    mailx -v -s "ar yo ok" matrixvirus@163.com
