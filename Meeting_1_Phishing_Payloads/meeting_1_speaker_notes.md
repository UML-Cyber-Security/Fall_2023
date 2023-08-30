# Speaker Notes Meeting 1

## Prereqs (before meeting)
+ Setup mail server to spoof email on the umlcyber.club domain.
+ Have several windows VMs set up, in case one breaks. Can use Proxmox for this.
+ Do I need to set up windows VMs on the Cyber Range machines?

### Mail Server Setup
Amazon SES
+ Verify the domain
+ Setup verified sender addresses
+ Get SMTP credentials
#### From scratch (not likely, who wants to pay for cloud hosting & get ports unblocked)
+ Postfix
+ Dovecot (to access over Outlook)
+ Roundcube (webmail interface)

### .scr/.exe files
mingw-w64 that provides a cross-compiler for Windows.

### Website setup?
+ Setup website as a payload they can download & run if they want to
