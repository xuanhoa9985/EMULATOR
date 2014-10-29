/* Copyright (C) 2010 The Android Open Source Project
**
** This software is licensed under the terms of the GNU General Public
** License version 2, as published by the Free Software Foundation, and
** may be copied, distributed, and modified under those terms.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
*/
#ifndef _ANDROID_LOG_LOW_LEVEL_H
#define _ANDROID_LOG_LOW_LEVEL_H

/* define log items */
typedef struct CPULogItem_android {
    int mask;
    const char *name;
    const char *help;
} CPULogItem_android;

//const CPULogItem_android cpu_log_items_android[];

#define CPU_LOG_ANDROID_TB_OUT_ASM (1 << 0)
#define CPU_LOG_ANDROID_TB_IN_ASM  (1 << 1)
#define CPU_LOG_ANDROID_TB_OP      (1 << 2)
#define CPU_LOG_ANDROID_TB_OP_OPT  (1 << 3)
#define CPU_LOG_ANDROID_INT        (1 << 4)
#define CPU_LOG_ANDROID_EXEC       (1 << 5)
#define CPU_LOG_ANDROID_PCALL      (1 << 6)
#define CPU_LOG_ANDROID_IOPORT     (1 << 7)
#define CPU_LOG_ANDROID_TB_CPU     (1 << 8)
#define CPU_LOG_ANDROID_RESET      (1 << 9)

const CPULogItem_android cpu_log_items_android[] = {
    { CPU_LOG_ANDROID_TB_OUT_ASM, "out_asm",
      "show generated host assembly code for each compiled TB" },
    { CPU_LOG_ANDROID_TB_IN_ASM, "in_asm",
      "show target assembly code for each compiled TB" },
    { CPU_LOG_ANDROID_TB_OP, "op",
      "show micro ops for each compiled TB" },
    { CPU_LOG_ANDROID_TB_OP_OPT, "op_opt",
      "show micro ops "
#ifdef TARGET_I386
      "before eflags optimization and "
#endif
      "after liveness analysis" },
    { CPU_LOG_ANDROID_INT, "int",
      "show interrupts/exceptions in short format" },
    { CPU_LOG_ANDROID_EXEC, "exec",
      "show trace before each executed TB (lots of logs)" },
    { CPU_LOG_ANDROID_TB_CPU, "cpu",
      "show CPU state before block translation" },
#ifdef TARGET_I386
    { CPU_LOG_ANDROID_PCALL, "pcall",
      "show protected mode far calls/returns/exceptions" },
    { CPU_LOG_ANDROID_RESET, "cpu_reset",
      "show CPU state before CPU resets" },
#endif
#ifdef DEBUG_IOPORT
    { CPU_LOG_ANDROID_IOPORT, "ioport",
      "show all i/o ports accesses" },
#endif
    { 0, NULL, NULL },
};


extern int cpu_str_to_log_mask(const char *str);
extern void cpu_set_log(int log_flags);

/* takes a comma separated list of log masks. Return 0 if error. */

static int cmp1_android(const char *s1, int n, const char *s2)
{
    if (strlen(s2) != n)
        return 0;
    return memcmp(s1, s2, n) == 0;
}

int cpu_str_to_log_mask_android(const char *str)
{
    const CPULogItem_android *item;
    int mask;
    const char *p, *p1;

    p = str;
    mask = 0;
    for(;;) {
        p1 = strchr(p, ',');
        if (!p1)
            p1 = p + strlen(p);
	if(cmp1_android(p,p1-p,"all")) {
		for(item = cpu_log_items_android; item->mask != 0; item++) {
			mask |= item->mask;
		}
	} else {
        for(item = cpu_log_items_android; item->mask != 0; item++) {
            if (cmp1_android(p, p1 - p, item->name))
                goto found;
        }
        return 0;
	}
    found:
        mask |= item->mask;
        if (*p1 != ',')
            break;
        p = p1 + 1;
    }
    return mask;
}

#endif /* _ANDROID_DISPLAY_H */
     
