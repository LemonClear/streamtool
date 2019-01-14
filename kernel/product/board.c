/*
#
# Copyright LemonClear
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include "common.h"
#include "of.h"


/**
 * global variants
 * @global_state:    the whole product run state-machine
 * @tick_counter:    the tick counts from the beginning
 * @all_phase_done:  all phase process ok
 *
 */
extern enum state global_state;
extern u64 tick_counter;
extern int all_phase_done;


/**
 * on - board power on
 * @board:   board pointer
 *
 */
static void on(ip *board)
{
        int id = 0;

        if (unlikely(!board)) {
                printf("ERR: board absent, please check! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_on;
        }

        /*board level do first*/
        //FIXME: todo...

        /*power on subips second*/
        while (board->subips[id]) {
                /*each subip*/
                board->subips[id]->ops->poweron(board->subips[id]);

                id++;
        }

        /*change state machine third*/
        board->status = RUN;

        printf("INFO: board:%s power on!!!!! %s, %s, %d\n",
                        board->name, __FILE__, __func__, __LINE__);

ret_on:
        return;
}


/**
 * off - board power off
 * @board:   board pointer
 *
 */
static void off(ip *board)
{
        int id = 0;

        if (unlikely(!board)) {
                printf("ERR: board absent, please check! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_off;
        }

        /*power off subips first*/
        while (board->subips[id]) {
                /*each subip*/
                board->subips[id]->ops->poweroff(board->subips[id]);

                id++;
        }

        /*board level do second*/
        //FIXME: todo...

        /*change state machine third*/
        board->status = OFF;

        printf("INFO: board:%s power off!!!!! %s, %s, %d\n",
                        board->name, __FILE__, __func__, __LINE__);

ret_off:
        return;
}


/**
 * idle - board idle
 * @board:   board pointer
 *
 */
static void idle(ip *board)
{
        int id = 0;

        if (unlikely(!board)) {
                printf("ERR: board absent, please check! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_idle;
        }

        /*idle subips first*/
        while (board->subips[id]) {
                /*each subip*/
                board->subips[id]->ops->idle(board->subips[id]);

                id++;
        }

        /*board level do second*/
        //FIXME: todo...

        /*change state machine third*/
        board->status = IDLE;

        printf("INFO: board:%s idle!!!!! %s, %s, %d\n",
                        board->name, __FILE__, __func__, __LINE__);

ret_idle:
        return;
}


/**
 * sleep - board sleep
 * @board:   board pointer
 *
 */
static void sleep(ip *board)
{
        int id = 0;

        if (unlikely(!board)) {
                printf("ERR: board absent, please check! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_sleep;
        }

        /*sleep subips first*/
        while (board->subips[id]) {
                /*each subip*/
                board->subips[id]->ops->sleep(board->subips[id]);

                id++;
        }

        /*board level do second*/
        //FIXME: todo...

        /*change state machine third*/
        board->status = SLEEP;

        printf("INFO: board:%s sleep!!!!! %s, %s, %d\n",
                        board->name, __FILE__, __func__, __LINE__);

ret_sleep:
        return;
}


/**
 * wakeup - board wakeup
 * @board:  board pointer
 *
 */
static void wakeup(ip *board)
{
        int id = 0;

        if (unlikely(!board)) {
                printf("ERR: board absent, please check! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_wakeup;
        }

        /*board level do first*/
        //FIXME: todo...

        /*wakeup subips second*/
        while (board->subips[id]) {
                /*each subip*/
                board->subips[id]->ops->wakeup(board->subips[id]);

                id++;
        }

        /*change state machine third*/
        board->status = RUN;

        printf("INFO: board:%s wakeup!!!!! %s, %s, %d\n",
                        board->name, __FILE__, __func__, __LINE__);

ret_wakeup:
        return;
}


/**
 * tick - one tick trigger
 * @board:   self pointer
 *
 */
static void tick(ip *board)
{
        int id = 0;

        if (unlikely(!board)) {
                printf("ERR: board absent, please check! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_tick;
        }

        /*begin*/
        printf("INFO: board:%s tick:%llu come!!!!! %s, %s, %d\n",
                        board->name, tick_counter, __FILE__, __func__, __LINE__);

        /*board level do first*/
        //FIXME: todo...


        /*tick trigger subips second*/
        while (board->subips[id]) {
                /*each subip*/
                board->subips[id]->ops->tickarrive(board->subips[id]);

                id++;
        }

        /*done*/
        printf("INFO: board:%s tick:%llu done!!!!! %s, %s, %d\n",
                        board->name, tick_counter, __FILE__, __func__, __LINE__);

ret_tick:
        return;
}


/**
 * dump - board dump informations
 * @board:   board pointer
 *
 */
static void dump(ip *board)
{
        int id = 0;

        printf("DEBUG: ========== board:%s dump start !!!!! ==========\n",
                        board->name);

        if (unlikely(!board)) {
                printf("ERR: board absent, dump failed! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_dump;
        }

        /*dump board elements first*/
        //FIXME: todo...

        /*dump subips second*/
        while (board->subips[id]) {
                /*each subip*/
                board->subips[id]->ops->dump(board->subips[id]);

                id++;
        }

        printf("DEBUG: ========== board:%s dump end !!!!! ==========\n",
                        board->name);

ret_dump:
        return;
}
/**
 * ops structure
 *
 */
static const ip_operations board_ops = {
        .poweron = on,
        .poweroff = off,
        .idle = idle,
        .sleep = sleep,
        .wakeup = wakeup,
        .tickarrive = tick,
        .dump = dump,
};


/**
 * parse_regconfig - parse reg config file xxx.reg
 * @reglist:   pointer to reglist
 *
 * FIXME: to be replace by dt
 */
static int parse_regconfig(regs **reglist)
{
        int ret = -1;
        char *config = "./board.reg";

        if (unlikely(!reglist)) {
                printf("ERR: board reglist absent! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_config;
        }

        //FIXME: todo...

ret_config:
        return ret;
}


/**
 * board_alloc - alloc board elements
 * @board:   pointer to board
 * @params:    init parameters
 *
 */
static int board_alloc(ip *board, param *params)
{
        int ret = -1;
        int id = -1;

        /*memory*/
        //FIXME: DO NOTHING!!!
        //NO NEED on board level!!!

        /*reg list*/
        if (!params->reg_count) { //FIXME: should separate ips reg count
                printf("INFO: board have no reg!!! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
        }

        board->reglist = malloc(params->reg_count * sizeof(regs *));
        if (unlikely(!board->reglist)) {
                printf("ERR: alloc board reglist failed! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_alloc;
        }
        memset((void *)board->reglist, 0, params->reg_count * sizeof(regs *));

        for (id = 0; id < params->reg_count; id++) {
                board->reglist[id] = malloc(sizeof(regs));
                if (unlikely(!board->reglist[id])) {
                        printf("ERR: alloc board reg%d failed! %s, %s, %d\n",
                                        id, __FILE__, __func__, __LINE__);
                        goto ret_alloc;
                }
                memset((void *)board->reglist[id], 0, sizeof(regs));
        }

        /*reg hastable*/
        board->name2reg = init_hashtable();
        if (unlikely(!board->name2reg)) {
                printf("ERR: alloc board reg hashtable failed! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_alloc;
        }

        board->addr2reg = init_hashtable();
        if (unlikely(!board->addr2reg)) {
                printf("ERR: alloc board reg hashtable failed! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_alloc;
        }

        /*subips list*/
        board->subips = malloc((params->chiplink_count +
                                params->chip_count + params->ddr_count +
                                params->fifobuf_count + params->pcie_count +
                                params->maincpu_count) * sizeof(ip *));
        if (unlikely(!board->subips)) {
                printf("ERR: board alloc subip array failed! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_alloc;
        }
        memset((void *)board->subips, 0, (params->chiplink_count +
                                params->chip_count + params->ddr_count +
                                params->fifobuf_count + params->pcie_count +
                                params->maincpu_count) * sizeof(ip *));

        for (id = 0; id < (params->chiplink_count +
                                params->chip_count + params->ddr_count +
                                params->fifobuf_count + params->pcie_count +
                                params->maincpu_count); id++) {
                board->subips[id] = malloc(sizeof(ip));
                if (unlikely(!board->subips[id])) {
                        printf("ERR: alloc board subip%d failed! %s, %s, %d\n",
                                        id, __FILE__, __func__, __LINE__);
                        goto ret_alloc;
                }
                memset((void *)board->subips[id], 0, sizeof(ip));
        }

        /*subips hastable*/
        board->name2subip = init_hashtable();
        if (unlikely(!board->name2subip)) {
                printf("ERR: alloc board subip hashtable failed! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_alloc;
        }

        board->addr2subip = init_hashtable();
        if (unlikely(!board->addr2subip)) {
                printf("ERR: alloc board subip hashtable failed! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_alloc;
        }

        ret = 0;

ret_alloc:
        return ret;
}


/**
 * board_init - init board with params
 * @father:    pointer to the board belongs to
 * @board:   pointer to board
 * @id:        board id
 * @params:    init parameters
 *
 */
int board_init(ip *father, ip *board, int id, param *params)
{
        int ret = -1;
        int sub = -1;
        char addr2str[32] = {0};

        /*begin*/
        printf("INFO: board init start!!!!! %s, %s, %d\n",
                        __FILE__, __func__, __LINE__);

        if (unlikely(!board) || unlikely(!params)) {
                printf("ERR: board or params is absent! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_init;
        }

        /*alloc*/
        ret = board_alloc(board, params);
        if (unlikely(ret)) {
                printf("ERR: board alloc elements failed! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_init;
        }

        /*name*/
        sprintf(board->name, "board%d", id);

        /*id*/
        board->id = id;

        /*state machine*/
        board->status = OFF;

        /*ops*/
        board->ops = &board_ops;

        /*memory*/
        //FIXME: DO NOTHING!!!
        //NO NEED on board level!!!

        /*reg list*/
        ret = parse_regconfig(board->reglist);
        if (unlikely(ret)) {
                printf("ERR: board reglist init failed! %s, %s, %d\n",
                                __FILE__, __func__, __LINE__);
                goto ret_init;
        }

        /*reg hashtable*/
        for (sub = 0; sub < params->reg_count; sub++) {
                /*bypass empty reglist elements*/
                if (unlikely(!strcmp(board->reglist[sub]->name, "")))
                        continue;

                /*table name2reg*/
                ret = insert_hashtable(board->reglist[sub]->name,
                                (void *)board->reglist[sub],
                                board->name2reg);
                if (unlikely(ret)) {
                        printf("ERR: hash reg%d:%s to name2reg table failed! %s, %s, %d\n",
                                        sub, board->reglist[sub]->name,
                                        __FILE__, __func__, __LINE__);
                        goto ret_init;
                }

                /*table addr2reg*/
                sprintf(addr2str, "0x%x", board->reglist[sub]->address);
                ret = insert_hashtable(addr2str, (void *)board->reglist[sub], board->addr2reg);
                if (unlikely(ret)) {
                        printf("ERR: hash reg%d:0x%x to addr2reg table failed! %s, %s, %d\n",
                                        sub, board->reglist[sub]->address,
                                        __FILE__, __func__, __LINE__);
                        goto ret_init;
                }
        }

        /*address*/
        board->address = board->reglist;

        /*parent*/
        board->parent = father;

        /*connected*/
        board->east = NULL;
        board->west = NULL;
        board->sourth = NULL;
        board->north = NULL;

        /*subips: chiplink 1st*/
        for (sub = 0; sub < params->chiplink_count; sub++) {
                /*call subip:chiplink init function*/
                ret = chiplink_init(board, board->subips[sub], sub, params);
                if (unlikely(ret)) {
                        printf("ERR: subip%d-chiplink init failed! %s, %s, %d\n",
                                        sub, __FILE__, __func__, __LINE__);
                        goto ret_init;
                }
        }
        /*subips: chip 2nd*/
        for (; sub < (params->chiplink_count + params->chip_count); sub++) {
                /*call subip:chip init function*/
                ret = chip_init(board, board->subips[sub], sub, params);
                if (unlikely(ret)) {
                        printf("ERR: subip%d-chip init failed! %s, %s, %d\n",
                                        sub, __FILE__, __func__, __LINE__);
                        goto ret_init;
                }
        }
        /*subips: ddr 3rd*/
        for (; sub < (params->chiplink_count + params->chip_count +
                                params->ddr_count); sub++) {
                /*call subip:ddr init function*/
                ret = ddr_init(board, board->subips[sub], sub, params);
                if (unlikely(ret)) {
                        printf("ERR: subip%d-ddr init failed! %s, %s, %d\n",
                                        sub, __FILE__, __func__, __LINE__);
                        goto ret_init;
                }
        }
        /*subips: fifobuf 4th*/
        for (; sub < (params->chiplink_count + params->chip_count +
                                params->ddr_count + params->fifobuf_count); sub++) {
                /*call subip:fifobuf init function*/
                ret = fifobuf_init(board, board->subips[sub], sub, params);
                if (unlikely(ret)) {
                        printf("ERR: subip%d-fifobuf init failed! %s, %s, %d\n",
                                        sub, __FILE__, __func__, __LINE__);
                        goto ret_init;
                }
        }
        /*subips: pcie 5th*/
        for (; sub < (params->chiplink_count + params->chip_count +
                                params->ddr_count + params->fifobuf_count +
                                params->pcie_count); sub++) {
                /*call subip:pcie init function*/
                ret = pcie_init(board, board->subips[sub], sub, params);
                if (unlikely(ret)) {
                        printf("ERR: subip%d-pcie init failed! %s, %s, %d\n",
                                        sub, __FILE__, __func__, __LINE__);
                        goto ret_init;
                }
        }
        /*subips: maincpu 6th*/
        for (; sub < (params->chiplink_count + params->chip_count +
                                params->ddr_count + params->fifobuf_count +
                                params->pcie_count + params->maincpu_count); sub++) {
                /*call subip:maincpu init function*/
                ret = maincpu_init(board, board->subips[sub], sub, params);
                if (unlikely(ret)) {
                        printf("ERR: subip%d-maincpu init failed! %s, %s, %d\n",
                                        sub, __FILE__, __func__, __LINE__);
                        goto ret_init;
                }
        }

        /*subips: hashtable*/
        for (sub = 0; sub < (params->chiplink_count +
                                params->chip_count + params->ddr_count +
                                params->fifobuf_count + params->pcie_count +
                                params->maincpu_count); sub++) {
                /*bypass empty subip elements*/
                if (unlikely(!strcmp(board->subips[sub]->name, "")))
                        continue;

                /*table name2subip*/
                ret = insert_hashtable(board->subips[sub]->name,
                                (void *)board->subips[sub],
                                board->name2subip);
                if (unlikely(ret)) {
                        printf("ERR: hash %s to name2subip table failed! %s, %s, %d\n",
                                        board->subips[sub]->name,
                                        __FILE__, __func__, __LINE__);
                        goto ret_init;
                }

                /*table addr2subip*/
                sprintf(addr2str, "0x%x", board->subips[sub]->address);
                ret = insert_hashtable(addr2str, (void *)board->subips[sub],
                                board->addr2subip);
                if (unlikely(ret)) {
                        printf("ERR: hash boardsubip%d:0x%x to addr2subip table failed! %s, %s, %d\n",
                                        sub, board->subips[sub]->address,
                                        __FILE__, __func__, __LINE__);
                        goto ret_init;
                }
        }

        printf("INFO: board init end!!!!! %s, %s, %d\n",
                        __FILE__, __func__, __LINE__);

ret_init:
        return ret;
}
