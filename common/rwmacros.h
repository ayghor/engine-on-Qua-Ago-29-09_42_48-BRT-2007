/*
 * rwmacros.h
 *
 * macros para leitura e escrita de arquivos
 *
 */

#ifndef __RWMACROS_H__
#define __RWMACROS_H__ 1

#define read_char(f, b) fread((b), 1, 1, (f))
#define read_short(f, b) fread((b), 4, 1, (f))
#define read_int(f, b) fread((b), 4, 1, (f))
#define read_long(f, b) fread((b), 4, 1, (f))
#define read_float(f, b) fread((b), 4, 1, (f))
#define read_double(f, b) fread((b), 8, 1, (f))

#define read_vec(f, v) read_double((f), (v))

#define read_vec2(f, v)			\
{					\
	read_vec((f), &(v)[0]);		\
	read_vec((f), &(v)[1]);		\
}

#define read_vec3(f, v)			\
{					\
	read_vec((f), &(v)[0]);		\
	read_vec((f), &(v)[1]);		\
	read_vec((f), &(v)[2]);		\
}

#define read_vec4(f, v)			\
{					\
	read_vec((f), &(v)[0]);		\
	read_vec((f), &(v)[1]);		\
	read_vec((f), &(v)[2]);		\
	read_vec((f), &(v)[3]);		\
}

#define read_fvec(f, v) read_float((f), (v))

#define read_fvec2(f, v)		\
{					\
	read_fvec((f), &(v)[0]);	\
	read_fvec((f), &(v)[1]);	\
}

#define read_fvec3(f, v)		\
{					\
	read_fvec((f), &(v)[0]);	\
	read_fvec((f), &(v)[1]);	\
	read_fvec((f), &(v)[2]);	\
}

#define read_fvec4(f, v)		\
{					\
	read_fvec((f), &(v)[0]);	\
	read_fvec((f), &(v)[1]);	\
	read_fvec((f), &(v)[2]);	\
	read_fvec((f), &(v)[3]);	\
}

#define write_char(f, b) fwrite((b), 1, 1, (f))
#define write_short(f, b) fwrite((b), 4, 1, (f))
#define write_int(f, b) fwrite((b), 4, 1, (f))
#define write_long(f, b) fwrite((b), 4, 1, (f))
#define write_float(f, b) fwrite((b), 4, 1, (f))
#define write_double(f, b) fwrite((b), 8, 1, (f))

#define write_vec(f, v) write_double((f), (v))

#define write_vec2(f, v)		\
{					\
	write_vec((f), &(v)[0]);	\
	write_vec((f), &(v)[1]);	\
}

#define write_vec3(f, v)		\
{					\
	write_vec((f), &(v)[0]);	\
	write_vec((f), &(v)[1]);	\
	write_vec((f), &(v)[2]);	\
}

#define write_vec4(f, v)		\
{					\
	write_vec((f), &(v)[0]);	\
	write_vec((f), &(v)[1]);	\
	write_vec((f), &(v)[2]);	\
	write_vec((f), &(v)[3]);	\
}

#define write_fvec(f, v) write_float((f), (v))

#define write_fvec2(f, v)		\
{					\
	write_fvec((f), &(v)[0]);	\
	write_fvec((f), &(v)[1]);	\
}

#define write_fvec3(f, v)		\
{					\
	write_fvec((f), &(v)[0]);	\
	write_fvec((f), &(v)[1]);	\
	write_fvec((f), &(v)[2]);	\
}

#define write_fvec4(f, v)		\
{					\
	write_fvec((f), &(v)[0]);	\
	write_fvec((f), &(v)[1]);	\
	write_fvec((f), &(v)[2]);	\
	write_fvec((f), &(v)[3]);	\
}

#endif /* __RWMACROS_H__ */

/* EOF */
