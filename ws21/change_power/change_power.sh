#!/usr/bin/env bash

XBACKLIGHT_MAX=70;
XBACKLIGHT_MIN=1;

## ---------------------------------------------------------------
## FUNCTIONS
## ---------------------------------------------------------------

warn () {
    echo "WARN:$PROGNAME: $1";
}

error () {
    echo "ERROR:$PROGNAME: $1" ; exit 1 ;
}

usage () {
PROGNAME=$0;
[[ x$0 = "x" ]] && PROGNAME="change_power";
cat <<CPUSAGE
Manual power managment utility for changing power consumption.
$PROGNAME [-h]|[[-m]|[-M]|[-a] [-v]]
-h | --help     shows this test.
-m | --min      minimizes a power consumption.
-M | --max      maximizes a power consumption. It increases a performance.
-a | --auto     uses automatic managment.
-v | --verbose  uses verbose mode. It tells about really actions for power managment .
CPUSAGE
}

notice() {
    [[ "x${verbose}" = "xyes" ]] && echo "# $@" 1>&2;
}

##
## @fn  catch an erorr and report it if verbose = yes.
##      erlang-like catch
##
catch () {
    command="$@;";
    [[ "x${verbose}" = "xyes" ]] && echo " TRY:  $command" 1>&2;
    eval "$command";
    ecode=$?;
    [[ "x${verbose}" = "xyes" ]] && echo "  OK:  $ecode" 1>&2;
}

catchset () {
    catch "echo $1 > $2";
}

modemax () {
    catch       xbacklight -set $XBACKLIGHT_MAX;
    catchset    1                  /proc/sys/vm/laptop_mode;
    catchset    max_performance    /sys/class/scsi_host/host0/link_power_management_policy;
    catchset    max_performance    /sys/class/scsi_host/host1/link_power_management_policy;
    catchset    max_performance    /sys/class/scsi_host/host2/link_power_management_policy;
    catchset    max_performance    /sys/class/scsi_host/host3/link_power_management_policy;
    catchset    max_performance    /sys/class/scsi_host/host4/link_power_management_policy;
    catchset    max_performance    /sys/class/scsi_host/host5/link_power_management_policy;
    catchset    ondemand           /sys/devices/system/cpu/cpu0/cpufreq/scaling_governor;
    catchset    ondemand           /sys/devices/system/cpu/cpu1/cpufreq/scaling_governor;
    catchset    ondemand           /sys/devices/system/cpu/cpu2/cpufreq/scaling_governor;
    catchset    ondemand           /sys/devices/system/cpu/cpu3/cpufreq/scaling_governor;
    catchset    0                  /sys/module/snd_hda_intel/parameters/power_save;
    catchset    5                  /proc/sys/vm/dirty_background_ratio;
    catchset    6000               /proc/sys/vm/dirty_writeback_centisecs;
}

modemin () {
    catch       xbacklight -set $XBACKLIGHT_MIN;
    catchset    5          /proc/sys/vm/laptop_mode;
    catchset    min_power  /sys/class/scsi_host/host0/link_power_management_policy;
    catchset    min_power  /sys/class/scsi_host/host1/link_power_management_policy;
    catchset    min_power  /sys/class/scsi_host/host2/link_power_management_policy;
    catchset    min_power  /sys/class/scsi_host/host3/link_power_management_policy;
    catchset    min_power  /sys/class/scsi_host/host4/link_power_management_policy;
    catchset    min_power  /sys/class/scsi_host/host5/link_power_management_policy;
    catchset    powersave  /sys/devices/system/cpu/cpu0/cpufreq/scaling_governor;
    catchset    powersave  /sys/devices/system/cpu/cpu1/cpufreq/scaling_governor;
    catchset    powersave  /sys/devices/system/cpu/cpu2/cpufreq/scaling_governor;
    catchset    powersave  /sys/devices/system/cpu/cpu3/cpufreq/scaling_governor;
    catchset    10         /sys/module/snd_hda_intel/parameters/power_save;
    catchset    1          /proc/sys/vm/dirty_background_ratio;
    catchset    60000      /proc/sys/vm/dirty_writeback_centisecs;
}

(( $# == 0  )) && { usage ; exit 1 ; }

_args=$(getopt -o hmMav -l "help,min,max,auto,verbose" -n $0 --  "$@");
set -- $_args;

mode="auto";
verbose="no";

while [[ -n $_args ]] ;
do
    case $1 in
        -h|--help)      usage               ;  exit 0;;
        -m|--min)       mode="min"          ;   shift;;
        -M|--max)       mode="max"          ;   shift;;
        -a|--auto)      mode="auto"         ;   shift;;
        -v|--verbose)   verbose="yes"       ;   shift;;
        '--')                                   break;;
        *) echo $'\n'"Unknown parameter '$1'."$'\n' ; usage ; exit 1 ;;
    esac;
done;

notice "verbose = ${verbose}";
notice "mode    = ${mode}";

case ${mode} in
    "min"  )    modemin;;
    "max"  )    modemax;;
    "auto" )
        if on_ac_power ; then
            modemax;
        else
            modemin;
        fi;;
    '')
        break;;
esac;

test -f /usr/share/acpi-support/key-constants ||  exit 0

. /usr/share/acpi-support/policy-funcs
if [ -z "$*" ] && ( [ `CheckPolicy` = 0 ] || CheckUPowerPolicy ); then
    notice "done (1).";
    exit;
fi
pm-powersave $*

notice "done (2).";


