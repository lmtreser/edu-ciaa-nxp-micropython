# 1 "<stdin>"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "<stdin>"
# 27 "<stdin>"
# 1 "../py/mpconfig.h" 1
# 45 "../py/mpconfig.h"
# 1 "./mpconfigport.h" 1
# 1 "/home/lucas/Software/gcc-arm-none-eabi-4_8-2014q2/lib/gcc/arm-none-eabi/4.8.4/include/stdint.h" 1 3 4
# 9 "/home/lucas/Software/gcc-arm-none-eabi-4_8-2014q2/lib/gcc/arm-none-eabi/4.8.4/include/stdint.h" 3 4
# 1 "/home/lucas/Software/gcc-arm-none-eabi-4_8-2014q2/arm-none-eabi/include/stdint.h" 1 3 4
# 12 "/home/lucas/Software/gcc-arm-none-eabi-4_8-2014q2/arm-none-eabi/include/stdint.h" 3 4
# 1 "/home/lucas/Software/gcc-arm-none-eabi-4_8-2014q2/arm-none-eabi/include/machine/_default_types.h" 1 3 4







# 1 "/home/lucas/Software/gcc-arm-none-eabi-4_8-2014q2/arm-none-eabi/include/sys/features.h" 1 3 4
# 9 "/home/lucas/Software/gcc-arm-none-eabi-4_8-2014q2/arm-none-eabi/include/machine/_default_types.h" 2 3 4
# 27 "/home/lucas/Software/gcc-arm-none-eabi-4_8-2014q2/arm-none-eabi/include/machine/_default_types.h" 3 4
typedef signed char __int8_t;
typedef unsigned char __uint8_t;
# 37 "/home/lucas/Software/gcc-arm-none-eabi-4_8-2014q2/arm-none-eabi/include/machine/_default_types.h" 3 4
typedef short int __int16_t;
typedef short unsigned int __uint16_t;
# 55 "/home/lucas/Software/gcc-arm-none-eabi-4_8-2014q2/arm-none-eabi/include/machine/_default_types.h" 3 4
typedef long int __int32_t;
typedef long unsigned int __uint32_t;
# 77 "/home/lucas/Software/gcc-arm-none-eabi-4_8-2014q2/arm-none-eabi/include/machine/_default_types.h" 3 4
typedef long long int __int64_t;
typedef long long unsigned int __uint64_t;
# 104 "/home/lucas/Software/gcc-arm-none-eabi-4_8-2014q2/arm-none-eabi/include/machine/_default_types.h" 3 4
typedef signed char __int_least8_t;
typedef unsigned char __uint_least8_t;
# 126 "/home/lucas/Software/gcc-arm-none-eabi-4_8-2014q2/arm-none-eabi/include/machine/_default_types.h" 3 4
typedef short int __int_least16_t;
typedef short unsigned int __uint_least16_t;
# 144 "/home/lucas/Software/gcc-arm-none-eabi-4_8-2014q2/arm-none-eabi/include/machine/_default_types.h" 3 4
typedef long int __int_least32_t;
typedef long unsigned int __uint_least32_t;
# 158 "/home/lucas/Software/gcc-arm-none-eabi-4_8-2014q2/arm-none-eabi/include/machine/_default_types.h" 3 4
typedef long long int __int_least64_t;
typedef long long unsigned int __uint_least64_t;
# 168 "/home/lucas/Software/gcc-arm-none-eabi-4_8-2014q2/arm-none-eabi/include/machine/_default_types.h" 3 4
typedef int __intptr_t;
typedef unsigned int __uintptr_t;
# 13 "/home/lucas/Software/gcc-arm-none-eabi-4_8-2014q2/arm-none-eabi/include/stdint.h" 2 3 4
# 41 "/home/lucas/Software/gcc-arm-none-eabi-4_8-2014q2/arm-none-eabi/include/stdint.h" 3 4
typedef __int8_t int8_t ;
typedef __uint8_t uint8_t ;




typedef __int_least8_t int_least8_t;
typedef __uint_least8_t uint_least8_t;




typedef __int16_t int16_t ;
typedef __uint16_t uint16_t ;




typedef __int_least16_t int_least16_t;
typedef __uint_least16_t uint_least16_t;




typedef __int32_t int32_t ;
typedef __uint32_t uint32_t ;




