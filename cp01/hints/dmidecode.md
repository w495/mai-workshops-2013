# Рекомендации

Информацию о устройствах Вашего компьютера можно получить с помощью `dmidecode`.
Утилиту всего скорее придется установить.

    $> sudo apt-get install dmidecode

или

    $> yum install dmidecode

Для работы `dmidecode` нужны права суперпользователя.
Для этого команду надо вызывать с `sudo`.

    $> sudo dmidecode --type <ТИП>

либо, сначала переключиться в режим суперпользователя, 
а потом пользоваться утилитой

    $> sudo su -
    [sudo] password: 
    #> dmidecode --type <ТИП>

# Процессор

## Информация о процессоре

    #> dmidecode --type processor

### Пример

    [w495@w495 ~]$ sudo dmidecode --type processor
    [sudo] password for w495: 
    # dmidecode 2.12
    SMBIOS 2.6 present.

    Handle 0x0004, DMI type 4, 42 bytes
    Processor Information
        Socket Designation: CPU 1
        Type: Central Processor
        Family: Core 2 Duo
        Manufacturer: Intel
        ID: A7 06 02 00 FF FB EB BF
        Signature: Type 0, Family 6, Model 42, Stepping 7
        Flags:
            FPU (Floating-point unit on-chip)
            VME (Virtual mode extension)
            DE (Debugging extension)
            PSE (Page size extension)
            TSC (Time stamp counter)
            MSR (Model specific registers)
            PAE (Physical address extension)
            MCE (Machine check exception)
            CX8 (CMPXCHG8 instruction supported)
            APIC (On-chip APIC hardware supported)
            SEP (Fast system call)
            MTRR (Memory type range registers)
            PGE (Page global enable)
            MCA (Machine check architecture)
            CMOV (Conditional move instruction supported)
            PAT (Page attribute table)
            PSE-36 (36-bit page size extension)
            CLFSH (CLFLUSH instruction supported)
            DS (Debug store)
            ACPI (ACPI supported)
            MMX (MMX technology supported)
            FXSR (FXSAVE and FXSTOR instructions supported)
            SSE (Streaming SIMD extensions)
            SSE2 (Streaming SIMD extensions 2)
            SS (Self-snoop)
            HTT (Multi-threading)
            TM (Thermal monitor supported)
            PBE (Pending break enabled)
        Version: Intel(R) Core(TM) i5-2557M CPU @ 1.70GHz       
        Voltage: 0.0 V
        External Clock: 100 MHz
        Max Speed: 4000 MHz
        Current Speed: 1700 MHz
        Status: Populated, Enabled
        Upgrade: Other
        L1 Cache Handle: 0x0005
        L2 Cache Handle: 0x0006
        L3 Cache Handle: Not Provided
        Serial Number: To Be Filled By O.E.M.
        Asset Tag: To Be Filled By O.E.M.
        Part Number: To Be Filled By O.E.M.
        Core Count: 2
        Core Enabled: 1
        Thread Count: 2
        Characteristics:
            64-bit capable

    [w495@w495 ~]$ 

### Что мы узнали

* Производитель: `Intel`.
* Семейство процессора: `Core 2 Duo`.
* Какие специальные (специфические для конкретного процессора) инструкции поддерживается: 
  раздел `flags`. В курсовой работе можно было бы рассказать про каждую из ник.
* Название конкретной модели:  `Intel(R) Core(TM) i5-2557M CPU @ 1.70GHz`.
* Внешняя частота синхронизации: 100 МГц.
* Текущая Частота процессора: 1700 МГц = 1.7 ГГц.
* Максимальная частота: `4000 МГц`.
  Всего скорее имеются ввиду иные процессоры этой версии, но может оказаться, 
  что и этот процессор можно разогнать до 4 ГГц, 
  но делать это крайне не рекомендуется.
* Кеши процессора: есть кеши L1 и L2. L3 нет.
* Процессор имеет 2 ядра по 2 треда каждое (процессор с мультитредингом), 
-- в итоге для нас доступно 4 ядра.
* Процессор поддерживает 64-битный режим.


# ОЗУ

## Информация о памяти


## Информация о процессоре

    #> dmidecode --type memory

