#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

// 定義狀態變數
bool st_430 = true;     // 初始狀態（430）
bool st_431 = false;    // 狀態431
bool st_432 = false;    // 狀態432
bool st_433 = false;    // 狀態433
bool st_434 = false;    // 狀態434
bool st_435 = false;    // 狀態435
bool st_436 = false;    // 狀態436
bool st_437 = false;    // 狀態437
bool st_438 = false;    // 狀態438

// 定義條件變數
bool 系統啟動 = false;
bool 檢測到緊急情況 = false;
bool 通訊請求 = false;
bool 人員到場 = false;
bool 通訊驗證成功 = false;
bool 通訊驗證失敗 = false;
bool 結束_通訊或緊急處理 = false;

// 函式原型宣告
void grafcet0();
void action0();
void s430();
void s431();
void s432();
void s433();
void s434();
void s435();
void s436();
void s437();
void s438();
// 初始化影音/網路
void grafcet1();
void action1();
// 分析檢測緊急情況
void grafcet2();
void action2();
// 緊急處置系統
void grafcet3();
void action3();
// 網路通訊系統
void grafcet4();
void action4();

void main(){
    while(1){
        grafcet0();
    }
}

// 依據各狀態變數的值，改變狀態變數(前一狀態變false, 下一狀態變true)
void grafcet0(){
    // 從系統啟動到初始化完成
    if(st_430 && 系統啟動){
        系統啟動 = false;
        st_430 = false;
        st_431 = true;
    }
    // 從初始化完成到分析緊急情況
    else if(st_431){
        st_431 = false;
        st_432 = true;
    }
    // 從分析緊急情況到處理驗證請求
    else if(st_432){
        if(通訊請求){
            通訊請求 = false;
            st_432 = false;
            st_433 = true;
        }
        else if(檢測到緊急情況){
            檢測到緊急情況 = false;
            st_432 = false;
            st_434 = true;
            st_435 = true;
        }
    }
    // 從處理驗證請求到顯示網路信息
    else if(st_433){
        if(通訊驗證失敗){
            通訊驗證失敗 = false;
            st_433 = false;
            st_436 = true;    
        }
        else if(通訊驗證成功){
            通訊驗證成功 = false;
            st_433 = false;
            st_437 = true;    
        }
    }
    // 從緊急系統到處理人員到場
    else if(st_434 && st_435 && 人員到場){
        人員到場 = false;
        st_434 = false;
        st_435 = false;
        st_438 = true;
    }
    // 從顯示網路信息返回到分析緊急情況
    else if(st_436 && 結束_通訊或緊急處理){
        結束_通訊或緊急處理 = false;
        st_436 = false;
        st_432 = true;
    }
    // 從處理成功通訊返回到分析緊急情況
    else if(st_437 && 結束_通訊或緊急處理){
        結束_通訊或緊急處理 = false;
        st_437 = false;
        st_432 = true;
    }
    // 從處理人員位置返回到分析緊急情況
    else if(st_438 && 結束_通訊或緊急處理){
        結束_通訊或緊急處理 = false;
        st_438 = false;
        st_432 = true;
    }
    
    // 執行動作
    action0();
}

// 依據各狀態變數，執行相應動作
void action0(){
    if(st_430){s430();}
    if(st_431){s431();}
    if(st_432){s432();}
    if(st_433){s433();}
    if(st_434){s434();}
    if(st_435){s435();}
    if(st_436){s436();}
    if(st_437){s437();}
    if(st_438){s438();}
}

// 狀態動作函式
static inline void s430(){
    printf("state 430: System Startup\n");
    sleep(1);   // 模擬 系統啟動
    系統啟動 = true;
}

static inline void s431(){
    printf("state 431: Initialize monitoring and networking\n");
    grafcet1(); // 初始化影音/網路 sub-grafcet
    sleep(1);   // 模擬 初始化
}

static inline void s432(){
    printf("state 432: Analyze and detect emergency situations\n");
    grafcet2(); // 分析檢測緊急情況 sub-grafcet
    sleep(1);   // 模擬 通訊請求 或 檢測到緊急情況
    檢測到緊急情況 = (rand() % 2) == 1;
    通訊請求 = 檢測到緊急情況 ? false : true;
}

static inline void s433(){
    printf("state 433: Processing Validation Requests\n");
    sleep(1); // 模擬 處理驗證請求
    通訊驗證成功 = (rand() % 2) == 1;
    通訊驗證失敗 = 通訊驗證成功 ? false : true;
}

static inline void s434(){
    printf("state 434: Activation of the Emergency Response System\n");
    grafcet3(); // 緊急處置系統 sub-grafcet
    sleep(1);   // 模擬 開啟緊急處置
    人員到場 = true;
}

static inline void s435(){
    printf("state 435: Sending Emergency Notices\n");
    sleep(1); // 模擬 發送通知
    人員到場 = true;
}

static inline void s436(){
    printf("state 436: Displaying Network Error Messages\n");
    sleep(1); // 模擬 顯示網路錯誤信息
    結束_通訊或緊急處理 = true;
}

static inline void s437(){
    printf("state 437: Network communication is in progress\n");
    grafcet4(); // 網路通訊系統 sub-grafcet
    sleep(1); // 模擬 通訊中
    結束_通訊或緊急處理 = true;
}

static inline void s438(){
    printf("state 438: Waiting for the relevant personnel to finish the process\n");
    sleep(1); // 模擬 等待人員回應
    結束_通訊或緊急處理 = true;
}

// 初始化影音/網路
void grafcet1(){action1();};
void action1(){};
// 分析檢測緊急情況
void grafcet2(){action2();};
void action2(){};
// 緊急處置系統
void grafcet3(){action3();};
void action3(){};
// 網路通訊系統
void grafcet4(){action4();};
void action4(){};