typedef __int_least32_t int_least32_t;
typedef __uint_least32_t uint_least32_t;




typedef __int64_t int64_t ;
typedef __uint64_t uint64_t ;




typedef __int_least64_t int_least64_t;
typedef __uint_least64_t uint_least64_t;
# 95 "/home/lucas/Software/gcc-arm-none-eabi-4_8-2014q2/arm-none-eabi/include/stdint.h" 3 4
  typedef int int_fast8_t;
  typedef unsigned int uint_fast8_t;
# 105 "/home/lucas/Software/gcc-arm-none-eabi-4_8-2014q2/arm-none-eabi/include/stdint.h" 3 4
  typedef int int_fast16_t;
  typedef unsigned int uint_fast16_t;
# 115 "/home/lucas/Software/gcc-arm-none-eabi-4_8-2014q2/arm-none-eabi/include/stdint.h" 3 4
  typedef int int_fast32_t;
  typedef unsigned int uint_fast32_t;
# 125 "/home/lucas/Software/gcc-arm-none-eabi-4_8-2014q2/arm-none-eabi/include/stdint.h" 3 4
  typedef long long int int_fast64_t;
  typedef long long unsigned int uint_fast64_t;
# 174 "/home/lucas/Software/gcc-arm-none-eabi-4_8-2014q2/arm-none-eabi/include/stdint.h" 3 4
  typedef long long int intmax_t;
# 183 "/home/lucas/Software/gcc-arm-none-eabi-4_8-2014q2/arm-none-eabi/include/stdint.h" 3 4
  typedef long long unsigned int uintmax_t;






typedef __intptr_t intptr_t;
typedef __uintptr_t uintptr_t;
# 10 "/home/lucas/Software/gcc-arm-none-eabi-4_8-2014q2/lib/gcc/arm-none-eabi/4.8.4/include/stdint.h" 2 3 4
# 2 "./mpconfigport.h" 2
# 89 "./mpconfigport.h"
typedef int mp_int_t;
typedef unsigned int mp_uint_t;
typedef void *machine_ptr_t;
typedef const void *machine_const_ptr_t;
typedef long mp_off_t;


extern const struct _mp_obj_fun_builtin_t mp_builtin_help_obj;
extern const struct _mp_obj_fun_builtin_t mp_builtin_input_obj;
extern const struct _mp_obj_fun_builtin_t mp_builtin_open_obj;






extern const struct _mp_obj_module_t pyb_module;
extern const struct _mp_obj_module_t mp_module_collections;
extern const struct _mp_obj_module_t mp_module_ustruct;
extern const struct _mp_obj_module_t mp_module_ubinascii;
extern const struct _mp_obj_module_t mp_module_ure;
extern const struct _mp_obj_module_t mp_module_uzlib;
extern const struct _mp_obj_module_t mp_module_ujson;
extern const struct _mp_obj_module_t mp_module_uheapq;
extern const struct _mp_obj_module_t mp_module_uhashlib;
extern const struct _mp_obj_module_t mp_module_uos;
extern const struct _mp_obj_module_t mp_module_io;
extern const struct _mp_obj_module_t mp_module_utime;
# 137 "./mpconfigport.h"
# 1 "/home/lucas/Software/gcc-arm-none-eabi-4_8-2014q2/arm-none-eabi/include/alloca.h" 1 3
# 10 "/home/lucas/Software/gcc-arm-none-eabi-4_8-2014q2/arm-none-eabi/include/alloca.h" 3
# 1 "/home/lucas/Software/gcc-arm-none-eabi-4_8-2014q2/arm-none-eabi/include/_ansi.h" 1 3
# 15 "/home/lucas/Software/gcc-arm-none-eabi-4_8-2014q2/arm-none-eabi/include/_ansi.h" 3
# 1 "/home/lucas/Software/gcc-arm-none-eabi-4_8-2014q2/arm-none-eabi/include/newlib.h" 1 3
# 16 "/home/lucas/Software/gcc-arm-none-eabi-4_8-2014q2/arm-none-eabi/include/_ansi.h" 2 3
# 1 "/home/lucas/Software/gcc-arm-none-eabi-4_8-2014q2/arm-none-eabi/include/sys/config.h" 1 3



