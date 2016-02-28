/*
 * r_model.h
 *
 * Funções para desenho de modelos 3d
 *
 */

#ifndef __R_MODEL_H__
#define __R_MODEL_H__ 1

#include "graphics/model.h"
#include "graphics/image.h"

inline void r_loadtexture(image_t* texture);
inline void r_render_vertex(const vertex_t* vert);
inline void r_render_point(const vertex_t* vert);
inline void r_render_line(const vertex_t* verta, const vertex_t* vertb);
inline void r_render_polygon(const polygon_t* poly);
inline void r_render_model(const model_t* model);

#endif /* __R_MODEL_H__ */

/* EOF */
