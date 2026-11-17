# Exploration-in-an-Application-of-Bitwise-Operators
An exploration into how subnet masks and bitwise AND operations are used to determine which network an IPv4 address belongs to.

All devices on IPv4 networks have an IP (internet protocol) address and a subnet mask.

### IP Address:
A unique 32-bit numerical label which is assigned to every device connected to a computer network. It identifies the network and 
the host/device. It is usually represented in dotted decimal notation as four 8-bit octets.
Example -- 192.168.1.45

### Subnet Mask:
A 32-bit number made up of a string of 1s followed by a string of 0s. It divides the IP address into a network address (1s) and
host address (0s). It can also be represented in dotted decimal notation, but CIDR notation is also used wherein a backslash is 
followed by the number of 1s.
Example -- 255.255.255.0 or /24

When a computer sends data to another device, it first needs to determine whether or not the receiving device is on the same
network. That determination is necessary because the process of local data transference is different than that of remote. Subnet
masks and IP addresses are used to make that determination.

Using a bitwise AND operation, all the 1s in the subnet mask maintain the network address and the 0s negate any of the device
specific identifiers. You end up with a pure network address which you can compare with the other network address to determine
if it is on the same network.
