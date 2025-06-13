#!/bin/bash

if [[ "${#}" -ne 2 ]]; then
    echo "Needs 2 args"
    exit 1
fi

if [[ ! -d "$2"  || ! -f "$1" ]]; then
	echo "Error: second arg not dir"
	exit 1
fi

if ! [[ "$1" =~ \.csv$ ]]; then   # !!!!! =~ for regex
    echo "Error: Output file must have .csv extension"
    exit 3
fi

echo "hostname,phy,vlans,hosts,failover,VPN-3DES-AES,peers,VLAN Trunk Ports,licence,SN,key" >> "$1"

find "$2" -type f -name "*.log" | while read -r f; do

    hostname=$(basename "$f" .log)
    phy=$(grep "Maximum Physical Interfaces" "$f" | cut -d ':' -f2 | xargs)
    vlans=$(grep "VLANs" "$f" | cut -d ':' -f2 | xargs)
    hosts=$(grep "Inside Hosts" "$f" | cut -d ':' -f2 | xargs)
    failover=$(grep "Failover" "$f" | cut -d ':' -f2 | xargs)
    vpn=$(grep "VPN-3DES-AES" "$f" | cut -d ':' -f2 | xargs)
    peers=$(grep "\*Total VPN Peers" "$f" | cut -d ':' -f2 | xargs)
    trunk_ports=$(grep "VLAN Trunk Ports" "$f" | cut -d ':' -f2 | xargs)
    license=$(grep "This platform has" "$f" | sed -e 's/This platform has an\{0,1\} //' -e 's/ license\.//g' | xargs)
    sn=$(grep "Serial Number" "$f" | cut -d ':' -f2 | xargs)
    key=$(grep "Running Activation Key" "$f" | cut -d ':' -f2 | xargs)

    echo "$hostname,$phy,$vlans,$hosts,$failover,$vpn,$peers,$trunk_ports,$license,$sn,$key" >> "$1"
done

# xargs -> take input from a pipe or stdin, and pass it as arguments to another command
# deafult runs echo