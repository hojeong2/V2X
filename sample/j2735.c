/*
 * UPER Based client application sample code
 *
 * Copyright (c) 2022, CEST
 *
 */

#include "j2735.h"

void print_hex(char *data, int len){
    printf("HEX[%d] : ",len);
    for(int i = 0 ; i < len ; i++){
        printf("%02X",(data[i] & 0xFF));
    }
    printf("\n");
}


int encode_j2735_uper(char *dst, unsigned short dstLen, MessageFrame_t *src)
{
    int res = -1;

    asn_enc_rval_t ret = uper_encode_to_buffer(&asn_DEF_MessageFrame,
                                               NULL,
                                               src,
                                               dst, dstLen);
      
    if (ret.encoded > 0)
        return ret.encoded; //  UPER Encoding Success
    else
    { 
        if (ret.failed_type != NULL)
            printf("encoded error value name = %s\n", ret.failed_type->name);

        return -1; // UPER Encoding failed
    }
}

int decode_j2735_uper(MessageFrame_t *dst, char *src, int size){ 
  
    int res = -1;

    MessageFrame_t *ptrMsg = NULL; 

    asn_dec_rval_t ret = uper_decode(NULL,
                                     &asn_DEF_MessageFrame,
                                     (void **)&dst,
                                     src, size, 0, 0);

    if (ret.code != RC_OK)
        return res;
    
    res = ret.consumed;
 
    //asn_fprint(stdout,&asn_DEF_MessageFrame,dst);

    parse_decoded_j2735(dst);

    return res;
}
 
 // [HCML] Message decoding part 
int parse_decoded_j2735(MessageFrame_t *msg)
{   printf("[HMCL] Parsing \n");
    switch(msg->messageId){
        case DSRC_ID_BSM:
            printf(">> Parse J2735 : BSM\n");
            break;
        case DSRC_ID_SPAT:
            printf(">> Parse J2735 : SPAT\n");
            parse_spat(&msg->value.choice.SPAT);
            break;  
        case DSRC_ID_MAP:
            printf(">> Parse J2735 : MAP\n");
            parse_map(&msg->value.choice.MapData);
            break;
    }
    return 0;
}
 
