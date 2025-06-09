# Ansible Collection - vgn.base

Documentation for the collection.

<https://github.com/gheesh/ansible-ovh-dns/tree/master>

<https://github.com/Nosmoht/ansible-module-powerdns>

## unattended_upgrades

```
{% if ansible_distribution_release != 'noble' %}
Unattended-Upgrade::Origins-Pattern {
{% else %}
Unattended-Upgrade::Allowed-Origins {
{% endif %}
```

```
templates/unattended_upgrades.j2:
Remplacer Unattended-Upgrade::Update-Days {{ unattended_update_days }}; par Unattended-Upgrade::Update-Days { {{ unattended_update_days }} };
```

## nftables

Dans le nft_input_default_rules, retirer

011 dhcp4: "{{ nft_templates.allow_in_dhcp4 }}"
012 dhcp6: "{{ nft_templates.allow_in_dhcp6 }}"
013 icmpv6: "{{ nft_templates.icmpv6_in_must_allow }}"
014 icmp: "{{ nft_templates.icmp_in_must_allow }}"
210 input tcp accepted: - tcp dport @in_tcp_accept ct state new accept

remplacer la partie log par
900 log: - "counter log prefix \"{{ nft_log_prefix }}\_IN-1-D \" group 2"

sur les output rules, supprimer

007 icmpv6: "{{ nft_templates.icmpv6_in_must_allow }}"
008 icmp: "{{ nft_templates.icmp_in_must_allow }}"
009 ping6: "{{ nft_templates.icmpv6_allow_ping }}"
010 ping: "{{ nft_templates.icmp_allow_ping }}"
011 dhcp4: "{{ nft_templates.allow_out_dhcp4 }}"
012 dhcp6: "{{ nft_templates.allow_out_dhcp6 }}"
013 mdns: "{{ nft_templates.allow_mdns }}"
013 upnp: "{{ nft_templates.allow_upnp }}"
200 output udp accepted: - udp dport @out_udp_accept ct state new accept
210 output tcp accepted: - tcp dport @out_tcp_accept ct state new accept
250 reset ssh: "{{ nft_templates.allow_rst }}"

900 log: - "counter log prefix \"{{ nft_log_prefix }}\_OUT-1-D \" group 2"

le forward
002 icmp: "{{ nft_templates.icmp_fwd_must_allow }}"
003 icmpv6: "{{ nft_templates.icmpv6_fwd_must_allow }}"
900 log: - "counter log prefix \"{{ nft_log_prefix }}\_FWD-1-D \" group 2"

## virtualbox-guests

<https://github.com/PeterMosmans/ansible-role-virtualbox-guest/tree/master>

Dans le main.yml, supprimer

```
- name: Check if the CD is present on the host
  stat:
    path: "/dev/sr0"
  register: file_path
  ignore_errors: yes
  when: file_path.stat is not defined or not file_path.stat.exists
```
