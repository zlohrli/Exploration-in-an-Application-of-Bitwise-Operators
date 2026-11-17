#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OCTETS 4
#define OCTET_MIN 0
#define OCTET_MAX 255
#define SUBNET 1
#define IP 0
#define CIDR_MAX 32

static const int subnet_values[] = {0, 128, 192, 224, 240, 248, 252, 254, 255};

int validator(int octets[OCTETS], int id);

int initialization(int octets[OCTETS], int id) {
    if (id == IP) {
        printf("Enter IP address: ");
    }

    if (id == SUBNET) {
        printf("Enter subnet mask: ");
    }

    char buffer[100];

    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return 1;
    }

    if (sscanf(buffer, "%d.%d.%d.%d", &octets[0], &octets[1], &octets[2],
               &octets[3]) == OCTETS) {
        return validator(octets, id);
    }

    return 1;
}

int validator(int octets[OCTETS], int id) {
    int found_non_255 = 0;

    for (int i = 0; i < OCTETS; i++) {
        if (octets[i] < OCTET_MIN || octets[i] > OCTET_MAX) {
            return 1;
        }

        if (id == SUBNET) {
            int validity = 0;

            for (int j = 0; j < sizeof(subnet_values) / sizeof(int); j++) {
                if (octets[i] == subnet_values[j]) {
                    validity += 1;
                    break;
                }
            }

            if (validity == 0) {
                return 1;
            }

            if (found_non_255 && octets[i] != 0) {
                return 1;
            }

            if (octets[i] < OCTET_MAX) {
                found_non_255 = 1;
            }
        }
    }
    return 0;
}

int decimal_to_cidr(int octets[OCTETS]) {
    int cidr = 0;
    for (int i = 0; i < OCTETS; i++) {
        if (octets[i] == OCTET_MAX) {
            cidr += 8;
        } else {
            for (int j = 0; j < sizeof(subnet_values) / sizeof(int); j++) {
                if (octets[i] == subnet_values[j]) {
                    cidr += j;
                    return cidr;
                }
            }
        }
    }
    return cidr;
}

int main() {
    int ip_octets[OCTETS];
    printf(
        "Enter all IP addresses and subnet masks in decimal.\nMake sure to "
        "include periods.\n");

    while (initialization(ip_octets, IP) == 1) {
        printf("Incorrect formatting or values.\n");
        printf(
            "Enter all IP addresses and subnet masks in decimal.\nMake sure to "
            "include periods.\n");
    }

    int subnet_octets[OCTETS];

    while (initialization(subnet_octets, SUBNET) == 1) {
        printf("Incorrect format or values.\n");
        printf(
            "Enter all IP addresses and subnet masks in decimal.\nMake sure to "
            "include periods.\n");
    }

    int cidr = decimal_to_cidr(subnet_octets);

    int network_octets[4];

    for (int i = 0; i < OCTETS; i++) {
        network_octets[i] = ip_octets[i] & subnet_octets[i];
    }

    printf("Network Address: %d.%d.%d.%d\n", network_octets[0],
           network_octets[1], network_octets[2], network_octets[3]);
    printf("CIDR Value: /%d\n", cidr);

    int possible_ips = 1 << (CIDR_MAX - cidr);
    printf("IPs on Same Network: %d\n", possible_ips);

    printf("Network IP Range: %d.%d.%d.%d to ", network_octets[0],
           network_octets[1], network_octets[2], network_octets[3]);

    network_octets[0] |= ((possible_ips - 1) >> 24) & 0xFF;
    network_octets[1] |= ((possible_ips - 1) >> 16) & 0xFF;
    network_octets[2] |= ((possible_ips - 1) >> 8) & 0xFF;
    network_octets[3] |= (possible_ips - 1) & 0xFF;

    printf("%d.%d.%d.%d\n", network_octets[0], network_octets[1],
           network_octets[2], network_octets[3]);

    return 0;
}