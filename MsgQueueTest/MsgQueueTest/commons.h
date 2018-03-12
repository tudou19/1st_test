#pragma once

#define offset_of(s,type,member) do{ \
	s = (size_t)(&(((type *)0)->member)); \
}while (false)

#define container_of(ct,ptr,type,member) do{ \
	size_t __s__; offset_of(__s__,type,member);\
	ct = (type *)((char *)ptr - __s__); \
}while(false)