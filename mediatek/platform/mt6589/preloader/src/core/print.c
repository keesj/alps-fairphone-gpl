#include "typedefs.h"
#include "platform.h"
#include "print.h"
#include "uart.h"

static int g_log_disable = 0;
static char *log_ptr = (char*)LOG_BUFFER_START;

static void outchar(const char c)
{
    if (g_log_disable) {
        *log_ptr++ = (char)c;        
    } else {
        PutUARTByte(c);
    }
}

static void outstr(const unsigned char *s)
{
    while (*s) {
        if (*s == '\n')
            outchar('\r');
        outchar(*s++);
    }
}

static void outdec(unsigned long n)
{
    if (n >= 10) {
        outdec(n / 10);
        n %= 10;
    }
    outchar((unsigned char)(n + '0'));
}

static void outhex(unsigned long n, long depth)
{
    if (depth)
        depth--;
    
    if ((n & ~0xf) || depth) {
        outhex(n >> 4, depth);
        n &= 0xf;
    }
    
    if (n < 10) {
        outchar((unsigned char)(n + '0'));
    } else {
        outchar((unsigned char)(n - 10 + 'A'));
    }
}

void log_ctrl(int enable)
{
    u32 len;
    char *ptr;

    g_log_disable = enable ? 0 : 1;

    /* flush log and reset log buf ptr */
    if (enable) {
        ptr = (char*)LOG_BUFFER_START;
        len = (u32)log_ptr - (u32)ptr;
        for (;len;len--) {
            outchar(*ptr++);
        }
        log_ptr = (char*)LOG_BUFFER_START;
    }
}

int log_status(void)
{
    return g_log_disable == 0 ? 1 : 0;
}

void dbg_print(char *fmt, ...)
{
    print(fmt);
}

void vprint(char *fmt, va_list vl)
{
    unsigned char c;
    unsigned int reg = 1; /* argument register number (32-bit) */

    while (*fmt) {
        c = *fmt++;
        switch (c)
        {
        case '%':
            c = *fmt++;
            switch (c)
            {
            case 'x':
                outhex(va_arg(vl, unsigned long), 0);
                break;
            case 'B':
                outhex(va_arg(vl, unsigned long), 2);
                break;
            case 'H':
                outhex(va_arg(vl, unsigned long), 4);
                break;
            case 'X':
                outhex(va_arg(vl, unsigned long), 8);
                break;
            case 'l':
                if (*fmt == 'l' && *(fmt+1) == 'x') {
                    u32 ltmp;
                    u32 htmp;

                    #ifdef __ARM_EABI__
                    /* Normally, compiler uses r0 to r6 to pass 32-bit or 64-bit 
                     * arguments. But with EABI, 64-bit arguments will be aligned 
                     * to an _even_ numbered register. for example:
                     *
                     *   int foo(int a, long long b, int c)
                     *
                     *   EABI: r0: a, r1: unused, r2-r3: b, r4: c
                     *   Normal: r0: a, r1-r2: b, r3:c
                     * 
                     * For this reason, need to align to even numbered register
                     * to retrieve 64-bit argument.
                     */

                    /* odd and unused argument */
                    if (reg & 0x1) {
                        /* 64-bit argument starts from next 32-bit register */
                        reg++;
                        /* ignore this 32-bit register */
                        ltmp = va_arg(vl, unsigned int);
                    }
                    reg++; /* 64-bit argument uses one more 32-bit register */
                    #endif
                    ltmp = va_arg(vl, unsigned int);
                    htmp = va_arg(vl, unsigned int);                    
                    
                    outhex(htmp, 8);
                    outhex(ltmp, 8);
                    fmt += 2;
                }
                break;
            case 'd':
                {
                    long l;

                    l = va_arg(vl, long);
                    if (l < 0) {
                        outchar('-');
                        l = -l;
                    }
                    outdec((unsigned long) l);
                }
                break;
            case 'u':
                outdec(va_arg(vl, unsigned long));
                break;
            case 's':
                outstr((const unsigned char *)va_arg(vl, char *));
                break;
            case '%':
                outchar('%');
                break;
            case 'c':
                c = va_arg(vl, int);
                outchar(c);
                break;
            default:
                outchar(' ');
                break;
            }
            reg++; /* one argument uses 32-bit register */
            break;
        case '\r':
            if (*fmt == '\n')
                fmt++;
            c = '\n';
        // fall through
        case '\n':
            outchar('\r');
        // fall through
        default:
            outchar(c);
        }
    }
}

void print(char *fmt, ...)
{
    va_list args;

    va_start(args, fmt);
    vprint(fmt, args);
    va_end(args);
}
