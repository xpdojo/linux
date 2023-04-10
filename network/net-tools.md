# net-tools

[net-tools](https://net-tools.sourceforge.io/),
A collection of programs that form the base set of the NET-3 networking distribution
for the Linux operating system. - [Linux Foundation](https://wiki.linuxfoundation.org/networking/net-tools)

| net-tools                                                        | 대체 명령어 | 자주 쓰는 명령어         |
| ---------------------------------------------------------------- | ----------- | ------------------------ |
| [netstat](https://net-tools.sourceforge.io/man/netstat.8.html)   | ss          | ss -nltp                 |
| [arp](https://net-tools.sourceforge.io/man/arp.8.html)           | ip neigh    | ip -br -c n              |
| [ifconfig](https://net-tools.sourceforge.io/man/ifconfig.8.html) | ip addr     | ip -br -c a              |
| ipmaddr                                                          | ip maddr    | ip -c ma                 |
| iptunnel                                                         | ip tunnel   | -                        |
| [route](https://net-tools.sourceforge.io/man/route.8.html)       | ip route    | ip -c r                  |
| [hostname](https://net-tools.sourceforge.io/man/hostname.1.html) | hostname    | hostnamectl set-hostname |

기존 net-tools를 사용하기 위해서는 설치가 필요하다.

```sh
sudo apt install net-tools
```
