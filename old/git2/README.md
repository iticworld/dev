# NOVEMBERIZING'S GIT JAVASCRIPT LIB

## DEVELOPMENT ENVIRONMENTS

 - node

  - esm
  - xmlhttprequest
  - text-encoding
  - base64-js
  
 - gitlab

```
sudo apt-get update
sudo apt-get install -y curl openssh-server ca-certificates
curl https://packages.gitlab.com/install/repositories/gitlab/gitlab-ee/script.deb.sh | sudo bash
sudo EXTERNAL_URL="http://gitlab.example.com" apt-get install gitlab-ee
sudo gitlab-ctl reconfigure
```

## SPECIFICATION

In protocol v2 these special packets will have the following semantics:

 - '0000' Flush Packet (flush-pkt) - indicates the end of a message
 - '0001' Delimiter Packet (delim-pkt) - separates sections of a message

 Initial Client Request
------------------------
 
## SEE

 - https://about.gitlab.com/installation/#ubuntu
 
