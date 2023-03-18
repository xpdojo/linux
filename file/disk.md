# Disk

```sh
df -Th

# Filesystem     Type   Size  Used Avail Use% Mounted on
# tmpfs          tmpfs  3.2G  2.2M  3.2G   1% /run
# /dev/nvme0n1p2 ext4   457G  107G  327G  25% /
# tmpfs          tmpfs   16G  264M   16G   2% /dev/shm
# tmpfs          tmpfs  5.0M  4.0K  5.0M   1% /run/lock
# /dev/nvme0n1p1 vfat   511M  5.3M  506M   2% /boot/efi
# tmpfs          tmpfs  3.2G  2.4M  3.2G   1% /run/user/1000
```

```sh
lsblk /dev/nvme0n1

# NAME        MAJ:MIN RM   SIZE RO TYPE MOUNTPOINTS
# nvme0n1     259:0    0 465.8G  0 disk 
# ├─nvme0n1p1 259:1    0   512M  0 part /boot/efi
# └─nvme0n1p2 259:2    0 465.3G  0 part /var/snap/firefox/common/host-hunspell
```

```sh
sudo fdisk -l /dev/nvme0n1

# Disk /dev/nvme0n1: 465.76 GiB, 500107862016 bytes, 976773168 sectors
# Disk model: Samsung SSD 970 EVO Plus 500GB          
# Units: sectors of 1 * 512 = 512 bytes
# Sector size (logical/physical): 512 bytes / 512 bytes
# I/O size (minimum/optimal): 512 bytes / 512 bytes
# Disklabel type: gpt
# Disk identifier: 1623B5FC-7505-4FFC-B71F-2C989707B479

# Device           Start       End   Sectors   Size Type
# /dev/nvme0n1p1    2048   1050623   1048576   512M EFI System
# /dev/nvme0n1p2 1050624 976771071 975720448 465.3G Linux filesystem
```
