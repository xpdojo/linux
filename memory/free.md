# free

## buff/cache

```sh
free -h
               total        used        free      shared  buff/cache   available
Mem:            31Gi       6.7Gi        19Gi       498Mi       5.2Gi        23Gi
Swap:           15Gi          0B        15Gi
```

Linux에서 `drop_cache`는 파일 시스템 캐시를 비워주는 기능입니다.
인자값으로는 3개가 있습니다.

`proc` [매뉴얼](https://man7.org/linux/man-pages/man5/proc.5.html)에서
`drop_cache` 인자에 대한 설명을 찾을 수 있습니다.

```sh
man proc
```

- `1`: 페이지 캐시만 비웁니다.
- `2`: dentry 및 inode 캐시를 비웁니다.
- `3`: 페이지, dentry 및 inode 캐시를 모두 비웁니다.

```sh
# user
echo 3 | sudo tee /proc/sys/vm/drop_caches

# root
echo 3 > /proc/sys/vm/drop_caches
```

```sh
free -h
               total        used        free      shared  buff/cache   available
Mem:            31Gi       6.8Gi        22Gi       518Mi       2.0Gi        23Gi
Swap:           15Gi          0B        15Gi
```
