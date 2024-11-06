# Copy the level02.pcap file from the VM to the host machine using scp
scp -P 4242 level02@192.168.56.101:/home/user/level02/level02.pcap ~/Downloads/ 

- scp is a secure tranfert files command between two locations
- A PCAP (Packet CAPture) file is a container for packets captured on a computer network, such as WiFi or Ethernet.

# Change permissions for level02.pcap
chmod 777 level02.pcap

# Use of Wireshark
- Open the folder -> level02.pcap
- Scroll every packets, you'll find some data with '...Pas sword:'
- On the menu bar, click Analyze, then Follow, TCP stream 
- then, 'Show data as' button : 'Hex Dump' 
- We can see that there is '7f' which 'Delete' is ascii table 

# Result:
ft_wandrNDRelL0L

# Delete three times to clean it up:
flag = ft_waNDReL0L

# Token obtained:
token = kooda2puivaav1idi4f57q8iq
