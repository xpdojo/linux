# 최대 open 파일 개수

시스템에서 열 수 있는 파일의 최대 개수를 확인한다.

```sh
cat /proc/sys/fs/file-max
```

```sh
ulimit -a
```

```sh
-t: cpu time (seconds)              unlimited
-f: file size (blocks)              unlimited
-d: data seg size (kbytes)          unlimited
-s: stack size (kbytes)             8192
-c: core file size (blocks)         0
-m: resident set size (kbytes)      unlimited
-u: processes                       127821
-n: file descriptors                1024
-l: locked-in-memory size (kbytes)  4100240
-v: address space (kbytes)          unlimited
-x: file locks                      unlimited
-i: pending signals                 127821
-q: bytes in POSIX msg queues       819200
-e: max nice                        0
-r: max rt priority                 0
-N 15:                              unlimited
```

동시에 열 수 있는 파일 디스크립터 개수는 ulimit으로도 확인할 수 있다.

```sh
# Soft
ulimit -Sn 

# Hard
ulimit -Hn
```

다른 세션 혹은 리부트해서도 유지되도록 설정하려면 `/etc/security/limits.conf`에 설정한다.

```sh
# /etc/security/limits.conf
*               soft    nofile            65536
*               hard    nofile            65536
root            soft    nofile            65536
root            hard    nofile            65536
```

```sh
prlimit
```

```sh
RESOURCE   DESCRIPTION                              SOFT       HARD UNITS
AS         address space limit                 unlimited  unlimited bytes
CORE       max core file size                          0  unlimited bytes
CPU        CPU time                            unlimited  unlimited seconds
DATA       max data size                       unlimited  unlimited bytes
FSIZE      max file size                       unlimited  unlimited bytes
LOCKS      max number of file locks held       unlimited  unlimited locks
MEMLOCK    max locked-in-memory address space 4198645760 4198645760 bytes
MSGQUEUE   max bytes in POSIX mqueues             819200     819200 bytes
NICE       max nice prio allowed to raise              0          0 
NOFILE     max number of open files                 1024    1048576 files
NPROC      max number of processes                127821     127821 processes
RSS        max resident set size               unlimited  unlimited bytes
RTPRIO     max real-time priority                      0          0 
RTTIME     timeout for real-time tasks         unlimited  unlimited microsecs
SIGPENDING max number of pending signals          127821     127821 signals
STACK      max stack size                        8388608  unlimited bytes
```
