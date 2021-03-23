# Find our IP

At first we should find our Ip address. Run `ip a` or `ifconfig` command in your shell
interpreter for this.  
Priority use `ip a` because this command show all IPs with its subnetwork address.

[comment]: <> (include print screen with command output)

# Scan our subnetwork

Our IP is `// input ip`. Then we scan our subnetwork, using `nmap <IP>`.  
Is recommended tune your Boot2Root VM with bridge network connection.

[comment]: <> (include print screen with command output)

Required IP will be marked by "Boot2Root Hack Me" string or will have only list
opened services such as:  
***ftp, ssh, http, imap, https, imaps***, - with its port.

So we see is opened *http* and *https* services we can scan its.

# Dirb

We want to find another web-resources hosted on this web-server.  
Use `dirb https://<IP> -r`

[comment]: <> (include print screen with command output)

Was found 3 web-sites:  
- forum
- webmail
- phpmyadmin

# Forum

Let's go to the forum. We see 4 posts there and one of it have name "Probleme login ?".  
We find log from ssh connection, opening this post.

Extract information with `curl --insecure https://<IP>/forum/index.php?id=6 | grep 'invalid user'`

[comment]: <> (include print screen with command output)

We see string like a password typed instead of username:

[comment]: <> (include print screen with command output)

Try to connect via ssh `ssh lmezard@<IP>`

[comment]: <> (include print screen with command output)

Permission denied. Ok, try login on forum with same credentials. Well done!)  
Check lmezard's user profile.

[comment]: <> (include print screen with command output)

Copy his e-mail and go to webmail web-site.

# Mail

Try login with copied e-mail and password from forum.  
We was been accepted. There is 2 e-mails, opening both we can find credentials for connection to a DB.

# Php My Admin

Login there with login and password from previous step.