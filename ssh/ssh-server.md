# SSH Server

## Installation

```sh
sudo apt install openssh-server
```

## Service

```sh
sudo systemctl status ssh
```

## Configuration

### SSH Server Configuration

```sh
sudo vi /etc/ssh/sshd_config
```

#### SSH Server Configuration: `PermitRootLogin`

```sh
# PermitRootLogin prohibit-password
PermitRootLogin yes
```

#### SSH Server Configuration: `PasswordAuthentication`

```sh
# PasswordAuthentication yes
PasswordAuthentication no
```

#### SSH Server Configuration: `PubkeyAuthentication`

```sh
PubkeyAuthentication yes
```
