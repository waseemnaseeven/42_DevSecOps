# BADASS

We'll have to a simulate a network using GNS3 and docker, focusing on advanced networking concepts like BGP (Border Gateway Protocol), EVPN (Ethernet VPN), and VXLAN (Virtual Extensible LAN). 

## Understanding Concepts 

- `BGP (Border Gateway Protocol)`: The protocol that drives the internet, used for routing data between autonomous systems.

- `MP-BGP (Multi-Protocol BGP)`: An extension of BGP that supports multiple address families, such as IPv6, VPNs, and EVPN.

- `EVPN (Ethernet VPN)`: A BGP address family that allows for Layer 2 VPNs over Layer 3 networks, facilitating MAC address learning and distribution.

- `VXLAN (Virtual Extensible LAN)`: A tunneling protocol that encapsulates Layer 2 frames within UDP packets, allowing for Layer 2 segments over Layer 3 networks.

- `OSPF (Open Shortest Path First)`: A routing protocol used within an autonomous system.

- `IS-IS (Intermediate System to Intermediate System)`: Another interior gateway protocol for routing within an autonomous system.

## Tools

- `Wireshark` : Open-Source Analysor of network packets. We can capture and inspect data on a network in real time. it use for: 
    - Identify communications problems
    - Security analysis
    - Protocol analysis

- `Dynamips`: Cisco rooter emulator for simulation. it use for:
    - Network simulation

- `GNS3`: Graphical Network Simulator-3, simulate complex networks with rooter, commutator and other virtual disposifs. it use for: 
    - Simulation : 
    - Graphical Interface 
    - Integration with other tool

- `GNS3 ubridge`: bridge on GNS3 use for network interface connection. it use for: 
    - link virtual interface to physical interface
    - treat network packets
    - optimisation of packets transmission

- `xterm`: terminal emulator, for GNS3 dispositif network simulation

## 2 images

1. Image with busybox
    - Use `Alpine Linux` as it's lightweight and suitable for network tasks.
    - Include bash

2. Image with Routing Capabilities
    - Use a Linux distribution of your choice (e.g., Ubuntu, Debian) or directly frr/routing directly.
    - `FRRouting (FRR)`: An open-source routing software suite that supports BGP, OSPF, and IS-IS.
    - Installation:
        - Add the FRR repository and install using package manager.
        - Configure `FRR daemons` (bgpd, ospfd, isisd) with the `daemons.conf` in the router folder.
        - Include BusyBox or equivalent for basic utilities.

3. Test images locally

## Configuration of GNS3 with docker images

- Add Docker Images to GNS3:
    - Open GNS3 and go to `Preferences > Docker Containers.`
    - Add new templates using your Docker images.
        - Start command : `/bin/sh`
        - `telnet`

## Simple Network Setup

Objective: Create a simple network with two machines using your Docker images.

- Drag and drop your Docker containers into the GNS3 workspace.
- Connect the containers using GNS3's network links.
- Ensure that both machines are operationnal with `Right Click` + `Auxiliary Console` : `ps` and `hostname` cmds.


