/*
 * Copyright (c) 2009-2022 Arm Limited. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/*============================ INCLUDES ======================================*/

#include "arm_2d.h"

#define __USER_SCENE_CMSIS_STREAM_IMPLEMENT__
#include "arm_2d_scene_cmsis_stream.h"

#include "arm_2d_helper.h"
#include "arm_extra_controls.h"

#include <stdlib.h>
#include <string.h>

#if defined(__clang__)
#   pragma clang diagnostic push
#   pragma clang diagnostic ignored "-Wunknown-warning-option"
#   pragma clang diagnostic ignored "-Wreserved-identifier"
#   pragma clang diagnostic ignored "-Wsign-conversion"
#   pragma clang diagnostic ignored "-Wpadded"
#   pragma clang diagnostic ignored "-Wcast-qual"
#   pragma clang diagnostic ignored "-Wcast-align"
#   pragma clang diagnostic ignored "-Wmissing-field-initializers"
#   pragma clang diagnostic ignored "-Wgnu-zero-variadic-macro-arguments"
#   pragma clang diagnostic ignored "-Wmissing-prototypes"
#   pragma clang diagnostic ignored "-Wunused-variable"
#   pragma clang diagnostic ignored "-Wgnu-statement-expression"
#   pragma clang diagnostic ignored "-Wdeclaration-after-statement"
#   pragma clang diagnostic ignored "-Wunused-function"
#   pragma clang diagnostic ignored "-Wmissing-declarations"  
#elif __IS_COMPILER_ARM_COMPILER_5__
#elif __IS_COMPILER_IAR__
#   pragma diag_suppress=Pa089,Pe188,Pe177,Pe174
#elif __IS_COMPILER_GCC__
#   pragma GCC diagnostic push
#   pragma GCC diagnostic ignored "-Wformat="
#   pragma GCC diagnostic ignored "-Wpedantic"
#   pragma GCC diagnostic ignored "-Wunused-function"
#   pragma GCC diagnostic ignored "-Wunused-variable"
#   pragma GCC diagnostic ignored "-Wunused-value"
#endif

/*============================ MACROS ========================================*/

/*
 * note: If you want to change the background picture, you can simply update 
 *       the macro c_tileCMSISStreamPanel to your own tile of the background picture.
 * 
 */

/*======================= MACROFIED FUNCTIONS ===========================*/
#undef this
#define this (*ptThis)

/*============================ TYPES =========================================*/
/*============================ GLOBAL VARIABLES ==============================*/

extern const arm_2d_tile_t c_tilecmsisLOGORGB565;


/*============================ PROTOTYPES ====================================*/
/*============================ LOCAL VARIABLES ===============================*/
/*============================ IMPLEMENTATION ================================*/

void wait_for_display()
{
    while (arm_fsm_rt_cpl != disp_adapter0_task()) ;
}


void scene_cmsis_stream_loader(user_scene_cmsis_stream_t *scene) 
{
    arm_2d_scene_cmsis_stream_init(&DISP0_ADAPTER,scene);
}

void arm2d_scene_cmsis_stream_new_layers(user_scene_cmsis_stream_t *ptScene,
   stream_2d_layer_t **layers,
   const int nb_layers)
{
    user_scene_cmsis_stream_t *ptThis = (user_scene_cmsis_stream_t *)ptScene;
    ptThis->nb_layers = nb_layers;
    ptThis->list_of_layers = layers;
}

static void __on_scene_cmsis_stream_depose(arm_2d_scene_t *ptScene)
{
    user_scene_cmsis_stream_t *ptThis = (user_scene_cmsis_stream_t *)ptScene;
    ARM_2D_UNUSED(ptThis);
    
    ptScene->ptPlayer = NULL;
    
    /* reset timestamp */
    arm_foreach(int64_t,this.lTimestamp, ptItem) {
        *ptItem = 0;
    }

    if (!this.bUserAllocated) {
        free(ptScene);
    }
}

/*----------------------------------------------------------------------------*
 * Scene cmsis stream                                                                    *
 *----------------------------------------------------------------------------*/

static void __on_scene_cmsis_stream_background_start(arm_2d_scene_t *ptScene)
{
    user_scene_cmsis_stream_t *ptThis = (user_scene_cmsis_stream_t *)ptScene;
    ARM_2D_UNUSED(ptThis);

}

static void __on_scene_cmsis_stream_background_complete(arm_2d_scene_t *ptScene)
{
    user_scene_cmsis_stream_t *ptThis = (user_scene_cmsis_stream_t *)ptScene;
    ARM_2D_UNUSED(ptThis);

}


static void __on_scene_cmsis_stream_frame_start(arm_2d_scene_t *ptScene)
{
    user_scene_cmsis_stream_t *ptThis = (user_scene_cmsis_stream_t *)ptScene;
    ARM_2D_UNUSED(ptThis);

}

static void __on_scene_cmsis_stream_frame_complete(arm_2d_scene_t *ptScene)
{
    user_scene_cmsis_stream_t *ptThis = (user_scene_cmsis_stream_t *)ptScene;
    ARM_2D_UNUSED(ptThis);

}

static void __before_scene_cmsis_stream_switching_out(arm_2d_scene_t *ptScene)
{
    user_scene_cmsis_stream_t *ptThis = (user_scene_cmsis_stream_t *)ptScene;
    ARM_2D_UNUSED(ptThis);

}

