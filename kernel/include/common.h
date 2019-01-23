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
#ifndef __COMMON_H__
#define __COMMON_H__
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
 * This file defines all kernel structures.
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */


#include "type.h"
#include "config.h"
#include "library.h"


/* * * * * * * * * * * * * * * * * * * * * * * *
 * struct declare
 * * * * * * * * * * * * * * * * * * * * * * * */
/*state machine*/
enum state {
        OFF = 0,     //off
        INIT,        //init
        RUN,         //run
        IDLE,        //idle
        SLEEP,       //sleep
        WAKEUP,      //wakeup
        PENDING,     //pending
        READ,        //read
        WRITE,       //write
        CAL,         //calculate
        INPUT,       //input
        OUTPUT,      //output
};

/*ip register*/
typedef struct registers {
        char name[64];           //register name
        address32_t address;     //register address
        reg32_t value;           //register value
}regs;

/*ip operation*/
typedef struct device_ops {
        int (*poweron)();       //poweron
        int (*poweroff)();      //poweroff
        int (*idle)();          //idle
        int (*sleep)();         //sleep
        int (*wakeup)();        //wakeup
        int (*init)();          //init
        int (*deinit)();        //deinit
        int (*read)();          //read mem
        int (*write)();         //write mem
        reg32_t (*readreg)();   //read register
        int (*writereg)();      //write register
        int (*clearreg)();      //clear register
        int (*tickarrive)();    //clock trigger
        int (*dump)();          //debug
}ip_operations;

/*ip*/
typedef struct device {
        char name[64];           //name
        int id;                  //id
        enum state status;       //state machine
        address32_t address;     //lower32 of reglist, used as hash string

        const ip_operations *ops;//operation

        address32_t **memory;    //memory space

        regs **reglist;          //register list
        hashtable *name2reg;     //register hashtable1: name->reg
        hashtable *addr2reg;     //register hashtable2: addr->reg

        struct device *parent;   //parent
        struct device *east;     //east connected ip
        struct device *west;     //west connected ip
        struct device *sourth;   //sourth connected ip
        struct device *north;    //north connected ip

        struct device **subips;  //submodule
        hashtable *name2subip;   //submodule hashtable1: name->subip
        hashtable *addr2subip;   //submodule hashtable2: addr->subip
}ip;

/*parameter*/
typedef struct parameter {
        /*product*/
        int product_reg_count;
        /*boardlink*/
        int boardlink_count;
        int boardlink_reg_count;
        /*board*/
        int board_count;
        int board_reg_count;
        /*chiplink*/
        int chiplink_count;
        int chiplink_reg_count;
        /*chip*/
        int chip_count;
        int chip_reg_count;
        /*ddr*/
        int ddr_count;
        int ddr_reg_count;
        int *ddr_size;
        /*fifo*/
        int fifo_count;
        int fifo_reg_count;
        int *fifo_size;
        /*fifo*/
        int pcie_count;
        int pcie_reg_count;
        /*main cpu*/
        int maincpu_count;
        int maincpu_reg_count;
        /*noc*/
        int noc_count;
        int noc_reg_count;
        /*core*/
        int core_count;
        int core_reg_count;
        /*mcu*/
        int mcu_count;
        int mcu_reg_count;
        /*ncp*/
        int ncp_count;
        int ncp_reg_count;
        /*tcp*/
        int tcp_count;
        int tcp_reg_count;
        /*ram*/
        int ram_count;
        int ram_reg_count;
        int *ram_size;
}param;

/*simulator*/
typedef struct simulator {
        param *params;
        ip *product;
}simu;



/* * * * * * * * * * * * * * * * * * * * * * * *
 * function declare
 * * * * * * * * * * * * * * * * * * * * * * * */
/*power*/
int power_on(ip *product);
int power_off(ip *product);
int power_idle(ip *product);
int power_sleep(ip *product);
/*clock*/
int clock_run(ip *product);
/*product*/
int product_init(ip *father, ip *product, int id, param *params);
int product_run(ip *product);
/*board*/
int board_init(ip *father, ip *board, int id, param *params);
int boardlink_init(ip *father, ip *boardlink, int id, param *params);
int ddr_init(ip *father, ip *ddr, int id, param *params);
int fifo_init(ip *father, ip *fifo, int id, param *params);
int pcie_init(ip *father, ip *pcie, int id, param *params);
int maincpu_init(ip *father, ip *maincpu, int id, param *params);
/*chip*/
int chip_init(ip *father, ip *chip, int id, param *params);
int chiplink_init(ip *father, ip *chiplink, int id, param *params);
/*core*/
int core_init(ip *father, ip *core, int id, param *params);
int noc_init(ip *father, ip *noc, int id, param *params);
int mcu_init(ip *father, ip *mcu, int id, param *params);
int ncp_init(ip *father, ip *ncp, int id, param *params);
int tcp_init(ip *father, ip *tcp, int id, param *params);
int ram_init(ip *father, ip *ram, int id, param *params);



/* * * * * * * * * * * * * * * * * * * * * * * *
 * global variants declare
 * * * * * * * * * * * * * * * * * * * * * * * */
extern enum state global_state;  //the whole product run state-machine
extern u64 tick_counter;         //the tick counts from the beginning
extern u64 step_counter;         //the step counts from the beginning
extern int all_step_done;        //all step process ok
extern int step_enable;          //one step done, process another step


#endif