### Пример

    [w495@w495 ~]$ sudo dmidecode --type memory
    # dmidecode 2.12
    SMBIOS 2.6 present.

    Handle 0x0040, DMI type 16, 15 bytes
    Physical Memory Array
        Location: System Board Or Motherboard
        Use: System Memory
        Error Correction Type: None
        Maximum Capacity: 32 GB
        Error Information Handle: Not Provided
        Number Of Devices: 4

    Handle 0x0041, DMI type 17, 28 bytes
    Memory Device
        Array Handle: 0x0040
        Error Information Handle: Not Provided
        Total Width: 64 bits
        Data Width: 64 bits
        Size: 2048 MB
        Form Factor: SODIMM
        Set: None
        Locator: ChannelA-DIMM0
        Bank Locator: BANK 0
        Type: DDR3
        Type Detail: Synchronous
        Speed: 1333 MHz
        Manufacturer: Elpida
        Serial Number: 00000000
        Asset Tag: 9876543210
        Part Number: [Empty]
        Rank: 1

    Handle 0x0042, DMI type 17, 28 bytes
    Memory Device
        Array Handle: 0x0040
        Error Information Handle: Not Provided
        Total Width: Unknown
        Data Width: Unknown
        Size: No Module Installed
        Form Factor: DIMM
        Set: None
        Locator: ChannelA-DIMM1
        Bank Locator: BANK 1
        Type: Unknown
        Type Detail: None
        Speed: Unknown
        Manufacturer: [Empty]
        Serial Number: [Empty]
        Asset Tag: 9876543210
        Part Number: [Empty]
        Rank: Unknown

    Handle 0x0043, DMI type 17, 28 bytes
    Memory Device
        Array Handle: 0x0040
        Error Information Handle: Not Provided
        Total Width: 64 bits
        Data Width: 64 bits
        Size: 2048 MB
        Form Factor: SODIMM
        Set: None
        Locator: ChannelB-DIMM0
        Bank Locator: BANK 2
        Type: DDR3
        Type Detail: Synchronous
        Speed: 1333 MHz
        Manufacturer: Elpida
        Serial Number: 00000000
        Asset Tag: 9876543210
        Part Number: [Empty]
        Rank: 1

    Handle 0x0044, DMI type 17, 28 bytes
    Memory Device
        Array Handle: 0x0040
        Error Information Handle: Not Provided
        Total Width: Unknown
        Data Width: Unknown
        Size: No Module Installed
        Form Factor: DIMM
        Set: None
        Locator: ChannelB-DIMM1
        Bank Locator: BANK 3
        Type: Unknown
        Type Detail: None
        Speed: Unknown
        Manufacturer: [Empty]
        Serial Number: [Empty]
        Asset Tag: 9876543210
        Part Number: [Empty]
        Rank: Unknown


### Что мы узнали

Материнская плата поддерживает 4 планки памяти, при этом максимальный объем 
может быть до 32 Гб ОЗУ. На данный момент на ноутбуке стоит только 
2 планки памяти. 

> Больше поставить не представляется возможности, из-за формфактора ЭВМ ---
> Слишком тонкий, ASUS Zenbook UX31E. Кроме того, при разборке ноутбука,
> выяснилось, что память еще и впаяна в материнскую плату, потому даже 
> замена самих планок памяти на более вместительные, 
> обернется уже инженерными работами.

По каждой планки:
* Тип `DDR3`. В Курсовой работе  DDR, DDR2, DDR3 и DDR4.
* Формфактор SO-DIMM (small outline dual in-line memory module) ---  
  отличается от DIMM уменьшенным габаритом. 
  В Курсовой работе тут можно было бы рассказать про DIMM.
* Обладает объемом 2048 МБ и тактовой частотой 1333 МГц.

```
    Memory Device
        Array Handle: 0x0040
        Error Information Handle: Not Provided
        Total Width: 64 bits
        Data Width: 64 bits
        Size: 2048 MB
        c: SODIMM
        Set: None
        Locator: ChannelA-DIMM0
        Bank Locator: BANK 0
        Type: DDR3
        Type Detail: Synchronous
        Speed: 1333 MHz
        Manufacturer: Elpida
        Serial Number: 00000000
        Asset Tag: 9876543210
        Part Number: [Empty]
        Rank: 1
```

