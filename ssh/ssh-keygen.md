# SSH Key Generation

## ED25519 시그니처로 생성

```sh
ssh-keygen -t ed25519 -f $HOME/.ssh/github_ed25519 -N ""
```

### Private Key

```sh
cat $HOME/.ssh/github_ed25519
```

```text
-----BEGIN OPENSSH PRIVATE KEY-----
b3BlbnNzaC1rZXktdjEAAAAABG5vbmUAAAAEbm9uZQAAAAAAAAABAAAAMwAAAAtzc2gtZW
QyNTUxOQAAACDEMj19nGBUWhbXdTbgiZ/nDxygP6fMN4+qKNICl6ktQQAAALCKTeb7ik3m
+wAAAAtzc2gtZWQyNTUxOQAAACDEMj19nGBUWhbXdTbgiZ/nDxygP6fMN4+qKNICl6ktQQ
AAAEDxx/f7ZSN+wswJcGo/RcLZ1Nvj0hGfQu3JgY1UHmgwBsQyPX2cYFRaFtd1NuCJn+cP
HKA/p8w3j6oo0gKXqS1BAAAAJmF1dG93aW5pQGF1dG93aW5pdWktTWFjQm9va1Byby00Lm
xvY2FsAQIDBAUGBw==
-----END OPENSSH PRIVATE KEY-----
```

### Public Key

```sh
cat $HOME/.ssh/bitbucket_ed25519.pub
```

```text
ssh-ed25519 AAAAC3NzaC1lZDI1NTE5AAAAIMQyPX2cYFRaFtd1NuCJn+cPHKA/p8w3j6oo0gKXqS1B comment
```

## RSA 시그니처로 생성

```sh
ssh-keygen -t rsa -b 4096 -f $HOME/.ssh/github_rsa -C "comment" -N ""
```

## 에러

### Add correct host key in `/home/markruler/.ssh/known_hosts`

```sh
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
@    WARNING: REMOTE HOST IDENTIFICATION HAS CHANGED!     @
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
IT IS POSSIBLE THAT SOMEONE IS DOING SOMETHING NASTY!
Someone could be eavesdropping on you right now (man-in-the-middle attack)!
It is also possible that a host key has just been changed.
The fingerprint for the RSA key sent by the remote host is
[...].
Please contact your system administrator.
Add correct host key in /home/markruler/.ssh/known_hosts to get rid of this message.
Offending RSA key in /home/markruler/.ssh/known_hosts:86
RSA host key for [...] has changed and you have requested strict checking.
Host key verification failed.
```

- 해결1: Removes all keys belonging to the specified hostname (with optional port number) from a known_hosts file.

```sh
ssh-keygen -R <ip_address_or_hostname>[:port]
```

- 해결2: `ssh-keyscan`으로 `known_hosts` 파일을 갱신한다. ([SO321167](https://serverfault.com/questions/321167))

```sh
ssh-keyscan <ip_address_or_hostname>[:port] >> ~/.ssh/known_hosts
```
