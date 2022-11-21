#!/bin/bash

RED='\033[1;31m'
GR='\033[1;32m'
NC='\033[0m'

info() {
    if [[ "$OSTYPE" == "linux-gnu"* ]]; 
    then
        if [ "$(grep "0 errors from 0 contexts" leak.log)" == "" ]
        then
            echo -e "${RED}-------------------------------------------------${NC}"
            echo -e "${RED}FAIL${NC}: $(grep "ERROR SUMMARY" leak.log)"
            echo -e "${RED}-------------------------------------------------${NC}"
            
        else
            echo -e "${GR}-------------------------------------------------${NC}"
            echo -e "${GR}SUCCESS${NC}: $(grep "ERROR SUMMARY" leak.log)"
            echo -e "${GR}-------------------------------------------------${NC}"
        fi
    elif [[ "$OSTYPE" == "darwin"* ]]; 
    then 
        if [ "$(grep "0 leaks for 0 total leaked bytes" test.log)" == "" ]
        then
            echo -e "${RED}-------------------------------------------------${NC}"
            echo -e "${RED}FAIL${NC}: $(grep "ERROR SUMMARY" test.log)"
            echo -e "${RED}-------------------------------------------------${NC}"
            echo -e "$(grep -e FAIL -e "}" -e "---" test.log)"
            
        else
            echo -e "${GR}-------------------------------------------------${NC}"
            echo -e "${GR}SUCCESS${NC}: $(grep "ERROR SUMMARY" test.log)"
            echo -e "${GR}-------------------------------------------------${NC}"
        fi
    fi
}

info