# 1 "/home/lucas/Software/gcc-arm-none-eabi-4_8-2014q2/arm-none-eabi/include/machine/ieeefp.h" 1 3
# 5 "/home/lucas/Software/gcc-arm-none-eabi-4_8-2014q2/arm-none-eabi/include/sys/config.h" 2 3
# 17 "/home/lucas/Software/gcc-arm-none-eabi-4_8-2014q2/arm-none-eabi/include/_ansi.h" 2 3
# 11 "/home/lucas/Software/gcc-arm-none-eabi-4_8-2014q2/arm-none-eabi/include/alloca.h" 2 3
# 1 "/home/lucas/Software/gcc-arm-none-eabi-4_8-2014q2/arm-none-eabi/include/sys/reent.h" 1 3
# 13 "/home/lucas/Software/gcc-arm-none-eabi-4_8-2014q2/arm-none-eabi/include/sys/reent.h" 3
# 1 "/home/lucas/Software/gcc-arm-none-eabi-4_8-2014q2/arm-none-eabi/include/_ansi.h" 1 3
# 14 "/home/lucas/Software/gcc-arm-none-eabi-4_8-2014q2/arm-none-eabi/include/sys/reent.h" 2 3
# 1 "/home/lucas/Software/gcc-arm-none-eabi-4_8-2014q2/lib/gcc/arm-none-eabi/4.8.4/include/stddef.h" 1 3 4
# 147 "/home/lucas/Software/gcc-arm-none-eabi-4_8-2014q2/lib/gcc/arm-none-eabi/4.8.4/include/stddef.h" 3 4
typedef int ptrdiff_t;
# 212 "/home/lucas/Software/gcc-arm-none-eabi-4_8-2014q2/lib/gcc/arm-none-eabi/4.8.4/include/stddef.h" 3 4
typedef unsigned int size_t;
# 324 "/home/lucas/Software/gcc-arm-none-eabi-4_8-2014q2/lib/gcc/arm-none-eabi/4.8.4/include/stddef.h" 3 4
typedef unsigned int wchar_t;
# 15 "/home/lucas/Software/gcc-arm-none-eabi-4_8-2014q2/arm-none-eabi/include/sys/reent.h" 2 3
# 1 "/home/lucas/Software/gcc-arm-none-eabi-4_8-2014q2/arm-none-eabi/include/sys/_types.h" 1 3
# 12 "/home/lucas/Software/gcc-arm-none-eabi-4_8-2014q2/arm-none-eabi/include/sys/_types.h" 3
# 1 "/home/lucas/Software/gcc-arm-none-eabi-4_8-2014q2/arm-none-eabi/include/machine/_types.h" 1 3
# 13 "/home/lucas/Software/gcc-arm-none-eabi-4_8-2014q2/arm-none-eabi/include/sys/_types.h" 2 3
# 1 "/home/lucas/Software/gcc-arm-none-eabi-4_8-2014q2/arm-none-eabi/include/sys/lock.h" 1 3





typedef int _LOCK_T;
typedef int _LOCK_RECURSIVE_T;
# 14 "/home/lucas/Software/gcc-arm-none-eabi-4_8-2014q2/arm-none-eabi/include/sys/_types.h" 2 3


typedef long _off_t;



typedef short __dev_t;



typedef unsigned short __uid_t;


typedef unsigned short __gid_t;



__extension__ typedef long long _off64_t;







typedef long _fpos_t;
# 55 "/home/lucas/Software/gcc-arm-none-eabi-4_8-2014q2/arm-none-eabi/include/sys/_types.h" 3
typedef signed int _ssize_t;
# 67 "/home/lucas/Software/gcc-arm-none-eabi-4_8-2014q2/arm-none-eabi/include/sys/_types.h" 3
# 1 "/home/lucas/Software/gcc-arm-none-eabi-4_8-2014q2/lib/gcc/arm-none-eabi/4.8.4/include/stddef.h" 1 3 4
# 353 "/home/lucas/Software/gcc-arm-none-eabi-4_8-2014q2/lib/gcc/arm-none-eabi/4.8.4/include/stddef.h" 3 4
typedef unsigned int wint_t;
# 68 "/home/lucas/Software/gcc-arm-none-eabi-4_8-2014q2/arm-none-eabi/include/sys/_types.h" 2 3



typedef struct
{
  int __count;
  union
  {
    wint_t __wch;
    unsigned char __wchb[4];
  } __value;
} _mbstate_t;



