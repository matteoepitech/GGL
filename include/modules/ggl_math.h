/*
** GGL PROJECT, 2025
** include/modules/ggl_math.h
** File description:
** GGL Math module header file
*/

#ifndef _GGL_MODULE_MATH_H_
    #define _GGL_MODULE_MATH_H_

    #include "../misc/ggl_types.h"

/*
 * Location : src/math/ggl_coords_helper.c
 */
ggl_vector2f ggl_coords_normalize_to_ndc(ggl_context *ctx,
    ggl_vector2f ref_coords);
ggl_vector2f ggl_coords_adapt_to_current_size(ggl_context *ctx,
    ggl_vector2f ref_coords);

#endif /* ifndef _GGL_MODULE_MATH_H_ */
