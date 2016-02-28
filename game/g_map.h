/*
 * g_map.h
 *
 * modulo do mapa
 *
 */

#ifndef __G_MAP_H__
#define __G_MAP_H__ 1

extern bsp_tree_t g_map;

int g_map_load(const char* filename);
void g_map_free();

#endif /* __G_MAP_H__ */

/* EOF */