typedef _LOCK_RECURSIVE_T _flock_t;




typedef void *_iconv_t;
# 16 "/home/lucas/Software/gcc-arm-none-eabi-4_8-2014q2/arm-none-eabi/include/sys/reent.h" 2 3






typedef unsigned long __ULong;
# 38 "/home/lucas/Software/gcc-arm-none-eabi-4_8-2014q2/arm-none-eabi/include/sys/reent.h" 3
struct _reent;






struct _Bigint
{
  struct _Bigint *_next;
  int _k, _maxwds, _sign, _wds;
  __ULong _x[1];
};


struct __tm
{
  int __tm_sec;
  int __tm_min;
  int __tm_hour;
  int __tm_mday;
  int __tm_mon;
  int __tm_year;
  int __tm_wday;
  int __tm_yday;
  int __tm_isdst;
};







struct _on_exit_args {
 void * _fnargs[32];
 void * _dso_handle[32];

 __ULong _fntypes;


 __ULong _is_cxa;
};
# 91 "/home/lucas/Software/gcc-arm-none-eabi-4_8-2014q2/arm-none-eabi/include/sys/reent.h" 3
struct _atexit {
 struct _atexit *_next;
 int _ind;

 void (*_fns[32])(void);
        struct _on_exit_args _on_exit_args;
};
# 115 "/home/lucas/Software/gcc-arm-none-eabi-4_8-2014q2/arm-none-eabi/include/sys/reent.h" 3
struct __sbuf {
 unsigned char *_base;
 int _size;
};
# 179 "/home/lucas/Software/gcc-arm-none-eabi-4_8-2014q2/arm-none-eabi/include/sys/reent.h" 3
struct __sFILE {
  unsigned char *_p;
  int _r;
  int _w;
  short _flags;
  short _file;
  struct __sbuf _bf;
  int _lbfsize;






  void * _cookie;

  int (* _read) (struct _reent *, void *, char *, int)
                                          ;
  int (* _write) (struct _reent *, void *, const char *, int)

                                   ;
  _fpos_t (* _seek) (struct _reent *, void *, _fpos_t, int);
  int (* _close) (struct _reent *, void *);


  struct __sbuf _ub;
  unsigned char *_up;
  int _ur;


  unsigned char _ubuf[3];
  unsigned char _nbuf[1];


  struct __sbuf _lb;


  int _blksize;
  _off_t _offset;


  struct _reent *_data;



  _flock_t _lock;

  _mbstate_t _mbstate;
  int _flags2;
};
# 285 "/home/lucas/Software/gcc-arm-none-eabi-4_8-2014q2/arm-none-eabi/include/sys/reent.h" 3
typedef struct __sFILE __FILE;



struct _glue
{
  struct _glue *_next;
  int _niobs;
  __FILE *_iobs;
};
# 317 "/home/lucas/Software/gcc-arm-none-eabi-4_8-2014q2/arm-none-eabi/include/sys/reent.h" 3
struct _rand48 {
  unsigned short _seed[3];
  unsigned short _mult[3];
  unsigned short _add;




};
# 569 "/home/lucas/Software/gcc-arm-none-eabi-4_8-2014q2/arm-none-eabi/include/sys/reent.h" 3
struct _reent
{
  int _errno;




  __FILE *_stdin, *_stdout, *_stderr;

  int _inc;
  char _emergency[25];

  int _current_category;
  const char *_current_locale;

  int __sdidinit;

  void (* __cleanup) (struct _reent *);


  struct _Bigint *_result;
  int _result_k;
  struct _Bigint *_p5s;
  struct _Bigint **_freelist;


  int _cvtlen;
  char *_cvtbuf;

  union
    {
      struct
        {
          unsigned int _unused_rand;
          char * _strtok_last;
          char _asctime_buf[26];
          struct __tm _localtime_buf;
          int _gamma_signgam;
          __extension__ unsigned long long _rand_next;
          struct _rand48 _r48;
          _mbstate_t _mblen_state;
          _mbstate_t _mbtowc_state;
          _mbstate_t _wctomb_state;
          char _l64a_buf[8];
          char _signal_buf[24];
          int _getdate_err;
          _mbstate_t _mbrlen_state;
          _mbstate_t _mbrtowc_state;
          _mbstate_t _mbsrtowcs_state;
          _mbstate_t _wcrtomb_state;
          _mbstate_t _wcsrtombs_state;
   int _h_errno;
        } _reent;



