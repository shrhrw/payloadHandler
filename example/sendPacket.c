#include <stdint.h>
#include <stdio.h>

void sendPacket()
{

    printf("Sent.\n");
}

int main(void) {
    sendPacket();
    printf("Sent a packet.\n");
    return 0;
}