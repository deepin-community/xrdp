
#if defined(HAVE_CONFIG_H)
#include <config_ac.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#include "../include/rfxcodec_encode.h"

int
main(int argc, char **argv)
{
    struct rfxcodec_encode_internals internals;
    int error;
    int index;

    unsigned char in_buffer[4096];
    short out_buffer1[4096];
    short tmp_buffer1[4096];
    //char quans[5] = { 0x66, 0x66, 0x66, 0x66, 0x66 };
    char quans[5] = { 0x99, 0x99, 0x99, 0x99, 0x99 };
#if 0
    short diff_buffer1[4096];
    short diff_buffer2[4096];
    short dwt_buffer[4096];
    short hist_buffer[4096];
    int diff_zeros1;
    int dwt_zeros1;
    int diff_zeros2;
    int dwt_zeros2;
    short out_buffer2[4096];
    short tmp_buffer2[4096];
    int fd;

    fd = open("/dev/urandom", O_RDONLY);
#endif
    error = rfxcodec_encode_get_internals(&internals);
    if (error == 0)
    {
#if 0
        read(fd, tmp_buffer2, 4096 * 2);
        for (index = 0; index < 1024 * 1024; index++)
        {
            int jndex;
            int kndex;
            short *dst;
            short *src;
            for (kndex = 0; kndex < 64; kndex++)
            {
                src = tmp_buffer2 + kndex * 64;
                dst = tmp_buffer1 + kndex;
                for (jndex = 0; jndex < 64; jndex += 8)
                {
                    *dst = *src; src++; dst += 64;
                    *dst = *src; src++; dst += 64;
                    *dst = *src; src++; dst += 64;
                    *dst = *src; src++; dst += 64;
                    *dst = *src; src++; dst += 64;
                    *dst = *src; src++; dst += 64;
                    *dst = *src; src++; dst += 64;
                    *dst = *src; src++; dst += 64;
                }
            }
        }
        if (memcmp(tmp_buffer1, tmp_buffer2, 4096 * 2) == 0)
        {
            printf("match\n");
        }
        else
        {
            printf("no match\n");
        }
#endif
#if 0
        read(fd, dwt_buffer, 4096 * 2);
        read(fd, hist_buffer, 4096 * 2);
        internals.rfx_encode_diff_count(diff_buffer1, dwt_buffer, hist_buffer, &diff_zeros1, &dwt_zeros1);
        internals.rfx_encode_diff_count_amd64(diff_buffer2, dwt_buffer, hist_buffer, &diff_zeros2, &dwt_zeros2);
        if (memcmp(diff_buffer1, diff_buffer2, 4096 * 2) == 0 && diff_zeros1 == diff_zeros2 && dwt_zeros1 == dwt_zeros2)
        {
            //printf("match\n");
        }
        else
        {
            printf("no match\n");
        }
#endif
#if 0
        read(fd, in_buffer, 4096);
        internals.rfx_encode_dwt_shift_rem(in_buffer, out_buffer1, tmp_buffer1, quans);
        //internals.rfx_encode_dwt_shift_rem(in_buffer, out_buffer2, tmp_buffer2, quans);
        internals.rfx_encode_dwt_shift_rem_sse2(in_buffer, out_buffer2, tmp_buffer2, quans);
        if (memcmp(out_buffer1, out_buffer2, 4096 * 2) == 0)
        //if (memcmp(tmp_buffer1, tmp_buffer2, 4096 * 2) == 0)
        {
            printf("match\n");
        }
        else
        {
            printf("no match\n");
        }
#endif
#if 1
        for (index = 0; index < 1024 * 1024; index++)
        {
            //internals.rfx_encode_diff_count_amd64(diff_buffer1, dwt_buffer, hist_buffer, &diff_zeros1, &dwt_zeros1);
            //internals.rfx_encode_diff_count(diff_buffer1, dwt_buffer, hist_buffer, &diff_zeros1, &dwt_zeros1);
            internals.rfx_encode_dwt_shift_rem_sse2(in_buffer, out_buffer1, tmp_buffer1, quans);
            //internals.rfx_encode_dwt_shift_rem(in_buffer, out_buffer1, tmp_buffer1, quans);
            //printf("hi %p\n", internals.rfxencode_dwt_shift_amd64_sse2);
            //internals.rfxencode_dwt_shift_amd64_sse2(quans, (char*)((int)in_buffer & ~31),
//                                                    (short*)(((int)out_buffer1) & ~31),
  //                                                  (short*)(((int)tmp_buffer1) & ~31));
        }
#endif
    }
    return 0;
}