      struct
        {

          unsigned char * _nextf[30];
          unsigned int _nmalloc[30];
        } _unused;
    } _new;



  struct _atexit *_atexit;
  struct _atexit _atexit0;



  void (**(_sig_func))(int);




  struct _glue __sglue;
  __FILE __sf[3];
};
# 762 "/home/lucas/Software/gcc-arm-none-eabi-4_8-2014q2/arm-none-eabi/include/sys/reent.h" 3
extern struct _reent *_impure_ptr ;
extern struct _reent *const _global_impure_ptr ;

void _reclaim_reent (struct _reent *);
# 12 "/home/lucas/Software/gcc-arm-none-eabi-4_8-2014q2/arm-none-eabi/include/alloca.h" 2 3
# 138 "./mpconfigport.h" 2
# 46 "../py/mpconfig.h" 2
# 457 "../py/mpconfig.h"
typedef float mp_float_t;
# 28 "<stdin>" 2





QCFG(BYTES_IN_LEN, (1))
QCFG(BYTES_IN_HASH, (1))

Q()
Q(*)
Q(_)
Q(__build_class__)
Q(__class__)
Q(__doc__)
Q(__import__)
Q(__init__)
Q(__new__)
Q(__locals__)
Q(__main__)
Q(__module__)
Q(__name__)
Q(__dict__)
Q(__hash__)
Q(__next__)
Q(__qualname__)
Q(__path__)
Q(__repl_print__)

Q(__file__)


Q(__bool__)
Q(__contains__)
Q(__enter__)
Q(__exit__)
Q(__len__)
Q(__iter__)
Q(__getitem__)
Q(__setitem__)
Q(__delitem__)
Q(__add__)
Q(__sub__)
Q(__repr__)
Q(__str__)





Q(__getattr__)
Q(__del__)
Q(__call__)
Q(__lt__)
Q(__gt__)
Q(__eq__)
Q(__le__)
Q(__ge__)
Q(__reversed__)
# 97 "<stdin>"
Q(micropython)
Q(bytecode)
Q(const)


Q(native)
Q(viper)
Q(uint)
Q(ptr)
Q(ptr8)
Q(ptr16)
Q(ptr32)



Q(asm_thumb)
Q(label)
Q(align)
Q(data)


Q(builtins)

Q(Ellipsis)
Q(StopIteration)




Q(BaseException)
Q(ArithmeticError)
Q(AssertionError)
Q(AttributeError)
Q(BufferError)
Q(EOFError)
Q(Exception)
Q(FileExistsError)
Q(FileNotFoundError)
Q(FloatingPointError)
Q(GeneratorExit)
Q(ImportError)
Q(IndentationError)
Q(IndexError)
Q(KeyboardInterrupt)
Q(KeyError)
Q(LookupError)
Q(MemoryError)
Q(NameError)
Q(NotImplementedError)
Q(OSError)



Q(OverflowError)
Q(RuntimeError)
Q(SyntaxError)
Q(SystemExit)
Q(TypeError)
Q(UnboundLocalError)
Q(ValueError)

Q(ViperTypeError)

Q(ZeroDivisionError)

Q(UnicodeError)


Q(None)
Q(False)
Q(True)
Q(object)

Q(NoneType)





Q(abs)
Q(all)
Q(any)
Q(args)

Q(array)

