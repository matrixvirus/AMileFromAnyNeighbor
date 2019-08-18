# if the gitlab you access using an invalid certificate
when you use git on you computer,you will git

	SSL certificate problem: unable to get local issuer certificate
	eer's Certificate issuer is not recognized.

you can

	git config --global http.sslVerify false

to solve it.
