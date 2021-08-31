#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <inttypes.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/poll.h>
#include <time.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include <signal.h>

#include <iostream>
#include "litepcie.h"
#include "config.h"
#include "csr.h"
#include "flags.h"

#include "liblitepcie.h"

static char litepcie_device[1024];
static int litepcie_device_num;


static void info(void)
{
    int fd;
    int i;
    unsigned char fpga_identification[256];

    fd = open(litepcie_device, O_RDWR);
    if (fd < 0) {
        fprintf(stderr, "Could not init driver\n");
        exit(1);
    }

    for(i=0; i<256; i++)
        fpga_identification[i] = litepcie_readl(fd, CSR_IDENTIFIER_MEM_BASE + 4*i);
    printf("FPGA identification: %s\n", fpga_identification);
#ifdef CSR_DNA_BASE
    printf("FPGA dna: 0x%08x%08x\n",
        litepcie_readl(fd, CSR_DNA_ID_ADDR + 4*0),
        litepcie_readl(fd, CSR_DNA_ID_ADDR + 4*1)
    );
#endif
}


int main()
{
    return 0; //Work on this function tomorrow
}