Q(bin)
Q({:#b})
Q(bool)

Q(bytearray)


Q(memoryview)

Q(bytes)
Q(callable)
Q(chr)
Q(classmethod)
Q(_collections)

Q(complex)
Q(real)
Q(imag)

Q(dict)
Q(dir)
Q(divmod)

Q(enumerate)

Q(eval)
Q(exec)

Q(execfile)


Q(filter)


Q(float)

Q(from_bytes)
Q(getattr)
Q(setattr)
Q(globals)
Q(hasattr)
Q(hash)
Q(hex)
Q(%#x)
Q(id)
Q(int)
Q(isinstance)
Q(issubclass)
Q(iter)
Q(len)
Q(list)
Q(locals)
Q(map)

Q(max)
Q(min)
Q(default)

Q(namedtuple)
Q(next)
Q(oct)
Q(%#o)
Q(open)
Q(ord)
Q(path)
Q(pow)
Q(print)
Q(range)
Q(read)
Q(repr)
Q(reversed)
Q(round)
Q(sorted)
Q(staticmethod)
Q(sum)
Q(super)
Q(str)
Q(sys)
Q(to_bytes)
Q(tuple)
Q(type)
Q(value)
Q(write)
Q(zip)







Q(sep)
Q(end)


Q(step)
Q(stop)


Q(clear)
Q(copy)
Q(fromkeys)
Q(get)
Q(items)
Q(keys)
Q(pop)
Q(popitem)
Q(setdefault)
Q(update)
Q(values)
Q(append)
Q(close)
Q(send)
Q(throw)
Q(count)
Q(extend)
Q(index)
Q(remove)
Q(insert)
Q(pop)
Q(sort)
Q(join)
Q(strip)
Q(lstrip)
Q(rstrip)
Q(format)
Q(key)
Q(reverse)
Q(add)
Q(clear)
Q(copy)
Q(pop)
Q(remove)
Q(find)
Q(rfind)
Q(rindex)
Q(split)

Q(splitlines)
Q(keepends)
Q(\n)

Q(rsplit)
Q(startswith)
Q(endswith)
Q(replace)
Q(partition)
Q(rpartition)
Q(lower)
Q(upper)
Q(isspace)
Q(isalpha)
Q(isdigit)
Q(isupper)
Q(islower)
Q(iterable)
Q(start)

Q(bound_method)
Q(closure)
Q(dict_view)
Q(function)
Q(generator)
Q(iterator)
Q(module)
Q(slice)


Q(discard)
Q(difference)
Q(difference_update)
Q(intersection)
Q(intersection_update)
Q(isdisjoint)
Q(issubset)
Q(issuperset)
Q(set)
Q(symmetric_difference)
Q(symmetric_difference_update)
Q(union)
Q(update)



Q(frozenset)



Q(math)
Q(e)
Q(pi)
Q(sqrt)
Q(pow)
Q(exp)



Q(log)
# 391 "<stdin>"
Q(cos)
Q(sin)
Q(tan)
Q(acos)
Q(asin)
Q(atan)
Q(atan2)
Q(ceil)
Q(copysign)
Q(fabs)
Q(fmod)
Q(floor)
Q(isfinite)
Q(isinf)
Q(isnan)
Q(trunc)
Q(modf)
Q(frexp)
Q(ldexp)
Q(degrees)
Q(radians)
# 421 "<stdin>"
Q(cmath)
Q(phase)
Q(polar)
Q(rect)
# 440 "<stdin>"
Q(maximum recursion depth exceeded)

Q(<module>)
Q(<lambda>)
Q(<listcomp>)
Q(<dictcomp>)
Q(<setcomp>)
Q(<genexpr>)
Q(<string>)
Q(<stdin>)
# 458 "<stdin>"
Q(argv)
Q(byteorder)
Q(big)
Q(exit)
Q(little)



Q(stdin)
Q(stdout)
Q(stderr)

Q(buffer)

Q(version)
Q(version_info)

Q(name)

Q(implementation)




Q(modules)




Q(print_exception)



Q(struct)
Q(ustruct)
Q(pack)
Q(unpack)
Q(calcsize)



Q(uctypes)
Q(struct)
Q(sizeof)
Q(addressof)
Q(bytes_at)
Q(bytearray_at)

Q(NATIVE)
Q(LITTLE_ENDIAN)
Q(BIG_ENDIAN)

Q(VOID)

Q(UINT8)
Q(INT8)
Q(UINT16)
Q(INT16)
Q(UINT32)
Q(INT32)
Q(UINT64)
Q(INT64)

Q(BFUINT8)
Q(BFINT8)
Q(BFUINT16)
Q(BFINT16)
Q(BFUINT32)
Q(BFINT32)

Q(FLOAT32)
Q(FLOAT64)

Q(ARRAY)
Q(PTR)


Q(BF_POS)
Q(BF_LEN)



Q(_io)
Q(readall)
Q(readinto)
Q(readline)
Q(readlines)
Q(seek)
Q(tell)
Q(FileIO)
Q(TextIOWrapper)
Q(StringIO)
Q(BytesIO)
Q(getvalue)
Q(file)
Q(mode)
Q(r)
Q(encoding)



Q(gc)
Q(collect)
Q(disable)
Q(enable)
Q(isenabled)
Q(mem_free)
Q(mem_alloc)



Q(property)
Q(getter)
Q(setter)
Q(deleter)



Q(uzlib)
Q(decompress)



Q(ujson)
Q(dumps)
Q(loads)



Q(ure)
Q(compile)
Q(match)
Q(search)
Q(group)
Q(DEBUG)



Q(uheapq)
Q(heappush)
Q(heappop)
Q(heapify)



Q(uhashlib)
Q(update)
Q(digest)
Q(sha256)



Q(ubinascii)
Q(hexlify)
Q(unhexlify)
Q(a2b_base64)
Q(b2a_base64)
# 661 "<stdin>"
Q(mount)
Q(readonly)
Q(mkfs)
Q(readblocks)
Q(writeblocks)
Q(sync)
Q(count)







Q(pyb)
Q(millis)
Q(elapsed_millis)
Q(delay)

Q(LED)
Q(on)
Q(off)
Q(toggle)
Q(intensity)

Q(Switch)
Q(switch)
Q(callback)

Q(collections)

Q(UART)
Q(baudrate)
Q(bits)
Q(stop)
Q(parity)
Q(flow)
Q(read_buf_len)
Q(buf)
Q(len)
Q(timeout)
Q(timeout_char)
Q(packet_mode)
Q(packet_end_char)
Q(init)
Q(deinit)
Q(any)
Q(writechar)
Q(readchar)
Q(readinto)
Q(write_readinto)
Q(sendbreak)
Q(RTS)
Q(CTS)
Q(readline)
Q(readlines)
Q(readall)
Q(FileIO)
Q(os)
Q(uos)
Q(io)
Q(input)
Q(help)
Q(get_baudrate)


Q(Pin)
Q(IN)
Q(OUT_PP)
Q(OUT_OD)
Q(PULL_NONE)
Q(PULL_UP)
Q(PULL_DOWN)
Q(mode)
Q(pull)
Q(af)
Q(value)
Q(low)
Q(high)

Q(binascii)
Q(re)
Q(zlib)
Q(json)
Q(heapq)
Q(hashlib)

Q(/)
Q(/flash)
Q(/flash/lib)
Q(/sd)
Q(/sd/lib)

Q(flash)
Q(sd)
Q(sysname)
Q(nodename)
Q(release)
Q(version)
Q(machine)
Q(uname)
Q(chdir)
Q(getcwd)
Q(listdir)
Q(mkdir)
Q(rename)
Q(remove)
Q(rmdir)
Q(unlink)
Q(sep)
Q(stat)
Q(urandom)
Q(sync)
Q(execfile)

Q(readonly)
Q(mkfs)
Q(readblocks)
Q(writeblocks)
Q(flush)

Q(ExtInt)
Q(pin)
Q(IRQ_RISING)
Q(IRQ_FALLING)
Q(IRQ_RISING_FALLING)
Q(line)
Q(enable)
Q(disable)
Q(swint)

Q(DAC)
Q(write)
Q(noise)
Q(triangle)
Q(write_timed)
Q(NORMAL)
Q(CIRCULAR)
Q(data)
Q(freq)

Q(Timer)
Q(prescaler)
Q(period)
Q(counter)
Q(interval)
Q(source_freq)

Q(PWM)
Q(duty_cycle)
Q(set_frequency)

Q(ADC)
Q(read)

Q(Keyboard)
Q(get_matrix)
Q(get_char)

Q(LCD)
Q(clear)
Q(goto_xy)
Q(config_cursor)

Q(EEPROM)
Q(read_byte)
Q(write_byte)
Q(read_int)
Q(write_int)
Q(read_float)
Q(write_float)

Q(SPI)

Q(RTC)
Q(datetime)
Q(read_bkp_reg)
Q(write_bkp_reg)
Q(calibration)
Q(alarm_datetime)
Q(alarm_disable)
Q(MASK_SEC)
Q(MASK_MIN)
Q(MASK_HR)
Q(MASK_DAY)
Q(MASK_MON)
Q(MASK_YR)
Q(MASK_DOW)

Q(utime)
Q(time)
Q(localtime)
Q(mktime)
Q(sleep)

Q(I2C)
Q(slave_addr)
