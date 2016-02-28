/*
 * tr_model.h
 *
 * ray tracing para modelos 3d
 *
 */

#ifndef __TR_MODEL_H__
#define __TR_MODEL_H__ 1

#include "common/vector.h"
#include "common/boolean.h"
#include "graphics/model.h"

inline bool tr_point_in_polygon(const vec3_t p, const polygon_t* poly);

#endif /* __TR_MODEL_H__ */

/* EOF */
