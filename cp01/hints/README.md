# Рекомендации

В устройстве вашего компьютера, (да и компьютеров в классе), 
помогут разобраться команды. Сами команды для Вашей системы могут отличаться. 
Например. у меня нет очень полезной команды `hwinfo`.

Для начала можно попробовать, то что приведено тут.
Кроме того, аналогичную инфомацию можно получить с помощью `dmidecode`.
http://linux-bash.ru/menusistem/106-dmidecode.html

# Топология вашей машины

Топология вашей машины (покажет в отдельном окне):

    $> lstopo 

![Изображение. Результат команды lstopo](https://pbs.twimg.com/media/BbBRXFfCAAAADlx.png "Результат команды lstopo")

# Процессор

## Информация о процессоре

    $> lscpu

### Пример

    [w495@w495 ~]$ lscpu
    Architecture:          x86_64
    CPU op-mode(s):        32-bit, 64-bit
    Byte Order:            Little Endian
    CPU(s):                4
    On-line CPU(s) list:   0-3
    Thread(s) per core:    2
    Core(s) per socket:    2
    Socket(s):             1
    NUMA node(s):          1
    Vendor ID:             GenuineIntel
    CPU family:            6
    Model:                 42
    Stepping:              7
    CPU MHz:               800.000
    BogoMIPS:              3392.31
    Virtualization:        VT-x
    L1d cache:             32K
    L1i cache:             32K
    L2 cache:              256K
    L3 cache:              3072K
    NUMA node0 CPU(s):     0-3

## Подробнее о процессоре

    $> cat /proc/cpuinfo 

### Пример

    [w495@w495 ~]$ cat /proc/cpuinfo 
    processor   : 0
    vendor_id   : GenuineIntel
    cpu family  : 6
    model       : 42
    model name  : Intel(R) Core(TM) i5-2557M CPU @ 1.70GHz
    stepping    : 7
    microcode   : 0x1a
    cpu MHz     : 800.000
    cache size  : 3072 KB
    physical id : 0
    siblings    : 4
    core id     : 0
    cpu cores   : 2
    apicid      : 0
    initial apicid  : 0
    fpu     : yes
    fpu_exception   : yes
    cpuid level : 13
    wp      : yes
    flags       : fpu vme de pse tsc msr pae mce cx8 apic sep mtrr pge \
                  mca cmov pat pse36 clflush dts acpi mmx fxsr sse sse2 \
                  ss ht tm pbe syscall nx rdtscp lm constant_tsc arch_perfmon \
                  pebs bts rep_good nopl xtopology nonstop_tsc aperfmperf \
                  eagerfpu pni pclmulqdq dtes64 monitor ds_cpl vmx smx est \
                  tm2 ssse3 cx16 xtpr pdcm pcid sse4_1 sse4_2 x2apic popcnt \
                  tsc_deadline_timer aes xsave avx lahf_lm ida arat epb \
                  xsaveopt pln pts dtherm tpr_shadow vnmi flexpriority ept vpid
    bogomips    : 3392.31
    clflush size    : 64
    cache_alignment : 64
    address sizes   : 36 bits physical, 48 bits virtual
    power management:

    processor   : 1
    vendor_id   : GenuineIntel
    cpu family  : 6
    model       : 42
    model name  : Intel(R) Core(TM) i5-2557M CPU @ 1.70GHz
    stepping    : 7
    microcode   : 0x1a
    cpu MHz     : 800.000
    cache size  : 3072 KB
    physical id : 0
    siblings    : 4
    core id     : 1
    cpu cores   : 2
    apicid      : 2
    initial apicid  : 2
    fpu     : yes
    fpu_exception   : yes
    cpuid level : 13
    wp      : yes
    flags       : fpu vme de pse tsc msr pae mce cx8 apic sep mtrr pge \
                  mca cmov pat pse36 clflush dts acpi mmx fxsr sse sse2 \
                  ss ht tm pbe syscall nx rdtscp lm constant_tsc arch_perfmon \
                  pebs bts rep_good nopl xtopology nonstop_tsc aperfmperf \
                  eagerfpu pni pclmulqdq dtes64 monitor ds_cpl vmx smx est \
                  tm2 ssse3 cx16 xtpr pdcm pcid sse4_1 sse4_2 x2apic popcnt \
                  tsc_deadline_timer aes xsave avx lahf_lm ida arat epb \
                  xsaveopt pln pts dtherm tpr_shadow vnmi flexpriority ept vpid
    bogomips    : 3392.31
    clflush size    : 64
    cache_alignment : 64
    address sizes   : 36 bits physical, 48 bits virtual
    power management:

    processor   : 2
    vendor_id   : GenuineIntel
    cpu family  : 6
    model       : 42
    model name  : Intel(R) Core(TM) i5-2557M CPU @ 1.70GHz
    stepping    : 7
    microcode   : 0x1a
    cpu MHz     : 800.000
    cache size  : 3072 KB
    physical id : 0
    siblings    : 4
    core id     : 0
    cpu cores   : 2
    apicid      : 1
    initial apicid  : 1
    fpu     : yes
    fpu_exception   : yes
    cpuid level : 13
    wp      : yes
    flags       : fpu vme de pse tsc msr pae mce cx8 apic sep mtrr pge \
                  mca cmov pat pse36 clflush dts acpi mmx fxsr sse sse2 \
                  ss ht tm pbe syscall nx rdtscp lm constant_tsc arch_perfmon \
                  pebs bts rep_good nopl xtopology nonstop_tsc aperfmperf \
                  eagerfpu pni pclmulqdq dtes64 monitor ds_cpl vmx smx est \
                  tm2 ssse3 cx16 xtpr pdcm pcid sse4_1 sse4_2 x2apic popcnt \
                  tsc_deadline_timer aes xsave avx lahf_lm ida arat epb \
                  xsaveopt pln pts dtherm tpr_shadow vnmi flexpriority ept vpid
    bogomips    : 3392.31
    clflush size    : 64
    cache_alignment : 64
    address sizes   : 36 bits physical, 48 bits virtual
    power management:

    processor   : 3
    vendor_id   : GenuineIntel
    cpu family  : 6
    model       : 42
    model name  : Intel(R) Core(TM) i5-2557M CPU @ 1.70GHz
    stepping    : 7
    microcode   : 0x1a
    cpu MHz     : 800.000
    cache size  : 3072 KB
    physical id : 0
    siblings    : 4
    core id     : 1
    cpu cores   : 2
    apicid      : 3
    initial apicid  : 3
    fpu     : yes
    fpu_exception   : yes
    cpuid level : 13
    wp      : yes
    flags       : fpu vme de pse tsc msr pae mce cx8 apic sep mtrr pge \
                  mca cmov pat pse36 clflush dts acpi mmx fxsr sse sse2 \
                  ss ht tm pbe syscall nx rdtscp lm constant_tsc arch_perfmon \
                  pebs bts rep_good nopl xtopology nonstop_tsc aperfmperf \
                  eagerfpu pni pclmulqdq dtes64 monitor ds_cpl vmx smx est \
                  tm2 ssse3 cx16 xtpr pdcm pcid sse4_1 sse4_2 x2apic popcnt \
                  tsc_deadline_timer aes xsave avx lahf_lm ida arat epb \
                  xsaveopt pln pts dtherm tpr_shadow vnmi flexpriority ept vpid
    bogomips    : 3392.31
    clflush size    : 64
    cache_alignment : 64
    address sizes   : 36 bits physical, 48 bits virtual
    

# ОЗУ

## Свободная память:

    $> free -lht

### Пример

Читайте `man free`.

    [w495@w495 ~]$ free -lht
                 total       used       free     shared    buffers     cached
    Mem:          3,8G       3,6G       165M         0B        30M       990M
    Low:          3,8G       3,6G       165M
    High:           0B         0B         0B
    -/+ buffers/cache:       2,6G       1,2G
    Swap:           0B         0B         0B
    Total:        3,8G       3,6G       165M

## Подробнее про ОЗУ

    $> cat /proc/meminfo


### Пример

    [w495@w495 ~]$ cat /proc/meminfo
    MemTotal:        3948340 kB
    MemFree:          155576 kB
    Buffers:           31368 kB
    Cached:          1036556 kB
    SwapCached:            0 kB
    Active:          2783588 kB
    Inactive:         741880 kB
    Active(anon):    2546572 kB
    Inactive(anon):   363520 kB
    Active(file):     237016 kB
    Inactive(file):   378360 kB
    Unevictable:        3500 kB
    Mlocked:            3500 kB
    SwapTotal:             0 kB
    SwapFree:              0 kB
    Dirty:              4748 kB
    Writeback:             0 kB
    AnonPages:       2461060 kB
    Mapped:           208172 kB
    Shmem:            450272 kB
    Slab:             104904 kB
    SReclaimable:      53316 kB
    SUnreclaim:        51588 kB
    KernelStack:        5272 kB
    PageTables:        72164 kB
    NFS_Unstable:          0 kB
    Bounce:                0 kB
    WritebackTmp:          0 kB
    CommitLimit:     1974168 kB
    Committed_AS:    6727924 kB
    VmallocTotal:   34359738367 kB
    VmallocUsed:      360936 kB
    VmallocChunk:   34359286908 kB
    HardwareCorrupted:     0 kB
    AnonHugePages:    284672 kB
    HugePages_Total:       0
    HugePages_Free:        0
    HugePages_Rsvd:        0
    HugePages_Surp:        0
    Hugepagesize:       2048 kB
    DirectMap4k:      115744 kB
    DirectMap2M:     3979264 kB

# Шина

Шина ввода-вывода:

    $> lspci


### Пример

    [w495@w495 ~]$ lspci
    00:00.0 Host bridge: Intel Corporation 2nd Generation Core Processor Family 
            DRAM Controller (rev 09)
    00:02.0 VGA compatible controller: Intel Corporation 2nd Generation 
            Core Processor Family Integrated Graphics Controller (rev 09)
    00:16.0 Communication controller: Intel Corporation 6 Series/C200 Series 
            Chipset Family MEI Controller #1 (rev 04)
    00:1b.0 Audio device: Intel Corporation 6 Series/C200 Series 
            Chipset Family High Definition Audio Controller (rev 05)
    00:1c.0 PCI bridge: Intel Corporation 6 Series/C200 Series 
            Chipset Family PCI Express Root Port 1 (rev b5)
    00:1c.1 PCI bridge: Intel Corporation 6 Series/C200 Series 
            Chipset Family PCI Express Root Port 2 (rev b5)
    00:1c.3 PCI bridge: Intel Corporation 6 Series/C200 Series 
            Chipset Family PCI Express Root Port 4 (rev b5)
    00:1d.0 USB controller: Intel Corporation 6 Series/C200 Series 
            Chipset Family USB Enhanced Host Controller #1 (rev 05)
    00:1f.0 ISA bridge: Intel Corporation QS67 Express 
            Chipset Family LPC Controller (rev 05)
    00:1f.2 SATA controller: Intel Corporation 6 Series/C200 Series 
            Chipset Family 6 port SATA AHCI Controller (rev 05)
    00:1f.3 SMBus: Intel Corporation 6 Series/C200 Series 
            Chipset Family SMBus Controller (rev 05)
    02:00.0 Network controller: Atheros Communications Inc. 
            AR9485 Wireless Network Adapter (rev 01)
    03:00.0 USB controller: Fresco Logic FL1009 USB 3.0 Host Controller (rev 02)

    
Как мне представляется для выполнения курсовой работы, было бы очень удобно
получить список устройств, который сообщает команда `lspci` и потом рассказать
про эти устройства.

# Диски

## SCSI

    $> lsscsi

### Пример

    [w495@w495 ~]$ lsscsi
    [0:0:0:0]    disk    ATA      SanDisk SSD U100 10.0  /dev/sda 


## Дерево блочных устройств

    $> lsblk

### Пример

    [w495@w495 ~]$ lsblk
    NAME                   MAJ:MIN RM   SIZE RO TYPE MOUNTPOINT
    sda                      8:0    0 238,5G  0 disk 
    ├─sda1                   8:1    0  95,4G  0 part 
    ├─sda2                   8:2    0     8G  0 part /var
    ├─sda3                   8:3    0     8G  0 part 
    ├─sda4                   8:4    0     1K  0 part 
    ├─sda5                   8:5    0   512M  0 part /boot
    └─sda6                   8:6    0 126,6G  0 part 
      ├─fedora-root (dm-0) 253:0    0    40G  0 lvm  /
      └─fedora-home (dm-1) 253:1    0  86,6G  0 lvm  /home


## Разделы и файловые системы:

    $> sudo fdisk -l /dev/sda

### Пример

    [w495@w495 ~]$ sudo fdisk -l /dev/sda
    [sudo] password for w495: 

    Disk /dev/sda: 256.1 GB, 256060514304 bytes, 500118192 sectors
    Units = sectors of 1 * 512 = 512 bytes
    Sector size (logical/physical): 512 bytes / 512 bytes
    I/O size (minimum/optimal): 512 bytes / 512 bytes
    Disk identifier: 0x13ba8fcf

    Устр-во   Загр  Начало       Конец       Блоки   Id  Система
    /dev/sda1  *      2048   200048639   100023296    7  HPFS/NTFS/exFAT
    /dev/sda2    200048640   216825855     8388608   82  Linux своп / Solaris
    /dev/sda3    483340288   500117503     8388608   1c  Скрытый W95 FAT32 (LBA)
    /dev/sda4    216825856   483340287   133257216    5  Расширенный
    /dev/sda5    216827904   217876479      524288   83  Linux
    /dev/sda6    217878528   483340287   132730880   8e  Linux LVM

Пункты таблицы разделов расположены не в дисковом порядке.


## Разделы и файловые системы

    $> df -TH

### Пример

    [w495@w495 ~]$ df -TH
    Файловая система        Тип      Размер  Исп. Дост. Исп.% Cмонтировано в
    devtmpfs                devtmpfs  2,1G    0   2,1G    0%   /dev
    tmpfs                   tmpfs     2,1G  381k  2,1G    1%   /dev/shm
    tmpfs                   tmpfs     2,1G  7,2M  2,1G    1%   /run
    tmpfs                   tmpfs     2,1G     0  2,1G    0%   /sys/fs/cgroup
    /dev/mapper/fedora-root ext4       43G   31G   10G   76%   /
    tmpfs                   tmpfs     2,1G  168k  2,1G    1%   /tmp
    /dev/sda2               ext4      8,4G  3,3G  4,6G   42%   /var
    /dev/sda5               ext4      512M  214M  261M   46%   /boot
    /dev/mapper/fedora-home ext4       92G   80G  7,3G   92%   /home


# Информация про USB

    $> lsusb

### Пример

    [w495@w495 ~]$ lsusb
    Bus 001 Device 002: ID 8087:0024 Intel Corp. Integrated Rate Matching Hub
    Bus 001 Device 001: ID 1d6b:0002 Linux Foundation 2.0 root hub
    Bus 002 Device 001: ID 1d6b:0002 Linux Foundation 2.0 root hub
    Bus 003 Device 001: ID 1d6b:0003 Linux Foundation 3.0 root hub
    Bus 001 Device 003: ID 13d3:5719 IMC Networks 
    Bus 001 Device 004: ID 0bda:0139 Realtek Semiconductor Corp. 
                                     RTS5139 Card Reader Controller
    Bus 001 Device 050: ID 13d3:3375 IMC Networks 


# Видеокарта


## Модель видеокарты

См. lspci

    $> lspci | grep VGA 

### Пример

    [w495@w495 ~]$ lspci | grep VGA 
    00:02.0 VGA compatible controller: Intel Corporation 2nd Generation 
                Core Processor Family Integrated Graphics Controller (rev 09)


## Производитель видеокарты

    $> glxinfo | grep vendor  

### Пример

    [w495@w495 ~]$ glxinfo | grep vendor 
    server glx vendor string: SGI
    client glx vendor string: Mesa Project and SGI
    OpenGL vendor string: Intel Open Source Technology Center


# Поддерживаемые монитором разрешения

    $> xrandr 

### Пример

    [w495@w495 ~]$ xrandr 
    Screen 0: minimum 320 x 200, current 1600 x 900, maximum 8192 x 8192
    eDP1 connected 1600x900+0+0 
    (normal left inverted right x axis y axis) 293mm x 164mm
       1600x900       60.0*+
       1024x768       60.0  
       800x600        60.3     56.2  
       640x480        59.9  
    VGA1 disconnected (normal left inverted right x axis y axis)
    HDMI1 disconnected (normal left inverted right x axis y axis)
    DP1 disconnected (normal left inverted right x axis y axis)

# Аудио

## Аудио-контроллеры:

    $> lspci | grep Audio

### Пример
    
    [w495@w495 ~]$ lspci | grep Audio
    00:1b.0 Audio device: Intel Corporation 6 Series/C200 Series 
                          Chipset Family High Definition Audio Controller 
                          (rev 05)


## Расширенная информация об аудио-контроллера

    $> aplay --list-devices 

### Пример

    [w495@w495 ~]$ aplay --list-devices 
    **** List of PLAYBACK Hardware Devices ****
    card 0: PCH [HDA Intel PCH], device 0: ALC269VB Analog [ALC269VB Analog]
      Subdevices: 1/1
      Subdevice #0: subdevice #0
    card 0: PCH [HDA Intel PCH], device 3: HDMI 0 [HDMI 0]
      Subdevices: 1/1
      Subdevice #0: subdevice #0



# Список устройств:

    $> sudo lshw-gui

## lshw-gui

![Изображение. Результат команды lshw-gui](https://pbs.twimg.com/media/BbBfkrNCAAAwszV.png "Результат команды lshw-gui")

## lshw

    $> sudo lshw

### Пример

    [w495@w495 ~]$ sudo lshw 
    w495
        description: Notebook
        product: UX31E
        vendor: ASUSTeK Computer Inc.
        version: 1.0
        serial: C1N0AS294366036
        width: 64 bits
        capabilities: smbios-2.6 dmi-2.6 vsyscall32
        configuration: boot=normal chassis=notebook family=UX 
                       uuid=004D0B43-3443-E181-2DED-C8600016EB94
      *-core
           description: Motherboard
           product: UX31E
           vendor: ASUSTeK Computer Inc.
           physical id: 0
           version: 1.0
           serial: BSN12345678901234567
           slot: MIDDLE
         *-firmware
              description: BIOS
              vendor: American Megatrends Inc.
              physical id: 0
              version: UX31E.214
              date: 08/14/2012
              size: 64KiB
              capacity: 2496KiB
              capabilities: pci upgrade shadowing cdboot bootselect edd 
                            int13floppy1200 int13floppy720 int13floppy2880 
                            int5printscreen int9keyboard int14serial 
                            int17printer acpi usb smartbattery 
                            biosbootspecification
         *-cpu
              description: CPU
              product: Core 2 Duo (To Be Filled By O.E.M.)
              vendor: Intel Corp.
              physical id: 4
              bus info: cpu@0
              version: Intel(R) Core(TM) i5-2557M CPU @ 1.70GHz
              serial: To Be Filled By O.E.M.
              slot: CPU 1
              size: 1701MHz
              capacity: 4GHz
              width: 64 bits
              clock: 100MHz
              capabilities: x86-64 fpu fpu_exception wp vme de pse tsc msr pae 
                            mce cx8 apic sep mtrr pge mca cmov pat pse36 
                            clflush dts acpi mmx fxsr sse sse2 ss ht tm 
                            pbe syscall nx rdtscp constant_tsc 
                            arch_perfmon pebs bts rep_good nopl xtopology 
                            nonstop_tsc aperfmperf eagerfpu pni pclmulqdq 
                            dtes64 monitor ds_cpl vmx smx est tm2 ssse3 
                            cx16 xtpr pdcm pcid sse4_1 sse4_2 x2apic 
                            popcnt tsc_deadline_timer aes xsave avx lahf_lm 
                            ida arat epb xsaveopt pln pts dtherm 
                            tpr_shadow vnmi flexpriority ept vpid cpufreq
              configuration: cores=2 enabledcores=1 threads=2
         *-memory
              description: System Memory
              physical id: 40
              slot: System board or motherboard
              size: 4GiB
            *-bank:0
                 description: SODIMM DDR3 Synchronous 1333 MHz (0,8 ns)
                 product: [Empty]
                 vendor: Elpida
                 physical id: 0
                 serial: 00000000
                 slot: ChannelA-DIMM0
                 size: 2GiB
                 width: 64 bits
                 clock: 1333MHz (0.8ns)
            *-bank:1
                 description: DIMM [empty]
                 product: [Empty]
                 vendor: [Empty]
                 physical id: 1
                 serial: [Empty]
                 slot: ChannelA-DIMM1
            *-bank:2
                 description: SODIMM DDR3 Synchronous 1333 MHz (0,8 ns)
                 product: [Empty]
                 vendor: Elpida
                 physical id: 2
                 serial: 00000000
                 slot: ChannelB-DIMM0
                 size: 2GiB
                 width: 64 bits
                 clock: 1333MHz (0.8ns)
            *-bank:3
                 description: DIMM [empty]
                 product: [Empty]
                 vendor: [Empty]
                 physical id: 3
                 serial: [Empty]
                 slot: ChannelB-DIMM1
         *-pci
              description: Host bridge
              product: 2nd Generation Core Processor Family DRAM Controller
              vendor: Intel Corporation
              physical id: 100
              bus info: pci@0000:00:00.0
              version: 09
              width: 32 bits
              clock: 33MHz
            *-display
                 description: VGA compatible controller
                 product: 2nd Generation Core Processor 
                          Family Integrated Graphics Controller
                 vendor: Intel Corporation
                 physical id: 2
                 bus info: pci@0000:00:02.0
                 version: 09
                 width: 64 bits
                 clock: 33MHz
                 capabilities: msi pm vga_controller bus_master cap_list rom
                 configuration: driver=i915 latency=0
                 resources: irq:51 memory:ddc00000-ddffffff 
                            memory:c0000000-cfffffff ioport:e000(size=64)
            *-communication
                 description: Communication controller
                 product: 6 Series/C200 Series Chipset Family MEI Controller #1
                 vendor: Intel Corporation
                 physical id: 16
                 bus info: pci@0000:00:16.0
                 version: 04
                 width: 64 bits
                 clock: 33MHz
                 capabilities: pm msi bus_master cap_list
                 configuration: driver=mei_me latency=0
                 resources: irq:52 memory:dfe09000-dfe0900f
            *-multimedia
                 description: Audio device
                 product: 6 Series/C200 Series Chipset 
                          Family High Definition Audio Controller
                 vendor: Intel Corporation
                 physical id: 1b
                 bus info: pci@0000:00:1b.0
                 version: 05
                 width: 64 bits
                 clock: 33MHz
                 capabilities: pm msi pciexpress bus_master cap_list
                 configuration: driver=snd_hda_intel latency=0
                 resources: irq:53 memory:dfe00000-dfe03fff
            *-pci:0
                 description: PCI bridge
                 product: 6 Series/C200 Series Chipset 
                          Family PCI Express Root Port 1
                 vendor: Intel Corporation
                 physical id: 1c
                 bus info: pci@0000:00:1c.0
                 version: b5
                 width: 32 bits
                 clock: 33MHz
                 capabilities: pci pciexpress msi pm normal_decode 
                               bus_master cap_list
                 configuration: driver=pcieport
                 resources: irq:42 ioport:d000(size=4096) 
                            memory:df400000-dfdfffff 
                            ioport:d1600000(size=10485760)
            *-pci:1
                 description: PCI bridge
                 product: 6 Series/C200 Series Chipset 
                          Family PCI Express Root Port 2
                 vendor: Intel Corporation
                 physical id: 1c.1
                 bus info: pci@0000:00:1c.1
                 version: b5
                 width: 32 bits
                 clock: 33MHz
                 capabilities: pci pciexpress msi pm normal_decode 
                               bus_master cap_list
                 configuration: driver=pcieport
                 resources: irq:43 ioport:c000(size=4096) 
                            memory:dea00000-df3fffff 
                            ioport:d0b00000(size=10485760)
               *-network
                    description: Wireless interface
                    product: AR9485 Wireless Network Adapter
                    vendor: Atheros Communications Inc.
                    physical id: 0
                    bus info: pci@0000:02:00.0
                    logical name: wlan0
                    version: 01
                    serial: 00:08:ca:86:2e:27
                    width: 64 bits
                    clock: 33MHz
                    capabilities: pm msi pciexpress bus_master cap_list 
                                  rom ethernet physical wireless
                    configuration: broadcast=yes driver=ath9k 
                                   driverversion=3.11.4-101.fc18.x86_64 
                                   firmware=N/A ip=192.168.1.4 latency=0 
                                   link=yes multicast=yes 
                                   wireless=IEEE 802.11bgn
                    resources: irq:17 memory:dea00000-dea7ffff 
                               memory:dea80000-dea8ffff
            *-pci:2
                 description: PCI bridge
                 product: 6 Series/C200 Series Chipset Family 
                          PCI Express Root Port 4
                 vendor: Intel Corporation
                 physical id: 1c.3
                 bus info: pci@0000:00:1c.3
                 version: b5
                 width: 32 bits
                 clock: 33MHz
                 capabilities: pci pciexpress msi pm normal_decode 
                               bus_master cap_list
                 configuration: driver=pcieport
                 resources: irq:44 ioport:b000(size=4096) 
                            memory:de000000-de9fffff 
                            ioport:d0000000(size=10485760)
               *-usb
                    description: USB controller
                    product: FL1009 USB 3.0 Host Controller
                    vendor: Fresco Logic
                    physical id: 0
                    bus info: pci@0000:03:00.0
                    version: 02
                    width: 64 bits
                    clock: 33MHz
                    capabilities: pm msi pciexpress msix xhci 
                                  bus_master cap_list
                    configuration: driver=xhci_hcd latency=0
                    resources: irq:19 memory:de000000-de00ffff 
                               memory:de011000-de011fff 
                               memory:de010000-de010fff
                  *-usbhost:0
                       product: xHCI Host Controller
                       vendor: Linux 3.11.4-101.fc18.x86_64 xhci_hcd
                       physical id: 0
                       bus info: usb@3
                       logical name: usb3
                       version: 3.11
                       capabilities: usb-3.00
                       configuration: driver=hub slots=2 speed=5000Mbit/s
                  *-usbhost:1
                       product: xHCI Host Controller
                       vendor: Linux 3.11.4-101.fc18.x86_64 xhci_hcd
                       physical id: 1
                       bus info: usb@2
                       logical name: usb2
                       version: 3.11
                       capabilities: usb-2.00
                       configuration: driver=hub slots=2 speed=480Mbit/s
            *-usb
                 description: USB controller
                 product: 6 Series/C200 Series Chipset 
                          Family USB Enhanced Host Controller #1
                 vendor: Intel Corporation
                 physical id: 1d
                 bus info: pci@0000:00:1d.0
                 version: 05
                 width: 32 bits
                 clock: 33MHz
                 capabilities: pm debug ehci bus_master cap_list
                 configuration: driver=ehci-pci latency=0
                 resources: irq:23 memory:dfe07000-dfe073ff
               *-usbhost
                    product: EHCI Host Controller
                    vendor: Linux 3.11.4-101.fc18.x86_64 ehci_hcd
                    physical id: 1
                    bus info: usb@1
                    logical name: usb1
                    version: 3.11
                    capabilities: usb-2.00
                    configuration: driver=hub slots=2 speed=480Mbit/s
                  *-usb
                       description: USB hub
                       product: Integrated Rate Matching Hub
                       vendor: Intel Corp.
                       physical id: 1
                       bus info: usb@1:1
                       version: 0.00
                       capabilities: usb-2.00
                       configuration: driver=hub slots=8 speed=480Mbit/s
                     *-usb:0
                          description: Video
                          product: USB2.0 VGA Webcam
                          vendor: Azurewave
                          physical id: 5
                          bus info: usb@1:1.5
                          version: 9.19
                          serial: NULL
                          capabilities: usb-2.00
                          configuration: driver=uvcvideo 
                                         maxpower=500mA speed=480Mbit/s
                     *-usb:1 UNCLAIMED
                          description: Generic USB device
                          product: USB2.0-CRW
                          vendor: Generic
                          physical id: 7
                          bus info: usb@1:1.7
                          version: 39.60
                          serial: 20100201396000000
                          capabilities: usb-2.00
                          configuration: maxpower=500mA speed=480Mbit/s
                     *-usb:2
                          description: Bluetooth wireless interface
                          product: Bluetooth USB Host Controller
                          vendor: Atheros Communications
                          physical id: 8
                          bus info: usb@1:1.8
                          version: 0.02
                          serial: Alaska Day 2006
                          capabilities: bluetooth usb-1.10
                          configuration: driver=btusb maxpower=100mA 
                                         speed=12Mbit/s
            *-isa
                 description: ISA bridge
                 product: QS67 Express Chipset Family LPC Controller
                 vendor: Intel Corporation
                 physical id: 1f
                 bus info: pci@0000:00:1f.0
                 version: 05
                 width: 32 bits
                 clock: 33MHz
                 capabilities: isa bus_master cap_list
                 configuration: driver=lpc_ich latency=0
                 resources: irq:0
            *-storage
                 description: SATA controller
                 product: 6 Series/C200 Series Chipset Family 6 port 
                          SATA AHCI Controller
                 vendor: Intel Corporation
                 physical id: 1f.2
                 bus info: pci@0000:00:1f.2
                 version: 05
                 width: 32 bits
                 clock: 66MHz
                 capabilities: storage msi pm ahci_1.0 bus_master cap_list
                 configuration: driver=ahci latency=0
                 resources: irq:45 ioport:e0b0(size=8) ioport:e0a0(size=4) 
                            ioport:e090(size=8) ioport:e080(size=4) 
                            ioport:e060(size=32) memory:dfe06000-dfe067ff
            *-serial UNCLAIMED
                 description: SMBus
                 product: 6 Series/C200 Series Chipset Family SMBus Controller
                 vendor: Intel Corporation
                 physical id: 1f.3
                 bus info: pci@0000:00:1f.3
                 version: 05
                 width: 64 bits
                 clock: 33MHz
                 configuration: latency=0
                 resources: memory:dfe05000-dfe050ff ioport:e040(size=32)
         *-scsi
              physical id: 1
              logical name: scsi0
              capabilities: emulated
            *-disk
                 description: ATA Disk
                 product: SanDisk SSD U100
                 physical id: 0.0.0
                 bus info: scsi@0:0.0.0
                 logical name: /dev/sda
                 version: 10.0
                 serial: 120133300875
                 size: 238GiB (256GB)
                 capabilities: partitioned partitioned:dos
                 configuration: ansiversion=5 logicalsectorsize=512 
                                sectorsize=512 signature=13ba8fcf
               *-volume:0
                    description: Windows NTFS volume
                    physical id: 1
                    bus info: scsi@0:0.0.0,1
                    logical name: /dev/sda1
                    version: 3.1
                    serial: 8a3aebc3-3267-9544-a428-7ea48f86d4c3
                    size: 95GiB
                    capacity: 95GiB
                    capabilities: primary bootable ntfs initialized
                    configuration: clustersize=4096 created=2011-11-15 02:30:03 
                                   filesystem=ntfs label=OS state=clean
               *-volume:1
                    description: EXT4 volume
                    vendor: Linux
                    physical id: 2
                    bus info: scsi@0:0.0.0,2
                    logical name: /dev/sda2
                    logical name: /var
                    version: 1.0
                    serial: 7417bbc3-02c5-47b6-902c-cef3140d0d81
                    size: 8GiB
                        capacity: 8GiB
                        capabilities: primary nofs journaled 
                                      extended_attributes large_files 
                                      huge_files dir_nlink extents 
                                      ext4 ext2 initialized
                        configuration: created=2013-04-05 21:29:29 
                                       filesystem=ext4 label=fedora var 
                                       lastmountpoint=/var 
                                       modified=2013-12-04 11:14:47 
                                       mount.fstype=ext4 
                                       mount.options=rw,noatime,discard,
                                       data=ordered mounted=2013-12-04 11:14:47 
                                       state=mounted
                   *-volume:2
                        description: Windows FAT volume
                        vendor: MSDOS5.0
                        physical id: 3
                        bus info: scsi@0:0.0.0,3
                        logical name: /dev/sda3
                        version: FAT32
                        serial: 6642-5ea2
                        size: 8181MiB
                        capacity: 8GiB
                        capabilities: primary hidden fat initialized
                        configuration: FATs=2 filesystem=fat label=RECOVERY
                   *-volume:3
                        description: Extended partition
                        physical id: 4
                        bus info: scsi@0:0.0.0,4
                        logical name: /dev/sda4
                        size: 127GiB
                        capacity: 127GiB
                        capabilities: primary extended partitioned 
                                      partitioned:extended
                      *-logicalvolume:0
                           description: Linux filesystem partition
                           physical id: 5
                           logical name: /dev/sda5
                           logical name: /boot
                           capacity: 512MiB
                           configuration: mount.fstype=ext4 mount.options=rw,
                                          noatime,discard,data=ordered 
                                          state=mounted
                      *-logicalvolume:1
                           description: Linux LVM Physical Volume partition
                           physical id: 6
                           logical name: /dev/sda6
                           serial: gCHW7B-ora3-Xh4f-0PyN-GjeF-gh4g-C1tIVv
                           size: 126GiB
                           capacity: 126GiB
                           capabilities: multi lvm2
          *-network DISABLED
               description: Ethernet interface
               physical id: 1
               logical name: virbr0-nic
               serial: 52:54:00:3f:97:15
               size: 10Mbit/s
               capabilities: ethernet physical
               configuration: autonegotiation=off broadcast=yes driver=tun 
                              driverversion=1.6 duplex=full link=no 
                              multicast=yes port=twisted pair speed=10Mbit/s
         
