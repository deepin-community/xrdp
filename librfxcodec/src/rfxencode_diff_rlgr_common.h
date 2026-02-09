/**
 * RFX codec encoder
 *
 * Copyright 2024 Jay Sorg <jay.sorg@gmail.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __RFXENCODE_DIFF_RLGR_COMMON_H
#define __RFXENCODE_DIFF_RLGR_COMMON_H

#define PIXELS_IN_TILE 4096

/* Constants used within the RLGR1/RLGR3 algorithm */
#define KPMAX   (80)  /* max value for kp or krp */
#define LSGR    (3)   /* shift count to convert kp to k */
#define UP_GR   (4)   /* increase in kp after a zero run in RL mode */
#define DN_GR   (6)   /* decrease in kp after a nonzero symbol in RL mode */
#define UQ_GR   (3)   /* increase in kp after nonzero symbol in GR mode */
#define DQ_GR   (3)   /* decrease in kp after zero symbol in GR mode */

#define GetNextInput do { \
    input = *coef; \
    coef++; \
    coef_size--; \
} while (0)

#define CheckWrite do { \
    while (bit_count >= 8) \
    { \
        if (cdata_size < 1) \
        { \
            return -1; \
        } \
        cdata_size--; \
        bit_count -= 8; \
        *cdata = bits >> bit_count; \
        cdata++; \
    } \
} while (0)

/* output GR code for (mag - 1) */
#define CodeGR(_krp, _lmag) do { \
    int lkr = _krp >> LSGR; \
    /* unary part of GR code */ \
    int lvk = _lmag >> lkr; \
    int llvk = lvk; \
    if (llvk > 0) \
    { \
        if (cdata_size < llvk / 8) \
        { \
            return -1; \
        } \
        while (llvk >= 8) \
        { \
            cdata_size--; \
            bits <<= 8; \
            bits |= 0xFF; \
            llvk -= 8; \
            *cdata = bits >> bit_count; \
            cdata++; \
        } \
        bits <<= llvk; \
        bits |= (1 << llvk) - 1; \
        bit_count += llvk; \
    } \
    bits <<= 1; \
    bit_count++; \
    /* remainder part of GR code, if needed */ \
    if (lkr) \
    { \
        bits <<= lkr; \
        bits |= _lmag & ((1 << lkr) - 1); \
        bit_count += lkr; \
    } \
    /* update _krp, only if it is not equal to 1 */ \
    if (lvk == 0) \
    { \
        _krp = MAX(0, _krp - 2); \
    } \
    else if (lvk > 1) \
    { \
        _krp = MIN(KPMAX, _krp + lvk); \
    } \
} while (0)

#endif