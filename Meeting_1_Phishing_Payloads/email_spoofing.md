# Email Spoofing
I don't think it is possible to get an email sever to spoof email by the time the meeting starts. 

This is my attempt to do so:

## Attempt 1: Amazon SES
1. Add the CNAME DNS records in Cloudflare to verify your domain ownersip
2. Setup verified sender addresses
3. Get SMTP credentials

At this point you can send email within your domain, or to verified recipients. 
The only way to get to spoofing level would be to get out of the SES sandbox, and I am pretty sure that if I state my intentions truthfully as "I want to spoof email," it will be automatically rejected

## Attempt 2: DigitalOcean
Following this tutorial: <https://youtu.be/j6NJnFcyIhQ?si=m0w_QdXSa3uatvGO>

1. Make a Droplet on DigitalOcean
2. On the droplet, run the docker files he made [here](https://github.com/6point6/mail-spoofer) to setup GoPhish
3. Realize DigitalOcean blocks port 25, and even if it was not blocked you would be on a blacklist
4. Give up

## Attempt 3: Hetzner
I am going to try Hetzner next. 

They are cheaper than DigitalOcean, and don't block port 25 (I think), but you have to have used them for 30 days before they give it to you.

### The plan once I get unblocked on Hetzner
Spoofing email is easy. The hard part is recieving it. 
To recieve email:
+ Postfix
+ Dovecot (to access over Outlook)
+ Roundcube (webmail interface)

## Attempt 4: Internal Email Server?
+ But they would need to be on the CCDC VPN to access it?
1. Setup a linux VM
2. Run `sudo apt install postfix dovecot-imapd dovecot-pop3d`
3. In Postfix's 'General mail configuration type', select 'Local Only'
4. in sudo nano /etc/postfix/main.cf I changed inet_interfaces to all
5. Restart Postfix to apply the changes. `sudo systemctl restart postfix`

For more information about dovecot:
<https://ubuntu.com/server/docs/mail-dovecot>

Run `sudo apt install mailutils`

Send a test email with: echo "Test mail body" | mail -s "Test subject" user@cyber-club.uml

To view dovecot's logs, run: `cat /var/log/mail.log`

To confirm your services are running, you can run 
`telnet localhost 143` to check IMAP, `telnet localhost 110` to check POP3
and `telnet localhost 25` for SMTP

To escape telnet, type `ctrl + ]` then at the new prompt, type `close`

To view the postfix configuration, type `postconf -n`

To change the postfix configuration, go to /etc/postfix/

The main configuration is main.cf

`mynetworks = 127.0.0.0/8, 192.168.0.0/21` (the cyber range is /21 CIDR notation, I asked Chris)

After making changes, run `sudo systemctl reload postfix`

`echo "Test mail body" | mail -s "Test subject" cyber-club@mail-server`

To view the mail of a user, look in /var/mail/username

To spoof an email, the sender is different from the 

`echo "Test mail body" | mail -s "Test subject" -a "From: forged-sender@mail-server" cyber-club@mail-server``

When conencting to Dovecot from Outlook, view error messages with
`tail -f /var/log/mail.log`

By default dovecot uses PAM (Pluggable Authentication Module) for the passdb (Password database), meaning it will authenticate users based on the system's user accounts.

To test the user's dovecot password, run `sudo doveadm auth test cyber-club [password]`

To do the equivalent of telnet in windows powershell, run `Test-NetConnection -ComputerName 192.168.0.6 -InformationLevel "Detailed" -Port 3389`

To access the email, I used Thunderbird with IMAP.

To forge an email, you can go to settings -> account settings




