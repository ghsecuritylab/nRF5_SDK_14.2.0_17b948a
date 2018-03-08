/**
 * Copyright (c) 2016 - 2017 Nordic Semiconductor ASA and Luxoft Global Operations Gmbh.
 * 
 * All Rights Reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 
 * 
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 
 * 2. Redistributions in binary form, except as embedded into a Nordic
 *    Semiconductor ASA integrated circuit in a product or a software update for
 *    such product, must reproduce the above copyright notice, this list of
 *    conditions and the following disclaimer in the documentation and/or other
 *    materials provided with the distribution.
 * 
 * 3. Neither the name of Nordic Semiconductor ASA nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 * 
 * 4. This software, with or without modification, must only be used with a
 *    Nordic Semiconductor ASA integrated circuit.
 * 
 * 5. Any software provided in binary form under this license must not be reverse
 *    engineered, decompiled, modified and/or disassembled.
 * 
 * 
 * THIS SOFTWARE IS PROVIDED BY NORDIC SEMICONDUCTOR ASA "AS IS" AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL NORDIC SEMICONDUCTOR ASA OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 */
#ifndef MAC_MCPS_PURGE_H_INCLUDED
#define MAC_MCPS_PURGE_H_INCLUDED

#if (CONFIG_PURGE_ENABLED == 1)

#include <stdint.h>
#include "mac_common.h"
#include "mac_task_scheduler.h"

/** @file
 * The MAC Purge module declares the MAC Purge routines and necessary types
 * according to the MAC specification.
 *
 * @defgroup mac_purge MAC MCPS Purge API
 * @ingroup mac_15_4
 * @{
 * @brief Module to declare MAC MCPS Purge API.
 * @details The MAC MCPS Purge module declares the MAC Purge routines and necessary types according to
 * the MAC specification. More specifically, MAC purge request mcps_purge_req(), and the
 * confirmation callback typedef is declared as mcps_purge_conf_cb_t. An additional primitive
 * not covered by the standard is declared. This is mpcs_purge() which is a synchronous version
 * of mcps_purge_req().
 */

/**
 * @brief   MCPS-PURGE.confirm.
 *
 * @details The MCPS-PURGE.confirm primitive allows the MAC sublayer to notify the next higher layer
 * of the success of its request to purge an MSDU from the transaction queue.
 *
 * In accordance with IEEE Std 802.15.4-2006, section 7.1.1.5.
 */
typedef struct
{
    /** The handle of the MSDU to be purged from the transaction queue. */
    uint8_t        msdu_handle;

    /** The status of the request to be purged an MSDU from the transaction queue. */
    mac_status_t   status;
} mcps_purge_conf_t;


/**
 * @brief   MCPS-PURGE.request.
 *
 * @details The MCPS-PURGE.request primitive allows the next higher layer
 * to purge an MSDU from the transaction queue.
 *
 * In accordance with IEEE Std 802.15.4-2006, section 7.1.1.4.
 */
typedef struct
{
    /** Do not edit this field. */
    mac_abstract_req_t  service;

    /** Confirmation to this request. */
    mcps_purge_conf_t   confirm;

    /** The handle of the MSDU to be purged from the transaction queue. */
    uint8_t       msdu_handle;
} mcps_purge_req_t;


/**
 * @brief   Confirmation function.
 *
 * @details The MCPS-PURGE.confirm primitive is generated by the MAC sublayer
 * entity in response to an MCPS-PURGE.request primitive. The MCPS-PURGE.confirm
 * primitive returns a status of either SUCCESS, indicating that the purge request
 * was successful, or INVALID_HANDLE, indicating an error.
 * The status values are fully described in 7.1.1.4.3.
 *
 * @param Pointer to confirmation primitive.
 */
typedef void (* mcps_purge_conf_cb_t)(mcps_purge_conf_t *);


/**
 * @brief   MCPS-PURGE.request service.
 *
 * @details The MCPS-PURGE.request primitive is generated by the next higher layer
 * whenever an MSDU is to be purged from the transaction queue.
 * After request completion, user callback will be issued with
 * valid data stored in structure mcps_purge_conf_t.
 *
 * @param req     Pointer to MCPS-PURGE request structure.
 * @param conf_cb Pointer to the confirmation function (user callback).
 *
 * In accordance with IEEE Std 802.15.4-2006, section 7.1.1.4.
 */
void mcps_purge_req(mcps_purge_req_t * req, mcps_purge_conf_cb_t conf_cb);

/**
 * @brief   Performs MCPS-PURGE.request directly (without request - confirm approach).
 *
 * @details Optional. Not covered by the standard.
 *
 * The MCPS-PURGE.request primitive is generated by the next higher layer
 * whenever an MSDU is to be purged from the transaction queue.
 *
 * @param req Pointer to MCPS-PURGE request structure.
 *
 * @return Result of the purge procedure.
 */
mac_status_t mcps_purge(mcps_purge_req_t * req);

/** @} */

#endif // (CONFIG_PURGE_ENABLED == 1)

#endif // MAC_MCPS_PURGE_H_INCLUDED
