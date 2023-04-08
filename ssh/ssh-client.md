# SSH Client

## Installation

```sh
sudo apt install openssh-client
```

## Commands

```sh
ssh user@host
```

```sh
ssh -i $HOME/.ssh/github_ed25519 -p 22 user@host
```

```sh
ssh -i $HOME/.ssh/github_ed25519 -p 22 user@host -t "command"
```

```sh
# some-host는 ssh_config에 등록된 호스트명
ssh some-host -t "pwd"
```

## Configuration

설정 우선순위는 다음과 같다.

- 명령행 옵션이 가장 우선한다.
- `$HOME/.ssh/config` 파일: 사용자별 설정 파일
- `/etc/ssh/ssh_config` 파일
  - `/etc/ssh/ssh_config.d/*.conf` 파일은 `/etc/ssh/ssh_config` 파일에 포함된다.

위 설정들을 전부 무시하려면 설정 파일을 직접 지정하는 `-F` 옵션에 `/dev/null` 을 입력한다.

```sh
ssh -F /dev/null user@host
```

### 옵션

- `Host`
  - 호스트명을 지정한다.
  - `*`와 같은 와일드카드를 사용할 수 있다.
  - `Host *`는 모든 호스트에 적용된다.
- `HostName`: 호스트명을 지정한다.
- `Port`: 포트번호를 지정한다.
- `User`: 사용자명을 지정한다.
- `IdentityFile`: Private Key 파일을 지정한다.

## Host Example

### 모든 호스트에 적용

```sh
Host *
  Port 22 # default
  User ubuntu
  IdentityFile ~/.ssh/id_ed25519
```

### 특정 호스트

```sh
Host jenkins
  HostName 192.168.0.219
  User = jenkins
```

### Bitbucket

```sh
Host bitbucket
  HostName bitbucket.org
  User git
  IdentityFile ~/.ssh/bitbucket_ed25519

# HostName을 생략하면 Host의 값이 사용된다.
Host bitbucket.org
  User git
  IdentityFile ~/.ssh/bitbucket_ed25519
```

### GitHub

```sh
Host github.com
  User git
  IdentityFile ~/.ssh/github_ed25519
```

### 두 개의 계정을 사용하는 GitHub

- [Git 계정 여러 개 동시 사용하기](https://blog.outsider.ne.kr/1448) - Outsider

```sh
# 회사 계정
Host work.github.com
  HostName github.com
  User git
  IdentityFile ~/.ssh/github_work_ed25519

# 개인 계정
Host github.com
  User git
  IdentityFile ~/.ssh/github_ed25519
```

Git remote URL에 `work.github.com`를 사용한다.

```sh
git clone git@work.github.com:markruler/linux.git
```

## 에러

### no matching host key type found

다음과 같은 에러가 발생 시 제공되는 key type을 지정한다.

```sh
Unable to negotiate with markruler.com port 22:
no matching host key type found.
Their offer: ssh-rsa,ssh-dss
```

```sh
Host tost
  HostName test.markruler.com
  Port 22
  HostKeyAlgorithms=+ssh-rsa,ssh-dss
  User markruler
  LogLevel VERBOSE
```
