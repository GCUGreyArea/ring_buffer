# Perf stats

The followin is the output for `perf -g ./build/producer_consumer`

```shell
# To display the perf.data header info, please use --header/--header-only options.
#
#
# Total Lost Samples: 0
#
# Samples: 1K of event 'cpu-clock:uhpppH'
# Event count (approx.): 392000000
#
# Children      Self  Command          Shared Object            Symbol                                                                                                                                                       
# ........  ........  ...............  .......................  .............................................................................................................................................................
#
    45.47%     0.00%  producer_consum  libpthread-2.31.so       [.] start_thread
            |
            ---start_thread
               |          
               |--16.39%--run_producer
               |          |          
               |          |--8.10%--__interceptor_sprintf
               |          |          |          
               |          |           --7.08%--__interceptor_vsprintf
               |          |                     |          
               |          |                     |--2.23%--_ZL13printf_commonPvPKcP13__va_list_tag
               |          |                     |          
               |          |                     |--1.66%--_ZN11__sanitizer15internal_memsetEPvim
               |          |                     |          
               |          |                      --1.34%--_ZN11__sanitizer15internal_strchrEPKci
               |          |          
               |          |--2.30%--rb_test
               |          |          
               |           --0.89%--rb_add
               |          
               |--14.41%--run_consumer
               |          |          
               |          |--5.74%--rb_test
               |          |          
               |          |--1.08%--rb_get
               |          |          
               |          |--0.96%--__strlen_avx2
               |          |          
               |           --0.57%--__interceptor_strcpy.part.0
               |          
               |--5.55%--__interceptor_sprintf
               |          |          
               |           --4.21%--__interceptor_vsprintf
               |                     |          
               |                     |--1.15%--_ZL13printf_commonPvPKcP13__va_list_tag
               |                     |          
               |                     |--0.89%--_ZN11__sanitizer15internal_strchrEPKci
               |                     |          
               |                      --0.70%--_ZN11__sanitizer15internal_memsetEPvim
               |          
               |--5.10%--rb_test
               |          
               |--1.79%--0x55d656525160
               |          
                --0.51%--__interceptor_printf

    16.39%     4.46%  producer_consum  producer_consumer        [.] run_producer
            |          
            |--11.93%--run_producer
            |          |          
            |          |--8.10%--__interceptor_sprintf
            |          |          |          
            |          |           --7.08%--__interceptor_vsprintf
            |          |                     |          
            |          |                     |--2.23%--_ZL13printf_commonPvPKcP13__va_list_tag
            |          |                     |          
            |          |                     |--1.66%--_ZN11__sanitizer15internal_memsetEPvim
            |          |                     |          
            |          |                      --1.34%--_ZN11__sanitizer15internal_strchrEPKci
            |          |          
            |          |--2.30%--rb_test
            |          |          
            |           --0.89%--rb_add
            |          
             --4.46%--start_thread
                       run_producer

    14.41%     5.87%  producer_consum  producer_consumer        [.] run_consumer
            |          
            |--8.55%--run_consumer
            |          |          
            |          |--5.74%--rb_test
            |          |          
            |          |--1.08%--rb_get
            |          |          
            |          |--0.96%--__strlen_avx2
            |          |          
            |           --0.57%--__interceptor_strcpy.part.0
            |          
             --5.87%--start_thread
                       run_consumer

    13.65%     1.47%  producer_consum  libasan.so.5.0.0         [.] __interceptor_sprintf
            |          
            |--12.18%--__interceptor_sprintf
            |          |          
            |          |--11.29%--__interceptor_vsprintf
            |          |          |          
            |          |          |--3.38%--_ZL13printf_commonPvPKcP13__va_list_tag
            |          |          |          
            |          |          |--2.36%--_ZN11__sanitizer15internal_memsetEPvim
            |          |          |          
            |          |          |--2.23%--_ZN11__sanitizer15internal_strchrEPKci
            |          |          |          
            |          |           --0.57%--_ZN11__sanitizer15internal_strlenEPKc
            |          |          
            |           --0.83%--_IO_vsprintf
            |          
             --1.47%--start_thread
                       |          
                       |--0.96%--__interceptor_sprintf
                       |          
                        --0.51%--run_producer
                                  __interceptor_sprintf

    13.14%    13.14%  producer_consum  libproducer_consumer.so  [.] rb_test
            |
            ---start_thread
               |          
               |--5.74%--run_consumer
               |          rb_test
               |          
               |--5.10%--rb_test
               |          
                --2.30%--run_producer
                          rb_test

    12.31%     1.21%  producer_consum  libc-2.31.so             [.] _IO_vsprintf
            |          
            |--11.10%--_IO_vsprintf
            |          |          
            |          |--6.57%--__vfprintf_internal
            |          |          
            |          |--1.66%--_itoa_word
            |          |          
            |          |--1.15%--__strchrnul_avx2
            |          |          
            |           --1.02%--_IO_default_xsputn
            |          
             --0.83%--start_thread

    11.86%     2.49%  producer_consum  libasan.so.5.0.0         [.] __interceptor_vsprintf
            |          
            |--9.38%--__interceptor_vsprintf
            |          |          
            |          |--3.38%--_ZL13printf_commonPvPKcP13__va_list_tag
            |          |          
            |          |--2.36%--_ZN11__sanitizer15internal_memsetEPvim
            |          |          
            |          |--2.23%--_ZN11__sanitizer15internal_strchrEPKci
            |          |          
            |           --0.57%--_ZN11__sanitizer15internal_strlenEPKc
            |          
             --2.49%--start_thread
                       |          
                       |--1.59%--run_producer
                       |          |          
                       |           --1.21%--__interceptor_sprintf
                       |                     __interceptor_vsprintf
                       |          
                        --0.70%--__interceptor_sprintf
                                  __interceptor_vsprintf

    11.22%     0.00%  producer_consum  [unknown]                [.] 0x00007f55702fde30
            |
            ---0x7f55702fde30
               |          
                --11.03%--__interceptor_vprintf
                          |          
                          |--2.93%--__vfprintf_internal
                          |          
                          |--2.10%--_ZL13printf_commonPvPKcP13__va_list_tag
                          |          
                          |--1.34%--_ZN11__sanitizer15internal_memsetEPvim
                          |          
                          |--0.70%--__strchrnul_avx2
                          |          
                          |--0.70%--_IO_file_xsputn@@GLIBC_2.2.5
                          |          
                          |--0.64%--_pthread_cleanup_pop_restore
                          |          
                          |--0.64%--_ZN11__sanitizer15internal_strlenEPKc
                          |          
                           --0.57%--_ZN11__sanitizer15internal_strchrEPKci

    11.22%     0.70%  producer_consum  libasan.so.5.0.0         [.] __interceptor_vprintf
            |          
            |--10.52%--__interceptor_vprintf
            |          |          
            |          |--2.93%--__vfprintf_internal
            |          |          
            |          |--2.10%--_ZL13printf_commonPvPKcP13__va_list_tag
            |          |          
            |          |--1.34%--_ZN11__sanitizer15internal_memsetEPvim
            |          |          
            |          |--0.70%--__strchrnul_avx2
            |          |          
            |          |--0.70%--_IO_file_xsputn@@GLIBC_2.2.5
            |          |          
            |          |--0.64%--_pthread_cleanup_pop_restore
            |          |          
            |          |--0.64%--_ZN11__sanitizer15internal_strlenEPKc
            |          |          
            |           --0.57%--_ZN11__sanitizer15internal_strchrEPKci
            |          
             --0.51%--0x7f55702fde30
                       __interceptor_vprintf

    10.20%    10.20%  producer_consum  libc-2.31.so             [.] clock_nanosleep@@GLIBC_2.17
            |
            ---clock_nanosleep@@GLIBC_2.17

     9.57%     9.57%  producer_consum  libc-2.31.so             [.] __vfprintf_internal
            |          
            |--2.93%--0x7f55702fde30
            |          __interceptor_vprintf
            |          __vfprintf_internal
            |          
            |--1.02%--0
            |          _IO_vsprintf
            |          __vfprintf_internal
            |          
            |--0.64%--0x31
            |          _IO_vsprintf
            |          __vfprintf_internal
            |          
             --0.51%--0x38
                       _IO_vsprintf
                       __vfprintf_internal

     5.55%     5.55%  producer_consum  libasan.so.5.0.0         [.] _ZL13printf_commonPvPKcP13__va_list_tag
            |          
            |--3.44%--start_thread
            |          |          
            |          |--2.30%--run_producer
            |          |          __interceptor_sprintf
            |          |          |          
            |          |           --2.23%--__interceptor_vsprintf
            |          |                     _ZL13printf_commonPvPKcP13__va_list_tag
            |          |          
            |           --1.15%--__interceptor_sprintf
            |                     __interceptor_vsprintf
            |                     _ZL13printf_commonPvPKcP13__va_list_tag
            |          
             --2.10%--0x7f55702fde30
                       __interceptor_vprintf
                       _ZL13printf_commonPvPKcP13__va_list_tag

     5.17%     5.17%  producer_consum  libasan.so.5.0.0         [.] _ZN11__sanitizer15internal_strchrEPKci
            |          
            |--2.23%--start_thread
            |          |          
            |          |--1.34%--run_producer
            |          |          __interceptor_sprintf
            |          |          __interceptor_vsprintf
            |          |          _ZN11__sanitizer15internal_strchrEPKci
            |          |          
            |           --0.89%--__interceptor_sprintf
            |                     __interceptor_vsprintf
            |                     _ZN11__sanitizer15internal_strchrEPKci
            |          
            |--1.66%--_ZN11__sanitizer15internal_strchrEPKci
            |          
            |--0.57%--0x7f55702fde30
            |          __interceptor_vprintf
            |          _ZN11__sanitizer15internal_strchrEPKci
            |          
             --0.51%--0
                       _ZN11__sanitizer15internal_strchrEPKci

     3.89%     0.00%  producer_consum  [unknown]                [.] 0000000000000000
            |
            ---0
               |          
               |--1.59%--_IO_vsprintf
               |          |          
               |           --1.02%--__vfprintf_internal
               |          
               |--0.57%--_ZL27maybe_parse_length_modifierPKcPc
               |          
               |--0.51%--_IO_str_init_static_internal
               |          
                --0.51%--_ZN11__sanitizer15internal_strchrEPKci

     3.83%     0.00%  producer_consum  [unknown]                [.] 0x0000619000000080
            |
            ---0x619000000080
               |          
               |--1.98%--_IO_file_xsputn@@GLIBC_2.2.5
               |          
               |--0.64%--__mempcpy_avx_unaligned_erms
               |          
                --0.57%--__memmove_avx_unaligned_erms

     3.76%     3.76%  producer_consum  libasan.so.5.0.0         [.] _ZN11__sanitizer15internal_memsetEPvim
            |          
            |--2.36%--start_thread
            |          |          
            |          |--1.66%--run_producer
            |          |          __interceptor_sprintf
            |          |          __interceptor_vsprintf
            |          |          _ZN11__sanitizer15internal_memsetEPvim
            |          |          
            |           --0.70%--__interceptor_sprintf
            |                     __interceptor_vsprintf
            |                     _ZN11__sanitizer15internal_memsetEPvim
            |          
             --1.34%--0x7f55702fde30
                       __interceptor_vprintf
                       _ZN11__sanitizer15internal_memsetEPvim

     2.68%     2.68%  producer_consum  libc-2.31.so             [.] _IO_file_xsputn@@GLIBC_2.2.5
            |          
            |--1.98%--0x619000000080
            |          _IO_file_xsputn@@GLIBC_2.2.5
            |          
             --0.70%--0x7f55702fde30
                       __interceptor_vprintf
                       _IO_file_xsputn@@GLIBC_2.2.5

     2.61%     2.61%  producer_consum  libc-2.31.so             [.] __libc_disable_asynccancel
            |          
             --1.79%--__libc_disable_asynccancel

     2.49%     2.49%  producer_consum  libc-2.31.so             [.] _IO_default_xsputn
            |          
             --1.47%--_IO_default_xsputn

     2.49%     2.49%  producer_consum  libc-2.31.so             [.] __GI___libc_write
            |          
            |--1.02%--0x323a676e69727473
            |          __GI___libc_write
            |          
             --1.02%--0x313a676e69727473
                       __GI___libc_write

     1.85%     1.85%  producer_consum  libc-2.31.so             [.] __strchrnul_avx2
            |          
             --0.70%--0x7f55702fde30
                       __interceptor_vprintf
                       __strchrnul_avx2

     1.79%     1.79%  producer_consum  producer_consumer        [.] 0x0000000000001160
            |
            ---start_thread
               0x55d656525160

     1.79%     0.00%  producer_consum  producer_consumer        [.] 0x000055d656525160
            |
            ---0x55d656525160

     1.72%     1.72%  producer_consum  libc-2.31.so             [.] __strlen_avx2
            |          
             --0.96%--start_thread
                       run_consumer
                       __strlen_avx2

     1.66%     1.66%  producer_consum  libc-2.31.so             [.] _itoa_word
     1.47%     0.00%  producer_consum  [unknown]                [.] 0x313a676e69727473
            |
            ---0x313a676e69727473
               |          
                --1.02%--__GI___libc_write

     1.40%     1.40%  producer_consum  libasan.so.5.0.0         [.] _ZL27maybe_parse_length_modifierPKcPc
            |          
             --0.57%--0
                       _ZL27maybe_parse_length_modifierPKcPc

     1.40%     0.00%  producer_consum  [unknown]                [.] 0x323a676e69727473
            |
            ---0x323a676e69727473
               |          
                --1.02%--__GI___libc_write

     1.34%     1.34%  producer_consum  libc-2.31.so             [.] __sleep
            |          
             --1.08%--__sleep

     1.21%     1.21%  producer_consum  libasan.so.5.0.0         [.] _ZN11__sanitizer15internal_strlenEPKc
            |          
            |--0.64%--0x7f55702fde30
            |          __interceptor_vprintf
            |          _ZN11__sanitizer15internal_strlenEPKc
            |          
             --0.57%--start_thread

     1.15%     1.15%  producer_consum  libproducer_consumer.so  [.] rb_get
            |
            ---start_thread
               |          
                --1.08%--run_consumer
                          rb_get

     1.02%     1.02%  producer_consum  libproducer_consumer.so  [.] rb_add
            |
            ---start_thread
               |          
                --0.89%--run_producer
                          rb_add

     0.96%     0.00%  producer_consum  [unknown]                [.] 0x0000000000000031
            |
            ---0x31
               _IO_vsprintf
               |          
                --0.64%--__vfprintf_internal

     0.89%     0.89%  producer_consum  libc-2.31.so             [.] _IO_do_write@@GLIBC_2.2.5
            |          
             --0.64%--_IO_do_write@@GLIBC_2.2.5

     0.89%     0.89%  producer_consum  libc-2.31.so             [.] _IO_file_write@@GLIBC_2.2.5
     0.89%     0.89%  producer_consum  libc-2.31.so             [.] _IO_str_init_static_internal
            |          
             --0.51%--0
                       _IO_str_init_static_internal

     0.89%     0.89%  producer_consum  libc-2.31.so             [.] __nanosleep
            |
            ---__nanosleep

     0.83%     0.83%  producer_consum  libasan.so.5.0.0         [.] _ZL20format_get_char_sizecPKc
            |          
             --0.70%--_ZL20format_get_char_sizecPKc

     0.83%     0.83%  producer_consum  libasan.so.5.0.0         [.] _ZL21format_get_value_sizecPKcb
     0.77%     0.00%  producer_consum  [unknown]                [.] 0x0000000000000032
            |
            ---0x32
               _IO_vsprintf

     0.70%     0.00%  producer_consum  [unknown]                [.] 0x0000000000000038
            |
            ---0x38
               _IO_vsprintf
               |          
                --0.51%--__vfprintf_internal

     0.64%     0.64%  producer_consum  libasan.so.5.0.0         [.] __interceptor_strcpy.part.0
            |
            ---start_thread
               |          
                --0.57%--run_consumer
                          __interceptor_strcpy.part.0

     0.64%     0.64%  producer_consum  libpthread-2.31.so       [.] _pthread_cleanup_pop_restore
            |
            ---0x7f55702fde30
               __interceptor_vprintf
               _pthread_cleanup_pop_restore

     0.64%     0.64%  producer_consum  libc-2.31.so             [.] __mempcpy_avx_unaligned_erms
            |
            ---0x619000000080
               __mempcpy_avx_unaligned_erms

     0.57%     0.00%  producer_consum  [unknown]                [.] 0x0000303331383235
            |
            ---0x303331383235
               |          
                --0.51%--_IO_vsprintf

     0.57%     0.57%  producer_consum  libc-2.31.so             [.] _IO_setb
     0.57%     0.57%  producer_consum  libc-2.31.so             [.] __memmove_avx_unaligned_erms
            |
            ---0x619000000080
               __memmove_avx_unaligned_erms

     0.57%     0.00%  producer_consum  [unknown]                [.] 0xd4c0000060300000
            |
            ---0xd4c0000060300000

     0.51%     0.00%  producer_consum  [unknown]                [.] 0x0000303031383235
            |
            ---0x303031383235

     0.51%     0.51%  producer_consum  libasan.so.5.0.0         [.] __interceptor_printf
            |
            ---start_thread
               __interceptor_printf

     0.51%     0.51%  producer_consum  libc-2.31.so             [.] _IO_old_init
     0.45%     0.00%  producer_consum  [unknown]                [.] 0x0000000000000034
     0.45%     0.45%  producer_consum  libc-2.31.so             [.] _IO_no_init
     0.45%     0.45%  producer_consum  libc-2.31.so             [.] __libc_enable_asynccancel
     0.38%     0.00%  producer_consum  [unknown]                [.] 0x0000000000000030
     0.38%     0.00%  producer_consum  [unknown]                [.] 0x0000000000000037
     0.38%     0.00%  producer_consum  [unknown]                [.] 0x0000000000000039
     0.32%     0.00%  producer_consum  [unknown]                [.] 0x0000000000000035
     0.32%     0.00%  producer_consum  [unknown]                [.] 0x0000303630383235
     0.32%     0.00%  producer_consum  [unknown]                [.] 0x0000303831383235
     0.32%     0.00%  producer_consum  [unknown]                [.] 0x0000306630383235
     0.26%     0.26%  producer_consum  libc-2.31.so             [.] 0x0000000000022390
     0.26%     0.00%  producer_consum  [unknown]                [.] 0x0000303032383235
     0.26%     0.00%  producer_consum  [unknown]                [.] 0x0000303131383235
     0.26%     0.00%  producer_consum  [unknown]                [.] 0x0000303930383235
     0.26%     0.26%  producer_consum  libc-2.31.so             [.] _IO_file_overflow@@GLIBC_2.2.5
     0.26%     0.26%  producer_consum  producer_consumer        [.] static_string_producer
     0.26%     0.00%  producer_consum  [unknown]                [.] 0x00007f55702fde60
     0.26%     0.00%  producer_consum  [unknown]                [.] 0x333a676e69727473
     0.26%     0.00%  producer_consum  libc-2.31.so             [.] 0x00007f55744f7390
     0.26%     0.00%  producer_consum  [unknown]                [.] 0x0000000000000036
     0.19%     0.19%  producer_consum  libc-2.31.so             [.] __strcpy_avx2
     0.19%     0.00%  producer_consum  [unknown]                [.] 0x0000303231383235
     0.19%     0.00%  producer_consum  [unknown]                [.] 0x0000303532383235
     0.19%     0.00%  producer_consum  [unknown]                [.] 0x0000303631383235
     0.19%     0.00%  producer_consum  [unknown]                [.] 0x0000306130383235
     0.19%     0.00%  producer_consum  [unknown]                [.] 0x0000306330383235
     0.19%     0.00%  producer_consum  [unknown]                [.] 0x0000306331383235
     0.19%     0.00%  producer_consum  [unknown]                [.] 0x0000306431383235
     0.19%     0.00%  producer_consum  [unknown]                [.] 0x0000306530383235
     0.19%     0.19%  producer_consum  libasan.so.5.0.0         [.] __interceptor_strcpy
     0.19%     0.19%  producer_consum  libc-2.31.so             [.] vprintf
     0.19%     0.00%  producer_consum  [unknown]                [.] 0xbebebebebebebebe
     0.13%     0.13%  producer_consum  libasan.so.5.0.0         [.] _ZN11__sanitizer20SizeClassAllocator32INS_4AP32EE16PopulateFreeListEPNS_14AllocatorStatsEPNS_30SizeClassAllocator32LocalCacheIS2_EEPNS2_13SizeClassInfoEm
     0.13%     0.13%  producer_consum  libasan.so.5.0.0         [.] 0x0000000000022a58
     0.13%     0.13%  producer_consum  libc-2.31.so             [.] 0x0000000000022460
     0.13%     0.13%  producer_consum  libpthread-2.31.so       [.] _pthread_cleanup_push_defer
     0.13%     0.00%  producer_consum  [unknown]                [.] 0x0000303132383235
     0.13%     0.00%  producer_consum  [unknown]                [.] 0x0000303232383235
     0.13%     0.00%  producer_consum  [unknown]                [.] 0x0000303431383235
     0.13%     0.00%  producer_consum  [unknown]                [.] 0x0000303531383235
     0.13%     0.00%  producer_consum  [unknown]                [.] 0x0000303931383235
     0.13%     0.00%  producer_consum  [unknown]                [.] 0x0000306231383235
     0.13%     0.00%  producer_consum  [unknown]                [.] 0x0000306631383235
     0.13%     0.13%  producer_consum  libc-2.31.so             [.] 0x00000000000225a0
     0.13%     0.13%  producer_consum  producer_consumer        [.] 0x0000000000001120
     0.13%     0.13%  producer_consum  producer_consumer        [.] 0x00000000000011a0
     0.13%     0.13%  producer_consum  producer_consumer        [.] 0x00000000000011f0
     0.13%     0.00%  producer_consum  libasan.so.5.0.0         [.] 0x00007f55746eea58
     0.13%     0.00%  producer_consum  [unknown]                [.] 0x303a676e69727473
     0.13%     0.00%  producer_consum  [unknown]                [.] 0x343a676e69727473
     0.13%     0.00%  producer_consum  [unknown]                [.] 0x353a676e69727473
     0.13%     0.00%  producer_consum  [unknown]                [.] 0x363a676e69727473
     0.13%     0.00%  producer_consum  [unknown]                [.] 0x373a676e69727473
     0.13%     0.00%  producer_consum  libc-2.31.so             [.] 0x00007f55744f7460
     0.13%     0.00%  producer_consum  libc-2.31.so             [.] 0x00007f55744f75a0
     0.13%     0.00%  producer_consum  producer_consumer        [.] 0x000055d656525120
     0.13%     0.00%  producer_consum  producer_consumer        [.] 0x000055d6565251a0
     0.13%     0.00%  producer_consum  [unknown]                [.] 0x000055d656528140
     0.13%     0.00%  producer_consum  producer_consumer        [.] 0x000055d6565251f0
     0.06%     0.06%  producer_consum  ld-2.31.so               [.] _dl_relocate_object
     0.06%     0.00%  producer_consum  ld-2.31.so               [.] _dl_sysdep_start
     0.06%     0.06%  producer_consum  ld-2.31.so               [.] _dl_lookup_symbol_x
     0.06%     0.06%  producer_consum  libc-2.31.so             [.] 0x0000000000022394
     0.06%     0.06%  producer_consum  libc-2.31.so             [.] 0x0000000000022464
     0.06%     0.06%  producer_consum  producer_consumer        [.] 0x0000000000001124
     0.06%     0.06%  producer_consum  producer_consumer        [.] 0x0000000000001150
     0.06%     0.00%  producer_consum  ld-2.31.so               [.] dl_main
     0.06%     0.06%  producer_consum  libc-2.31.so             [.] __GI___sigaction
     0.06%     0.00%  producer_consum  [unknown]                [.] 0x0000000000000033
     0.06%     0.00%  producer_consum  [unknown]                [.] 0x000055d6565280c0
     0.06%     0.00%  producer_consum  [unknown]                [.] 0x000055d6565280e0
     0.06%     0.00%  producer_consum  [unknown]                [.] 0x000055d656528160
     0.06%     0.00%  producer_consum  [unknown]                [.] 0x000055d6565281b0
     0.06%     0.00%  producer_consum  [unknown]                [.] 0x000055d656528200
     0.06%     0.00%  producer_consum  [unknown]                [.] 0x000055d656528230
     0.06%     0.00%  producer_consum  libc-2.31.so             [.] 0x00007f55744f7394
     0.06%     0.00%  producer_consum  libc-2.31.so             [.] 0x00007f55744f7464
     0.06%     0.00%  producer_consum  [unknown]                [.] 0x0000303432383235
     0.06%     0.00%  producer_consum  [unknown]                [.] 0x0000303731383235
     0.06%     0.00%  producer_consum  [unknown]                [.] 0x0000306131383235
     0.06%     0.00%  producer_consum  [unknown]                [.] 0x0000306230383235
     0.06%     0.00%  producer_consum  [unknown]                [.] 0x0000306430383235
     0.06%     0.00%  producer_consum  [unknown]                [.] 0x0000303332383235
     0.06%     0.00%  producer_consum  [unknown]                [.] 0x383a676e69727473
     0.06%     0.00%  producer_consum  producer_consumer        [.] 0x000055d656525124
     0.06%     0.00%  producer_consum  producer_consumer        [.] 0x000055d656525150
     0.06%     0.00%  producer_consum  [unknown]                [.] 0x41e589480000b274
     0.06%     0.00%  producer_consum  [unknown]                [.] 0x8348c0940fe5394d


#
# (Tip: Use parent filter to see specific call path: perf report -p <regex>)
#
(END)
```