static
IMPL_PFB_ON_DRAW(__pfb_draw_scene_cmsis_stream_background_handler)
{
    user_scene_cmsis_stream_t *ptThis = (user_scene_cmsis_stream_t *)pTarget;
    ARM_2D_UNUSED(ptTile);
    ARM_2D_UNUSED(bIsNewFrame);
    /*-----------------------draw back ground begin-----------------------*/


    /*-----------------------draw back ground end  -----------------------*/
    arm_2d_op_wait_async(NULL);

    return arm_fsm_rt_cpl;
}

#include <stdio.h>

static
IMPL_PFB_ON_DRAW(__pfb_draw_scene_cmsis_stream_handler)
{
    user_scene_cmsis_stream_t *ptThis = (user_scene_cmsis_stream_t *)pTarget;
    ARM_2D_UNUSED(ptTile);
    ARM_2D_UNUSED(bIsNewFrame);


    
    arm_2d_canvas(ptTile, __canvas) {

    /*-----------------------draw the foreground begin-----------------------*/

        /* following code is just a demo, you can remove them */

        arm_2d_fill_colour(ptTile, NULL, GLCD_COLOR_WHITE);

        
        if (ptThis->nb_layers>=1)
        {
            arm_2d_layout(__canvas) {

                for(int i=0;i<ptThis->nb_layers;i++) 
                {

                 arm_2d_region_t region = ptThis->list_of_layers[i]->tile.tRegion;
                 region.tLocation= ptThis->list_of_layers[i]->pos;

                 arm_2d_container(ptTile, __control, &region) {

                  
                     
                      if (ptThis->list_of_layers[i]->copy_only_mode)
                      {
                          arm_2d_tile_copy_only(&ptThis->list_of_layers[i]->tile,
                             ptTile,
                             &region);
                      }
                      else
                      {



                          arm_2d_tile_copy_with_colour_keying_and_opacity(
                            &ptThis->list_of_layers[i]->tile,
                            ptTile,
                            &region,
                            ptThis->list_of_layers[i]->alpha,
                            (__arm_2d_color_t){ptThis->list_of_layers[i]->color}
                            );

                      }

                  
                  
              }

          }
      }
  }

    /*-----------------------draw the foreground end  -----------------------*/
}

arm_2d_op_wait_async(NULL);

return arm_fsm_rt_cpl;
}

#include <stdio.h>
ARM_NONNULL(1)
user_scene_cmsis_stream_t *__arm_2d_scene_cmsis_stream_init(arm_2d_scene_player_t *ptDispAdapter, 
    user_scene_cmsis_stream_t *ptThis)
{
    bool bUserAllocated = false;
    assert(NULL != ptDispAdapter);

    /*! define dirty regions */
    IMPL_ARM_2D_REGION_LIST(s_tDirtyRegions, static)


    ADD_LAST_REGION_TO_LIST(s_tDirtyRegions,
        .tLocation = {
            .iX = 0,
            .iY = 0,
        },
        .tSize = {
            .iWidth = 240,
            .iHeight = 240,
        },
        ),


    END_IMPL_ARM_2D_REGION_LIST(s_tDirtyRegions)
    
    s_tDirtyRegions[dimof(s_tDirtyRegions)-1].ptNext = NULL;

    /* get the screen region */
    arm_2d_region_t tScreen
    = arm_2d_helper_pfb_get_display_area(
        &ptDispAdapter->use_as__arm_2d_helper_pfb_t);
    
    
    if (NULL == ptThis) {
        ptThis = (user_scene_cmsis_stream_t *)malloc(sizeof(user_scene_cmsis_stream_t));
        assert(NULL != ptThis);
        if (NULL == ptThis) {
            return NULL;
        }
        
    } else {
        bUserAllocated = true;
        
    }

    memset(ptThis, 0, sizeof(user_scene_cmsis_stream_t));

    
    *ptThis = (user_scene_cmsis_stream_t){
        .use_as__arm_2d_scene_t = {
            /* Please uncommon the callbacks if you need them
             */
            //.fnBackground   = &__pfb_draw_scene_cmsis_stream_background_handler,
            .fnScene        = &__pfb_draw_scene_cmsis_stream_handler,
            //.ptDirtyRegion  = (arm_2d_region_list_item_t *)s_tDirtyRegions,
            

            //.fnOnBGStart    = &__on_scene_cmsis_stream_background_start,
            //.fnOnBGComplete = &__on_scene_cmsis_stream_background_complete,
            .fnOnFrameStart = &__on_scene_cmsis_stream_frame_start,
            //.fnBeforeSwitchOut = &__before_scene_cmsis_stream_switching_out,
            .fnOnFrameCPL   = &__on_scene_cmsis_stream_frame_complete,
            .fnDepose       = &__on_scene_cmsis_stream_depose,
        },
        .bUserAllocated = bUserAllocated,
    };

    ptThis->nb_layers=0;
    ptThis->list_of_layers=NULL;

    arm_2d_scene_player_append_scenes(  ptDispAdapter, 
        &this.use_as__arm_2d_scene_t, 
        1);

    return ptThis;
}

#if defined(__clang__)
#   pragma clang diagnostic pop
#endif

