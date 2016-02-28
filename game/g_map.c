/*
 * g_map.c
 *
 * modulo do mapa
 *
 */

#include "sys/sys_common.h"
#include "bsp/bsp.h"

bsp_tree_t g_map;

int g_map_load(const char* filename)
{
	int r;

	r = bsp_tree_read(&g_map, filename);
	if(r == -1)
	{
		sys_warn(_("error opening %s."), filename);
		return -1;
	}

	return 0;
}

void g_map_free()
{
	bsp_tree_free(&g_map);
}

/* EOF */