int parse_map(MapData_t *map){
    // printf("\033[0;31m [Success]Receiving MAP data\033[0m \n");
    for (int i = 0; i < map->intersections->list.count; i++)
    {   
        printf("\n\033[0;34m[Success]Receiving MAP data\033[0m \n");
         struct IntersectionGeometry *ptr= map->intersections->list.array[i]; 
        // MISSION : MAP 메시지에 포함된 IntersectionGeometry별 Intersection ID 추출
        //           Intersection 내 Ref Position을 기준으로 LaneSet의 Node 좌표 계산 및 출력
        //           Node로 연결된 차선의 Line 별 ID와 SignalGroupID를 출력 
        // #1 ptr: ID  
            // printf("\033[0;31m ID: %d \033[0m \n", ptr->id.id);
            if (ptr->id.id == 1)
            {   
                // IntersectionGeometry

                // Section #1
                // Intersection name:  KIAPI -1 / 

                printf("\n\033[0;31m[KIAPI-1]   \033[0m \n \n");
                printf("Intersection Name: %ld \n", ptr->name);  // need to find out data type..... %d %c %s
                // IntersectionReferenceID
                printf("IntersectionReferenceID: # %d \n", ptr->id.id);
                // Ref point & laneWidth
                printf("[Ref point] \n lat: %d \n lon: %d \n ele: %d \n ", ptr->refPoint.lat ,ptr->refPoint.Long , ptr->refPoint.elevation);
                printf("laneWidth: %d \n",ptr->laneWidth);  

                // Section #2
                // GenericLane
                
                // nunmer of laneSet 

                int i;
                int len_1 = ptr->laneSet.list.count;
                
                for (int i= 0 ; i < len_1; i++)
                    {
                    printf("\n \033[0;33m  [GenericLane] \033[0m \n");    
                    printf("lane ID: %d \n" , ptr->laneSet.list.array[i]->laneID); 
                    printf("directionalUse: %d \n" , ptr->laneSet.list.array[i]->laneAttributes.directionalUse.bits_unused);
                    printf("sharedWith: %d \n" , ptr->laneSet.list.array[i]->laneAttributes.sharedWith.bits_unused);
                    printf("laneType: %d \n" , ptr->laneSet.list.array[i]->laneAttributes.laneType.present);
                    printf("Maeuvers: %d \n ",ptr->laneSet.list.array[i]->maneuvers);
                    printf("Direction %d \n", ptr->laneSet.list.array[i]->laneAttributes.directionalUse.buf[0]); // 128: out  64: in
                    // printf( "check_2 %d \n", ptr->laneSet.list.array[2]->laneAttributes.directionalUse.buf[0]); // 128: out  64: in
                    // printf( "%d \n", ptr->laneSet.list.array[2]->connectsTo->list.array[0]->connectingLane.lane);
                    // printf("chceck_1 %d \n" , ptr->laneSet.list.array[0]->connectsTo->list.array[0]->connectingLane.lane);
                    // printf("chceck_2 %d \n" , ptr->laneSet.list.array[0]->connectsTo->list.array[1]->connectingLane.lane);
                    int len_2 =ptr->laneSet.list.array[1]->nodeList.choice.nodes.list.count;
          
                        for(int j=0;j<len_2 ;j++){
                            printf("[Node XY #%d] \n #%d-%d \n x:%d \n y:%d \n",j,ptr->laneSet.list.array[i]->nodeList.choice.nodes.list.array[j]->delta.choice.node_XY6.x,ptr->laneSet.list.array[i]->nodeList.choice.nodes.list.array[j]->delta.choice.node_XY6.y);
                      
                    }

                    int len_3 = ptr->laneSet.list.array[1]->connectsTo->list.count;
                       for(int k=0; k<len_3 ;k++){
                            // printf("i: %d \n k: %d \n", i,k);
                            if (ptr->laneSet.list.array[i]->laneAttributes.directionalUse.buf[0] == 64){
                            

                            }else{
                                printf("[ConnectingLane #%d] \n lane: %d\n maneuver: %d \n signalGroup: %d \n" ,k, ptr->laneSet.list.array[i]->connectsTo->list.array[k]->connectingLane.lane,ptr->laneSet.list.array[i]->connectsTo->list.array[k]->connectingLane.maneuver,ptr->laneSet.list.array[i]->connectsTo->list.array[k]->signalGroup);
                            }
                                

                    }
                    
                    }
                  
                // printf("\n \033[0;31m  [End]Check here!!!!!!!!!!!!! \033[0m \n");

                return 0;
            }
            
            if (ptr->id.id == 2)
            {
                // IntersectionGeometry

                // Section #1
                // Intersection name:  KIAPI -1 / 

                printf("\033[0;31m  [KIAPI-2]   \033[0m \n \n");
                printf("Intersection Name: %ld \n", ptr->name);  // need to find out data type..... %d %c %s
                // IntersectionReferenceID
                printf("IntersectionReferenceID: # %d \n", ptr->id.id);
                // Ref point & laneWidth
                printf("[Ref point] \n lat: %d \n lon: %d \n ele: %d \n ", ptr->refPoint.lat ,ptr->refPoint.Long , ptr->refPoint.elevation);
                printf("laneWidth: %d \n",ptr->laneWidth);  

                // Section #2
                // GenericLane
                
                // nunmer of laneSet 

                int i;
                int len_1 = ptr->laneSet.list.count;
                
                for (int i= 0 ; i < len_1; i++)
                    {
                    printf("\n \033[0;33m  [GenericLane] \033[0m \n");    
                    printf("lane ID: %d \n" , ptr->laneSet.list.array[i]->laneID); 
                    printf("directionalUse: %d \n" , ptr->laneSet.list.array[i]->laneAttributes.directionalUse.bits_unused);
                    printf("sharedWith: %d \n" , ptr->laneSet.list.array[i]->laneAttributes.sharedWith.bits_unused);
                    printf("laneType: %d \n" , ptr->laneSet.list.array[i]->laneAttributes.laneType.present);
                    printf("Maeuvers: %d \n ",ptr->laneSet.list.array[i]->maneuvers);
                    printf("Direction %d \n", ptr->laneSet.list.array[i]->laneAttributes.directionalUse.buf[0]); // 128: out  64: in
                    // printf( "check_2 %d \n", ptr->laneSet.list.array[2]->laneAttributes.directionalUse.buf[0]); // 128: out  64: in
                    // printf( "%d \n", ptr->laneSet.list.array[2]->connectsTo->list.array[0]->connectingLane.lane);
                    // printf("chceck_1 %d \n" , ptr->laneSet.list.array[0]->connectsTo->list.array[0]->connectingLane.lane);
                    // printf("chceck_2 %d \n" , ptr->laneSet.list.array[0]->connectsTo->list.array[1]->connectingLane.lane);
                    int len_2 =ptr->laneSet.list.array[1]->nodeList.choice.nodes.list.count;
          
                        for(int j=0;j<len_2 ;j++){
                            printf("[Node XY #%d] \n #%d-%d \n x:%d \n y:%d \n",j,ptr->laneSet.list.array[i]->nodeList.choice.nodes.list.array[j]->delta.choice.node_XY6.x,ptr->laneSet.list.array[i]->nodeList.choice.nodes.list.array[j]->delta.choice.node_XY6.y);
                      
                    }

                    int len_3 = ptr->laneSet.list.array[1]->connectsTo->list.count;
                       for(int k=0; k<len_3 ;k++){
                            // printf("i: %d \n k: %d \n", i,k);
                            if (ptr->laneSet.list.array[i]->laneAttributes.directionalUse.buf[0] == 64){
                            

                            }else{
                                printf("[ConnectingLane #%d] \n lane: %d\n maneuver: %d \n signalGroup: %d \n" ,k, ptr->laneSet.list.array[i]->connectsTo->list.array[k]->connectingLane.lane,ptr->laneSet.list.array[i]->connectsTo->list.array[k]->connectingLane.maneuver,ptr->laneSet.list.array[i]->connectsTo->list.array[k]->signalGroup);
                            }
                                

                    }
                
                    }
                  
                // printf("\n \033[0;31m  [End]Check here!!!!!!!!!!!!! \033[0m \n");

                return 0;
            }
              if (ptr->id.id == 3)
            {
             
              
                printf("\033[0;33m  point # %d \033[0m \n", ptr->id.id);
                return 0;
            }
            
            

    }
       
    return 0;
}

