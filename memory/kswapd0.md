# Swap

- [Swap](#swap)
  - [Virtual Memory](#virtual-memory)
    - [가상 메모리 영역 확인 1](#가상-메모리-영역-확인-1)
    - [가상 메모리 영역 확인 2](#가상-메모리-영역-확인-2)
    - [가상 메모리 영역 확인 3](#가상-메모리-영역-확인-3)
  - [Page Fault 이벤트 확인](#page-fault-이벤트-확인)
  - [Memory Reclaim](#memory-reclaim)

## Virtual Memory

```sh
cat /proc/meminfo | grep Vm
cat /proc/meminfo | grep Swap
```

### 가상 메모리 영역 확인 1

```sh
# 현재 프로세스인 /bin/bash의 PID 출력
echo $$
```

```sh
cat /proc/$$/maps
cat /proc/$PID/maps

55b36db96000-55b36dbc5000 r--p 00000000 103:02 22545664                  /usr/bin/bash
55b36dbc5000-55b36dca4000 r-xp 0002f000 103:02 22545664                  /usr/bin/bash
55b36dca4000-55b36dcde000 r--p 0010e000 103:02 22545664                  /usr/bin/bash
55b36dcdf000-55b36dce3000 r--p 00148000 103:02 22545664                  /usr/bin/bash
55b36dce3000-55b36dcec000 rw-p 0014c000 103:02 22545664                  /usr/bin/bash
55b36dcec000-55b36dcf7000 rw-p 00000000 00:00 0 
55b36fb82000-55b36fceb000 rw-p 00000000 00:00 0                          [heap]
7fbdf2400000-7fbdf2abb000 r--p 00000000 103:02 22544638                  /usr/lib/locale/locale-archive
7fbdf2c00000-7fbdf2c28000 r--p 00000000 103:02 22555459                  /usr/lib/x86_64-linux-gnu/libc.so.6
7fbdf2c28000-7fbdf2dbd000 r-xp 00028000 103:02 22555459                  /usr/lib/x86_64-linux-gnu/libc.so.6
7fbdf2dbd000-7fbdf2e15000 r--p 001bd000 103:02 22555459                  /usr/lib/x86_64-linux-gnu/libc.so.6
7fbdf2e15000-7fbdf2e19000 r--p 00214000 103:02 22555459                  /usr/lib/x86_64-linux-gnu/libc.so.6
7fbdf2e19000-7fbdf2e1b000 rw-p 00218000 103:02 22555459                  /usr/lib/x86_64-linux-gnu/libc.so.6
7fbdf2e1b000-7fbdf2e28000 rw-p 00000000 00:00 0 
7fbdf2efb000-7fbdf2efe000 rw-p 00000000 00:00 0 
7fbdf2efe000-7fbdf2f0c000 r--p 00000000 103:02 22550080                  /usr/lib/x86_64-linux-gnu/libtinfo.so.6.3
7fbdf2f0c000-7fbdf2f1d000 r-xp 0000e000 103:02 22550080                  /usr/lib/x86_64-linux-gnu/libtinfo.so.6.3
7fbdf2f1d000-7fbdf2f2b000 r--p 0001f000 103:02 22550080                  /usr/lib/x86_64-linux-gnu/libtinfo.so.6.3
7fbdf2f2b000-7fbdf2f2f000 r--p 0002c000 103:02 22550080                  /usr/lib/x86_64-linux-gnu/libtinfo.so.6.3
7fbdf2f2f000-7fbdf2f30000 rw-p 00030000 103:02 22550080                  /usr/lib/x86_64-linux-gnu/libtinfo.so.6.3
7fbdf2f3b000-7fbdf2f42000 r--s 00000000 103:02 23203949                  /usr/lib/x86_64-linux-gnu/gconv/gconv-modules.cache
7fbdf2f42000-7fbdf2f44000 rw-p 00000000 00:00 0 
7fbdf2f44000-7fbdf2f46000 r--p 00000000 103:02 22545014                  /usr/lib/x86_64-linux-gnu/ld-linux-x86-64.so.2
7fbdf2f46000-7fbdf2f70000 r-xp 00002000 103:02 22545014                  /usr/lib/x86_64-linux-gnu/ld-linux-x86-64.so.2
7fbdf2f70000-7fbdf2f7b000 r--p 0002c000 103:02 22545014                  /usr/lib/x86_64-linux-gnu/ld-linux-x86-64.so.2
7fbdf2f7c000-7fbdf2f7e000 r--p 00037000 103:02 22545014                  /usr/lib/x86_64-linux-gnu/ld-linux-x86-64.so.2
7fbdf2f7e000-7fbdf2f80000 rw-p 00039000 103:02 22545014                  /usr/lib/x86_64-linux-gnu/ld-linux-x86-64.so.2
7fff49843000-7fff49864000 rw-p 00000000 00:00 0                          [stack]
7fff499ca000-7fff499ce000 r--p 00000000 00:00 0                          [vvar]
7fff499ce000-7fff499d0000 r-xp 00000000 00:00 0                          [vdso]
ffffffffff600000-ffffffffff601000 --xp 00000000 00:00 0                  [vsyscall]
```

- binary (`/usr/bin/bash`)
- heap
- stack
- vvar
- vdso
- vsyscall

```sh
# self도 현재 프로세스를 나타내기 때문에 cat 프로세스의 메모리 영역을 볼 수 있음
cat /proc/self/maps
```

### 가상 메모리 영역 확인 2

```sh
cat /proc/self/status | grep Vm
```

### 가상 메모리 영역 확인 3

```sh
gcc memory_proc.c
./a.out
```

## Page Fault 이벤트 확인

page_fault 이벤트 트레이싱

```sh
echo 1 > /sys/kernel/debug/tracing/events/exceptions/page_fault_user/enable
```

```sh
cat /sys/kernel/debug/tracing/trace_pipe
```

전체 이벤트 tracing 끄기

```sh
echo 0 > /sys/kernel/debug/tracing/events/enable
```

## Memory Reclaim

```sh
ps -ef | grep kswapd0
```

```sh
python3 page_reclaim.py
```