The following is the report for `perf record ./build/producer_consumer`

```shell
# To display the perf.data header info, please use --header/--header-only options.
#
#
# Total Lost Samples: 0
#
# Samples: 3K of event 'cpu-clock:uhpppH'
# Event count (approx.): 979250000
#
# Overhead  Command          Shared Object            Symbol                                                                                                                                                       
# ........  ...............  .......................  .............................................................................................................................................................
#
    16.29%  producer_consum  libproducer_consumer.so  [.] rb_test
    10.39%  producer_consum  libc-2.31.so             [.] __vfprintf_internal
     9.65%  producer_consum  producer_consumer        [.] run_consumer
     6.82%  producer_consum  libasan.so.5.0.0         [.] _ZL13printf_commonPvPKcP13__va_list_tag
     4.52%  producer_consum  libc-2.31.so             [.] clock_nanosleep@@GLIBC_2.17
     4.47%  producer_consum  libasan.so.5.0.0         [.] _ZN11__sanitizer15internal_strchrEPKci
     3.75%  producer_consum  libasan.so.5.0.0         [.] _ZN11__sanitizer15internal_memsetEPvim
     3.04%  producer_consum  libc-2.31.so             [.] _IO_file_xsputn@@GLIBC_2.2.5
     2.86%  producer_consum  producer_consumer        [.] 0x0000000000001160
     2.78%  producer_consum  libc-2.31.so             [.] _IO_default_xsputn
     2.40%  producer_consum  producer_consumer        [.] run_producer
     2.25%  producer_consum  libc-2.31.so             [.] __strchrnul_avx2
     2.09%  producer_consum  libasan.so.5.0.0         [.] __interceptor_vsprintf
     1.89%  producer_consum  libc-2.31.so             [.] __strlen_avx2
     1.68%  producer_consum  libasan.so.5.0.0         [.] _ZN11__sanitizer15internal_strlenEPKc
     1.61%  producer_consum  libproducer_consumer.so  [.] rb_add
     1.48%  producer_consum  libc-2.31.so             [.] __GI___libc_write
     1.38%  producer_consum  libc-2.31.so             [.] _IO_vsprintf
     1.33%  producer_consum  libasan.so.5.0.0         [.] _ZL27maybe_parse_length_modifierPKcPc
     1.15%  producer_consum  libc-2.31.so             [.] _itoa_word
     1.10%  producer_consum  libasan.so.5.0.0         [.] __interceptor_vprintf
     1.07%  producer_consum  libc-2.31.so             [.] __libc_disable_asynccancel
     1.02%  producer_consum  libproducer_consumer.so  [.] rb_get
     0.97%  producer_consum  libc-2.31.so             [.] __sleep
     0.94%  producer_consum  libc-2.31.so             [.] __memmove_avx_unaligned_erms
     0.87%  producer_consum  libasan.so.5.0.0         [.] __interceptor_sprintf
     0.84%  producer_consum  libc-2.31.so             [.] _IO_file_write@@GLIBC_2.2.5
     0.77%  producer_consum  libasan.so.5.0.0         [.] _ZL21format_get_value_sizecPKcb
     0.77%  producer_consum  libc-2.31.so             [.] _IO_str_init_static_internal
     0.74%  producer_consum  libc-2.31.so             [.] _IO_old_init
     0.71%  producer_consum  libc-2.31.so             [.] _IO_do_write@@GLIBC_2.2.5
     0.69%  producer_consum  libc-2.31.so             [.] _IO_setb
     0.69%  producer_consum  libc-2.31.so             [.] __libc_enable_asynccancel
     0.69%  producer_consum  libc-2.31.so             [.] __nanosleep
     0.64%  producer_consum  libc-2.31.so             [.] _IO_no_init
     0.64%  producer_consum  libc-2.31.so             [.] __mempcpy_avx_unaligned_erms
     0.61%  producer_consum  libasan.so.5.0.0         [.] __interceptor_printf
     0.59%  producer_consum  libasan.so.5.0.0         [.] _ZL20format_get_char_sizecPKc
     0.59%  producer_consum  libasan.so.5.0.0         [.] __interceptor_strcpy.part.0
     0.51%  producer_consum  libc-2.31.so             [.] __strcpy_avx2
     0.36%  producer_consum  libc-2.31.so             [.] 0x0000000000022390
     0.36%  producer_consum  libpthread-2.31.so       [.] _pthread_cleanup_pop_restore
     0.31%  producer_consum  libc-2.31.so             [.] vprintf
     0.28%  producer_consum  libpthread-2.31.so       [.] _pthread_cleanup_push_defer
     0.26%  producer_consum  libc-2.31.so             [.] _IO_file_overflow@@GLIBC_2.2.5
     0.20%  producer_consum  libc-2.31.so             [.] 0x0000000000022460
     0.18%  producer_consum  libasan.so.5.0.0         [.] 0x0000000000022a58
     0.15%  producer_consum  producer_consumer        [.] static_string_producer
     0.13%  producer_consum  libc-2.31.so             [.] 0x00000000000225a0
     0.13%  producer_consum  producer_consumer        [.] 0x0000000000001120
     0.10%  producer_consum  libasan.so.5.0.0         [.] __interceptor_strcpy
     0.05%  producer_consum  libasan.so.5.0.0         [.] _ZN11__sanitizer20SizeClassAllocator32INS_4AP32EE16PopulateFreeListEPNS_14AllocatorStatsEPNS_30SizeClassAllocator32LocalCacheIS2_EEPNS2_13SizeClassInfoEm
     0.05%  producer_consum  libc-2.31.so             [.] 0x0000000000022394
     0.05%  producer_consum  producer_consumer        [.] 0x00000000000011a0
     0.03%  producer_consum  ld-2.31.so               [.] mmap64
     0.03%  producer_consum  producer_consumer        [.] 0x0000000000001150
     0.03%  producer_consum  producer_consumer        [.] 0x0000000000001164
     0.03%  producer_consum  producer_consumer        [.] 0x00000000000011d4
     0.03%  producer_consum  producer_consumer        [.] 0x00000000000011f0


#
# (Tip: For tracepoint events, try: perf report -s trace_fields)
#
(END)
```