int parse_spat(SPAT_t *spat){
    // printf("\033[0;31m [Success]Receiving SpaT data\033[0m \n");
    for (int i = 0; i < spat->intersections.list.count; i++)
    {   
        printf("\033[0;34m [Success]Receiving SpaT data\033[0m \n");
        struct IntersectionState *ptr = spat->intersections.list.array[i];

        // MISSION : MAP 메시지에 포함된 Intersection ID 추출
        //           Intersection 내 Ref Position을 기준으로 Offset Node 좌표 추출
        //           Node로 연결된 차선의 Line 별 ID와 SignalGroupID를 출력
        // printf("SPAT ID is %d \n", ptr->id.id);
        // printf("Signal Group is %ld \n", ptr->states.list.array[i]->signalGroup);
        // printf("state_time_speed is %d \n", ptr->states.list.array[i]->state_time_speed.list.array[0]->eventState);
        // printf("\n");
        
        // for (int num = 1; num < 4; num++)
        // // for (int num = 1; num < 2; num++)
        // {
        //     if (ptr->id.id == num)
        //     {
        //         int minute = ptr->moy[0];
        //         int sec = ptr->timeStamp[0];
        //         int remain = ptr->states.list.array[i]->state_time_speed.list.array[0]->timing->minEndTime;
        //         if (ptr->id.id == 1)
        //         {
        //             printf("\033[31mSPAT ID is %d \n \033[0m", ptr->id.id);
        //         }
        //         else if (ptr->id.id == 2)
        //         {
        //             printf("\033[32mSPAT ID is %d \n \033[0m", ptr->id.id);
        //         }
        //         else if (ptr->id.id == 3)
        //         {
        //             printf("\033[34mSPAT ID is %d \n \033[0m", ptr->id.id);
        //         }
        //         printf("\n");

        //         if (((minute/60)/24)<32)
        //         {
        //             printf("Jan %d, %d:%d:%d   \n", (minute/60)/24+1,  (minute/60)%24, minute%60, sec/1000);
        //         }
        //         else if ((31<(minute/60)/24) && ((minute/60)/24)<(31+28+1))
        //         {
        //             printf("Feb %d, %d:%d:%d   \n", (minute/60)/24-31+1,  (minute/60)%24, minute%60, sec/1000);
        //         }
        //         else if (((31+28)<(minute/60)/24) && ((minute/60)/24)<(31+28+31+1))
        //         {
        //             printf("Mar %d, %d:%d:%d   \n", (minute/60)/24-31-28+1,  (minute/60)%24, minute%60, sec/1000);
        //         }
        //         else if (((31+28+31)<(minute/60)/24) && ((minute/60)/24)<(31+28+31+30+1))
        //         {
        //             printf("Apr %d, %d:%d:%d   \n", (minute/60)/24-31-28-31+1,  (minute/(60*24)%24), minute%60, sec/1000);
        //         }

        //         int signal_number = ptr->states.list.count;
        //         for (int i = 0; i < signal_number; i++)
        //         {   
        //             if (ptr->states.list.array[i]->state_time_speed.list.array[0]->eventState!=3)
        //             // if (ptr->states.list.array[i]->state_time_speed.list.array[0]->eventState==7)
        //             {
        //                 printf("\033[36mTurn on %ld, state : %d, remaining time : %dm%ds \n\033[0m", ptr->states.list.array[i]->signalGroup, ptr->states.list.array[i]->state_time_speed.list.array[0]->eventState,(remain/10)/60, (remain/10)%60);
        //                 // STR, 3 or 5 or 7 (Red / Green / Yellow)
        //                 // LEF, 3 or 6 or 8 (Red / Green / Yellow)
        //                 // PED, 3 or 5      (Red / Green)
        //                 // Yellow : 남은 시간이 충분하더라도 현재 상태가 7이나 8이면 곧 신호가 바뀐다.
        //             }
        //         }
        //         printf("\n");
        //     }
        // }
        int a = 0;
        if (ptr->id.id == 1 && a < 12)
        {
            int Signum = ptr->states.list.count;
            for (int k = 0; k <Signum; k++)
            {
                printf("\033[31mSPAT ID is %d \n\033[0m", ptr->id.id);
                int minute = ptr->moy[0];
                int sec = ptr->timeStamp[0];
                printf("Apr %d, %d:%d:%d   \n", (minute/60)/24-31-28-31+1,  (minute/(60*24)%24), minute%60, sec/1000); // April
                printf("\n");
                printf("Direction : %c%c%c \n", ptr->states.list.array[k]->movementName->buf[0],ptr->states.list.array[k]->movementName->buf[1],ptr->states.list.array[k]->movementName->buf[2]);
                printf("Signal ID : %d \n", ptr->states.list.array[k]->signalGroup);
                printf("State : %d \n", ptr->states.list.array[k]->state_time_speed.list.array[0]->eventState);
                int remain = ptr->states.list.array[k]->state_time_speed.list.array[0]->timing->minEndTime;
                printf("Remain Time : %dm%ds \n", (remain/10)/60, (remain/10)%60);
                printf("\n");
                printf("ConnectionID : %d \n", ptr->states.list.array[k]->maneuverAssistList->list.array[0]->connectionID);
                printf("Ped or Bic : %d \n", ptr->states.list.array[k]->maneuverAssistList->list.array[0]->pedBicycleDetect[0]);
                printf("\n");
                a++;
            }
        }
        a = 0;
        if (ptr->id.id == 2 && a < 12)
        {
            int Signum = ptr->states.list.count;
            for (int k = 0; k <Signum; k++)
            {
                printf("\033[32mSPAT ID is %d \n\033[0m", ptr->id.id);
                int minute = ptr->moy[0];
                int sec = ptr->timeStamp[0];
                printf("Apr %d, %d:%d:%d   \n", (minute/60)/24-31-28-31+1,  (minute/(60*24)%24), minute%60, sec/1000); // April
                printf("\n");
                printf("Direction : %c%c%c \n", ptr->states.list.array[k]->movementName->buf[0],ptr->states.list.array[k]->movementName->buf[1],ptr->states.list.array[k]->movementName->buf[2]);
                printf("Signal ID : %d \n", ptr->states.list.array[k]->signalGroup);
                printf("State : %d \n", ptr->states.list.array[k]->state_time_speed.list.array[0]->eventState);
                int remain = ptr->states.list.array[k]->state_time_speed.list.array[0]->timing->minEndTime;
                printf("Remain Time : %dm%ds \n", (remain/10)/60, (remain/10)%60);
                printf("\n");
                printf("ConnectionID : %d \n", ptr->states.list.array[k]->maneuverAssistList->list.array[0]->connectionID);
                printf("Ped or Bic : %d \n", ptr->states.list.array[k]->maneuverAssistList->list.array[0]->pedBicycleDetect[0]);
                printf("\n");
                a++;
            }
            
        }
        a = 0;
        if (ptr->id.id == 3 && a < 12)
        {
            int Signum = ptr->states.list.count;
            for (int k = 0; k <Signum; k++)
            {
                printf("\033[34mSPAT ID is %d \n\033[0m", ptr->id.id);
                int minute = ptr->moy[0];
                int sec = ptr->timeStamp[0];
                printf("Apr %d, %d:%d:%d   \n", (minute/60)/24-31-28-31+1,  (minute/(60*24)%24), minute%60, sec/1000); // April
                printf("\n");
                printf("Direction : %c%c%c \n", ptr->states.list.array[k]->movementName->buf[0],ptr->states.list.array[k]->movementName->buf[1],ptr->states.list.array[k]->movementName->buf[2]);
                printf("Signal ID : %d \n", ptr->states.list.array[k]->signalGroup);
                printf("State : %d \n", ptr->states.list.array[k]->state_time_speed.list.array[0]->eventState);
                int remain = ptr->states.list.array[k]->state_time_speed.list.array[0]->timing->minEndTime;
                printf("Remain Time : %dm%ds \n", (remain/10)/60, (remain/10)%60);
                printf("\n");
                printf("ConnectionID : %d \n", ptr->states.list.array[k]->maneuverAssistList->list.array[0]->connectionID);
                printf("Ped or Bic : %d \n", ptr->states.list.array[k]->maneuverAssistList->list.array[0]->pedBicycleDetect[0]);
                printf("\n");
                a++;
            }
            
        }
    }

    return 0;
}

int parse_bsm(BasicSafetyMessage_t *bsm){
 
    // MISSION : BSM 내 temporary ID 추출
    //           차량의 위치(위도,경도,고도)와 주행 방향, 속도 출력


 
    return 0;
}


